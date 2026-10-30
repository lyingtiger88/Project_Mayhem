# Project Mayhem — Animal & Wildlife System Design

**Status:** Design specification only. No gameplay code has been implemented or tested by this document.
**Target:** Unreal Engine 5.8, C++ gameplay logic.
**Scope:** Domestic animals and wildlife as persistent, systemic parts of the open world.

## 1. Design goals

Animals must feel like living inhabitants of the world, not decorative props or ordinary hostile NPCs. Domestic and wild species share reusable foundations but have distinct behavior, needs, habitat rules, and relationships with people.

Core goals:
- Populate suitable world regions with species appropriate to habitat and time of day.
- Give animals species-specific senses, movement, social behavior, needs, and reactions.
- Support domestic ownership/care and working roles where appropriate.
- Support wildlife survival behaviors such as grazing, drinking, resting, fleeing, defending, hunting, and group movement.
- Let animals interact with players, pedestrians, traffic, gangs, and the environment without making every animal an expensive full-AI actor.
- Persist important animal/world state while keeping distant simulation bounded.
- Keep gameplay logic in C++; use data assets for species tuning, not Blueprint gameplay logic.

## 2. Animal categories

### Domestic and farm animals
Initial candidate species:
- Dogs: companion, guard, herding, or stray variants.
- Cats: household, farm, and stray variants.
- Horses and donkeys: riding, pack, and working roles if supported by the game.
- Cattle, sheep, and goats: herd and farm behavior.
- Chickens and roosters: flock/coop behavior.
- Pigs: farm groups and scavenging behavior.

Domestic does not mean universally tame. A neglected, frightened, injured, or unfamiliar animal may avoid or defend itself.

### Wildlife
Candidate species depend on the authored map and its biomes:
- Deer and similar herbivores.
- Wild boar.
- Foxes and wolves.
- Bears only where the setting and map justify them.
- Rabbits and other small mammals.
- Birds, with grounded, perched, flocking, and short-flight behaviors as appropriate.

The list is a content proposal, not a promise that every species will appear in every district. Species must match the world's climate, terrain, and setting.

## 3. Shared species definition and runtime state

Use a data-driven species definition containing:
- Stable SpeciesId, display name, category, size class, and habitat tags.
- Skeletal mesh, animation references, movement profile, collision dimensions, and audio cues.
- Diet, preferred food/water sources, activity periods, and environmental tolerances.
- Sight, hearing, smell (abstracted if needed), alertness, curiosity, fear, and aggression parameters.
- Social structure: solitary, pair, herd, pack, flock, or household animal.
- Reproduction and population tuning, if enabled.
- Domestic handling, ownership, work-role, and interaction capabilities.
- Spawn density, population cap, and LOD/simulation budget.

Runtime state may include health, hunger, thirst, fatigue, fear, stress, injury, current task, social group, owner/handler, home area, and last known threats. Do not simulate every need with a per-frame tick; use scheduled updates and meaningful events.

## 4. Behavior model

Use a shared animal decision framework with species-specific state transitions. Example states:
- Idle / Resting
- Feeding / Grazing
- Drinking
- Roaming / Exploring
- FollowingGroup
- FollowingOwner
- Guarding / Herding
- InvestigatingSound
- Alert
- Fleeing
- Defending / Attacking
- SeekingShelter
- Injured / Recovering
- Sleeping

Not every species supports every state. A rabbit should not use a wolf's combat behavior, and a cow should not behave like a guard dog.

Decision priority should consider immediate danger, injury, essential needs, social bonds, assigned domestic tasks, and ambient activity. Add reaction delays and imperfect perception so animals do not behave like omniscient sensors.

## 5. Perception and reactions

Animals can use tuned combinations of:
- Vision: line of sight, distance, movement, and lighting modifiers.
- Hearing: sound events with distance/occlusion and confidence.
- Scent or trail awareness: optional abstract stimulus, not a costly simulation of literal scent particles.
- Social alerts: nearby group members can react to alarm calls or sudden movement.

Example reactions:
- Deer and rabbits flee from approaching people, vehicles, or predators.
- Wild boars may flee first but defend themselves if cornered or protecting young.
- Wolves coordinate pack movement and hunting only if that species and gameplay scope require it.
- Dogs may bark, approach, follow, guard, herd, or retreat depending on training, trust, and threat.
- Cats tend to avoid crowds and may hide or flee.
- Livestock generally move as a group and can panic if startled.

Fear and aggression must be species- and context-dependent. Avoid making all wildlife attack the player on sight.

## 6. Domestic ownership, care, and work

Where supported by gameplay, domestic animals can have:
- Owner/handler and home location.
- Trust/familiarity and training level.
- Feeding, watering, rest, and shelter requirements.
- Follow, stay, return-home, guard, herd, or work commands appropriate to species.
- Injury, neglect, recovery, and care interactions.
- Stable/pen/coop or designated home areas.

Ownership and trust should be explicit state, not inferred from proximity. A stray dog does not become owned merely because the player stands beside it.

Potential gameplay uses include companion dogs, guard dogs at properties, horses for transport, and livestock at farms. These are optional content layers and should be implemented only when the related player systems exist.

## 7. Wildlife ecology and population

Wildlife should spawn in valid habitats and follow daily/seasonal activity profiles where the world supports them.

- Use authored habitat regions and spawn points/volumes with species suitability checks.
- Keep population caps per species and region.
- Use group spawning for herds, packs, and flocks; avoid placing individuals uniformly like random props.
- Represent food, water, shelter, predators, and disturbance through lightweight local suitability values.
- Allow populations to shift slowly due to hunting, traffic deaths, habitat disturbance, and reproduction only if those systems are implemented.
- Avoid unbounded reproduction, infinite respawning, or instant replacement after an animal dies.
- Distant populations may be simulated statistically; near-player animals use full actors and perception.

Do not build a full ecological research simulator. The target is believable gameplay at a controlled performance cost.

## 8. World and gameplay interactions

### Player and pedestrians
- Animals can approach, avoid, follow, warn, defend, or attack according to species and state.
- Pedestrians may stop, avoid, flee, react verbally, or help an injured domestic animal.
- Interactions should use explicit interfaces and distance/line-of-sight checks.

### Vehicles and roads
- Animals near roads should assess traffic and may wait, cross, flee, or panic.
- Vehicle AI should treat animals as moving hazards and brake/steer within safe control limits.
- Avoid teleporting animals across roads or forcing vehicle collisions as a default behavior.
- Traffic incidents may create world events and witness evidence if the crime system supports them.

### Gangs and crime
- Dogs may be used as guards or companions by selected NPC groups if appropriate.
- Livestock theft, animal attacks, or property damage may create events for owners, witnesses, gangs, or police through shared event interfaces.
- Animal ownership and gang affiliation must not be hard-coded into one another.

### Environment
- Support navigation constraints for fences, steep slopes, water, narrow spaces, and species-specific traversal.
- Use NavMesh for suitable ground movement, with custom links or movement modes for species that need them.
- Flight, climbing, swimming, and mounted movement require dedicated movement capabilities; do not assume ordinary NavMesh handles them.

## 9. Proposed C++ architecture

Names are provisional until the actual Unreal module name is confirmed.

- UAnimalWorldSubsystem: population regions, spawn budgets, and low-frequency world simulation.
- UAnimalSpeciesDefinition: species configuration data.
- UAnimalPopulationSubsystem: regional population records, caps, and respawn/repopulation rules.
- UAnimalBehaviorComponent: shared needs, state, and decision scheduling.
- UAnimalPerceptionComponent: tuned sight/hearing and stimulus handling.
- UAnimalSocialGroupComponent: herd, pack, flock, or household group membership.
- UAnimalOwnershipComponent: owner, handler, trust, and domestic task state.
- AAnimalAIController: navigation and high-level movement decisions.
- IAnimalInteractable: stable interaction contract for player/NPC systems.
- Save-game records: stable IDs and persistent ownership, injuries, and important population changes.

Keep species behavior modular. Avoid one giant controller full of species-name conditionals. Prefer data profiles plus small behavior policies or species-specific extensions where genuinely needed.

## 10. Performance and simulation distance

- Near the player: full animal actor, animation, perception, and navigation.
- Mid-distance: lower-frequency decisions and simplified group movement.
- Far away: population and group state updated statistically, without one actor per animal.
- Use spawn caps, update intervals, significance/visibility checks, and actor pooling where appropriate.
- Do not tick every animal every frame.
- On pooling/reuse, clear owner, group, target, threat, and interaction state.
- Save only stable, meaningful state; rebuild transient perception and navigation references after loading.

## 11. Development phases

1. Confirm the actual UE project and module before creating source files.
2. Define species IDs, categories, behavior states, habitat tags, and event payloads.
3. Implement a basic animal actor/controller and data-driven species profile.
4. Add one domestic species and one wildlife species as vertical slices.
5. Add group behavior, perception, fleeing, and defensive reactions.
6. Add habitat spawning, population caps, and distance-based simulation.
7. Add domestic ownership/care and selected work roles.
8. Integrate road hazards, pedestrian reactions, gangs, crime, and save/load through interfaces.
9. Profile crowded areas and test edge cases: startled herd, animal trapped by traffic, injured owned animal, predator/prey encounter, group leader removed, and save/load during a flee state.

## 12. Acceptance criteria

A first playable animal milestone should demonstrate:
- At least one domestic and one wild species with distinct behavior.
- Species-specific perception and reactions rather than a universal attack-on-player rule.
- Group movement for at least one herd/pack species.
- Animals spawn only in valid regions and respect population caps.
- Vehicles and pedestrians can react to animals without navigation deadlocks.
- Distant simulation is bounded and does not require every animal to remain spawned.
- Important domestic ownership and animal state survive save/load.
- Actual UE 5.8 build and test results are reported honestly.

## 13. Current status

This is a design specification only. The repository state must be checked for an actual .uproject, module, and gameplay source before implementation. No animal C++ code, Unreal build, or gameplay test is claimed.
