#include "test.h"
#include "ev3dev.h"
#include <iostream>

void Test::run() const {
  typedef std::string         mode_type;
  typedef std::set<mode_type> mode_set;
  typedef std::string         address_type;

  ev3dev::large_motor A(ev3dev::OUTPUT_A);

  A.run_forever();

}
