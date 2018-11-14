#include "test.h"
#include "ev3dev.h"

int Test::run() const {

  ev3dev::large_motor A(ev3dev::OUTPUT_A);

  if(A.connected()){
    A.set_command("running");
    A.set_speed_sp(A.max_speed());
    A.run_forever();
    return 0;
  } else {
    return -1;
  }


}
