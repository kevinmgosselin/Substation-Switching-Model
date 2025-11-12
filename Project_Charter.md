# Summary
This page documents the guidelines for a model of the distribution side of a transmission-to-distribution substation. The model will start from
the low-side of a single transformer bank, with three "phases" of wire energized by 12V DC. The functional parts of the model will be multiple
switching elements, typical of a realistic switchard. These elements will include, but may not be limited to: air-break switches, knife switches,
circuit breakers, and reclosers. These switches will be tripped by faults following a realistic switching schema, responding to faults quickly 
and in a manner that isolates equipment and customers from faults appropriately. Faults will be simulated using either a creation of ground-fault
current or by user input. The model will be controlled by an esp32 module, which will handle the physical model operation and network interfaces.

# Guiding Statement
This project was not necessarily started to solve a problem that I'm seeing at work, like switching issues, clarity about substation operation,
or model-to-field drift. Rather, it was born out of an urge to build a project to completion that would require learning skills that I
do not currently have. I believe that by seeing a relatively large, indepedent project through and learning along the way, I will have proved to
myself that I am capable of taking on issues that I do not yet know how to solve.

I am considering this a passion project, as I find the interaction between the seen and unseen world of electrical engineering fascinating. 
I'd like to be able to demonstrate to others how powerful this capability to cross the barrier between code and creation really is through a live,
working model. For example, detecting and locating a fault (software) and then isolating it with physical breaker action that you can perceive
with your senses (hardware).

# Objectives
I do not want this project to have an "end point", where I can walk into my room and say, "This project is complete. When should I disassemble
it to clear up my workspace again?" Rather, I'd like to establish a goal for the project as a point of motivation, knowing that when I reach the
goal I can allow myself the satisfaction of having created a working model, but that room for additions and improvements still remain.
## Skill Objectives
I'd like to become moderately proficient in the following skills:
- 3D modeling with Fusion
- Object Oriented Programming using C++ and esp32
- Management of electrical hardware (soldering, perfboards, etc)
## Software Objectives
- Determine and update the state of the system, even after loss of switchard power
- Permit user input via:
  - Physical interface (buttons, rotary encorder, etc)
  - Online dashboard
- As determined by user input or faults, trip switches and carry out realistic reclosing schemes
  - A soft objective is to have fault location be identifiable and have appropriate switching schemes automatically executed
- Display state information on:
  - A 128x32 OLED for basic state information
  - A web dashboard
## Hardware Objectives
- Dynamic models:
  - An air break switch (from the transformer low-side)
    - Three phase operated by a single servo with limit switches to confirm close position
  - Capacitor bank switch
  -   Three phase operated by a single servo with limit switches to confirm close position
  -   A bus rail will will link the capacitor bank switch to the phases
  - Circuit breaker
    - Three phases will be fed to the single breaker mechanism
    - Partially enclosed in a box, with one face missing/enclosed by transparent material
    - Some sort of rapid-open mechanism
  - Transfer bus tie
  - Distribution recloser
- Static Models:
  - Realistic structures supporting the aforementioned dynamic models
  - Perforated metal baseplate to serve as the network ground
  - Visually interesting load elements for each phase
  - Visible and audible indicators  of system state and state changes
    - For example, a strobing LED and buzzer when an element is being energized
# Safety
Few things are more critical than safe operation of the model. The hazards presented in the construction and operation
are primarily as follows:
- Fire
- Electric Shock
- Toxic or otherwise noxious vapors
- Burns

To mitigate risks of fire and electric shock the system will operate on a fused 12V DC circuit with a 10A DC circuit breaker
and be physically isolated from mains voltage when unattended.
To mitigate risks of noxious vapor inhalation, soldering will be performed either outside, or in proximity to an open window
with a fan actively circulating area through the workspace. To mitigate risks of burns, work gloves will be used when utilizing
the soldering iron.



