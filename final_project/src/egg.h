#ifndef __EGG_AGENT__H
#define __EGG_AGENT__H 

#include <string>
#include <math.h>
#include "enviro.h"

using namespace enviro;

class EggController : public Process, public AgentInterface {

    public:
    EggController() : Process(), AgentInterface() {}

    void init() {

    }
    void start() {}
    void update() {
        emit(Event("Target", id()));
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








// #ifndef __EGG_AGENT__H
// #define __EGG_AGENT__H 

// #include <string>
// #include <math.h>
// #include "enviro.h"

// using namespace enviro;

// class EggController : public Process, public AgentInterface {

//     public:
//     EggController() : Process(), AgentInterface() {}

//     void init() {
//         phase = "waiting";
//         emit(Event("EggPosition", { 
//             { "x", position().x }, 
//             { "y", position().y }
//         }));
//         // notice_collisions_with("Leader", [&](Event &e) { 
//         //     emit(Event("Locate")); 
//         //     watch("Target", [this](Event e) {
//         //         Agent& target = find_agent(e.value());
//         //         attach_to(target);
//         //         phase = "last"; 
//         //     });
//         // }); 
//     }
//     void start() {}
//     void update() {

//         if (phase == "hit"){ 
//             watch("Target", [this](Event e) {
//                 Agent& target = find_agent(e.value());
//                 watch("TargetPosition", [this](Event e) {
//                     x = e.value()["x"];
//                     y = e.value()["y"];
//                     theta = e.value()["angle"];
                    


//                     teleport(goal_x, goal_y, theta);
//                 });
//                 Agent& target = find_agent(e.value());
//                 attach_to(target);
//                 //phase = "hit";
//             });
//             phase = "last"; 
//         }  
//         else if (phase == "waiting"){   
//             // emit(Event("EggPosition", { 
//             //     { "x", position().x }, 
//             //     { "y", position().y }
//             // }));
//             watch("Hit", [this](Event e) {
//                 emit(Event("Locate")); 
//                 // watch("Target", [this](Event e) {
//                 //     Agent& target = find_agent(e.value());
//                 //     phase = "hit";
//                 // });
//                 phase = "hit";
//             });
//         }
//         else if (phase == "last"){
//             watch("Locate", [this](Event e) {
//                 emit(Event("Target", id()));
//                 phase = "chain";
//             });
//         }

//             // emit(Event(line_number, { 
//             //     { "x", position().x }, 
//             //     { "y", position().y } 
//             // }));
//     }
//     void stop() {}
//     std::string phase;
//     double x, y, z, theta;
//     double goal_x, goal_y;
// };

// class Egg : public Agent {
//     public:
//     Egg(json spec, World& world) : Agent(spec, world) {
//         add_process(c);
//     }
//     private:
//     EggController c;
// };

// DECLARE_INTERFACE(Egg)

// #endif














// #ifndef __EGG_AGENT__H
// #define __EGG_AGENT__H 

// #include <string>
// #include <math.h>
// #include "enviro.h"

// using namespace enviro;

// class EggController : public Process, public AgentInterface {

//     public:
//     EggController() : Process(), AgentInterface() {}

//     void init() {
//         phase = "waiting";
//         emit(Event("EggPosition", { 
//             { "x", position().x }, 
//             { "y", position().y }
//         }));
//         // notice_collisions_with("Leader", [&](Event &e) { 
//         //     emit(Event("Locate")); 
//         //     watch("Target", [this](Event e) {
//         //         Agent& target = find_agent(e.value());
//         //         attach_to(target);
//         //         phase = "last"; 
//         //     });
//         // }); 
//     }
//     void start() {}
//     void update() {

//         if (phase == "hit"){ 
//             watch("Target", [this](Event e) {
//                 Agent& target = find_agent(e.value());
//                 watch("TargetPosition", [this](Event e) {
//                     x = e.value()["x"];
//                     y = e.value()["y"];
//                     theta = e.value()["angle"];
                    


//                     teleport(goal_x, goal_y, theta);
//                 });
//                 Agent& target = find_agent(e.value());
//                 attach_to(target);
//                 //phase = "hit";
//             });
//             phase = "last"; 
//         }  
//         else if (phase == "waiting"){   
//             // emit(Event("EggPosition", { 
//             //     { "x", position().x }, 
//             //     { "y", position().y }
//             // }));
//             watch("Hit", [this](Event e) {
//                 emit(Event("Locate")); 
//                 // watch("Target", [this](Event e) {
//                 //     Agent& target = find_agent(e.value());
//                 //     phase = "hit";
//                 // });
//                 phase = "hit";
//             });
//         }
//         else if (phase == "last"){
//             watch("Locate", [this](Event e) {
//                 emit(Event("Target", id()));
//                 phase = "chain";
//             });
//         }

//             // emit(Event(line_number, { 
//             //     { "x", position().x }, 
//             //     { "y", position().y } 
//             // }));
//     }
//     void stop() {}
//     std::string phase;
//     double x, y, z, theta;
//     double goal_x, goal_y;
// };

// class Egg : public Agent {
//     public:
//     Egg(json spec, World& world) : Agent(spec, world) {
//         add_process(c);
//     }
//     private:
//     EggController c;
// };

// DECLARE_INTERFACE(Egg)

// #endif













// #ifndef __EGG_AGENT__H
// #define __EGG_AGENT__H 

// #include <string>
// #include <math.h>
// #include "enviro.h"

// using namespace enviro;

// class EggController : public Process, public AgentInterface {

//     public:
//     EggController() : Process(), AgentInterface() {}

//     void init() {
//         phase = "waiting";
//         // notice_collisions_with("Leader", [&](Event &e) { 
//         //     emit(Event("Locate")); 
//         //     watch("Target", [this](Event e) {
//         //         Agent& target = find_agent(e.value());
//         //         attach_to(target);
//         //         phase = "last"; 
//         //     });
//         // }); 
//     }
//     void start() {}
//     void update() {

//         if (phase == "hit"){ 
//                 watch("Target", [this](Event e) {
//                     Agent& target = find_agent(e.value());
//                     attach_to(target);
//                     phase = "hit";
//                 });
//             phase = "last"; 
//         }  
//         else if (phase == "waiting"){   
//             emit(Event("EggPosition", { 
//                 { "x", position().x }, 
//                 { "y", position().y }
//             }));
//             watch("Hit", [this](Event e) {
//                 emit(Event("Locate")); 
//                 // watch("Target", [this](Event e) {
//                 //     Agent& target = find_agent(e.value());
//                 //     phase = "hit";
//                 // });
//                 phase = "hit";
//             });
//         }
//         else if (phase == "last"){
//             watch("Locate", [this](Event e) {
//                 emit(Event("Target", id()));
//                 phase = "chain";
//             });
//         }

//             // emit(Event(line_number, { 
//             //     { "x", position().x }, 
//             //     { "y", position().y } 
//             // }));
//     }
//     void stop() {}
//     std::string phase;
// };

// class Egg : public Agent {
//     public:
//     Egg(json spec, World& world) : Agent(spec, world) {
//         add_process(c);
//     }
//     private:
//     EggController c;
// };

// DECLARE_INTERFACE(Egg)

// #endif


// #include <string>
// #include <math.h>
// #include "enviro.h"

// namespace {

//     using namespace enviro;

//     class Following : public State, public AgentInterface {
//         public:
//         void entry(const Event& e) {}
//         void during() { 
//             // track_velocity(4,0);
//             // if ( sensor_value(0) < 40 ) {
//             //     emit(Event(tick_name));
//             // }            
//         }
//         void exit(const Event& e) {}
//         void set_tick_name(std::string s) { tick_name = s; }
//         std::string tick_name;
//     };

//     class Waiting : public State, public AgentInterface {
//         public:
//         void entry(const Event& e) { 
//             emit(Event("EggPosition", { 
//                 { "x", position().x }, 
//                 { "y", position().y }
//             }));
//         }
//         void during() { 
//             // emit(Event("EggPosition", { 
//             //     { "x", position().x }, 
//             //     { "y", position().y }
//             // }));
//         }
        
//         void exit(const Event& e) {
//             //emit(Event(tick_name));
//             //watch("goal_change", [this](Event e) {}
//         }
//         double rate;
//         void set_tick_name(std::string s) { tick_name = s; }
//         std::string tick_name;        
//     };

//     class EggController : public StateMachine, public AgentInterface {

//         public:
//         EggController() : StateMachine() {

//             set_initial(waiting);
//             tick_name = "tick_" + std::to_string(rand()%1000); // use an agent specific generated 
//                                                                // event name in case there are 
//                                                                // multiple instances of this class
//             add_transition(tick_name, waiting, following);
//             //add_transition(tick_name, rotating, moving_forward);
//             following.set_tick_name(tick_name);
//             waiting.set_tick_name(tick_name);

//         }

//         Following following;
//         Waiting waiting;
//         std::string tick_name;

//     };

//     class Egg : public Agent {

//         public:
//         Egg(json spec, World& world) : Agent(spec, world) {
//             add_process(ec);
//         }

//         EggController ec;

//     };

//     DECLARE_INTERFACE(Egg);

// }

// #endif