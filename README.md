# **Broad Localization Algorithm for Mobile Robots**
**Languages & Tools:** C++, CMake, Ninja, Docker  

---

## **Overview of the Project**

This project implements a **coordinate-based perimeter localization algorithm** designed for warehouse automation and autonomous mobile robots.  
The algorithm enforces geographic boundary constraints with six-decimal precision for both latitude and longitude. When a robot’s GPS coordinates exceed the defined perimeter, the system triggers a **fault event** and can issue a **safety shutdown command** to prevent further operation beyond designated areas.

The purpose of this project is to provide a lightweight and modular safety mechanism that integrates with existing robot control systems, allowing for efficient spatial validation without requiring extensive sensor fusion or SLAM frameworks.

---

## **Use Cases for the Project**

- **Warehouse Automation:** Enforce safety zones or restricted areas for autonomous vehicles operating near humans or sensitive equipment.  
- **Outdoor Robotics:** Provide perimeter enforcement for field robots or delivery drones operating in GPS-defined zones.  
- **Simulation & Testing:** Integrate into simulation environments to validate fault detection and shutdown behavior before deployment.  
- **Fleet Management Systems:** Extend functionality to monitor multiple robots and apply coordinate-based constraints from a central control server.

---

## **Technical Overview**

The algorithm uses a **static perimeter model** defined by latitude and longitude pairs. Each robot continuously compares its current GPS position to the boundary polygon, using a simple but precise geospatial check at six-decimal accuracy (≈10 cm resolution).  

When a violation is detected:  
1. A **fault code** is triggered to log the boundary breach.  
2. A **shutdown sequence** is executed if the robot remains outside the boundary beyond a configurable threshold duration.  
3. A **reset flag** is provided to clear the fault upon re-entry into the safe zone.  

The entire system is implemented in native C++ for high performance and minimal latency, with build automation through **CMake** and **Ninja** for portability across platforms.  

---

## **Project Weaknesses**

- Currently depends solely on GPS coordinates (no IMU or SLAM integration).  
- Requires pre-defined perimeter coordinates — no dynamic boundary updates at runtime.  
- Tested in simulation and standalone mode only; hardware-integration layer still under development.  

Future versions will incorporate IMU fusion for drift correction and runtime reconfiguration of safe zones through network commands.

---

## **Running the Project**

To build and execute the localization system locally:  
```bash
git clone https://github.com/JeramayaGramby/broadLocalization
cd broadLocalization
mkdir build && cd build
cmake ..
ninja
./localization
