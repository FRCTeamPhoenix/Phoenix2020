#include "commands/DefaultOperate.h"
#include "ControlBinding.h"
#include "Constants.h"

DefaultOperate::DefaultOperate() {
    AddRequirements({Shooter::getInstance()});
}

void DefaultOperate::Initialize() {}

void DefaultOperate::Execute() {
    double shoot = -ControlBinding::getInstance()->getControlStatus("shoot");
    double loaderSpeed = -ControlBinding::getInstance()->getControlStatus("moveloader");
    bool intake = ControlBinding::getInstance()->getControlStatus("intake") > 0.1;
    bool outtake = ControlBinding::getInstance()->getControlStatus("outtake") > 0.1;
    bool tiltIntakeUp = ControlBinding::getInstance()->getControlStatus("tiltIntakeUp") > 0.1;
    bool tiltIntakeDown = ControlBinding::getInstance()->getControlStatus("tiltIntakeDown") > 0.1;

    Shooter::getInstance()->setLoaderSpeed(loaderSpeed * LOADER_SPEED);
    Shooter::getInstance()->setShooterSpeed(loaderSpeed * SHOOTER_SPEED);
    Shooter::getInstance()->setFlywheelSpeed(shoot * 0.5);

    if (intake) {
        Shooter::getInstance()->setIntakeSpeed(INTAKE_SPEED);
    } else if (outtake) {
        Shooter::getInstance()->setIntakeSpeed(-INTAKE_SPEED);
    } else {
        Shooter::getInstance()->setIntakeSpeed(0);
    }

    /*if (tiltIntakeUp) {
        Shooter::getInstance()->setIntakeTiltSpeed(1.0);
    } else if (tiltIntakeDown) {
        Shooter::getInstance()->setIntakeTiltSpeed(-1.0);
    } else{
        Shooter::getInstance()->setIntakeTiltSpeed(0.0);
    }*/

    if (tiltIntakeUp && Shooter::getInstance()->getTiltPosition() < INTAKE_TILT_UPPER_LIMIT) {
        Shooter::getInstance()->setIntakeTiltSpeed(1.0);
    } else if (tiltIntakeDown && Shooter::getInstance()->getTiltPosition() > INTAKE_TILT_LOWER_LIMIT) {
        Shooter::getInstance()->setIntakeTiltSpeed(-1.0);
    } else{
        Shooter::getInstance()->setIntakeTiltSpeed(0.0);
    }
}

void DefaultOperate::End(bool interrupted) {
    Shooter::getInstance()->stop();
}

bool DefaultOperate::IsFinished() {
    return false;
}
