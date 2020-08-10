/**
 * @file recipient.hpp
 * @brief Description of the "Recipient" class.
 *
 * @details
 * The class describes the work of the "Recipient" of data from the network
 * using the UDP protocol and the specified port.
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

#ifndef CORE_RECIPIENT_HPP_
#define CORE_RECIPIENT_HPP_

#if defined(__WIN32__) || defined(_WIN32)
#include <WinSock2.h>

typedef SOCKET socktype_t;
typedef int socklen_t;

#else
typedef int socktype_t;
#endif /* defined(__WIN32__) || defined(_WIN32) */

#include <functional>
#include <memory>

/* Forward declaration  for std */
namespace std {
class thread;
} /* std */

/** @brief The namespace of the "Packet Parse" library. */
namespace ppars {

/* Forward declaration */
namespace common {
class count_data;
} /* common:: */

/** @brief The namespace of the "Core" */
namespace core {

typedef enum { from_pack, from_read } pack_size_t;

/** @brief The ejector class. */
class recipient {
  using thread_ptr_t = std::unique_ptr<std::thread, std::function<void(std::thread*)>>;
  using cntdat_ptr_t = std::shared_ptr<common::count_data>;

  socktype_t sock_;

  thread_ptr_t worker_;
  cntdat_ptr_t cntdat_;

  unsigned short port_;
  bool stopped_;
  bool openned_;

  pack_size_t pack_size_;

public:
  /** @brief Constructor with param. */
  explicit recipient(unsigned short port, cntdat_ptr_t cntdat, pack_size_t ps = from_pack) noexcept;
  ~recipient() noexcept;

  bool open() noexcept;
  void exec();

protected:
  recipient() noexcept;
  void worker();
};

} /* core:: */
} /* ppars:: */

#endif /* CORE_RECIPIENT_HPP_ */
