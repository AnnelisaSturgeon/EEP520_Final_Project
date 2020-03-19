# EEP520_Final_Project

Overview
===
The goal of this project was to create a simulation of a Leader agent that is locked in a rectangular room, whose goal it is to find one egg at a time. When the leader comes in contact with the egg, it turns into a “bad egg” and a new egg is created for the leader to seek. During the leader’s quest for each new egg, it tries to avoid contact with all the bad egg because the bad eggs will fracture upon contact into 5 pieces of equal size to the original bad egg. The leader wants to avoid this as much as possible because the egg fragments take up 5 times the amount of space as a bad egg. Once a bad egg has fractured, i’s pieces turn blue. The leader can come in contact with them and move them out of the way without any consequence. The leader’s goal is to capture as many eggs as possible before being crushed or completely stuck by all the bad eggs and fragment trapped in the room. 

Challenges
===
The biggest challenge faced with this project was figuring out how to refine the leader’s motion and sensing abilities to efficiently search for the egg while avoiding the bad eggs. I spent a lot of time fine tuning the leader’s movement to prevent it from getting stuck for too long, while giving it enough time to get itself unstuck if possible. I addressed this challenge through a combination of sensors, for loop conditions with different types of movement (rotational, forward, tracking), and indexing variables. All these pieces were then iterated and fine-tuned to work in harmony with one another to create adequate movement around the obstacles and collision with the obstacles when the leader is stuck for a set amount of cycles.   

I also struggled with creating and timing the watching events in combination with the destructions and addition of agents during the simulation. All of the removals and addition of agents were triggered by watch events or collision events. It took me a while to realize my simulation was not working because I put the addition and removal of agents directly into the watch and collision events.  I resolved this by creating Boolean values that set to true when the events were triggered and putting the agent additions and removals into for loops set to the Boolean values. 


Instalation
===

Start by cloning the git repository.

Then start the docker image environment
```bash
docker run -p80:80 -p8765:8765 -v $PWD/EEP520_Final_Project:/source -it klavins/enviro:v1.61 bash

```
Then navigate to the file, start the environment, compile the file, and ititate the enviro
```bash
cd final_project
esm start
make
enviro
```
This will start the the simulation. 
To view the simulation open a web browser and trype in http://localhost/

Running the Simulation
===

The simulation will run automatically. There are no user commands needed. Simply watch and enjoy the leaders progress.

===

Outside Sources of Information
===
This project is built off of enviro: https://github.com/klavinslab/enviro

It also uses math.h and string

Code
===

The code has 4 agent types:
  Leader
  Egg
  BadEgg
  Fragment
  
The Leader is the main player in the simulation. The leader will chase an egg, remove that egg upon contact, replace the removed egg with a bad egg, and create a new egg to chase. If the leader gets stuck and is forced to touch a bad egg, the bad egg will be removed and replaced with 5 fragments. The leader can touch and move the fragments without any furthur consiquence.

The Egg is created and destroyed by the leader. It's only functionality is to transmit its agnet id and position to the leader. 

The BadEgg is created and destroyed by the leader. It watches for collisions with the leader, then notifies the leader of its agnet id and position to the leader. 

The Fragment has no functionality. Five fragments are created by the leader upon collision with a bad egg. 

