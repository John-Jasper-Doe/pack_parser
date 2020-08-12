/**
 * @file ifile.cpp
 * @brief Intrface of the class for working with a file.
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

#include <libppars/file/ifile.hpp>

/** @brief The namespace of the "Packet Parse" library. */
namespace ppars {
/** @brief The namespace of the "File" */
namespace file {

namespace {

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

ifile::ifile(const char* fname) noexcept {
  is_exist_ = is_file_exist(fname);

  fstrm_ = fstrm_t(new std::fstream(), [](std::fstream* fs) { fs->close(); });

  fstrm_->exceptions(std::fstream::failbit | std::fstream::badbit);
  fstrm_->open(fname, std::ios::out | std::ios::app);
  fstrm_->unsetf(std::ios::skipws);
}

ifile::~ifile() noexcept {}

bool ifile::is_exist() const noexcept {
  return is_exist_;
}

bool ifile::is_open() const noexcept {
  return fstrm_->is_open();
}

bool ifile::write(std::string&& data) noexcept {
  if (is_open()) {
    (*fstrm_) << data;
    fstrm_->flush();
    return true;
  }

  return false;
}

} /* file:: */
} /* ppars:: */
