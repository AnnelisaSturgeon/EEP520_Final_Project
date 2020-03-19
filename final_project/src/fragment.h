#ifndef __FRAGMENT_AGENT__H
#define __FRAGMENT_AGENT__H 

#include "enviro.h"

using namespace enviro;

class FragmentController : public Process, public AgentInterface {

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