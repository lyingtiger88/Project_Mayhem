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

## Approved product direction

- World inspiration: realistic.
- Target platforms: high-end PC and current-generation consoles.
- World scale: massive, multi-region ambition.
- Design focus: balanced story, action, freedom, and systemic simulation.
- Release strategy: single-player first; multiplayer is a future option, not a current implementation target.
- Architecture: modular, data-driven, event-driven C++.

## Verified repository state

The live main branch now contains both the design documents and an initial Unreal Engine 5.8 C++ project scaffold.

- Root Unreal project descriptor: ProjectMayhem.uproject.
- Build targets: Source/ProjectMayhem.Target.cs and Source/ProjectMayhemEditor.Target.cs.
- Runtime module: Source/ProjectMayhem/ProjectMayhem.Build.cs.
- Core C++ primitives:
  - UPMWorldEventSubsystem: publishes typed world events and keeps a bounded recent-event history.
  - UPMEntityIdentityComponent: assigns a stable GUID to an Actor; persistence across loads still requires the future Save system to serialize and restore it.
  - UPMWorldClockSubsystem: tracks world-local game time, day progress, pause, and time scale.
- Architecture and roadmap: Docs/ARCHITECTURE.md and Docs/ROADMAP.md.
- Unreal Engine target: 5.8; module name/API macro: ProjectMayhem / PROJECTMAYHEM_API.

**Validation status:** GitHub accepted the source and project files. No Unreal Editor, UnrealBuildTool, or C++ compiler build has been run in this workflow. The project is a committed starter scaffold, not a verified build or playable game. Generate project files and compile it in an installed Unreal Engine 5.8 environment before adding dependent gameplay systems.

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

## Gang system design

A design specification is now documented in `GANG_SYSTEM.md`. It covers gang identity/runtime state, territory influence and contested control, inter-gang relations, player reputation and witness-based memory, layered gang/squad/member AI, event-driven escalation, distance-based simulation, and integration with crime/police, vehicles, missions, economy, and save/load. This is design only; no gang C++ implementation or UE build has been completed.

## Animal and wildlife system design

A design specification is documented in ANIMAL_SYSTEM.md. It covers domestic/farm animals and wildlife; data-driven species profiles; needs and species-specific behavior; perception and reactions; ownership, trust, care and work roles; habitat-based spawning and population limits; herd/pack/flock behavior; interactions with pedestrians, vehicles, gangs and crime; and distance-based simulation/performance. The bird design has now been expanded to cover urban, farm, wild, raptor, and water-bird groups; grounded movement, hopping, takeoff, powered flight, gliding/soaring, landing, perching, roosting, nesting, flock cohesion/separation/alignment, alarm propagation, and optional migration. Flight and perch selection are explicitly separate from ordinary ground NavMesh movement. This remains design only; no animal C++ implementation or UE build has been completed.

## Procedural animation and active-ragdoll design

A design specification is now documented in ANIMATION_SYSTEM.md. It targets fluid locomotion, procedural pose correction, impact-aware physical reactions, balance recovery, partial physics, and selective Euphoria-like active-ragdoll behavior. It also defines smooth blending, character variation, networking considerations, and open-world performance tiers. This is an original design direction inspired by the qualities associated with Euphoria, not a reproduction of proprietary middleware. No animation C++ implementation, assets, UE build, or runtime test has been completed.

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

## Current art and environment setup

- Approved art direction: realistic / photorealistic.
- Initial asset sourcing: free assets only.
- Added Content/Python/Build_PM_FirstDistrict.py. It creates a repeatable 300 m x 300 m urban greybox using Unreal built-in primitive meshes, road strips, sidewalks, lane markings, crosswalks, placeholder buildings, lamps/trees, PlayerStart, and NavMeshBoundsVolume. It removes only actors carrying the PM_Generated_Blockout tag when rerun.
- Added Docs/ASSET_PIPELINE.md and Docs/ASSET_CREDITS.md.
- ProjectMayhem.uproject enables PythonScriptPlugin and EditorScriptingUtilities for editor automation.
- Important distinction: no external photorealistic asset pack has been downloaded or migrated into the project yet. The generated district is a greybox, not final art.
- Recommended free city source: Epic City Sample updated for UE 5.8; migrate selected assets through Unreal Editor's Asset Migration workflow, not filesystem copying.
- Manual validation required: restart Unreal Editor after plugin activation, execute Content/Python/Build_PM_FirstDistrict.py from Tools > Execute Python Script, inspect the generated map, and save/confirm it.

## Change log

### 2026-10-30 — Procedural and physics-assisted animation design added
- Added ANIMATION_SYSTEM.md covering authored animation foundations, procedural pose adjustment, impact-aware physics response, balance recovery, selective active ragdoll, Euphoria-like adaptive behavior goals, smooth blending, character variation, and open-world performance tiers.
- ANIMATION_SYSTEM.md commit: 6e3d57e2ebc63c199b188bd25c035f2bc2dc8031.
- Updated README.md to link to ANIMATION_SYSTEM.md.
- README commit: a27fe932e37041de1e72fb8b44f858848c757a69.
- Validation: GitHub accepted both documentation commits. No Unreal build, runtime profiling, or animation tests were run; this is design documentation only.

### 2026-10-30 — Insect scope limited to four types
- Updated ANIMAL_SYSTEM.md to restrict insects to cockroaches, butterflies, bees, and ants, with lightweight behavior definitions and explicit population/performance limits.
- ANIMAL_SYSTEM.md commit: 752d917683d4de4b4e40550799861bc0e6375970.
- Validation: GitHub accepted the animal design update. No Unreal build or gameplay tests were run.



### 2026-10-30 — Bird and flight behavior design expanded
- Expanded ANIMAL_SYSTEM.md with first-class bird categories (urban, domestic/farm, wild, raptors, and water birds), species-appropriate habitat, flight capabilities, takeoff/landing, perching, nesting/roosting, flock behavior, reactions, and provisional C++ capabilities.
- Added acceptance criteria for non-teleporting bird flight/perching and flock behavior with individual variation.
- ANIMAL_SYSTEM.md commit: 97932c6776b852598ffa723a0ef0b9aa57de4fb3.
- Validation: GitHub accepted the documentation update. No Unreal build or gameplay tests were run; this remains design documentation only.
- Next step: confirm the actual UE 5.8 .uproject and module before implementing bird movement or animal gameplay code in C++.


### 2026-10-30 — Animal and wildlife system design added
- Added ANIMAL_SYSTEM.md with the domestic-animal and wildlife design specification, proposed C++ architecture, integration points, performance model, development phases, and acceptance criteria.
- Commit: cbe6e559f0913d1b0b55a59902def644b0cd3d16.
- Updated README.md to link to ANIMAL_SYSTEM.md.
- README commit: 99e1f9812acb3e5c4abf3dff85583a60af1f631d.
- Validation: GitHub accepted both documentation commits and the files were written. No Unreal build or gameplay tests were run; this is design documentation only.
- Next step: confirm the actual UE 5.8 .uproject and module before implementing the first domestic and wildlife species in C++.

### 2026-10-29 — Gang system design added
- Updated `README.md` to link directly to `GANG_SYSTEM.md`.
- README commit: `5a78b80c7825a89a247fe7f3d03e9a70abc8ba55`.
- Added `GANG_SYSTEM.md` with the proposed gang/faction simulation design, architecture, integration contracts, phased implementation plan, and acceptance criteria.
- Commit: `2dfdbab64280d20211451c37fad67dc3cf66f661`.
- Validation: GitHub accepted the documentation commit. No Unreal build or gameplay tests were run; the document is a design specification, not implementation.
- Next step: confirm the actual Unreal project/module and then implement the first testable gang data/state milestone in C++.


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

## Change log

### 2026-10-30 — Unreal project scaffold and core services committed
- Added root ProjectMayhem.uproject targeting Unreal Engine 5.8, game/editor targets, the ProjectMayhem C++ module, and Unreal .gitignore rules.
- Added UPMWorldEventSubsystem with event IDs, source/subject IDs, location, severity, confidence, world timestamp, broadcast, and a bounded 256-event recent history.
- Added UPMEntityIdentityComponent for stable per-Actor GUID identity. SaveGame metadata is present, but Save/Load serialization is not implemented yet.
- Added UPMWorldClockSubsystem with elapsed game time, day progress, pause, and time scale.
- Added Docs/ARCHITECTURE.md and Docs/ROADMAP.md; updated README.md to reflect the approved realistic / high-end / massive / balanced / single-player-first direction.
- Commit: eafd5530d6e492a712cdbc90cac511ffaa79d15f.
- Validation: GitHub accepted the commit and main was advanced using an expected-head check. No UE 5.8 compile, editor launch, runtime test, or playable build has been performed.
- Next step: open ProjectMayhem.uproject in Unreal Engine 5.8, generate project files, compile the Development Editor target, and resolve any toolchain/API issues before expanding gameplay code.

### 2026-10-30 — First district editor generator and free asset pipeline
- Added Content/Python/Build_PM_FirstDistrict.py for repeatable editor-side city greyboxing from engine primitive meshes.
- Added Docs/ASSET_PIPELINE.md and Docs/ASSET_CREDITS.md.
- Enabled PythonScriptPlugin and EditorScriptingUtilities in ProjectMayhem.uproject.
- Updated README.md with the asset pipeline and first-district setup.
- Commit: 851f9a8931ea12c22ccfd499857347ae063cbfaf.
- Validation: GitHub accepted all files and advanced main. The script has not yet been executed in the user's Unreal Editor; no external asset pack has been downloaded or migrated. The generated scene is a greybox, not photorealistic final art.
- Next step: restart UE 5.8, run the editor Python script, inspect/save the generated map, then migrate selected free City Sample assets through Unreal's migration workflow.

## Working rules for agents

- Read current source before editing; do not overwrite files based on assumptions.
- Keep changes scoped and modular.
- Do not introduce Blueprint-based gameplay logic; the target is C++.
- Do not add fake implementations, placeholder claims, or invented test results.
- Summarize changed files, the reason for each change, build/test status, and any manual Unreal Editor setup required.
- Preserve user changes and avoid force-pushing or destructive history rewrites.
- Commit messages should describe the actual change, not the intended future result.


### 2026-10-31 — District generator safety and map-size fix
- Updated `Content/Python/Build_PM_FirstDistrict.py` to create or load `/Game/Maps/PM_FirstDistrict` before editing actors, rather than modifying an unrelated currently open level. Fixed base ground to cover 300 m square in Unreal's 100 cm primitive scale.
- Code commit: `57fb1d284df807ae4623182ed5de73b9ebe90ba1`.
- Added empty Content Browser diagnosis and step-by-step local execution to `Docs/ASSET_PIPELINE.md`.
- Documentation commit: `64bad8dd4215d85552fb106f637b79ac2c67d61d`.
- Validation: GitHub writes accepted; the Python script **has not been run in Unreal Editor**. A generated `.umap` is not committed. Requires a local UE 5.8 execution and Output Log review.


### 2026-10-31 — First district daylight pass
- User confirmed the generated first district exists in Unreal Editor (screenshot showed `PM_FirstDistrict` and 486 actors).
- Extended `Content/Python/Build_PM_FirstDistrict.py` with a tagged directional sun, skylight, sky atmosphere, and exponential height fog so reruns replace the previous generated lighting safely.
- Commit: `b96452b7936d04b8c784db2fc69f1fb5aa1c6e0a`.
- Validation: script edit committed; lighting has not yet been executed/verified in Unreal. Re-run the script in Editor and inspect Output Log; if any Python API property warning appears, share it for compatibility adjustment.
