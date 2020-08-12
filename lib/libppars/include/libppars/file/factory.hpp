/**
 * @file factory.hpp
 * @brief Defining a class "Factory".
 *
 * @details
 * This class implements the Factory pattern. If in the future there are
 * several types of files for displaying information.
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

#ifndef FILE_FACTORY_HPP_
#define FILE_FACTORY_HPP_

#include <memory>

/** @brief The namespace of the "Packet Parse" library. */
namespace ppars {
/** @brief The namespace of the "File" */
namespace file {

/* Forward declaration */
class ifile;

/** @brief The types of files that can be created. */
enum class file_type { ft_csv };
using file_type_t = file_type;

/** @brief The factory class. */
class factory {
public:
  /** @brief Get instance. */
  static factory& instance() noexcept;

  /**
   * @brief Create a file object of the specified type.
   * @param [in] type - file types.
   * @return File object.
   */
  std::shared_ptr<ifile> creator(file_type_t type);

protected:
  factory() noexcept;
};

} /* file:: */
} /* ppars:: */

#endif /* FILE_FACTORY_HPP_ */
