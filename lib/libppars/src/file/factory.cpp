/**
 * @file factory.cpp
 * @brief Defining a class "Factory".
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

#include <libppars/file/factory.hpp>

#include <libppars/file/csvfile.hpp>

/** @brief The namespace of the "Packet Parse" library. */
namespace ppars {
/** @brief The namespace of the "File" */
namespace file {

factory::factory() noexcept {}

factory& factory::instance() noexcept {
  static factory sfact;
  return sfact;
}

std::shared_ptr<ifile> factory::creator(file_type_t type) {
  switch (type) {
  case file_type::ft_csv:
    return std::shared_ptr<file::csvfile>(new file::csvfile());
  }
  return nullptr;
}

} /* file:: */
} /* ppars:: */
