/**
 * @file ejector.hpp
 * @brief Implementation of the class for dumping data.
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

#include <chrono>
#include <thread>

#include <libppars/core/ejector.hpp>

#include <libppars/common/countdata.hpp>
#include <libppars/file/csvfile.hpp>
#include <libppars/file/factory.hpp>

/** @brief The namespace of the "Packet Parse" library. */
namespace ppars {
/** @brief The namespace of the "Core" */
namespace core {

namespace {
static constexpr std::chrono::seconds PERIOD(20);
} /* :: */

ejector::ejector(cntdat_ptr_t cntdat) noexcept
  : csv_{file::factory::instance().creator(file::file_type::ft_csv)}
  , cntdat_{std::move(cntdat)}
  , stopped_{false} {}

ejector::ejector() noexcept
  : csv_{file::factory::instance().creator(file::file_type::ft_csv)}
  , cntdat_{cntdat_ptr_t(new common::count_data())}
  , stopped_{false} {}

ejector::~ejector() noexcept {
  stopped_ = true;
}

void ejector::exec() {
  try {
    auto wrk = [this]() {
      while (!stopped_) {
        std::this_thread::sleep_for(PERIOD);
        csv_->dumping(cntdat_);
      }
    };

    worker_ = thread_ptr_t(new std::thread(wrk), [](std::thread* t) { t->join(); });
  }
  catch (std::bad_alloc&) {
  }
}

} /* core:: */
} /* ppars:: */
