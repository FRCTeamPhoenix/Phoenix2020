#pragma once

#include <frc/DigitalInput.h>
#include <frc2/command/SubsystemBase.h>
#include <ctre/Phoenix.h>

#include "Constants.h"

class Shooter : public frc2::SubsystemBase {
    public:
        static Shooter* getInstance() {
            static Shooter instance;
            return &instance;
        }

        Shooter(Shooter const&) = delete;
        void operator = (Shooter const&) = delete;
        void initialize();
        void setFlywheelSpeed(const double& percent);
        void setShooterSpeed(const double& percent);
        void setLoaderSpeed(const double& percent);
        void setIntakeSpeed(const double& percent);
        void setIntakeTiltSpeed(const double& speed);
        void zeroEncoders();
        void execute();
        void stop();
        int getTiltPosition();
    
    private:
        Shooter();
        TalonSRX m_flywheelLeft = {TALON_FLYWHEEL_LEFT};
        TalonSRX m_flywheelRight = {TALON_FLYWHEEL_RIGHT};
        TalonSRX m_shooterTop = {TALON_SHOOTER_TOP};
        TalonSRX m_loaderLeft = {TALON_LOADER_LEFT};
        TalonSRX m_loaderRight = {TALON_LOADER_RIGHT};
        VictorSPX m_intake = {VICTOR_INTAKE};
        TalonSRX m_intakeTilt = {TALON_INTAKE_TILT};
};