//
// Created by christoph on 03.03.22.
//

#ifndef AUTOGROWER_SETTINGSOVERVIEW_H
#define AUTOGROWER_SETTINGSOVERVIEW_H

#include "State.h"

struct SettingsOverView : public State {
    void run(StateContext&) override;

    void handleLeft(StateContext&) override;

    void handleRight(StateContext&) override;
    void handleClick(StateContext&) override;
};

extern SettingsOverView settings_overview_state;

#endif //AUTOGROWER_SETTINGSOVERVIEW_H
