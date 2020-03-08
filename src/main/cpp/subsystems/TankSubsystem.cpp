#include "subsystems/TankSubsystem.h"
#include "PCMHandler.h"

#include <frc/smartdashboard/SmartDashboard.h>

TankSubsystem::TankSubsystem() {
    
}

void TankSubsystem::init(){
    //switch what sensor we want to feedback
    //left side should use velocity
    m_frontLeft.ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, PID_VELOCITY_SLOT);
    //right side should use sum of the two sides
    m_frontRight.ConfigSelectedFeedbackSensor(FeedbackDevice::SensorSum, PID_VELOCITY_SLOT);
    //also should use remote sensor 1 to get heading
    m_frontRight.ConfigSelectedFeedbackSensor(FeedbackDevice::RemoteSensor1, PID_HEADING_SLOT);

    //remote sensor 0 should be the other device's quad encoder
    m_frontRight.ConfigRemoteFeedbackFilter(m_frontLeft.GetDeviceID(), RemoteSensorSource::RemoteSensorSource_TalonSRX_SelectedSensor, 0); 
    //remote sensor 1 should be the imu
    m_frontRight.ConfigRemoteFeedbackFilter(m_imu.GetDeviceNumber(), RemoteSensorSource::RemoteSensorSource_Pigeon_Yaw, 1);

    //use the sum of the two sensors to determine distance
    m_frontRight.ConfigSensorTerm(SensorTerm::SensorTerm_Sum0, FeedbackDevice::QuadEncoder); //this side
    m_frontRight.ConfigSensorTerm(SensorTerm::SensorTerm_Sum1, FeedbackDevice::RemoteSensor0); //other side
    
    //set the aux PID polarity (is it rotating the right way?)
    m_frontRight.ConfigAuxPIDPolarity(false);

    m_backLeft.Follow(m_frontLeft, FollowerType_PercentOutput);
    m_backRight.Follow(m_frontRight, FollowerType_PercentOutput);

    //change output to match + (input = output ?)
    m_frontLeft.SetSensorPhase(true);

    //invert left side motion (is it going the right way ?)
    m_frontLeft.SetInverted(true);
    m_backLeft.SetInverted(true);

    //change output to match +
    m_frontRight.SetSensorPhase(false);
    m_frontLeft.SetSensorPhase(false);

    //invert the right side motion
    m_frontRight.SetInverted(false);
    m_backRight.SetInverted(false);

    //prevent the motors from bumping small percents to a minimum
    m_frontLeft.ConfigNominalOutputForward(0);
	m_frontLeft.ConfigNominalOutputReverse(0);
	m_frontRight.ConfigNominalOutputForward(0);
	m_frontRight.ConfigNominalOutputReverse(0);

    //set it for low speed control
    m_frontLeft.ConfigNeutralDeadband(0.001);
    m_frontRight.ConfigNeutralDeadband(0.001);

    //allow us to use the full motor power without a cap
    m_frontLeft.ConfigPeakOutputForward(1.0);
	m_frontLeft.ConfigPeakOutputReverse(-1.0);
	m_frontRight.ConfigPeakOutputForward(1.0);
    m_frontRight.ConfigPeakOutputReverse(-1.0);
    
    //m_frontLeft.Config_kP(0, 0.25);
    //(75% X 1023) / (speed at 75%)
    //left = 1092
    //m_frontLeft.Config_kF(0, (.75 * 1023.0) / 1092.0);

    //configure only the front right for motion profile
    
    //primary PID loop
    m_frontRight.Config_kP(PID_VELOCITY_SLOT, 0.25);
    m_frontRight.Config_kI(PID_VELOCITY_SLOT, 0.0);
    m_frontRight.Config_kD(PID_VELOCITY_SLOT, 0.0);
    //right = 957
    m_frontRight.Config_kF(PID_VELOCITY_SLOT, (.75 * 1023.0) / 957.0); //minimum speed
    m_frontRight.Config_IntegralZone(PID_VELOCITY_SLOT, 400); //allowable error
    m_frontRight.ConfigClosedLoopPeakOutput(PID_VELOCITY_SLOT, 1.0); //max percent output
    //secondary PID loop
    m_frontRight.Config_kP(PID_HEADING_SLOT, 0.25);
    m_frontRight.Config_kI(PID_HEADING_SLOT, 0.0);
    m_frontRight.Config_kD(PID_HEADING_SLOT, 0.0);
    //right = 957
    m_frontRight.Config_kF(PID_HEADING_SLOT, 0.0);
    m_frontRight.Config_IntegralZone(PID_HEADING_SLOT, 400); //allowable error
    m_frontRight.ConfigClosedLoopPeakOutput(PID_HEADING_SLOT, 0.5); //max percent output

    //set both wheels to coast
    setCoastMode();
}

void TankSubsystem::setSpeed(const double& left, const double& right){
    m_frontLeft.Set(ControlMode::PercentOutput, left);
    m_frontRight.Set(ControlMode::PercentOutput, right);
}
void TankSubsystem::setHighGear() {
    PCMHandler::getInstance()->setHighGear();
}

void TankSubsystem::setLowGear(){
    PCMHandler::getInstance()->setLowGear();
}

void TankSubsystem::setBrakeMode(){
    m_frontLeft.SetNeutralMode(Brake);
    m_frontRight.SetNeutralMode(Brake);
}

void TankSubsystem::setCoastMode(){
    m_frontLeft.SetNeutralMode(Coast);
    m_frontRight.SetNeutralMode(Coast);
}

void TankSubsystem::zeroEncoders(){
    m_frontLeft.GetSensorCollection().SetQuadraturePosition(0);
    m_frontRight.GetSensorCollection().SetQuadraturePosition(0);
    
}

void TankSubsystem::zeroGyro(){
    m_imu.SetYaw(0.0);
}

void TankSubsystem::updateGyro(){
    
    //update the values
    double ypr[3];
    m_imu.GetYawPitchRoll(ypr);
    ypr[0] = 0.0;
    ypr[1] = 0.0;
    ypr[2] = 0.0;

    frc::SmartDashboard::PutNumber("Gyro Yaw", (int)ypr[0]);
    frc::SmartDashboard::PutNumber("Gyro Pitch", (int)ypr[1]);
    frc::SmartDashboard::PutNumber("Gyro Roll", (int)ypr[2]);

    if(frc::SmartDashboard::GetBoolean("GyroZero",false)){
        zeroGyro();
    }

    //reset the values
    frc::SmartDashboard::PutBoolean("GyroZero", false);
}