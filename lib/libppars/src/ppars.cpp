/**
 * @file ppars.cpp
 * @brief Implementation of the "Parser" class.
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

#include <libppars/ppars.hpp>

#include <libppars/common/countdata.hpp>
#include <libppars/core/ejector.hpp>
#include <libppars/core/recipient.hpp>

/** @brief The namespace of the "Packet Parse" library. */
namespace ppars {

parser::parser(unsigned short port) noexcept
  : cntdat_{cntdat_ptr_t(new common::count_data())}
  , recipient_{recipient_ptr_t(new core::recipient(port, cntdat_))}
  , ejector_{ejector_ptr_t(new core::ejector(cntdat_))} {}

void parser::main_loop() noexcept {
  if (recipient_->open()) {
    recipient_->exec();
    ejector_->exec();

    for (;;) {
    }
  }
  else {
    return;
  }
}

} /* ppars:: */
