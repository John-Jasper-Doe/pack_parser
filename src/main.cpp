#include <iostream>

#include <libppars/ppars.hpp>

int main(/*int argc, const char* argv[]*/) {
  ppars::parser prs(9995);
  prs.main_loop();

  return EXIT_SUCCESS;
}
