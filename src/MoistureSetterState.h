//
// Created by christoph on 03.03.22.
//

#ifndef AUTOGROWER_MOISTURESETTERSTATE_H
#define AUTOGROWER_MOISTURESETTERSTATE_H

#include "State.h"

struct MoistureSetter : public State {
    void run(StateContext&) override;

    void handleLeft(StateContext&) override;

    void handleRight(StateContext&) override;
    void handleClick(StateContext&) override;
};

extern MoistureSetter moisture_setter_state;

#endif //AUTOGROWER_MOISTURESETTERSTATE_H
