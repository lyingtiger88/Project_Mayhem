# Project Mayhem — Agent Handoff

This is the live handoff and change log for any shared AI agent or contributor working on this repository. Read `AGENTS.md`, this file, and `README.md` before making changes.

## Project identity

- Repository: `lyingtiger88/Project_Mayhem`
- Engine target: Unreal Engine 5.8
- Implementation language: C++ only for gameplay logic
- Genre: open-world action game inspired by GTA-style systemic gameplay
- Default branch: `main`

## Important scope rule

Project Mayhem is an independent project. Do not merge its assumptions, source files, architecture, or task history with the user's other Unreal projects unless the user explicitly asks.

## Verified repository state

The repository currently contains project documentation files:
- `AGENTS.md`: agent instructions and mandatory inspection workflow.
- `HANDOFF.md`: this file; architecture, requirements, next steps, and change log.
- `README.md`: project overview and architecture/roadmap.

The repository tree was inspected on 2026-10-29 and these were the files returned by GitHub. No `.uproject`, `Source/` directory, or gameplay C++ implementation appeared in that tree. Re-check the live tree before acting because the repository may have changed since this note was written.

- Architecture documented: yes
- Gameplay C++ implementation: not present in the inspected tree
- Unreal project file (`.uproject`): not present in the inspected tree
- Build/test status: no Unreal build or gameplay test has been run from this workflow
- Playable build: not established

Do not claim compilation or a playable build. Before implementing engine source, confirm whether the actual Unreal project/module exists elsewhere or get explicit approval to establish a project skeleton. Never invent the module name or API export macro.

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
2. Confirm whether an Unreal Engine 5.8 `.uproject` and module exist. If absent, coordinate before creating a project skeleton.
3. Establish shared enums/structs for driver goals, navigation modes, driver personality, and crime events.
4. Implement the road-network data model and route query interface before building advanced driver behavior.
5. Add pedestrian NavMesh movement with vehicle-aware crossing/avoidance.
6. Implement road-following vehicle AI with steering, braking, throttle, hazard sensing, and stuck recovery.
7. Add fear/criminal behavior and goal-driven detours only after ordinary driving is stable.
8. Compile in the actual UE 5.8 project and report exact results, including errors. Never describe uncompiled code as tested.

## Change synchronization rule

Whenever a change is actually made to this repository:
1. Update this handoff in the same work session with the change summary, files changed, commit SHA/link, and validation status.
2. Update the current status and next steps if the change affects them.
3. Keep `AGENTS.md`, `HANDOFF.md`, and `README.md` consistent when their information overlaps.
4. Do not log a change as completed until the GitHub write succeeds. Distinguish planned work from committed work.
5. If the handoff itself is changed in a commit, include that commit in the log after the resulting SHA is known (a following documentation commit may be used if necessary).

## Change log

### 2026-10-29 — Agent discovery and handoff synchronization
- Added `AGENTS.md` with mandatory instructions for agents to read the handoff and README and inspect the repository before editing.
- Updated `README.md` to link to `AGENTS.md` and `HANDOFF.md` at the top.
- Verified via GitHub that the root tree contains `AGENTS.md`, `HANDOFF.md`, and `README.md`.
- Commits:
  - `efd9c9963871eaaf6f9450ef445cfdbbab74ac0c` — add root agent instructions (the file's current blob SHA may differ from the commit SHA).
  - `946980e7adb7d7795b7c4acf244bd7819b87c766` — link agent instructions from README.
- Validation: GitHub file reads and root-tree inspection succeeded. No Unreal build or gameplay tests were run.
- Next step: use the agent's explicit prompt to read the three files and report repository contents; confirm the Unreal project/module before writing gameplay C++.

### 2026-10-29 — Handoff status refresh
- Updated this handoff to reflect the inspected live repository tree, document the required handoff synchronization rule, and record the AGENTS/README discovery improvements above.
- Commit: `a9482d2079d9ffc590fe34dc68e23d138ac095b3`.
- Validation: the update was accepted by GitHub; no Unreal build or gameplay tests were run.

## Working rules for agents

- Read current source before editing; do not overwrite files based on assumptions.
- Keep changes scoped and modular.
- Do not introduce Blueprint-based gameplay logic; the target is C++.
- Do not add fake implementations, placeholder claims, or invented test results.
- Summarize changed files, the reason for each change, build/test status, and any manual Unreal Editor setup required.
- Preserve user changes and avoid force-pushing or destructive history rewrites.
- Commit messages should describe the actual change, not the intended future result.
