/**
 * @file countdata.hpp
 * @brief Description of the data structure.
 *
 * @details
 * Description of the data structure used in the project for traffic counting.
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

#ifndef COMMON_COUNTDATA_HPP_
#define COMMON_COUNTDATA_HPP_

#include <atomic>
#include <mutex>
#include <string>

/** @brief The namespace of the "Packet Parse" library. */
namespace ppars {
/** @brief The namespace of the "Common" */
namespace common {

typedef enum { pt_v9, pt_ipfix, pt_other } pack_type_t;

/** @brief The count_data struct */
class count_data {
  /** @brief Packet counter with data version V9. */
  std::atomic_ulong v9_{0};
  /** @brief Packet counter with data version IPFIX. */
  std::atomic_ulong ipfix_{0};
  /** @brief Source IP address and port number. */
  std::atomic_ulong other_{0};
  /** @brief Packet counter V9. */
  std::string src_{""};

  std::mutex mtx_;

public:
  count_data() noexcept {}

  void append_to(pack_type_t pt, unsigned long val) noexcept {
    switch (pt) {
    case pt_v9: {
      std::lock_guard<std::mutex> lock(mtx_);
      v9_ += val;
      break;
    }

    case pt_ipfix: {
      std::lock_guard<std::mutex> lock(mtx_);
      ipfix_ += val;
      break;
    }

    case pt_other: {
      std::lock_guard<std::mutex> lock(mtx_);
      other_ += val;
      break;
    }
    }
  }

  void set_source(std::string&& val) noexcept {
    std::lock_guard<std::mutex> lock(mtx_);
    src_ = std::move(val);
  }

  std::string as_str() noexcept {
    std::string str{src_ + "," + std::to_string(v9_) + "," + std::to_string(ipfix_) + ","
                    + std::to_string(other_)};
    return str;
  }

  /** @brief Cleaning counters. */
  void counts_clear() noexcept {
    std::lock_guard<std::mutex> lock(mtx_);
    v9_ = 0;
    ipfix_ = 0;
    other_ = 0;
  }
};

} /* common:: */
} /* ppars:: */

#endif /* COMMON_COUNTDATA_HPP_ */
