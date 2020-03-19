#ifndef __BAD_EGG_AGENT__H
#define __BAD_EGG_AGENT__H 

#include "enviro.h"

using namespace enviro;

class BadEggController : public Process, public AgentInterface {
    // The BadEgg class is the controller for the BadEgg class.
    // Its only behavior is to watch for collisions with the leader,
    // then notify the leader of its ID and Position so the leader can
    // destroy it. 

    public:
    BadEggController() : Process(), AgentInterface() {}

    void init() {
        // watching for collisions with the leader
        notice_collisions_with("Leader", [&](Event &e) {
            emit(Event("BadEggHit", id()));
            emit(Event("BadEggPosition", { 
                { "x", position().x }, 
                { "y", position().y },
                { "theta", angle() }
            }));
        }); 
    }
    void start() {}
    void update() {}
    void stop() {}

};

class BadEgg : public Agent {
    public:
    BadEgg(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    BadEggController c;
};

DECLARE_INTERFACE(BadEgg)

#endif