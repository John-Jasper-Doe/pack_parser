/**
 * @file csvfile.cpp
 * @brief Description of the class for working with a CSV file.
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

#include <libppars/file/csvfile.hpp>

#include <libppars/common/countdata.hpp>
#include <libppars/common/time.hpp>

/** @brief The namespace of the "Packet Parse" library. */
namespace ppars {
/** @brief The namespace of the "File" */
namespace file {

namespace {

/** @brief CSV-file name. */
static const char* CSV_FILE_NAME = "collected_data.csv";

} /* :: */

csvfile::csvfile() noexcept : ifile(CSV_FILE_NAME) {
  if (!is_exist())
    write("DATE_TIME,SOURCE,V9,IPFIX,other\n");
}

csvfile::~csvfile() noexcept {}

void csvfile::dumping(cntdat_ptr_t& data) noexcept {
  common::data_t dat = data->data();
  std::string str{common::timestamp() + "," + dat.src + "," + std::to_string(dat.v9) + ","
                  + std::to_string(dat.ipfix) + "," + std::to_string(dat.other) + "\n"};
  write(std::move(str));
}

} /* file:: */
} /* ppars:: */
