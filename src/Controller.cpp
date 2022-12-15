#include "Controller.h"
#include "StateContext.h"
#include "TemperatureSetterState.h"
#include "RelayOverview.h"
#include "SettingsOverview.h"

void Controller::run(StateContext &context) {
    //context.m_LCD.clear();

    auto const current_time = millis();

    if (!m_ForceCheck && !HasPassedSince(m_LastCheck, m_IntervallUpdate))
        return;

    m_LastCheck = current_time;

    auto const temperature = m_TempSensor.read();
    context.m_LCD.setCursor(0, 0);
    context.m_LCD.print("temp: ");
    context.m_LCD.print(temperature);
    context.m_LCD.print(static_cast<char>(223));
    context.m_LCD.print("C   ");

    auto const moisture = m_MoistureSensor.read();
    context.m_LCD.setCursor(0, 1);
    context.m_LCD.print("moisture: ");
    context.m_LCD.print(moisture * 100);
    context.m_LCD.print("% ");

    // check for heatmap every 10 minutes
    if (m_ForceCheck || HasPassedSince(m_LastHeatCheck, 1800000)) {
        m_LastHeatCheck = millis();
        if (temperature < context.m_Temperature) {
            m_Heat.on();
        } else {
            m_Heat.off();
        }
    }

    // check for pump every 5 minutes
    if (m_ForceCheck || HasPassedSince(m_LastPumpCheck, 300000)) {
        m_LastPumpCheck = millis();
        if (moisture < context.m_Moisture) {
            m_Pump.on();
            context.m_LCD.clear();
            context.m_LCD.setCursor(0, 0);
            context.m_LCD.print("pumping ... ");
            delay(10000);
            m_Pump.off();
        } else {
            m_Pump.off();
        }
    }

    m_ForceCheck = false;
}

void Controller::handleLeft(StateContext &context) {
}

void Controller::handleRight(StateContext &context) {
    context.SetState(&settings_overview_state);
}

void Controller::handleClick(StateContext &context) {
    m_Pump.off();
    m_Heat.off();
    m_ForceCheck = true;
    return context.SetState(&temperature_setter_state);
}

bool Controller::HasPassedSince(unsigned long starting_time, unsigned long timeout) {
    return (millis() - starting_time) > timeout;
}

Controller controller_state{};