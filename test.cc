#include "test.h"
#include "ev3dev.h"

void Test::run() const {

  ev3dev::large_motor A(ev3dev::OUTPUT_A);
  A.connected();
  A.set_speed_sp(A.max_speed());
  A.run_forever();

}
