#include "SettingsOverview.h"
#include "Controller.h"
#include "StateContext.h"
#include "RelayOverview.h"


void SettingsOverView::run(StateContext &context) {
    context.m_LCD.setCursor(0, 0);
    context.m_LCD.print("targets:        ");

    context.m_LCD.setCursor(0, 1);
    context.m_LCD.print(context.m_Temperature);
    context.m_LCD.print(static_cast<char>(223));
    context.m_LCD.print("C | ");
    context.m_LCD.print(context.m_Moisture * 100);
    context.m_LCD.print("%");

    delay(500);
}

void SettingsOverView::handleLeft(StateContext &context) {
    context.SetState(&controller_state);
}

void SettingsOverView::handleRight(StateContext &context) {
    context.SetState(&relay_overview_state);
}

void SettingsOverView::handleClick(StateContext &context) {
}

SettingsOverView settings_overview_state{};