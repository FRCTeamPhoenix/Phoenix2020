#include "commands/DefaultDrive.h"
#include "ControlBinding.h"
#include "Constants.h"
#include "Cameras.h"

DefaultDrive::DefaultDrive() {
    AddRequirements({TankSubsystem::getInstance()});
}

void DefaultDrive::Initialize() {}

void DefaultDrive::Execute() {
    double leftStick = ControlBinding::getInstance()->getControlStatus("driveLeft", DEADZONE);
    double rightStick = ControlBinding::getInstance()->getControlStatus("driveRight", DEADZONE);
    bool shiftHigh = ControlBinding::getInstance()->getControlStatus("shiftHigh") > 0.1;
    bool shiftLow = ControlBinding::getInstance()->getControlStatus("shiftLow") > 0.1;

    if (shiftHigh) {
        TankSubsystem::getInstance()->setHighGear();
    } else if (shiftLow) {
        TankSubsystem::getInstance()->setLowGear();
    }

    if(std::abs(leftStick) > DEADZONE || std::abs(rightStick) > DEADZONE){
        TankSubsystem::getInstance()->setCoastMode();
        if (m_inverted) {
            //swap sides and direction
            TankSubsystem::getInstance()->setSpeed(rightStick, leftStick);
        } else {
            TankSubsystem::getInstance()->setSpeed(-leftStick, -rightStick);
        }
    }else {
        TankSubsystem::getInstance()->setSpeed(0.0, 0.0);
    }
    
    //enable brake mode when 'X' is pressed
    if(ControlBinding::getInstance()->getControlStatus("eBrake") > 0.1){
        TankSubsystem::getInstance()->setBrakeMode();
        TankSubsystem::getInstance()->setSpeed(0.001, 0.001);
    }
    
    //toggle direction using the 'B' button
    if (ControlBinding::getInstance()->getControlStatus("switchCamera") > 0.1) {
        if (!m_pressedBefore) {
            m_inverted = !m_inverted;
            CameraHost::getInstance()->setReverse(m_inverted);
        }
        m_pressedBefore = true;
    } else {
        m_pressedBefore = false;
    }
}

void DefaultDrive::End(bool interrupted) {
    TankSubsystem::getInstance()->setSpeed(0.0, 0.0);
}

bool DefaultDrive::IsFinished() {
    return false;
}
