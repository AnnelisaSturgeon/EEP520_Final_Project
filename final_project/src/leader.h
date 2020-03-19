#ifndef __LEADER_AGENT__H
#define __LEADER_AGENT__H 

#include <string>
#include <math.h>
#include "enviro.h"

using namespace enviro;

class LeaderController : public Process, public AgentInterface {

    public:
    LeaderController() : Process(), AgentInterface() {}

    void init() {
        track = 0;
        count = 0;
        hit = false;
        demolish = false;
        //first_round = true;
        notice_collisions_with("Egg", [&](Event &e) {
            damp_movement();
            hit = true;
            count = 0;
            track = 0;
            //emit(Event("Hit"));
        }); 
        // notice_collisions_with("BadEgg", [&](Event &e) {
        //     damp_movement();
        //     demolish = true;
        //     //emit(Event("Hit"));
        // }); 
    }
    void start() {}
    void update() {

            watch("Target", [this](Event e) {
                target_id = e.value();
            });

            watch("EggPosition", [this](Event e) {
                goal_x = e.value()["x"];
                goal_y = e.value()["y"];
                goal_theta = e.value()["theta"];
            });
            
            watch("BadEggHit", [this](Event e) {
                damp_movement();
                bad_egg_id = e.value();
                watch("BadEggPosition", [this](Event e) {
                    xx = e.value()["x"];
                    yy = e.value()["y"];
                    theta_0 = e.value()["theta"];
                });
                demolish = true;
            });

            //move_toward(goal_x, goal_y);
            if (demolish == true){
                    remove_agent(bad_egg_id);
                    Agent& fragment1 = add_agent("Fragment", xx+0.5, yy+0.5, theta_0+0.5, FRAGMENT_STYLE);
                    Agent& fragment2 = add_agent("Fragment", xx-0.5, yy+0.5, theta_0+0.7, FRAGMENT_STYLE);
                    Agent& fragment3 = add_agent("Fragment", xx, yy, theta_0, FRAGMENT_STYLE);
                    Agent& fragment4 = add_agent("Fragment", xx, yy-0.5, theta_0+0.2, FRAGMENT_STYLE);
                    count = 0;
                    track = 0;
                    demolish = false;
            }

            if (hit == true){
                // if (line == false){
                //     watch("Locate", [this](Event e) {
                //         emit(Event("Target", id()));
                //         emit(Event("TargetPosition", { 
                //             { "x", position().x }, 
                //             { "y", position().y },
                //             { "theta", angle() }
                //         }));
                //         line = true;
                //     });
                // }
                old_x = goal_x;
                old_y = goal_y;
                old_theta = goal_theta;
                remove_agent(target_id);
                Agent& bad_egg = add_agent("BadEgg", goal_x, goal_y, old_theta, BAD_EGG_STYLE);
                
                std::vector<double> pos = ran_num();
                Agent& egg = add_agent("Egg", pos[0], pos[1], 0, EGG_STYLE);
                //goal_x = pos[0];
                //goal_y = pos[1];
                //emit(Event("Hit"));
                hit = false;
                //first_round = false;
            }
            else if (track < 10 || count < 30) {
                // values = sensor_values();
                // //move_toward(goal_x, goal_y);
                // for(int i=0; i<values.size(); i++) {
                //     if (values(i) == "Egg"){
                //         goal = sensor(value)
                //     }
                // }
                if ((sensor_reflection_type(0) == "BadEgg" && sensor_value(0) < 20 ) || (sensor_reflection_type(1) == "BadEgg" && sensor_value(1) < 20 ) || (sensor_reflection_type(2) == "BadEgg" && sensor_value(2) < 20 )|| (sensor_reflection_type(7) == "BadEgg" && sensor_value(7) < 20 ) || (sensor_reflection_type(8) == "BadEgg" && sensor_value(8) < 20 )){
                    track_velocity(0,5);
                    count ++;
                    //move_toward(goal_x, goal_y, 0, 10);
                }
                else if ((sensor_reflection_type(3) == "BadEgg" && sensor_value(3) < 20 ) || (sensor_reflection_type(4) == "BadEgg" && sensor_value(4) < 20 ) || (sensor_reflection_type(5) == "BadEgg" && sensor_value(5) < 20 ) || (sensor_reflection_type(6) == "BadEgg" && sensor_value(6) < 20 )){
                    track_velocity(10,0);
                    //move_toward(goal_x, goal_y, 0, 10);
                }
                else {
                    move_toward(goal_x, goal_y);
                    if (count+3 >= count_old){
                        track ++;
                    }
                    count_old = count;
                }
                
                //while (sensor_reflection_type(0) != "BadEgg" && sensor_value(0) < 40 ){
                //move_toward(goal_x, goal_y);     
                //}
                //if ((sensor_value(0) < 40 || sensor_value(1) < 40 || sensor_value(2) < 40 || sensor_value(3) < 25 || sensor_value(4) < 25) && count < 20){
                //damp_movement(); 
                //move_toward(goal_x, goal_y);   
            }
            else {
                //damp_movement();
                move_toward(goal_x, goal_y);
                // if(sensor_reflection_type(0) == "BadEgg" && sensor_value(0) < 40 ){
                //     damp_movement();
                //     track_velocity(5,0); 
                //     //damp_movement();
                // }
                // else{
                //     track_velocity(0,5);  
                //     //damp_movement(); 
                // }
            }


            // values = sensor_values();
            // if (values(i) == "Egg"){
                
            //     emit(Event("EggCall", line_number));

                // emit(Event(line_number, { 
                //     { "x", position().x }, 
                //     { "y", position().y } 
                // }));

                //goal = sensor(value)
        }
    //values = sensor_values();
    //track_velocity(0,rate);
    //move_toward(goal_x, goal_y);
    void stop() {}

    std::vector<double> ran_num() {
        double x = rand() % 300 + -300;
        double y = rand() % 150 + -150;
        return {x, y};
    }

    

    double goal_x, goal_y, goal_theta;
    double old_x, old_y, old_theta;
    double xx, yy, theta_0;
    bool line;
    bool hit;
    bool first_round;
    int count;
    int count_old;
    int track;
    bool demolish;
    //std::vector<std::string> values;
    int target_id;
    int bad_egg_id;

    const json  EGG_STYLE = { 
                    {"fill", "yellow"}, 
                    {"stroke", "black"}, 
                    {"strokeWidth", "1px"}
               },
               BAD_EGG_STYLE = { 
                    {"fill", "red"}, 
                    {"stroke", "black"}, 
                    {"strokeWidth", "1px"}
               },
                FRAGMENT_STYLE = { 
                    {"fill", "blue"}, 
                    {"stroke", "black"}, 
                    {"strokeWidth", "1px"}
               };
};
            

class Leader : public Agent {
    public:
    Leader(json spec, World& world) : Agent(spec, world) {
        add_process(lc);
    }
    private:
    LeaderController lc;
};

DECLARE_INTERFACE(Leader);

#endif












// #ifndef __LEADER_AGENT__H
// #define __LEADER_AGENT__H 

// #include <string>
// #include <math.h>
// #include "enviro.h"

// using namespace enviro;

// class LeaderController : public Process, public AgentInterface {

//     public:
//     LeaderController() : Process(), AgentInterface() {}

//     void init() {
//         line = false;
//         first_round = true;
//         notice_collisions_with("Egg", [&](Event &e) {
//             hit = true;
//             emit(Event("Hit"));
//         }); 
//         watch("EggPosition", [this](Event e) {
//             goal_x = e.value()["x"];
//             goal_y = e.value()["y"];
//         });
//     }
//     void start() {}
//     void update() {
//             //move_toward(goal_x, goal_y);

//             if (hit == true){
//                 if (line == false){
//                     watch("Locate", [this](Event e) {
//                         emit(Event("Target", id()));
//                         emit(Event("TargetPosition", { 
//                             { "x", position().x }, 
//                             { "y", position().y },
//                             { "theta", angle() }
//                         }));
//                         line = true;
//                     });
//                 }

//                 std::vector<double> pos = ran_num();
//                 Agent& egg = add_agent("Egg", pos[0], pos[1], 0, EGG_STYLE);
//                 goal_x = pos[0];
//                 goal_y = pos[1];
//                 //emit(Event("Hit"));
//                 hit = false;
//                 first_round = false;
//             }
//             else {
//                 move_toward(goal_x, goal_y);
//             }


//             // values = sensor_values();
//             // if (values(i) == "Egg"){
                
//             //     emit(Event("EggCall", line_number));

//                 // emit(Event(line_number, { 
//                 //     { "x", position().x }, 
//                 //     { "y", position().y } 
//                 // }));

//                 //goal = sensor(value)
//         }
//     //values = sensor_values();
//     //track_velocity(0,rate);
//     //move_toward(goal_x, goal_y);
//     void stop() {}

//     std::vector<double> ran_num() {
//         double x = rand() % 300 + -300;
//         double y = rand() % 150 + -150;
//         return {x, y};
//     }

    

//     double goal_x, goal_y;
//     bool line;
//     bool hit = false;
//     bool first_round;

//     const json  EGG_STYLE = { 
//                     {"fill", "yellow"}, 
//                     {"stroke", "black"}, 
//                     {"strokeWidth", "5px"},
//                     {"strokeOpacity", "0.25"}
//                };
// };
            

// class Leader : public Agent {
//     public:
//     Leader(json spec, World& world) : Agent(spec, world) {
//         add_process(lc);
//     }
//     private:
//     LeaderController lc;
// };

// DECLARE_INTERFACE(Leader);

// #endif











// #ifndef __LEADER_AGENT__H
// #define __LEADER_AGENT__H 

// #include <string>
// #include <math.h>
// #include "enviro.h"

// namespace {

//     using namespace enviro;

//     class Chasing : public State, public AgentInterface {
//         public:
//         void entry(const Event& e) {}
//         void during() { 
//             track_velocity(4,0);
//             if ( sensor_value(0) < 40 ) {
//                 emit(Event(tick_name));
//             }            
//         }
//         void exit(const Event& e) {}
//         void set_tick_name(std::string s) { tick_name = s; }
//         std::string tick_name;
//     };

//     class Searching : public State, public AgentInterface {
//         public:
//         void entry(const Event& e) { 
//             //rate = rand() % 2 == 0 ? 2 : -2; 
//             values = sensor_values();
//             }
//         void during() { 
//             for(int i=0; i<values.size(); i++) {
//                 if (values(i) == "Egg"){
//                     goal = sensor(value)
//                 }


//                 }
            


//             values = sensor_values();



//             track_velocity(0,rate); 
//             if ( sensor_value(0) > 140 ) {
//                 emit(Event(tick_name));
//             }
//         }
//         void exit(const Event& e) {}
//         double rate;
//         void set_tick_name(std::string s) { tick_name = s; }
//         std::string tick_name;
//         std::vector<std::string> values        
//     };

//     class LeaderController : public StateMachine, public AgentInterface {

//         public:
//         LeaderController() : StateMachine() {

//             set_initial(searching);
//             tick_name = "tick_" + std::to_string(rand()%1000); // use an agent specific generated 
//                                                                // event name in case there are 
//                                                                // multiple instances of this class
//             add_transition(tick_name, chasing, searching);
//             add_transition(tick_name, searching, chasing);
//             chasing.set_tick_name(tick_name);
//             searching.set_tick_name(tick_name);

//         }

//         Chasing chasing;
//         Searching searching;
//         std::string tick_name;

//     };

//     class Leader : public Agent {

//         public:
//         Leader(json spec, World& world) : Agent(spec, world) {
//             add_process(lc);
//         }

//         LeaderController lc;

//     };

//     DECLARE_INTERFACE(Wanderer);

// }

// #endif













// #ifndef __LEADER_AGENT__H
// #define __LEADER_AGENT__H 

// #include <string>
// #include <math.h>
// #include "enviro.h"

// using namespace enviro;

// class LeaderController : public Process, public AgentInterface {

//     public:
//     LeaderController() : Process(), AgentInterface() {}

//     void init() {
//         notice_collisions_with("Egg", [&](Event &e) {
//             hit = true;
//             //emit(Event("Hit"));
//         }); 
//         watch("EggPosition", [this](Event e) {
//             goal_x = e.value()["x"];
//             goal_y = e.value()["y"];
//         });
//     }
//     void start() {}
//     void update() {
//         move_toward(goal_x, goal_y);

//         if (line == false){
//             watch("Locate", [this](Event e) {
//                 emit(Event("Target", id()));
//                 line = true;
//             });
//         }

//         if (hit == true){
//             std::vector<double> pos = ran_num();
//             Agent& egg = add_agent("Egg", pos[0], pos[1], 0, EGG_STYLE);
//             emit(Event("Hit"));
//             hit = false;
//         }
//         // values = sensor_values();
//         // if (values(i) == "Egg"){
            
//         //     emit(Event("EggCall", line_number));

//             // emit(Event(line_number, { 
//             //     { "x", position().x }, 
//             //     { "y", position().y } 
//             // }));

//             //goal = sensor(value)
//         }
//     //values = sensor_values();
//     //track_velocity(0,rate);
//     //move_toward(goal_x, goal_y);
//     void stop() {}

//     std::vector<double> ran_num() {
//         double x = rand() % 350 + -350;
//         double y = rand() % 200 + -200;
//         return {x, y};
//     }

    

//     double goal_x, goal_y;
//     bool line;
//     bool hit = false;

//     const json  EGG_STYLE = { 
//                     {"fill", "yellow"}, 
//                     {"stroke", "black"}, 
//                     {"strokeWidth", "5px"},
//                     {"strokeOpacity", "0.25"}
//                };
// };
            

// class Leader : public Agent {
//     public:
//     Leader(json spec, World& world) : Agent(spec, world) {
//         add_process(lc);
//     }
//     private:
//     LeaderController lc;
// };

// DECLARE_INTERFACE(Leader);

// #endif