/**
 * @file time.hpp
 * @brief Implementation of functions for using timestamp.
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

#ifndef COMMON_TIME_HPP_
#define COMMON_TIME_HPP_

#include <chrono>
#include <ctime>
#include <string>

/** @brief The namespace of the "Packet Parse" library. */
namespace ppars {
/** @brief The namespace of the "Common" */
namespace common {

/**
 * @brief Get time now.
 * @return Timestamp in a custom data structure.
 */
inline tm time_now() noexcept {
  auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  return *std::localtime(&t);
}

/**
 * @brief Format time.
 * @param [in] st_tm - tm struct.
 * @param [in] str_fmt - string format of time.
 * @return Time on string of request format.
 */
inline std::string fmt_time(const tm& st_tm, const std::string& str_fmt) noexcept {
  char str[100];
  std::strftime(str, sizeof(str), str_fmt.data(), &st_tm);
  return std::string(str);
}

/**
 * @brief Timestamp
 * @param [in] str_fmt - string format of time.
 * @return Time on string of request format.
 */
inline std::string timestamp(const std::string& str_fmt = "%Y_%m_%d-%H:%M:%S") noexcept {
  return fmt_time(time_now(), str_fmt);
}

} /* common:: */
} /* ppars:: */

#endif /* COMMON_TIME_HPP_ */
