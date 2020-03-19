#ifndef __FRAGMENT_AGENT__H
#define __FRAGMENT_AGENT__H 

#include "enviro.h"

using namespace enviro;

class FragmentController : public Process, public AgentInterface {
    // the FragmentController controlls the Fragement class. This
    // class has no defined behavior. It's role is to ocupy space
    // and allow the Leader to push it out of the way.

    public:
    FragmentController() : Process(), AgentInterface() {}

    void init() {}
    void start() {}
    void update() {}
    void stop() {}

};

class Fragment : public Agent {
    public:
    Fragment(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    FragmentController c;
};

DECLARE_INTERFACE(Fragment)

#endif