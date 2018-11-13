/*
 * Copyright (c) 2014 - Franz Detro
 *
 * Some real world test program for motor control
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "ev3dev.h"

#include <thread>
#include <chrono>
#include <iostream>
#include <fstream>

#ifndef NO_LINUX_HEADERS
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#define KEY_RELEASE 0
#define KEY_PRESS   1
#define KEY_REPEAT  2
#endif

using namespace std;
using namespace ev3dev;

class control
{
public:
  control();
  ~control();

  void drive(int speed, int time=0);
  void turn(int direction);
  void stop();
  void reset();

  bool initialized() const;


  void drive_autonomously();

  void terminate() { _terminate = true; }

protected:
  large_motor     _motor_left;


  enum state
  {
    state_idle,
    state_driving,
    state_turning
  };

  state _state;
  bool  _terminate;
};

control::control() :
  _motor_left(OUTPUT_A),

  _state(state_idle),
  _terminate(false)
{
}

control::~control()
{
  reset();
}

void control::drive(int speed, int time)
{
  _motor_left.set_speed_sp(-speed);



  _state = state_driving;

  if (time > 0)
  {
    _motor_left .set_time_sp(time).run_timed();

    while (_motor_left.state().count("running") )
      this_thread::sleep_for(chrono::milliseconds(10));

    _state = state_idle;
  }
  else
  {
    _motor_left.run_forever();

  }
}

void control::turn(int direction)
{
  if (_state != state_idle)
    stop();

  if (direction == 0)
    return;

  _state = state_turning;

  _motor_left. set_position_sp( direction).set_speed_sp(500).run_to_rel_pos();


  while (_motor_left.state().count("running") )
    this_thread::sleep_for(chrono::milliseconds(10));

  _state = state_idle;
}

void control::stop()
{
  _motor_left .stop();


  _state = state_idle;
}

void control::reset()
{
  if (_motor_left.connected())
    _motor_left.reset();

  _state = state_idle;
}

bool control::initialized() const
{
  return (_motor_left .connected() );
}






void control::drive_autonomously()
{

  while (!_terminate)
  {

      if (_state != state_driving){}
        drive(750);
      this_thread::sleep_for(chrono::milliseconds(10));
  }

  

}

int main()
{
  control c;

  if (c.initialized())
  {

    int mode = 2;
    if (mode == 2)
    {


      c.drive_autonomously();
    }
  }
  else
  {
    cout << "you need to connect an infrared sensor and large motors to ports B and C!" << endl;
    return 0;
  }

  return 0;
}
