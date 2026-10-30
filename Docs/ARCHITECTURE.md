# Project Mayhem — Architecture Baseline

**Approved direction:** realistic-world inspiration; high-end PC and current-generation console target; massive multi-region world; balanced action, story, freedom, and systemic simulation; single-player first with a future multiplayer path.

**Engine:** Unreal Engine 5.8  
**Gameplay:** C++  
**Architecture:** modular, data-driven, event-driven.

## Product principles

1. Believable world: systems respond consistently to context and available information.
2. Player freedom: multiple viable approaches to goals and interactions.
3. Persistent consequences: important events can affect later world state.
4. Scalable simulation: detail is allocated by relevance and distance, not uniformly to every entity.
5. Honest validation: a feature is not complete until compiled and tested in the actual Unreal project.

## Runtime layers

- **Gameplay experience:** player, combat, interaction, missions, vehicles.
- **AI systems:** pedestrians, drivers, police, gangs, animals, perception, squad coordination.
- **World systems:** crime, economy, weather, dynamic events, faction and population simulation.
- **World infrastructure:** region streaming, road graph, navigation, world partition and content layers.
- **Core services:** event routing, stable entity identity, world clock, configuration, save/load and simulation scheduling.
- **Engine foundation:** Unreal Engine 5.8 C++, Chaos, World Partition, MassEntity, StateTree and other engine systems where prototypes and profiling justify them.

## Core implementation rules

- Systems communicate through narrow interfaces and meaningful events; avoid direct dependencies between unrelated systems.
- World events are discrete facts, not a per-frame messaging channel.
- Important entities receive stable IDs. IDs alone do not implement persistence; the Save system must serialize and restore them.
- Game time is separate from wall-clock time and can be scaled or paused.
- Road routing and pedestrian navigation remain distinct. Vehicle movement uses vehicle control/physics, not pedestrian AI MoveTo.
- Use full Actors for nearby/high-value entities and data-oriented or abstract simulation for large/distant populations.
- Keep gameplay rules in C++. Data Assets/Data Tables may hold tuning and content definitions.
- Multiplayer is a future constraint, not a first-release feature: isolate state mutation and define explicit ownership, but do not build networking infrastructure before the single-player vertical slice proves the gameplay.

## World scale and regions

The intended world can contain multiple connected cities, suburbs, industrial/port areas, rural settlements, highways, and wilderness. Do not attempt to build all regions before a vertical slice. Use World Partition and streaming boundaries appropriate to the authored world; preserve region-level persistent state independently of loaded Actors.

## Performance model

- **Near/high significance:** full Actor behavior, detailed perception, animation and selective physics.
- **Mid-range:** reduced update rates, squad/group intent, simplified navigation and animation.
- **Distant:** bounded statistical simulation and persistent state updates without requiring every entity to remain spawned.

Budgets must be measured on target hardware. Initial performance goal is 60 FPS where feasible on the agreed high-quality target profile; this is a target to validate, not a guarantee.

## Multiplayer direction

Version one is single-player. Design stable IDs, explicit state ownership, event payloads, and save boundaries so later replication can be introduced without rewriting every gameplay system. Do not add dedicated servers, matchmaking, or replication complexity until separately approved.

## Initial code foundation

- UPMWorldEventSubsystem: event publication and bounded recent-event history.
- UPMEntityIdentityComponent: stable GUID identity for Actors.
- UPMWorldClockSubsystem: world-local elapsed game time, day progress, pause, and time scale.

These are foundation primitives only. They do not yet implement crime, police, traffic, gangs, animals, missions, economy, or save/load.

## Validation status

The repository includes a minimal Unreal project/module scaffold and initial C++ core services. No Unreal Editor/toolchain build has been run in this environment. Compile and runtime validation remain required in Unreal Engine 5.8.
