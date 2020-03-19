#ifndef __EGG_AGENT__H
#define __EGG_AGENT__H 

#include <string>
#include <math.h>
#include "enviro.h"

using namespace enviro;

class EggController : public Process, public AgentInterface {
    // The egg controller class is used to control the egg class. 
    // The egg class does nothing besides emit it's agent id and position.

    public:
    EggController() : Process(), AgentInterface() {}

    void init() {

    }
    void start() {}
    void update() {
        // emit Target event so Leader can read ID
        emit(Event("Target", id()));
        // emit EggPosition event so Leader can read positions
        emit(Event("EggPosition", { 
            { "x", position().x }, 
            { "y", position().y },
            { "theta", angle() }
        }));
    }
    void stop() {}

};

class Egg : public Agent {
    public:
    Egg(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    EggController c;
};

DECLARE_INTERFACE(Egg)

#endif
