/**
 * @file ejector.hpp
 * @brief Implementation of the class for dumping data.
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

#include <chrono>
#include <thread>

#include <libppars/common/countdata.hpp>
#include <libppars/core/ejector.hpp>
#include <libppars/file/csvfile.hpp>

/** @brief The namespace of the "Packet Parse" library. */
namespace ppars {
/** @brief The namespace of the "Core" */
namespace core {

namespace {
static constexpr std::chrono::seconds PERIOD(5);
} /* :: */

ejector::ejector(cntdat_ptr_t cntdat) noexcept : cntdat_{cntdat}, stopped_{false} {}

ejector::ejector() noexcept : cntdat_{cntdat_ptr_t(new common::count_data())}, stopped_{false} {}

ejector::~ejector() noexcept {
  stopped_ = true;
}

void ejector::exec() {
  try {
    csv_ = csvfile_ptr_t(new file::csvfile());
    worker_ =
        thread_ptr_t(new std::thread(&ejector::worker, this), [](std::thread* t) { t->join(); });
  }
  catch (std::bad_alloc&) {
  }
}

void ejector::worker() {
  while (!stopped_) {
    std::this_thread::sleep_for(PERIOD);
    csv_->write(cntdat_->as_str());
  }
}

} /* core:: */
} /* ppars:: */
