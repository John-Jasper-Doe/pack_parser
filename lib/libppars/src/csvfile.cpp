/**
 * @file csvfile.cpp
 * @brief Description of the class for working with a CSV file.
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

#include <libppars/common/time.hpp>
#include <libppars/file/csvfile.hpp>

/** @brief The namespace of the "Packet Parse" library. */
namespace ppars {
/** @brief The namespace of the "File" */
namespace file {

namespace {

/** @brief CSV-file name. */
static const char* CSV_FILE_NAME = "collected_data.csv";

/**
 * @brief Checking the existence of the specified file.
 * @param [in] fname - file name
 * @return "True" is file exist, otherwise - "False".
 */
bool is_file_exist(const char* fname) {
  std::fstream f_test(fname);
  return f_test.good();
}

} /* :: */

csvfile::csvfile() noexcept {
  bool is_exist = is_file_exist(CSV_FILE_NAME);

  fstrm_ = fstrm_t(new std::fstream(), [](std::fstream* fs) { fs->close(); });

  fstrm_->exceptions(std::fstream::failbit | std::fstream::badbit);
  fstrm_->open(CSV_FILE_NAME, std::ios::out | std::ios::app);
  fstrm_->unsetf(std::ios::skipws);

  if (!is_exist)
    *fstrm_ << "DATE_TIME, SOURCE, V9, IPFIX, other\n";
}

bool csvfile::write(common::count_data& data) noexcept {
  if (fstrm_->is_open()) {
    *fstrm_ << common::timestamp() << "," << data.src << "," << data.v9 << "," << data.ipfix << ","
            << data.other << "\n";
    return true;
  }
  return false;
}

} /* file:: */
} /* ppars:: */
