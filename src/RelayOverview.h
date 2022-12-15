//
// Created by christoph on 03.03.22.
//

#ifndef AUTOGROWER_RELAYOVERVIEW_H
#define AUTOGROWER_RELAYOVERVIEW_H

#include "State.h"

struct RelayOverView : public State {
    void run(StateContext&) override;

    void handleLeft(StateContext&) override;

    void handleRight(StateContext&) override;
    void handleClick(StateContext&) override;
};

extern RelayOverView relay_overview_state;

#endif //AUTOGROWER_RELAYOVERVIEW_H
