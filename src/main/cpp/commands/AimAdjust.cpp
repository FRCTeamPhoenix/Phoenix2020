#include "commands/AimAdjust.h"

#include "Limelight.h"
#include "Constants.h"
#include "subsystems/TankSubsystem.h"
#include <iostream>
AimAdjust::AimAdjust(bool autoVersion) : m_autoVersion(autoVersion) {
    AddRequirements({TankSubsystem::getInstance()});
}

void AimAdjust::Initialize() {
    Limelight::enableLight();
    std::cout<<"Aim adjust started"<<std::endl;
}

void AimAdjust::Execute() {
    //adjust if the target is in view
    
    if(Limelight::seesTarget()){
        float err = Limelight::getTx();
        float distErr = Limelight::getTy();

        float speed = AIM_P * err;
        float distSpeed = 0.0f;

        if(abs(distErr) >= DIST_THRESH)
            distSpeed = AIM_DIST_P * distErr;
        TankSubsystem::getInstance()->setSpeed(distSpeed + speed, distSpeed - speed);
    }
}

void AimAdjust::End(bool interrupted) {
    Limelight::disableLight();
    std::cout<<interrupted<<std::endl;
    //Limelight::disableLight();
    TankSubsystem::getInstance()->setSpeed(0.0, 0.0);

    std::cout<<"Aim adjust over"<<std::endl;
}

bool AimAdjust::IsFinished() {
    if(m_autoVersion){
        float err = Limelight::getTx();
        float distErr = Limelight::getTy();
        return (std::abs(err) < AIM_THRESH && std::abs(distErr) < DIST_THRESH);
    }else{
        return !m_driverJoystick.GetRawButton(1);
    }
}