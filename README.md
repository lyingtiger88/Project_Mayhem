# Project Mayhem

> **AI agents and contributors: start with [AGENTS.md](AGENTS.md), then read [HANDOFF.md](HANDOFF.md).**
>
> Architecture and delivery plan: [Docs/ARCHITECTURE.md](Docs/ARCHITECTURE.md) and [Docs/ROADMAP.md](Docs/ROADMAP.md).
> Free realistic asset workflow: [Docs/ASSET_PIPELINE.md](Docs/ASSET_PIPELINE.md).
> Gang/faction gameplay design: [GANG_SYSTEM.md](GANG_SYSTEM.md).
> Animal and wildlife gameplay design: [ANIMAL_SYSTEM.md](ANIMAL_SYSTEM.md).
> Procedural and physics-assisted animation design: [ANIMATION_SYSTEM.md](ANIMATION_SYSTEM.md).

Open-world action game prototype built with Unreal Engine 5.8 and C++.

## Approved product direction

- Realistic-world inspiration.
- High-end PC and current-generation console target.
- Massive multi-region world ambition.
- Balanced focus across story, action, player freedom, and systemic simulation.
- Single-player first, with a future multiplayer path considered in the architecture.

## Project rules

- Keep this repository independent from other game projects.
- Gameplay systems are implemented in C++; Blueprint is not the implementation target.
- Prefer modular systems that can be tested independently.
- Do not claim a system is complete until it has been compiled and tested in Unreal Engine.
- Distinguish committed source from validated Unreal builds.

## Initial implementation

The Unreal project descriptor is at the repository root. C++ source is in Source/ProjectMayhem/.

The first core services are:
- UPMWorldEventSubsystem: event publication and bounded recent-event history.
- UPMEntityIdentityComponent: stable GUID identity for Actors.
- UPMWorldClockSubsystem: world-local game time, day progress, pause, and time scale.

These are foundation primitives, not completed gameplay systems.

## Core architecture

- **Core**: game mode, game state, shared gameplay configuration and core services.
- **Player**: player character, controller, interaction and combat interfaces.
- **Vehicles**: vehicle pawn and driving interface.
- **Crime**: crime events, witnesses, wanted level, police response.
- **AI / Pedestrians**: pedestrian navigation, crossing and vehicle-aware avoidance.
- **AI / Drivers**: driver personality, route selection, hazard assessment and vehicle control.
- **World / Road Network**: road segments, lanes, intersections, legal connections and speed limits.
- **Missions**: objectives, mission state and progression.
- **Economy**: money, inventory and shops.
- **Save**: persistent player and world state.

## Driving and navigation design

Navigation is split into three distinct concerns:

1. **Goal selection** — reach a destination, flee from a threat, pursue/attack a target, evade police, assist an injured person, or recover from being stuck.
2. **Route planning** — ordinary drivers follow a road graph and lane/intersection connections. NavMesh is used for pedestrians and, only where a vehicle-compatible navigation setup and terrain checks allow it, off-road detours.
3. **Vehicle control** — follows the planned route through steering, braking and throttle. Walking-character AI MoveTo must not be used as a substitute for vehicle physics/control.

Ordinary drivers usually obey road rules and avoid pedestrians. Personality and situation modify their behavior:
- **Law-abiding**: follows lanes, speed limits and traffic signals; brakes for hazards.
- **Cautious**: leaves larger gaps and slows early.
- **Aggressive/criminal**: may speed, ignore rules, flee or take a viable off-road detour.
- **Panic-prone**: may brake late, swerve or make poor choices under fear, but should still respect basic collision and movement constraints.

## Implementation order

1. Generate project files and compile the C++ scaffold in Unreal Engine 5.8.
2. Establish shared gameplay types and a crime-reporting subsystem.
3. Implement wanted-level tracking and police response hooks.
4. Build the road graph and road-following driver navigation.
5. Add pedestrian routing, crossing and vehicle-aware avoidance.
6. Add driver personalities, fear, fleeing, pursuit and situational detours.
7. Add missions, economy and save/load.
8. Compile and test each integrated milestone in Unreal Engine 5.8.

## First district setup

The editor script at Content/Python/Build_PM_FirstDistrict.py creates a repeatable urban greybox from Unreal's built-in primitive meshes. Follow Docs/ASSET_PIPELINE.md for plugin setup and execution. The greybox is a gameplay prototype, not final photorealistic art.

## Current status

The repository now contains a minimal Unreal Engine 5.8 project scaffold and initial C++ core primitives. The scaffold has not yet been compiled or tested in Unreal Engine. No playable build is claimed.
