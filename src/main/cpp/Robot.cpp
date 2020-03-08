/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2019 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandScheduler.h>
#include <frc2/command/button/JoystickButton.h>
#include "subsystems/TankSubsystem.h"
#include "PCMHandler.h"
#include "Limelight.h"
#include "Cameras.h"

#include "ControlBinding.h"
#include "subsystems/Shooter.h"

void Robot::RobotInit() {
    ControlBinding::getInstance()->initialize();
    Shooter::getInstance()->initialize();
    TankSubsystem::getInstance()->init();
    TankSubsystem::getInstance()->zeroEncoders();
    CameraHost::getInstance()->init();
    Limelight::disableLight();
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want to run during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() { 
    frc2::CommandScheduler::GetInstance().Run();
    // TankSubsystem::getInstance()->updateGyro();

    //update color sensor values
    /* frc::Color detectedColor = m_colorSensor.getDetectedColor();
    std::string approxColor = m_colorSensor.getApproximateColor();

    frc::SmartDashboard::PutNumber("R", detectedColor.red);
    frc::SmartDashboard::PutNumber("G", detectedColor.green);
    frc::SmartDashboard::PutNumber("B", detectedColor.blue);
    frc::SmartDashboard::PutString("Detected Color", approxColor);

    if(!frc::SmartDashboard::GetBoolean("Should Auto", false)){
        frc::SmartDashboard::PutBoolean("Should Auto", false);
    } */
}

/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {
    Limelight::disableLight();
}

/**
 * This autonomous runs the autonomous command selected by your {@link
 * RobotContainer} class.
 */
void Robot::AutonomousInit() {
    TankSubsystem::getInstance()->setSpeed(0.0, 0.0);
    TankSubsystem::getInstance()->zeroEncoders();
    TankSubsystem::getInstance()->zeroGyro();

    m_counter = 0;
    frc2::CommandScheduler::GetInstance().CancelAll();
}

void Robot::AutonomousPeriodic() {
    //teleop logic
    if(m_counter > 1){
        TankSubsystem::getInstance()->setSpeed(0.0, 0.0);
        TankSubsystem::getInstance()->zeroEncoders();
        TankSubsystem::getInstance()->zeroGyro();
        frc2::CommandScheduler::GetInstance().Schedule(true, &m_autoCommand);
    }

    m_counter++;
}

void Robot::TeleopInit() {
    //make robot stop
    TankSubsystem::getInstance()->setSpeed(0.0, 0.0);

    frc2::CommandScheduler::GetInstance().Schedule(true, &m_defaultDrive);
    frc2::CommandScheduler::GetInstance().Schedule(true, &m_defaultOperate);
}

/**
 * This function is called periodically during operator control.
 */
void Robot::TeleopPeriodic() {
    //teleop logic
    //press the 'X' button to auto lock
    if (ControlBinding::getInstance()->getControlStatus("visionAim") > 0.1) {
        if (!m_buttonPressed) {
            frc2::CommandScheduler::GetInstance().Schedule(true, &m_nonAutoAim);
        }
        m_buttonPressed = true;
    } else {
        if (m_buttonPressed) {
            frc2::CommandScheduler::GetInstance().Schedule(true, &m_defaultDrive);
        }
            
        m_buttonPressed = false;
    }
}

void Robot::TestInit() {
}

/**
 * This function is called periodically during test mode.
 */
void Robot::TestPeriodic() {
}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
