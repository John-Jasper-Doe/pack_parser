/**
 * @file ifile.hpp
 * @brief Intrface of the class for working with a file.
 *
 * @details
 * A simple interface class for opening and uploading information to a file.
 * You can inherit from it to create any type of file.
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

#ifndef FILE_IFILE_HPP_
#define FILE_IFILE_HPP_

#include <fstream>
#include <functional>
#include <memory>

/** @brief The namespace of the "Packet Parse" library. */
namespace ppars {

/* Forward declaration */
namespace common {
class count_data;
} /* common:: */

using cntdat_ptr_t = std::shared_ptr<common::count_data>;

/** @brief The namespace of the "File" */
namespace file {

class ifile;
using file_ptr_t = std::shared_ptr<file::ifile>;

/** @brief The ifile class. */
class ifile {
  using fstrm_t = std::unique_ptr<std::fstream, std::function<void(std::fstream*)>>;

  /** @brief Pointer of the csv-file. */
  fstrm_t fstrm_;

  /** @brief File existence flag. */
  bool is_exist_;

public:
  /** @brief Constructor by default. */
  explicit ifile(const char* fname) noexcept;

  /** @brief Virtual distructor by default. */
  virtual ~ifile() noexcept;

  /**
   * @brief Get the file existence flag.
   * @details
   * Checks if the file existed before opening. This is required to download the
   * file.
   */
  bool is_exist() const noexcept;

  /** @brief Check if the file is open. */
  bool is_open() const noexcept;

  /**
   * @brief Dumping data to a file.
   * @param [in] data - dumped data.
   */
  virtual void dumping(cntdat_ptr_t& data) noexcept = 0;

protected:
  /**
   * @brief Write into file.
   * @param [in] data - string of data.
   * @return "True" is all good, otherwise - "Falsse".
   */
  bool write(std::string&& data) noexcept;
};

} /* file:: */
} /* ppars:: */

#endif /* FILE_IFILE_HPP_ */
