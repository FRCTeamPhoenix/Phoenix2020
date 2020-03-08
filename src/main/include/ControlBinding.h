#pragma once

#include <unordered_map>

#include <frc/Joystick.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableEntry.h>
#include <networktables/NetworkTableInstance.h>

#include "Constants.h"

enum class JoystickType {
    DRIVER, OPERATOR
};

enum class ControlType {
    AXIS, BUTTON
};

struct ControlData {
    JoystickType driver;
    ControlType control;
    int id;
};

class ControlBinding {
    public:
        static ControlBinding* getInstance() {
            static ControlBinding instance;
            return &instance;
        }

        ControlBinding(ControlBinding const&) = delete;
        void operator = (ControlBinding const&) = delete;
        ControlBinding();
        void initialize();
        double getControlStatus(std::string control, double deadzone = 0);

    private:
        frc::Joystick m_driverJoystick{DRIVER_JOYSTICK};
        frc::Joystick m_operatorJoystick{OPERATOR_JOYSTICK};
        std::unordered_map<std::string, ControlData> m_controlData;

        std::shared_ptr<nt::NetworkTable> m_controls = nt::NetworkTableInstance::GetDefault().GetTable("Control Bindings");
        std::shared_ptr<nt::NetworkTable> m_driverControls = m_controls->GetSubTable("Driver Controls");
        std::shared_ptr<nt::NetworkTable> m_operatorControls = m_controls->GetSubTable("Operator Controls");
        std::shared_ptr<nt::NetworkTable> m_configurations = m_controls->GetSubTable("Control Configurations");

        void setDefaultControls();
        void displayControlBindings();
        void updateControlBinding(std::string controlName, int id);
        void enableControlBindingConfigurations();
};