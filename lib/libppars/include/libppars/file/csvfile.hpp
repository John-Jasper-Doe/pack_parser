/**
 * @file csvfile.hpp
 * @brief Description of the class for working with a CSV file.
 *
 * @details
 * A simple class for opening and dumping information of a given format into a
 * CSV file.
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

#ifndef FILE_CSVFILE_HPP_
#define FILE_CSVFILE_HPP_

#include <fstream>
#include <functional>
#include <memory>

/** @brief The namespace of the "Packet Parse" library. */
namespace ppars {
/** @brief The namespace of the "File" */
namespace file {

/** @brief The csvfile class. */
class csvfile {
  using fstrm_t = std::unique_ptr<std::fstream, std::function<void(std::fstream*)>>;

  /** @brief Pointer of the csv-file. */
  fstrm_t fstrm_;

public:
  /** @brief Constructor by default. */
  csvfile() noexcept;

  /**
   * @brief Write into file.
   * @param [in] data - string of data.
   * @return "True" is all good, otherwise - "Falsse".
   */
  bool write(std::string&& data) noexcept;
};

} /* file:: */
} /* ppars:: */

#endif /* FILE_CSVFILE_HPP_ */
