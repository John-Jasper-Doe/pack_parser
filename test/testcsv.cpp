#include <iostream>

#include <libppars/file/csvfile.hpp>
#include <libppars/common/countdata.hpp>

void test_csv() {
  std::cout << "test_csv" << std::endl;

  ppars::file::csvfile csv;

  std::shared_ptr<ppars::common::count_data> dat =
      std::shared_ptr<ppars::common::count_data>(new ppars::common::count_data());
  dat->append_to(ppars::common::pt_v9, 9);
  dat->append_to(ppars::common::pt_ipfix, 100);
  dat->append_to(ppars::common::pt_other, 20);
  dat->set_source("127.0.0.1:2255");

  csv.dumping(dat);
}
