
#define NDEBUG
#include <cassert>
#include <iostream>
#include <thread>

#include <libppars/core/ejector.hpp>
#include <libppars/common/countdata.hpp>

static constexpr std::chrono::seconds COUNT_SEC(30);

void test_ejector() {
  std::cout << "test_ejector (30 sec): " << std::flush;

  std::shared_ptr<ppars::common::count_data> dat =
      std::shared_ptr<ppars::common::count_data>(new ppars::common::count_data());
  dat->append_to(ppars::common::pt_v9, 9);
  dat->append_to(ppars::common::pt_ipfix, 100);
  dat->append_to(ppars::common::pt_other, 20);
  dat->set_source("127.0.0.1:2255");

  ppars::core::ejector ej(dat);
  ej.exec();

  std::this_thread::sleep_for(COUNT_SEC);
  std::cout << dat->as_str() << std::endl;
}
