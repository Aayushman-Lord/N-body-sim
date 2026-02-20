# Real-Time Gravity Simulator (Accretion, Collision, Orbit Mechanics)

A real-time N-body gravity simulator written in C++ using Raylib.  
This project simulates gravitational interaction, orbital mechanics, elastic and inelastic collisions, accretion, and mass transfer between objects.

Designed for realism, stability, and experimentation.

---

## Important Notice 
This repo is created in c++, MAKEFILE is just used to compile 

---

## Preview

Simulates:

- Planetary orbits
- Object collisions
- Accretion (mass stealing)
- Core merging
- Stable orbital mechanics
- Real-time object spawning

---

## Features

### Core Physics
• Newtonian gravity (inverse square law)  
• Stable Leapfrog integration (energy-preserving)  
• Real-time orbital mechanics  
• Momentum conservation  
• Energy-aware simulation  

### Collision System
• Elastic and inelastic collisions  
• Mass transfer during contact  
• Accretion mechanics  
• Core merging  
• Overlap correction  

### Advanced Mechanics
• Orbit assist system  
• Automatic circular orbit injection  
• Elliptical orbit support  
• Mass-based object growth  
• Density-based radius scaling  

### Visualization
• Real-time rendering  
• Motion trails  
• Velocity vectors  
• Mass-based coloring  
• Camera movement and zoom  

### Interactive Controls
• Spawn objects with mouse drag  
• Pause and time control  
• Camera navigation  
• Orbit injection  

---

## Physics Model

### Newton's Law of Gravitation

F = G * (m₁ m₂) / r²

Acceleration:

a = G * m / r²

---

### Leapfrog Integration

Used for high stability and energy conservation.

Steps:

v(t + dt/2) = v(t) + a(t) dt/2  
x(t + dt) = x(t) + v(t + dt/2) dt  
v(t + dt) = v(t + dt/2) + a(t + dt) dt/2  

This prevents orbital decay.

---

### Collision Impulse Equation

Impulse:

j = -(1 + e)(v · n) / (1/m₁ + 1/m₂)

Ensures momentum conservation.

---

### Orbital Velocity Equation

Circular orbit velocity:

v = sqrt(GM / r)

Used in orbit assist system.

---

## Controls

| Key | Action |
|----|--------|
| Mouse Drag | Spawn object |
| C | Circular orbit assist |
| E | Elliptical orbit assist |
| + | Increase time speed |
| - | Decrease time speed |
| SPACE | Pause simulation |
| WASD | Move camera |
| Mouse Wheel | Zoom |
| V | Toggle trails |

---

## Object Behavior

Objects can:

• Orbit  
• Collide  
• Merge  
• Steal mass  
• Grow in size  
• Form stable systems  

Large objects naturally consume smaller ones.

---

## Object Color Meaning

| Color | Mass Range |
|------|------------|
| Red | Small |
| Yellow | Medium-small |
| Orange | Medium |
| Blue | Large |
| Purple | Very large |
| White | Massive |
| Gray | Extreme |

---

## Technologies Used

• C++  
• Raylib  
• Classical mechanics  
• Leapfrog integrator  
• Real-time physics  

---

## Why Leapfrog Integration?

Leapfrog is used because it:

• preserves energy  
• prevents orbit decay  
• is used in real astrophysics simulations  
• is far more stable than Euler integration  

Used in:

• NASA simulations  
• astrophysics engines  
• orbital mechanics  

---

## Installation

Install Raylib:

https://www.raylib.com/

---

## Compile

Press F5 


---

## Run

GravitySim.exe


---

## Example Scenarios You Can Create

• Solar systems  
• Binary star systems  
• Planet collisions  
• Accretion disks  
• Orbit capture  
• Multi-body chaos  

---

## Future Improvements

• Black holes  
• Relativistic physics  
• Field visualization  

---


---

## Author

Aayushman

---

## License

MIT License

---

## Educational Purpose

This simulator demonstrates:

• orbital mechanics  
• gravity physics  
• collision physics  
• accretion  
• numerical integration  

---

## Inspiration

Astrophysics, orbital mechanics, and real N-body simulations.

---

## Contributing

Contributions welcome.
You can improve physics accuracy, performance, or visualization.

