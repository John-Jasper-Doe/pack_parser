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

#include <libppars/file/ifile.hpp>

/** @brief The namespace of the "Packet Parse" library. */
namespace ppars {
/** @brief The namespace of the "File" */
namespace file {

/** @brief The csvfile class. */
class csvfile : public ifile {
public:
  /** @brief Constructor by default. */
  csvfile() noexcept;

  virtual ~csvfile() noexcept override;
  /**
   * @brief Dumping data to a file.
   * @param [in] data - dumped data.
   */
  virtual void dumping(cntdat_ptr_t& data) noexcept override;
};

} /* file:: */
} /* ppars:: */

#endif /* FILE_CSVFILE_HPP_ */
