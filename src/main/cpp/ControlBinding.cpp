#include <exception>
#include <chrono>
#include <thread>

#include "ControlBinding.h"
#include "ControlModeDoesNotExistException.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <ntcore_cpp.h>

ControlBinding::ControlBinding() {}

void ControlBinding::initialize() {
    enableControlBindingConfigurations();
    setDefaultControls();
    displayControlBindings();
}

double ControlBinding::getControlStatus(std::string control, double deadzone /* = 0 */) {

    // Determine if control mode is active
    if (m_controlData.find(control) != m_controlData.end()) {
        auto it = m_controlData.find(control);
        if (it->second.driver == JoystickType::DRIVER && it->second.control == ControlType::AXIS) {
            double rawAxis = m_driverJoystick.GetRawAxis(it->second.id);
            return std::abs(rawAxis) > deadzone ? rawAxis : 0;
        } else if (it->second.driver == JoystickType::DRIVER && it->second.control == ControlType::BUTTON) {
            return m_driverJoystick.GetRawButton(it->second.id);
        } else if (it->second.driver == JoystickType::OPERATOR && it->second.control == ControlType::AXIS) {
            double rawAxis = m_operatorJoystick.GetRawAxis(it->second.id);
            return std::abs(rawAxis) > deadzone ? rawAxis : 0;
        } else if (it->second.driver == JoystickType::OPERATOR && it->second.control == ControlType::BUTTON) {
            return m_operatorJoystick.GetRawButton(it->second.id);
        }
    }

    return false;
}

void ControlBinding::setDefaultControls() {
    // Driver controls
    m_controlData["driveLeft"] = {JoystickType::DRIVER, ControlType::AXIS, 1};          // Left Axis
    m_controlData["driveRight"] = {JoystickType::DRIVER, ControlType::AXIS, 3};         // Right Axis
    m_controlData["shiftHigh"] = {JoystickType::DRIVER, ControlType::BUTTON, 8};        // Right Trigger
    m_controlData["shiftLow"] = {JoystickType::DRIVER, ControlType::BUTTON, 7};         // Left Trigger
    m_controlData["switchCamera"] = {JoystickType::DRIVER, ControlType::BUTTON, 3};     // Button 'B'
    m_controlData["visionAim"] = {JoystickType::DRIVER, ControlType::BUTTON, 1};        // Button 'X'
    m_controlData["eBrake"] = {JoystickType::DRIVER, ControlType::BUTTON, 6};            // Right Bumper
    // Operator controls
    m_controlData["moveloader"] = {JoystickType::OPERATOR, ControlType::AXIS, 1};       // Left Axis
    m_controlData["shoot"] = {JoystickType::OPERATOR, ControlType::AXIS, 3};            // Right Axis
    m_controlData["intake"] = {JoystickType::OPERATOR, ControlType::BUTTON, 8};         // Right Trigger
    m_controlData["outtake"] = {JoystickType::OPERATOR, ControlType::BUTTON, 7};        // Left Trigger
    m_controlData["tiltIntakeUp"] = {JoystickType::OPERATOR, ControlType::BUTTON, 5};   // Left Bumper
    m_controlData["tiltIntakeDown"] = {JoystickType::OPERATOR, ControlType::BUTTON, 6}; // Right Bumper
}

void ControlBinding::displayControlBindings() {
    for(auto it = m_controlData.begin(); it != m_controlData.end(); it++){
        if (it->second.driver == JoystickType::DRIVER) {
            // Display driver control bindings
            m_driverControls->GetEntry(it->first).SetDouble(it->second.id);
        } else {
            // Display operator control bindings
            m_operatorControls->GetEntry(it->first).SetDouble(it->second.id);
        }
    }
}

void ControlBinding::updateControlBinding(std::string control, int id) {
    // If control exists, update corresponding joystick ID
    if (m_controlData.find(control) != m_controlData.end()) {
        auto it = m_controlData.find(control);
        it->second.id = id;
        if (it->second.driver == JoystickType::DRIVER) {
            m_driverControls->GetEntry(it->first).SetDouble(it->second.id);
        } else {
            m_operatorControls->GetEntry(it->first).SetDouble(it->second.id);
        }
        m_configurations->GetEntry("Control Name").SetString("Successfully Bound");
        m_configurations->GetEntry("Joystick ID").SetDouble(-1);
    } else {
        m_configurations->GetEntry("Control Name").SetString("Invalid Input");
    }
}

void ControlBinding::enableControlBindingConfigurations() {    
    nt::NetworkTableEntry saveControlsEntry = m_configurations->GetEntry("Save Controls");
    nt::NetworkTableEntry useDefaultControlsEntry = m_configurations->GetEntry("Use Default Controls");

    // Update control bindings if "Save Controls" button is clicked
    saveControlsEntry.AddListener([this] (nt::EntryNotification event) {
        m_configurations->GetEntry("Save Controls").SetBoolean(false);
        std::string controlName = m_configurations->GetEntry("Control Name").GetString("Name");
        int id = m_configurations->GetEntry("Joystick ID").GetDouble(-1);
        updateControlBinding(controlName, id);
    }, NT_NOTIFY_NEW | NT_NOTIFY_UPDATE);

    useDefaultControlsEntry.AddListener([this] (nt::EntryNotification event) {
        m_configurations->GetEntry("Use Default Controls").SetBoolean(false);
        setDefaultControls();
        displayControlBindings();
    }, NT_NOTIFY_NEW | NT_NOTIFY_UPDATE);

    m_configurations->GetEntry("Control Name").SetString("Name");
    m_configurations->GetEntry("Joystick ID").SetDouble(-1);
    m_configurations->GetEntry("Save Controls").SetBoolean(false);
    m_configurations->GetEntry("Use Default Controls").SetBoolean(false);
}