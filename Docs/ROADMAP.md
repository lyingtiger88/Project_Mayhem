# Project Mayhem — Approved Roadmap

## Product baseline

- Realistic-world inspiration.
- High-end PC and current-generation console target.
- Massive world ambition: multiple cities/regions, suburbs, industry, ports, rural areas, highways, and wilderness.
- Balanced focus across story, action, player freedom, and systemic simulation.
- Single-player first; multiplayer may be evaluated later.

## Phase 0 — Project and engineering foundation

- Confirm Unreal Engine 5.8 installation and target platforms.
- Generate project files and compile the C++ scaffold.
- Establish coding conventions, branch policy, build reporting, and test conventions.
- Confirm module naming, asset directory conventions, and source-control handling for Unreal binary assets.
- Add a minimal playable map and game mode.

**Exit criteria:** clean Development Editor build in UE 5.8; project opens; source module loads; no unverified build claims.

## Phase 1 — Vertical slice

Build one compact, representative district:
- Player character, camera, input, interaction.
- One drivable vehicle with proper vehicle control.
- Road graph prototype, lanes, intersections, and traffic signals.
- Pedestrian navigation and vehicle-aware crossing.
- A small set of driver archetypes.
- One short mission and basic combat/interaction loop.
- Basic save/load proof.

**Exit criteria:** a repeatable playable scenario; vehicles and pedestrians navigate without systematic deadlocks; measurable CPU/GPU/memory profile.

## Phase 2 — Systemic city

- Crime evidence, witnesses, wanted level, and police response as separate responsibilities.
- NPC identity, daily schedule prototype, and witness-aware memory.
- Dynamic world events and event history.
- Gang relationships, reputation, territory influence, and squad response.
- Mission and economy interfaces.
- Persistent state for one district.

**Exit criteria:** player actions create observable, explainable consequences that can be saved and restored.

## Phase 3 — World expansion and economy

- Region streaming and world-partition content workflow.
- Additional districts and rural/industrial/port regions.
- Road network expansion and long-distance travel.
- Shops, inventory, business state, and bounded economic simulation.
- Mission variety and story progression.
- Region-level population and faction simulation.

**Exit criteria:** multiple regions stream reliably and preserve important world state.

## Phase 4 — Natural world and advanced animation

- One domestic and one wildlife vertical slice.
- Habitat/population controls and group behavior.
- Bird flight/perching prototype.
- Weather effects on driving, NPCs, and wildlife.
- Procedural pose correction and impact-aware reactions.
- Selective partial physics/active ragdoll prototype.
- Environmental destruction only for selected object classes.

**Exit criteria:** each feature demonstrates its core behavior and meets measured performance budgets.

## Phase 5 — Content, polish, and release

- Complete world, missions, narrative, audio, UI, accessibility, and localization.
- Save migration and recovery testing.
- Performance, stability, and compatibility testing on target hardware.
- QA pass for mission progression, AI edge cases, and long sessions.
- Release candidate and post-release support plan.

**Exit criteria:** release criteria, platform requirements, and performance targets are met and documented.

## Cross-cutting requirements

- Keep gameplay logic in C++.
- Prefer data-driven content tuning.
- Use modular systems and event contracts.
- Build/test each integrated milestone in the actual UE version.
- Keep near/mid/far simulation tiers and hard budgets for costly systems.
- Do not simulate every distant NPC/animal as a full Actor.
- Keep version one single-player; preserve future multiplayer options without premature networking scope.

## Current implementation checkpoint

The repository now has a minimal UE 5.8 C++ scaffold plus core world-event, identity, and clock primitives. The scaffold has not yet been compiled in Unreal Engine. The next action is to generate project files and validate a Development Editor build in UE 5.8 before expanding gameplay systems.
