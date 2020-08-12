/**
 * @file ppars.hpp
 * @brief Discription of the "Parser" class.
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

#ifndef PPARS_HPP_
#define PPARS_HPP_

#include <memory>

#include <libppars/core/ejector.hpp>
#include <libppars/core/recipient.hpp>

/** @brief The namespace of the "Packet Parse" library. */
namespace ppars {

class parser {
  using recipient_ptr_t = std::unique_ptr<core::recipient>;
  using ejector_ptr_t = std::unique_ptr<core::ejector>;
  using cntdat_ptr_t = std::shared_ptr<common::count_data>;

  cntdat_ptr_t cntdat_;
  recipient_ptr_t recipient_;
  ejector_ptr_t ejector_;

public:
  /** @brief Constructor with params. */
  explicit parser(unsigned short port) noexcept;

  /** @brief Start all tasks and wait for completion. */
  void main_loop() noexcept;
};

} /* ppars:: */

#endif /* PPARS_HPP_ */
