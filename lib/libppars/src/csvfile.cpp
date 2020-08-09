
#include <libppars/file/csvfile.hpp>

namespace ppars {
namespace file {

namespace {

static const char* CSV_FILE_NAME = "collected_data.csv";

} /* :: */

csvfile::csvfile() noexcept {
  fstrm_ = fstrm_t(new std::fstream(), [](std::fstream* fs) { fs->close(); });

  fstrm_->exceptions(std::fstream::failbit | std::fstream::badbit);
  fstrm_->open(CSV_FILE_NAME, std::ios::out | std::ios::app);
  fstrm_->unsetf(std::ios::skipws);

  *fstrm_ << "DATE_TIME, SOURCE, V9, IPFIX, other\n";
}

bool csvfile::is_open() noexcept {
  return fstrm_->is_open();
}

bool csvfile::write() noexcept {
  return true;
}

} /* file:: */
} /* ppars:: */

