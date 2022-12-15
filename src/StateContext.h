#ifndef STATECONTEXT_H
#define STATECONTEXT_H

#include "State.h"
#include "Controller.h"
#include <LiquidCrystal_I2C.h>

class StateContext {
public:
    explicit StateContext(LiquidCrystal_I2C &lcd, float temp, float moist) : m_LCD(lcd), m_Temperature(temp),
                                                                             m_Moisture(moist),
                                                                             m_CurrentState{&controller_state} {
    }

    void run() {
        m_CurrentState->run(*this);
    }

    void handleLeft() {
        m_CurrentState->handleLeft(*this);
    }

    void handleRight() {
        m_CurrentState->handleRight(*this);
    }

    void handleClick() {
        m_CurrentState->handleClick(*this);
    }

    void SetState(State *new_state) {
        m_CurrentState = new_state;
    }

    LiquidCrystal_I2C &m_LCD;

    float m_Temperature;
    float m_Moisture;

private:
    State *m_CurrentState;
};


#endif