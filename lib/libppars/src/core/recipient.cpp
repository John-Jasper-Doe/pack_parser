/**
 * @file recipient.cpp
 * @brief Implementation of the "Recipient" class.
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

#ifdef linux
#include <arpa/inet.h>
#include <sys/socket.h>

#define SOCKET_ERROR -1
#endif /* linux */

#include <array>
#include <thread>

#include <libppars/common/countdata.hpp>
#include <libppars/core/recipient.hpp>

/** @brief The namespace of the "Packet Parse" library. */
namespace ppars {
/** @brief The namespace of the "Core" */
namespace core {

namespace {

#if defined(__WIN32__) || defined(_WIN32)
typedef int addr_size_t;

void init_sockets() {
  WSADATA wsaData;
  WSAStartup(MAKEWORD(2, 2), &wsaData);
}
#else
typedef unsigned int addr_size_t;

void init_sockets() {}
#endif /* defined(__WIN32__) || defined(_WIN32) */

bool is_littleendian() {
  const int current_byte_order = (*reinterpret_cast<const int*>("\x01\x02\x03\x04"));
  return (current_byte_order == 0x04030201);
}

bool is_bigendian() {
  const int current_byte_order = (*reinterpret_cast<const int*>("\x01\x02\x03\x04"));
  return (current_byte_order == 0x01020304);
}

unsigned short byte_order(unsigned short value) {
  unsigned char res[] = {0, 0};

  if (is_littleendian()) {
    res[0] = (reinterpret_cast<unsigned char*>(&value))[1];
    res[1] = (reinterpret_cast<unsigned char*>(&value))[0];
  }
  else if (is_bigendian()) {
    res[0] = (reinterpret_cast<unsigned char*>(&value))[0];
    res[1] = (reinterpret_cast<unsigned char*>(&value))[1];
  }
  else {
    throw "Undefined byte order";
  }

  return *reinterpret_cast<unsigned short*>(res);
}

common::counter_type_t pack_type(unsigned short pack_id) {
  switch (pack_id) {
  case 0x0009:
    return common::pt_v9;

  case 0x000a:
    return common::pt_ipfix;

  default:
    return common::pt_other;
  }
}

} /* :: */

recipient::recipient(unsigned short port, cntdat_ptr_t cntdat, pack_size_t ps) noexcept
  : cntdat_{std::move(cntdat)}, port_(port), stopped_{false}, openned_{false}, pack_size_(ps) {}

recipient::recipient() noexcept
  : cntdat_{cntdat_ptr_t(new common::count_data())}
  , port_(11011)
  , stopped_{false}
  , openned_{false}
  , pack_size_(from_pack) {}

recipient::~recipient() noexcept {
  stopped_ = true;
}

bool recipient::open() noexcept {
  if (!openned_) {
    init_sockets();

    sock_ = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock_ != SOCKET_ERROR) {
      sockaddr_in local_addr;
      local_addr.sin_family = AF_INET;
      local_addr.sin_addr.s_addr = INADDR_ANY;
      local_addr.sin_port = htons(port_);

      if (bind(sock_, reinterpret_cast<sockaddr*>(&local_addr), sizeof(local_addr))) {
        return (openned_ = false);
      }
    }
    else
      return (openned_ = false);
  }
  return (openned_ = true);
}

void recipient::exec() {
  if (openned_) {
    try {
      worker_ = thread_ptr_t(new std::thread(&recipient::worker, this),
                             [](std::thread* t) { t->join(); });
    }
    catch (std::bad_alloc& e) {
      throw std::runtime_error(e.what());
    }
  }
  else
    throw "The socket is not open";
}

void recipient::worker() {
  std::array<char, 2048> buff;

  while (!stopped_) {
    sockaddr_in server_addr;
    addr_size_t server_addr_size = sizeof(server_addr);
    int n = recvfrom(sock_, &buff[0], buff.size(), 0, reinterpret_cast<sockaddr*>(&server_addr),
                     &server_addr_size);

    try {
      std::string src{std::string(inet_ntoa(server_addr.sin_addr)) + ":"
                      + std::to_string(ntohs(server_addr.sin_port))};
      common::counter_type_t pt =
          pack_type(byte_order(*(reinterpret_cast<unsigned short*>(&buff[0]))));
      unsigned short sz = (pack_size_ == from_pack)
          ? byte_order(*(reinterpret_cast<unsigned short*>(&buff[2])))
          : static_cast<unsigned short>(n);
      cntdat_->inc_to(pt, sz);
      cntdat_->set_source(std::move(src));
    }
    catch (std::runtime_error&) {
    }
  }
}

} /* core:: */
} /* ppars:: */
