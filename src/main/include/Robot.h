/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2019 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/TimedRobot.h>
#include <frc2/command/Command.h>
#include <frc/Joystick.h>
#include <frc2/command/SequentialCommandGroup.h>
#include <frc/Timer.h>
#include <frc2/command/InstantCommand.h>
#include <frc2/command/FunctionalCommand.h>

#include "commands/MotionMagic.h"
#include "commands/Turn.h"
#include "commands/DefaultDrive.h"
#include "commands/AimAdjust.h"
#include "commands/DefaultOperate.h"

#include "ColorSensor.h"

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestInit() override;
  void TestPeriodic() override;

private:
  DefaultDrive m_defaultDrive;
  DefaultOperate m_defaultOperate;
  frc::Joystick m_driverJoystick{DRIVER_JOYSTICK};
  AimAdjust m_nonAutoAim{false};
  
  frc2::FunctionalCommand m_moveForward{
    [this]{TankSubsystem::getInstance()->setSpeed(0.0, 0.0);
    TankSubsystem::getInstance()->zeroEncoders();},
    [this]{TankSubsystem::getInstance()->setSpeed(0.5, 0.5); Shooter::getInstance()->setFlywheelSpeed(FLYWHEEL_SPEED); Shooter::getInstance()->setShooterSpeed(0.0); 
  Shooter::getInstance()->setLoaderSpeed(0.0);},
    [this](bool interrupted){TankSubsystem::getInstance()->setSpeed(0.0, 0.0);},
    [this]{return TankSubsystem::getInstance()->getFrontRight()->GetSelectedSensorPosition(0) > AUTO_DISTANCE;},
    {TankSubsystem::getInstance()},
  };

  frc2::FunctionalCommand m_moveBackward{
    [this]{TankSubsystem::getInstance()->setSpeed(0.0, 0.0);
    TankSubsystem::getInstance()->zeroEncoders();},
    [this]{TankSubsystem::getInstance()->setSpeed(-0.5, -0.5);},
    [this](bool interrupted){TankSubsystem::getInstance()->setSpeed(0.0, 0.0);},
    [this]{return TankSubsystem::getInstance()->getFrontRight()->GetSelectedSensorPosition(0) < -AUTO_DISTANCE;},
    {TankSubsystem::getInstance()},
  };

  /*frc2::FunctionalCommand m_fireBalls{
    [this]{m_timer.Start();},
    [this]{Shooter::getInstance()->setFlywheelSpeed(FLYWHEEL_SPEED); 
  Shooter::getInstance()->setShooterSpeed(SHOOTER_SPEED); 
  Shooter::getInstance()->setLoaderSpeed(LOADER_SPEED);},
    [this](bool interrupted){Shooter::getInstance()->setFlywheelSpeed(0.0); 
  Shooter::getInstance()->setShooterSpeed(0.0); 
  Shooter::getInstance()->setLoaderSpeed(0.0);},
    [this]{return m_timer.HasPeriodPassed(5.0);},
    {Shooter::getInstance()}
  };*/

  frc2::InstantCommand m_fireBalls{[this] {Shooter::getInstance()->setFlywheelSpeed(FLYWHEEL_SPEED); 
  Shooter::getInstance()->setShooterSpeed(SHOOTER_SPEED); 
  Shooter::getInstance()->setLoaderSpeed(LOADER_SPEED);},
  {Shooter::getInstance()}};
  //use this version if vision target bad
  //frc2::SequentialCommandGroup m_autoCommand{m_moveForward};
  frc2::SequentialCommandGroup m_autoCommand{m_moveForward, m_moveBackward, m_fireBalls};
  
  bool m_buttonPressed = false;
  int m_counter = 0;

  ColorSensor m_colorSensor;
  frc::Timer m_timer;
};
