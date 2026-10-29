# Project Mayhem — Agent Handoff

This file is the starting point for any shared AI agent or contributor working on this repository. Read this file and `README.md` before making changes.

## Project identity

- Repository: `lyingtiger88/Project_Mayhem`
- Engine target: Unreal Engine 5.8
- Implementation language: C++ only for gameplay logic
- Genre: open-world action game inspired by GTA-style systemic gameplay
- Default branch: `main`

## Important scope rule

Project Mayhem is an independent project. Do not merge its assumptions, source files, architecture, or task history with the user's other Unreal projects unless the user explicitly asks.

## Verified repository state

At handoff creation, the repository was empty before the initial documentation commit. The current known commit adds only `README.md` with the agreed architecture and roadmap.

- Architecture documented: yes
- Gameplay C++ source files present: not yet verified; the repository was empty before README was added, so treat gameplay source as not implemented unless a fresh repository inspection proves otherwise
- Unreal project file (`.uproject`): not present in the initial empty repository
- Build/test status: not run; do not claim compilation or a playable build

Before implementing code, inspect the latest repository tree and commit history. Do not assume the project module name. If there is no `.uproject`, do not invent a module export macro or claim code is ready to compile. Ask for or establish the actual Unreal project/module identity before adding engine source that depends on it.

## Agreed gameplay requirements

### Pedestrians
- Use NavMesh for walkable-space navigation.
- Choose sensible destinations and avoid standing in vehicle paths.
- Include vehicle-aware hazard checks and crossing decisions; RVO alone is not enough.
- React to nearby traffic and danger without constantly replanning or oscillating.

### Drivers
- Ordinary drivers should generally follow roads, lanes, intersections, speed limits, and traffic signals.
- A road graph/network is required for normal vehicle routes; splines alone are not a complete road network.
- Vehicle movement must use vehicle steering/throttle/brake control, not walking-character `AI MoveTo` as a substitute.
- Driver personality and context affect decisions: cautious drivers slow early; aggressive/criminal drivers may break rules; frightened drivers can panic, brake suddenly, or swerve.
- For appropriate goals, drivers may take a viable sidewalk-adjacent or off-road detour, flee, pursue a target, attack a target, evade police, help an injured person, or recover when stuck.
- Off-road navigation must account for vehicle dimensions, slope, collision, clearance, and turning space. Do not blindly route cars across pedestrian NavMesh.
- If no viable route exists, stop or recover safely instead of steering forever or clipping through obstacles.

### Crime and wanted system
- Support crime events, witnesses, wanted-level escalation/decay, and future police response.
- Crime detection, witness visibility, wanted levels, and police response should remain separate, testable responsibilities.

## Suggested architecture

Names are provisional until the real Unreal module name is confirmed.

- `Core/`: GameMode, GameState, shared gameplay configuration
- `Player/`: player character, controller, interaction/combat interfaces
- `Vehicles/`: vehicle pawn and driving/control interface
- `Crime/`: crime events, witness detection, wanted-level component
- `AI/Pedestrians/`: NavMesh routing, crossing and traffic-aware avoidance
- `AI/Drivers/`: driver goals, personality, threat assessment, route following
- `World/RoadNetwork/`: road segments, lanes, intersections, speed limits, legal connections
- `Missions/`: objectives and mission state
- `Economy/`: money, inventory and shops
- `Save/`: persistent player/world state

Prefer small, coherent classes and explicit interfaces. Avoid a single giant AI class that owns every behavior.

## Recommended next actions

1. Inspect the current `main` tree and latest commit.
2. Confirm whether an Unreal Engine 5.8 `.uproject` and module already exist. If absent, coordinate before creating a project skeleton.
3. Establish shared enums/structs for driver goals, navigation modes, driver personality, and crime events.
4. Implement the road-network data model and route query interface before building advanced driver behavior.
5. Add pedestrian NavMesh movement with vehicle-aware crossing/avoidance.
6. Implement road-following vehicle AI with steering, braking, throttle, hazard sensing, and stuck recovery.
7. Add fear/criminal behavior and goal-driven detours only after ordinary driving is stable.
8. Compile in the actual UE 5.8 project and report exact results, including errors. Never describe uncompiled code as tested.

## Working rules for agents

- Read current source before editing; do not overwrite files based on assumptions.
- Keep changes scoped and modular.
- Do not introduce Blueprint-based gameplay logic; the target is C++.
- Do not add fake implementations, placeholder claims, or invented test results.
- Summarize changed files, the reason for each change, build/test status, and any manual Unreal Editor setup required.
- Preserve user changes and avoid force-pushing or destructive history rewrites.
- Commit messages should describe the actual change, not the intended future result.
