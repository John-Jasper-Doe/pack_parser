
#ifndef FILE_CSVFILE_HPP_
#define FILE_CSVFILE_HPP_

#include <fstream>
#include <functional>
#include <memory>

namespace ppars {
namespace file {

class csvfile {
  using fstrm_t = std::unique_ptr<std::fstream, std::function<void(std::fstream*)>>;

  fstrm_t fstrm_;

public:
  csvfile() noexcept;

  bool is_open() noexcept;
  bool write() noexcept;
};

} /* file:: */
} /* ppars:: */

#endif /* FILE_CSVFILE_HPP_ */
