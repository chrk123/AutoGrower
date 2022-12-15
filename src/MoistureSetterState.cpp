#include "MoistureSetterState.h"
#include "Controller.h"
#include "StateContext.h"

#include <math.h>

void MoistureSetter::run(StateContext &context) {
    context.m_LCD.setCursor(0, 0);
    context.m_LCD.print("set moisture:       ");
    context.m_LCD.setCursor(0, 1);
    context.m_LCD.print(static_cast<int>(context.m_Moisture * 100));
    context.m_LCD.print("%              ");
}

void MoistureSetter::handleLeft(StateContext &context) {
    context.m_Moisture = fmax(0, context.m_Moisture - 0.01);
}

void MoistureSetter::handleRight(StateContext &context) {
    context.m_Moisture = fmin(1, context.m_Moisture + 0.01);
}

void MoistureSetter::handleClick(StateContext &context) {
    context.SetState(&controller_state);
}

MoistureSetter moisture_setter_state{};