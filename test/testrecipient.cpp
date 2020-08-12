#include <iostream>
#include <thread>

#include <libppars/core/recipient.hpp>
#include <libppars/common/countdata.hpp>
#include <libppars/common/time.hpp>

static constexpr std::chrono::seconds COUNT_SEC(60);

void test_recipient() {
  std::cout << "test_recipient (60 sec): " << std::flush;

  std::shared_ptr<ppars::common::count_data> data =
      std::shared_ptr<ppars::common::count_data>(new ppars::common::count_data());
  ppars::core::recipient rec(9995, data);
  if (rec.open()) {
    rec.exec();
    std::this_thread::sleep_for(COUNT_SEC);
  }
  else {
    std::cout << "error" << std::endl;
    return;
  }

  ppars::common::data_t dat = data->data();
  std::string str{ppars::common::timestamp() + "," + dat.src + "," + std::to_string(dat.v9) + "," +
        std::to_string(dat.ipfix) + "," + std::to_string(dat.other) + "\n"};
  std::cout << str << std::endl;
}
