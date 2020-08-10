
#define NDEBUG
#include <cassert>
#include <iostream>

#include <libppars/file/csvfile.hpp>

void test_csv() {
  std::cout << "test_csv" << std::endl;

  ppars::file::csvfile csv;

  ppars::common::count_data dat;
  dat.v9 = 9;
  dat.ipfix = 100;
  dat.other = 20;
  dat.src = "127.0.0.1:2255";

  csv.write(dat);
  assert(true);
}
