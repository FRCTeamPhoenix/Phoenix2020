#include "subsystems/Shooter.h"

#include "PCMHandler.h"

Shooter::Shooter() {}

void Shooter::initialize() {
    // Configure encoders on motors (remove if encoder is absent)
    m_flywheelLeft.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0);
    m_flywheelRight.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0);
    m_shooterTop.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0);
    m_loaderLeft.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0);
    m_loaderRight.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0);
    m_intake.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0);
    m_intakeTilt.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0);
    
    //invert sensor phase
    m_intakeTilt.SetSensorPhase(true);

    // Make sure corresponding motors spin opposite direction 
    m_flywheelLeft.SetInverted(true);
    m_flywheelRight.SetInverted(true);
    m_shooterTop.SetInverted(true);
    m_loaderLeft.SetInverted(false);
    m_loaderRight.SetInverted(false);
    m_intake.SetInverted(false);
    m_intakeTilt.SetInverted(true);

    // Configure nominal output for motors
    m_flywheelLeft.ConfigNominalOutputForward(0);
    m_flywheelLeft.ConfigNominalOutputReverse(0);
    m_flywheelRight.ConfigNominalOutputForward(0);
    m_flywheelRight.ConfigNominalOutputReverse(0);
    m_shooterTop.ConfigNominalOutputForward(0);
    m_shooterTop.ConfigNominalOutputReverse(0);
    m_loaderLeft.ConfigNominalOutputForward(0);
    m_loaderLeft.ConfigNominalOutputReverse(0);
    m_loaderRight.ConfigNominalOutputForward(0);
    m_loaderRight.ConfigNominalOutputReverse(0);
    m_intake.ConfigNominalOutputForward(0);
    m_intake.ConfigNominalOutputReverse(0);
    m_intakeTilt.ConfigNominalOutputForward(0);
    m_intakeTilt.ConfigNominalOutputReverse(0);

    // Configure power limits on motors (change if needed)
    m_flywheelLeft.ConfigPeakOutputForward(FLYWHEEL_SPEED);
    m_flywheelLeft.ConfigPeakOutputReverse(-FLYWHEEL_SPEED);
    m_flywheelRight.ConfigPeakOutputForward(FLYWHEEL_SPEED);
    m_flywheelRight.ConfigPeakOutputReverse(-FLYWHEEL_SPEED);
    m_shooterTop.ConfigPeakOutputForward(SHOOTER_SPEED);
    m_shooterTop.ConfigPeakOutputReverse(-SHOOTER_SPEED);
    m_loaderLeft.ConfigPeakOutputForward(LOADER_SPEED);
    m_loaderLeft.ConfigPeakOutputReverse(-LOADER_SPEED);
    m_loaderRight.ConfigPeakOutputForward(LOADER_SPEED);
    m_loaderRight.ConfigPeakOutputReverse(-LOADER_SPEED);
    m_intake.ConfigPeakOutputForward(1.0);
    m_intake.ConfigPeakOutputReverse(-1.0);
    m_intakeTilt.ConfigPeakOutputForward(0.75);
    m_intakeTilt.ConfigPeakOutputReverse(-0.75);
    
    m_flywheelLeft.Follow(m_flywheelRight);
    m_loaderLeft.Follow(m_loaderRight);

    zeroEncoders();
}

void Shooter::setFlywheelSpeed(const double& percent) {
    m_flywheelRight.Set(ControlMode::PercentOutput, percent);
}

void Shooter::setShooterSpeed(const double& percent) {
    m_shooterTop.Set(ControlMode::PercentOutput, percent);
}

void Shooter::setLoaderSpeed(const double& percent) {
    m_loaderRight.Set(ControlMode::PercentOutput, percent);
}

void Shooter::setIntakeSpeed(const double& percent) {
    m_intake.Set(ControlMode::PercentOutput, percent);
}

void Shooter::setIntakeTiltSpeed(const double& speed) {
    m_intakeTilt.Set(ControlMode::PercentOutput, speed);
}

void Shooter::zeroEncoders() {
    m_intakeTilt.GetSensorCollection().SetQuadraturePosition(0);
}

void Shooter::stop() {
    setFlywheelSpeed(0);
    setShooterSpeed(0);
    setLoaderSpeed(0);
    setIntakeSpeed(0);
}

int Shooter::getTiltPosition(){
    return m_intakeTilt.GetSelectedSensorPosition(0);
}