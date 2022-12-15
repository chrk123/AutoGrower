#ifndef MENU_H
#define MENU_H

class StateContext;

struct State {
    virtual void run(StateContext &) = 0;

    virtual void handleLeft(StateContext &) = 0;

    virtual void handleRight(StateContext &) = 0;

    virtual void handleClick(StateContext &) = 0;

    virtual ~State() = default;
};

#endif