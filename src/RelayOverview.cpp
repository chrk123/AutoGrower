#include "RelayOverview.h"
#include "SettingsOverview.h"
#include "StateContext.h"

void RelayOverView::run(StateContext &context) {
    context.m_LCD.setCursor(0, 0);
    context.m_LCD.print("Heat mat:      ");
    context.m_LCD.println(digitalRead(12));

    context.m_LCD.setCursor(0, 1);
    context.m_LCD.print("Pump:          ");
    context.m_LCD.print(digitalRead(11));
}

void RelayOverView::handleLeft(StateContext &context) {
    context.SetState(&settings_overview_state);
}

void RelayOverView::handleRight(StateContext &context) {
}

void RelayOverView::handleClick(StateContext &context) {
}

RelayOverView relay_overview_state{};