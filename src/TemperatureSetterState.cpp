#include <math.h>
#include "TemperatureSetterState.h"
#include "MoistureSetterState.h"
#include "StateContext.h"

void TemperatureSetter::run(StateContext &context) {
    context.m_LCD.setCursor(0, 0);
    context.m_LCD.println("set temp:       ");
    context.m_LCD.setCursor(0, 1);
    context.m_LCD.print(context.m_Temperature);
    context.m_LCD.print(static_cast<char>(223));
    context.m_LCD.print("C            ");
}

void TemperatureSetter::handleLeft(StateContext &context) {
    context.m_Temperature = fmax(0, context.m_Temperature - 0.5);
}

void TemperatureSetter::handleRight(StateContext &context) {
    context.m_Temperature = fmin(40, context.m_Temperature + 0.5);
}

void TemperatureSetter::handleClick(StateContext &context) {
    context.SetState(&moisture_setter_state);
}

TemperatureSetter temperature_setter_state{};
