#include <iostream>
#include <thread>

#include <libppars/core/ejector.hpp>
#include <libppars/common/countdata.hpp>
#include <libppars/common/time.hpp>

static constexpr std::chrono::seconds COUNT_SEC(30);

void test_ejector() {
  std::cout << "test_ejector (30 sec): " << std::flush;

  std::shared_ptr<ppars::common::count_data> data =
      std::shared_ptr<ppars::common::count_data>(new ppars::common::count_data());
  data->inc_to(ppars::common::pt_v9, 9);
  data->inc_to(ppars::common::pt_ipfix, 100);
  data->inc_to(ppars::common::pt_other, 20);
  data->set_source("127.0.0.1:2255");

  ppars::core::ejector ej(data);
  ej.exec();

  std::this_thread::sleep_for(COUNT_SEC);
  ppars::common::data_t dat = data->data();
  std::string str{ppars::common::timestamp() + "," + dat.src + "," + std::to_string(dat.v9) + "," +
        std::to_string(dat.ipfix) + "," + std::to_string(dat.other) + "\n"};
  std::cout << str << std::endl;
}
