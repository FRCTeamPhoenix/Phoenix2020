#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/Phoenix.h>
#include <frc/drive/DifferentialDrive.h>

#include "Constants.h"

class TankSubsystem : public frc2::SubsystemBase {
    public:
        //have a singleton based subsytem since you will only have 1 object
        static TankSubsystem* getInstance(){
            static TankSubsystem instance;
            
            return &instance;
        }

        //prevent copying
        TankSubsystem(TankSubsystem const&) = delete;
        void operator=(TankSubsystem const&)  = delete;
        void init();
        void setSpeed(const double& left, const double& right);
        void setHighGear();
        void setLowGear();
        void setBrakeMode();
        void setCoastMode();

        //zero encoders
        void zeroEncoders();

        //zero gyro
        void zeroGyro();

        //used to check the dashboard for any calibration related things to gyro
        void updateGyro();

        //add a new motion profile instance to a drivetrain
        TalonSRX* getFrontLeft() {return &m_frontLeft;}
        TalonSRX* getFrontRight() {return &m_frontRight;}
    private:
        TankSubsystem();

        PigeonIMU m_imu = {IMU_ID};

        const int TIMEOUT = 10;

        TalonSRX m_frontLeft = {TALON_FRONT_LEFT};
        TalonSRX m_frontRight = {TALON_FRONT_RIGHT};
        VictorSPX m_backLeft = {VICTOR_BACK_LEFT};
        VictorSPX m_backRight = {VICTOR_BACK_RIGHT};
};