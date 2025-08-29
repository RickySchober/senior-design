# Waypoint Profiler – Autonomous Water Column Sampling Robot

The **Waypoint Profiler** is an autonomous surface and underwater vehicle designed to help marine researchers collect valuable water column data and samples.  
It can be **launched from shore**, navigate to user-defined GPS waypoints, and perform **vertical dives** to sample oxygen, pH, and other measurements at specified depths.  

---

## Project Overview

- **Motivation**: Traditional methods for sampling water columns (e.g., boat-based deployments) are costly, logistically challenging, and often seasonally limited. The Waypoint Profiler provides a **low-cost, autonomous, and shore-launchable solution**.  
- **Capabilities**:  
  - Navigate across the water surface to **GPS-defined waypoints**.  
  - Perform a **controlled flip maneuver** to transition from surface navigation to vertical diving.  
  - Dive to **user-specified depths** and collect data/samples.  
  - Resurface and return to shore.  

---

## Demo
Video of profiler navigating to gps waypoint.
<p align="center">
  <img src="WaypointNavigation (1).gif" width="600" alt="Waypoint Profiler navigation and dive demo"/>
</p>
Video of profiler flipping oreintation and diving to desired depth.
<p align="center">
  <img src="WaypointNavigation (2).gif" width="600" alt="Waypoint Profiler navigation and dive demo"/>
</p>
The profiler is tethered in both videos with a rope as a failsafe but a final product would be tetherless.
---

##  System Design

- **Surface Navigation**  
  - GPS-based waypoint following  
  - Autonomous motor control for heading and stability  

- **Flip & Dive Mechanism**  
  - Second set of motors applies torque to control robots pitch
  - Smooth transition from horizontal to vertical mode  

- **Sensing & Sampling**  
  - Modular sensor payload based on researchers interest (ph, oxegyn, turbidity, physical samples)
  - IMU provides orientation control while GPS provides position at surface

---

## Component Block Diagram
<p align="center">
  <img src="component block diagram.drawio.png" width="700" alt="Waypoint Profiler Component Block Diagram"/>
</p>

---
## System Architecture

The Waypoint Profiler’s computing and control are split across two levels:

- **Arduino Microcontroller**  
  - Interfaces directly with sensors and actuators.  
  - Handles real-time tasks such as thruster commands, sensor polling (GPS, IMU, depth, pressure, leak detection), and ESC (Electronic Speed Controller) management.  
  - Ensures reliable, low-latency hardware control.  

- **Raspberry Pi (Master Computer)**  
  - Runs higher-level computation in parallel processes.  
  - Implements a **ROS-based state machine** that coordinates surface navigation, diving, and sampling behaviors.  
  - Communicates with the Arduino over USB serial to send commands and receive sensor feedback.  
  - Connects to a **router** for wireless communication with the **Base Station** at water surface.  

This architecture balances **real-time reliability** (Arduino) with **computational flexibility** (Raspberry Pi), allowing robust autonomous operation in a marine environment.  




