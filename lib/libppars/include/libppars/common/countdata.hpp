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
#include <string>

/** @brief The namespace of the "Packet Parse" library. */
namespace ppars {
/** @brief The namespace of the "Common" */
namespace common {

/** @brief The count_data struct */
struct count_data {
  /** @brief Packet counter with data version V9. */
  std::atomic_ulong v9{0};
  /** @brief Packet counter with data version IPFIX. */
  std::atomic_ulong ipfix{0};
  /** @brief Source IP address and port number. */
  std::atomic_ulong other{0};
  /** @brief Packet counter V9. */
  std::string src{""};

  /** @brief Cleaning counters. */
  void counts_clear() noexcept {
    v9 = 0;
    ipfix = 0;
    other = 0;
  }
};

} /* common:: */
} /* ppars:: */

#endif /* COMMON_COUNTDATA_HPP_ */
