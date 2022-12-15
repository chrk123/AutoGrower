#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "State.h"
#include "Components.h"

struct Controller : public State {
    void run(StateContext &) override;

    void handleLeft(StateContext &) override;

    void handleRight(StateContext &) override;

    void handleClick(StateContext &) override;

    bool HasPassedSince(unsigned long starting_time, unsigned long timeout);

    MoistureSensor m_MoistureSensor{3};
    TemperatureSensor m_TempSensor{4};

    Relay m_Pump{11};
    Relay m_Heat{12};

    unsigned long m_IntervallCheckPump{300000};
    unsigned long m_IntervallCheckHeat{600000};
    unsigned long m_IntervallUpdate{10000};

    unsigned long m_LastCheck{0};
    unsigned long m_LastPumpCheck{0};
    unsigned long m_LastHeatCheck{0};

    bool m_ForceCheck{true};
};

extern Controller controller_state;

#endif