#include "subsystems/Shooter.h"

#include "PCMHandler.h"

Shooter::Shooter() {}

void Shooter::initialize() {
    // Configure encoders on motors (remove if encoder is absent)
    m_flywheelLeft.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0);
    m_flywheelRight.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0);
    m_shooterTop.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0);
    m_shooterBottom.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0);
    m_loaderLeft.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0);
    m_loaderRight.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0);
    m_intake.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0);
    
    // Make sure corresponding motors spin opposite direction 
    m_flywheelLeft.SetInverted(true);
    m_flywheelRight.SetInverted(true);
    m_shooterTop.SetInverted(false);
    m_shooterBottom.SetInverted(false);
    m_loaderLeft.SetInverted(true);
    m_loaderRight.SetInverted(false);

    // Configure nominal output for motors
    m_flywheelLeft.ConfigNominalOutputForward(0);
    m_flywheelLeft.ConfigNominalOutputReverse(0);
    m_flywheelRight.ConfigNominalOutputForward(0);
    m_flywheelRight.ConfigNominalOutputReverse(0);
    m_shooterTop.ConfigNominalOutputForward(0);
    m_shooterTop.ConfigNominalOutputReverse(0);
    m_shooterBottom.ConfigNominalOutputForward(0);
    m_shooterBottom.ConfigNominalOutputReverse(0);
    m_loaderLeft.ConfigNominalOutputForward(0);
    m_loaderLeft.ConfigNominalOutputReverse(0);
    m_loaderRight.ConfigNominalOutputForward(0);
    m_loaderRight.ConfigNominalOutputReverse(0);
    m_intake.ConfigNominalOutputForward(0);
    m_intake.ConfigNominalOutputReverse(0);

    // Configure power limits on motors (change if needed)
    m_flywheelLeft.ConfigPeakOutputForward(0.5);
    m_flywheelLeft.ConfigPeakOutputReverse(-0.5);
    m_flywheelRight.ConfigPeakOutputForward(0.5);
    m_flywheelRight.ConfigPeakOutputReverse(-0.5);
    m_shooterTop.ConfigPeakOutputForward(1.0);
    m_shooterTop.ConfigPeakOutputReverse(-1.0);
    m_shooterBottom.ConfigPeakOutputForward(1.0);
    m_shooterBottom.ConfigPeakOutputReverse(-1.0);
    m_loaderLeft.ConfigPeakOutputForward(1.0);
    m_loaderLeft.ConfigPeakOutputReverse(-1.0);
    m_loaderRight.ConfigPeakOutputForward(1.0);
    m_loaderRight.ConfigPeakOutputReverse(-1.0);
    m_intake.ConfigPeakOutputForward(1.0);
    m_intake.ConfigPeakOutputReverse(-1.0);
    
    m_flywheelLeft.Follow(m_flywheelRight);
    m_shooterTop.Follow(m_shooterBottom);
    m_loaderLeft.Follow(m_loaderRight);
}

void Shooter::setFlywheelSpeed(const double& percent) {
    m_flywheelRight.Set(ControlMode::PercentOutput, percent);
}

void Shooter::setShooterSpeed(const double& percent) {
    m_shooterBottom.Set(ControlMode::PercentOutput, percent);
}

void Shooter::setLoaderSpeed(const double& percent) {
    m_loaderRight.Set(ControlMode::PercentOutput, percent);
}

void Shooter::setIntakeSpeed(const double& percent) {
    m_intake.Set(ControlMode::PercentOutput, percent);
}

void Shooter::tiltIntakeUp(bool active) {
    std::cout << "Tilt up: " << active << std::endl;
    PCMHandler::getInstance()->tiltIntakeUp(active);
}

void Shooter::tiltIntakeDown(bool active) {
    std::cout << "Tilt down: " << active << std::endl;
    PCMHandler::getInstance()->tiltIntakeDown(active);
}

void Shooter::stop() {
    setFlywheelSpeed(0);
    setShooterSpeed(0);
    setLoaderSpeed(0);
    setIntakeSpeed(0);
}