#ifndef __LEADER_AGENT__H
#define __LEADER_AGENT__H 

#include <string>
#include <math.h>
#include "enviro.h"

using namespace enviro;

class LeaderController : public Process, public AgentInterface {
    // The controller class for the leader class.
    // the leader will chase an egg, remove that egg upon contact, replace
    // the removed egg with a bad egg, and create a new egg to chase. If 
    // the leader gets stuck and is forced to touch a bad egg, the bad egg
    // will be removed and replaced with 5 fragments. The leader can touch and
    // move the fragments without any furthur consiquence.
    public:
    LeaderController() : Process(), AgentInterface() {}

    void init() {
        // set initial variables
        count = 0; 
        temp = 0; 
        hit = false;  
        demolish = false;  

        // watch for collisions with the Egg class
        notice_collisions_with("Egg", [&](Event &e) {
            damp_movement();
            hit = true;
            count = 0; // reset variable
        }); 
    }
    void start() {}
    void update() {

            // watch for Target event from Egg to get ID
            watch("Target", [this](Event e) {
                target_id = e.value();
            });

            // watch for EggPosition event from Egg to get Egg positions
            watch("EggPosition", [this](Event e) {
                goal_x = e.value()["x"];
                goal_y = e.value()["y"];
                goal_theta = e.value()["theta"];
            });

            // watch for BadEggHit event from BadEgg to initialize fragmentation
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

            // loop to reset vaiables when obsticals are no longer in the way
            if (temp > 5) {
                count = 0;
                temp = 0;
            }

            // loop to demolish and reset variables
            if (demolish == true){
                    demo();
                    // reset variables
                    count = 0; 
                    temp = 0; 
                    demolish = false; 
            }

            // loop to initiate hit egg removal and replacement
            if (hit == true){
                new_egg();
                hit = false;
            }

            // loop to coordinate movement that is unstuck or has not been stuck for more than 20 counts
            if (count < 20) {
                // loop for rotation when a BadEgg is in front sensor range
                if ((count < 15) && ((sensor_reflection_type(0) == "BadEgg" && sensor_value(0) < 20 ) || (sensor_reflection_type(1) == "BadEgg" && sensor_value(1) < 20 ) || (sensor_reflection_type(2) == "BadEgg" && sensor_value(2) < 20 ) || (sensor_reflection_type(7) == "BadEgg" && sensor_value(7) < 20 ) || (sensor_reflection_type(8) == "BadEgg" && sensor_value(8) < 20 ) || (sensor_reflection_type(8) == "BadEgg" && sensor_value(8) < 20 ) || (sensor_reflection_type(10) == "BadEgg" && sensor_value(10) < 20 ))){
                    track_velocity(0,8);
                    count ++;
                    temp = 0;
                }
                // loop for moving forward when a BadEgg is in side sensor range
                else if ((count < 15) && (((sensor_reflection_type(3) == "BadEgg" && sensor_value(3) < 20 ) || (sensor_reflection_type(4) == "BadEgg" && sensor_value(4) < 20 ) || (sensor_reflection_type(5) == "BadEgg" && sensor_value(5) < 20 ) || (sensor_reflection_type(6) == "BadEgg" && sensor_value(6) < 20 )))) {
                    track_velocity(10,0);
                }
                // loop for rotation when a BadEgg has been in sensor range for more that 15 counts
                else if (count >= 15 && count < 20) {
                    track_velocity(0,10);
                    count ++;
                    temp = 0;
                }
                // loop moving twards egg when BadEggs are not in sensor range, or 
                // when a BadEgg has been in sensor range for more 20 counts
                else {
                    move_toward(goal_x, goal_y);
                    count ++;
                    temp ++;                    
                }  
            }
            // loop for stuck movement. Leader no longer cares about hitting BadEggs
            else {
                move_toward(goal_x, goal_y);
                temp ++;
            }
        }
    void stop() {}

    // method to remove BadEgg that has been hit and create fragments
    void demo() {
        remove_agent(bad_egg_id);
        Agent& fragment1 = add_agent("Fragment", xx, yy, theta_0, FRAGMENT_STYLE);
        Agent& fragment2 = add_agent("Fragment", xx, yy, theta_0, FRAGMENT_STYLE);
        Agent& fragment3 = add_agent("Fragment", xx, yy, theta_0, FRAGMENT_STYLE);
        Agent& fragment4 = add_agent("Fragment", xx, yy, theta_0, FRAGMENT_STYLE);
        Agent& fragment5 = add_agent("Fragment", xx, yy, theta_0, FRAGMENT_STYLE);
    }

    // method to remove hit egg, replace with a bad egg, and add new egg
    void new_egg() {
        // capture hit eggs position
        old_x = goal_x;
        old_y = goal_y;
        old_theta = goal_theta;
        // remove egg and replace with bad egg
        remove_agent(target_id);
        Agent& bad_egg = add_agent("BadEgg", goal_x, goal_y, old_theta, BAD_EGG_STYLE);
        // add new egg in random position
        std::vector<double> pos = ran_num();
        Agent& egg = add_agent("Egg", pos[0], pos[1], 0, EGG_STYLE);
    }

    // method to generate ranom x and y positions
    std::vector<double> ran_num() {
        double x = rand() % 741 + (-370);
        double y = rand() % 541 + (-270);
        return {x, y};
    }

    // json styles for adding Agents during simulation
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

    private:
    // trigger variables
    bool demolish;
    bool hit;
    // agent position variables
    double goal_x, goal_y, goal_theta;
    double old_x, old_y, old_theta;
    double xx, yy, theta_0;
    // agent id variables 
    int target_id;
    int bad_egg_id;
    // indexing variables
    int count;
    int temp;  
};
            
// Leader class defines the leader type
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