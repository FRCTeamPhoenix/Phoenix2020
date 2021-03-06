#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc/Joystick.h>

#include "Constants.h"

class AimAdjust : public frc2::CommandHelper<frc2::CommandBase, AimAdjust>{
public:
    AimAdjust(bool autoVersion = false);

    void Initialize() override;

    void Execute() override;

    void End(bool interrupted) override;

    bool IsFinished() override;
private:
    bool m_autoVersion;
    frc::Joystick m_driverJoystick{DRIVER_JOYSTICK};
};