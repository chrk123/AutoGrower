//
// Created by christoph on 03.03.22.
//

#ifndef AUTOGROWER_TEMPERATURESETTERSTATE_H
#define AUTOGROWER_TEMPERATURESETTERSTATE_H

#include "State.h"

struct TemperatureSetter : public State {
    void run(StateContext&) override;

    void handleLeft(StateContext&) override;

    void handleRight(StateContext&) override;

    void handleClick(StateContext&) override;
};

extern TemperatureSetter temperature_setter_state;

#endif //AUTOGROWER_TEMPERATURESETTERSTATE_H
