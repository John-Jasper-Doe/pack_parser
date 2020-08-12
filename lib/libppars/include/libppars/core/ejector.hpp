/**
 * @file ejector.hpp
 * @brief Description of the class for dumping data.
 *
 * @details
 * The class describes the work of dumping data into the storage after a given
 * period of time.
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

#ifndef CORE_EJECTOR_HPP_
#define CORE_EJECTOR_HPP_

#include <functional>
#include <memory>

#include <libppars/file/ifile.hpp>

/* Forward declaration  for std */
namespace std {
class thread;
} /* std */

/** @brief The namespace of the "Packet Parse" library. */
namespace ppars {

/** @brief The namespace of the "Core" */
namespace core {

/** @brief The ejector class. */
class ejector {
  using thread_ptr_t = std::unique_ptr<std::thread, std::function<void(std::thread*)>>;

  file::file_ptr_t csv_;
  thread_ptr_t worker_;
  cntdat_ptr_t cntdat_;

  bool stopped_;

public:
  /**
   * @brief Constructor with param.
   * @param [in] cntdat - pointer on data.
   */
  explicit ejector(cntdat_ptr_t cntdat) noexcept;
  ~ejector() noexcept;

  /** @brief Run for execution. */
  void exec();

protected:
  ejector() noexcept;
};

} /* core:: */
} /* ppars:: */

#endif /* CORE_EJECTOR_HPP_ */
