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

#include <libppars/file/csvfile.hpp>

/* Forward declaration  for std */
namespace std {
class thread;
} /* std */

/** @brief The namespace of the "Packet Parse" library. */
namespace ppars {

/* Forward declaration */
namespace file {
class csvfile;
} /* file:: */

namespace common {
class count_data;
} /* common:: */

/** @brief The namespace of the "Core" */
namespace core {

/** @brief The ejector class. */
class ejector {
  using thread_ptr_t = std::unique_ptr<std::thread, std::function<void(std::thread*)>>;
  using csvfile_ptr_t = std::unique_ptr<file::csvfile>;
  using cntdat_ptr_t = std::shared_ptr<common::count_data>;

  csvfile_ptr_t csv_;
  thread_ptr_t worker_;
  cntdat_ptr_t cntdat_;

  bool stopped_;

public:
  /** @brief Constructor with param. */
  explicit ejector(cntdat_ptr_t cntdat) noexcept;
  ~ejector() noexcept;

  void exec();

protected:
  ejector() noexcept;
  void worker();
};

} /* core:: */
} /* ppars:: */

#endif /* CORE_EJECTOR_HPP_ */
