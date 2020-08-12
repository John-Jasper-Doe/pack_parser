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

namespace details {
typedef struct {
  /** @brief Packet counter with data version V9. */
  unsigned long v9{0};
  /** @brief Packet counter with data version IPFIX. */
  unsigned long ipfix{0};
  /** @brief Source IP address and port number. */
  unsigned long other{0};
  /** @brief Packet counter V9. */
  std::string src{""};
} data_t;

} /* details */

typedef enum { pt_v9, pt_ipfix, pt_other } pack_type_t;
typedef details::data_t data_t;

/** @brief The count_data struct */
class count_data {
  details::data_t data_;

  std::mutex mtx_;

public:
  count_data() noexcept {}

  void append_to(pack_type_t pt, unsigned long val) noexcept {
    switch (pt) {
    case pt_v9: {
      std::lock_guard<std::mutex> lock(mtx_);
      data_.v9 += val;
      break;
    }

    case pt_ipfix: {
      std::lock_guard<std::mutex> lock(mtx_);
      data_.ipfix += val;
      break;
    }

    case pt_other: {
      std::lock_guard<std::mutex> lock(mtx_);
      data_.other += val;
      break;
    }
    }
  }

  void set_source(std::string&& val) noexcept {
    std::lock_guard<std::mutex> lock(mtx_);
    data_.src = std::move(val);
  }

  data_t data() noexcept {
    std::lock_guard<std::mutex> lock(mtx_);
    data_t dat = data_;
    counts_clear();
    return dat;
  }

protected:
  /** @brief Cleaning counters. */
  void counts_clear() noexcept {
    data_.v9 = 0;
    data_.ipfix = 0;
    data_.other = 0;
  }
};

} /* common:: */
} /* ppars:: */

#endif /* COMMON_COUNTDATA_HPP_ */
