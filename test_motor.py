#!/usr/bin/env python3
from ev3dev.motor import LargeMotor, OUTPUT_A, OUTPUT_D, SpeedPercent, MoveTank
from ev3dev.sensor import INPUT_1
from ev3dev.sensor.lego import TouchSensor
from ev3dev.led import Leds


tank_drive = MoveTank(OUTPUT_A, OUTPUT_D)

# drive in a turn for 5 rotations of the outer motor
# the first two parameters can be unit classes or percentages.
tank_drive.on_for_rotations(SpeedPercent(50), SpeedPercent(75), 10)

# drive in a different turn for 3 seconds
tank_drive.on_for_seconds(SpeedPercent(60), SpeedPercent(30), 3)