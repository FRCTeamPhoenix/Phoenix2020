/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/I2C.h>
#include <frc/util/Color.h>

/**
 * The Constants header provides a convenient place for teams to hold robot-wide
 * numerical or boolean constants.  This should not be used for any other
 * purpose.
 *
 * It is generally a good idea to place constants into subsystem- or
 * command-specific namespaces within this header, which can then be used where
 * they are needed.
 */

// Deadzone
const double DEADZONE = 0.1;

// Joystick IDs
const int DRIVER_JOYSTICK = 0;
const int OPERATOR_JOYSTICK = 1;

// Talon IDs
// Note: Make the robot follow this id system using phoenix tuner
const int IMU_ID = 0;
const int TALON_FRONT_LEFT = 1;
const int TALON_FRONT_RIGHT = 2;
const int VICTOR_BACK_LEFT = 3;
const int VICTOR_BACK_RIGHT = 4;
const int TALON_FLYWHEEL_LEFT = 5;
const int TALON_FLYWHEEL_RIGHT = 6;
const int TALON_SHOOTER_TOP = 7;
const int TALON_LOADER_LEFT = 9;
const int TALON_LOADER_RIGHT = 10;
const int VICTOR_INTAKE = 11;
const int TALON_INTAKE_TILT = 12;

// Solenoid IDs
const int PCM_CAN_ID = 11;
const int SOLENOID_HIGH_GEAR = 6;
const int SOLENOID_LOW_GEAR = 7;
const int SOLENOID_INTAKE_TILT_UP = 0;
const int SOLENOID_INTAKE_TILT_DOWN = 1;

// Sensor ports
const int LOADER_SENSOR_PORT = 0;
const auto COLOR_SENSOR_PORT = frc::I2C::Port::kOnboard;
const frc::Color BLUE_TARGET = frc::Color(0.143, 0.427, 0.429);
const frc::Color GREEN_TARGET = frc::Color(0.197, 0.561, 0.240);
const frc::Color RED_TARGET = frc::Color(0.561, 0.232, 0.114);
const frc::Color YELLOW_TARGET = frc::Color(0.361, 0.524, 0.113);

// Slots for the two different pid configs on talons
const int PID_VELOCITY_SLOT = 0;
const int PID_HEADING_SLOT = 1;

//distance to move in auto
const int AUTO_DISTANCE = 4096 * 2;

//used for the aim adjust
const double AIM_P = 0.2;
const double AIM_DIST_P = 0.15;
const double AIM_THRESH = 0.4;
const double DIST_THRESH = 0.3;

//used for the turning maneuver
const double TURN_P = 0.02;
const double TURN_FF = 0.01;
const double TURN_THRESH = 10.0;
const double TURN_END_TRESH = 5;

//info about the target and camera for distance calculations
const double TARGET_HEIGHT_IN = 48.0;
const double CAMERA_HEIGHT_IN = 7.5;
const double CAMERA_ANGLE = 0.0;

//speeds for the shooter mechanism
const double FLYWHEEL_SPEED = 0.5;
const double LOADER_SPEED = 0.2;
const double SHOOTER_SPEED = 0.35;
const double INTAKE_SPEED = 0.8;

// Intake tilt upper and lower limits
const int INTAKE_TILT_UPPER_LIMIT = -350;
const int INTAKE_TILT_LOWER_LIMIT = -17500;

//conversion values
const double TICKS_PER_REV = 4096.0;
const double TICKS_PER_IMU_ROTATION = 8192.0;
const double WHEEL_DIMATER_IN = 6;
const double DRIVE_TRAIN_WIDTH_IN = 26;
const double PI = 3.1415;
const double ROTATIONS_TO_DISTANCE = WHEEL_DIMATER_IN * PI;
const double TICKS_TO_DISTANCE = ROTATIONS_TO_DISTANCE / TICKS_PER_REV;

//camera constants
const int CAMERA_FRONT = 0;
const int CAMERA_BACK = 1;
