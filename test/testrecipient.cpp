
#define NDEBUG
#include <cassert>
#include <iostream>
#include <thread>

#include <libppars/core/recipient.hpp>
#include <libppars/common/countdata.hpp>

static constexpr std::chrono::seconds COUNT_SEC(60);

void test_recipient() {
  std::cout << "test_recipient (60 sec): " << std::flush;

  std::shared_ptr<ppars::common::count_data> dat =
      std::shared_ptr<ppars::common::count_data>(new ppars::common::count_data());
  ppars::core::recipient rec(9995, dat);
  if (rec.open()) {
    rec.exec();
    std::this_thread::sleep_for(COUNT_SEC);
  }
  else {
    std::cout << "error" << std::endl;
    return;
  }

  std::cout << dat->as_str() << std::endl;
}
