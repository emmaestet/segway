#include "test.h"
#include "ev3dev.h"
#include <iostream>

void Test::run() const {
  typedef std::string         mode_type;
  typedef std::set<mode_type> mode_set;
  typedef std::string         address_type;

  ev3dev::large_motor B;
    B.run_forever();
  /*function_motor(, 1000, 15, "run-timed");
  B.run_forever();*/
}
