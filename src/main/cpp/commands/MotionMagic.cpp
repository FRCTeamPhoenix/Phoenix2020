#include "commands/MotionMagic.h"

#include "subsystems/TankSubsystem.h"

#include <iostream>
#include <frc/trajectory/TrajectoryGenerator.h>
#include <frc/kinematics/DifferentialDriveKinematics.h>

MotionMagic::MotionMagic(const double& distance, const double& heading, const double& maxErr, const double& maxErrHeading) : m_distance(distance), m_heading(heading), m_maxErr(maxErr), m_maxErrHeading(maxErrHeading){
    AddRequirements(TankSubsystem::getInstance());
}

void MotionMagic::Initialize(){
    TankSubsystem::getInstance()->setSpeed(0.0, 0.0);
    TankSubsystem::getInstance()->zeroEncoders();
    TankSubsystem::getInstance()->zeroGyro();

    //start a a motion magic
    m_frontRight = TankSubsystem::getInstance()->getFrontRight();

    //make sure to config motor for this
    m_frontRight->ConfigMotionCruiseVelocity(957);
    m_frontRight->ConfigMotionAcceleration(957);
    m_frontRight->ConfigMotionSCurveStrength(2);

    std::cout<<"started motion magic: "<<m_distance<<" with heading "<<m_heading<<std::endl;

    TankSubsystem::getInstance()->getFrontLeft()->Follow(*m_frontRight, FollowerType_AuxOutput1);
    m_frontRight->Set(ControlMode::MotionMagic, m_distance, DemandType::DemandType_AuxPID, m_heading);
}

void MotionMagic::Execute(){
}

void MotionMagic::End(bool interrupted)
{
    TankSubsystem::getInstance()->setSpeed(0.0, 0.0);
    std::cout<<"motion magic end"<<std::endl;
}

bool MotionMagic::IsFinished(){
    double err = m_frontRight->GetClosedLoopTarget(0) - m_frontRight->GetSelectedSensorPosition(0);
    double errHeading = m_heading - m_frontRight->GetSelectedSensorPosition(1);

    bool isFinished = abs(err) < m_maxErr && abs(errHeading) < m_maxErrHeading;
    std::cout<<err<<" "<< m_frontRight->GetSelectedSensorPosition(0)<<" "<<errHeading<<" "<<isFinished<<std::endl;
    return isFinished;
}