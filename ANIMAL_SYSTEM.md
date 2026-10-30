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
- Urban birds: pigeons, sparrows, crows, gulls, and other species suited to the city setting.
- Domestic and farm birds: chickens, roosters, ducks, geese, and turkeys.
- Wild and water birds: locally appropriate songbirds, raptors (such as hawks, falcons, and eagles), owls, storks, herons, and waterfowl.
- Species selection must follow the game's region, climate, habitats, and authored world population; this is not a requirement to include every listed bird.

The list is a content proposal, not a promise that every species will appear in every district. Species must match the world's climate, terrain, and setting.

## 3. Bird-specific behavior and flight

Birds are a first-class animal category, not merely a generic wildlife entry. They share the animal population, perception, save, and performance foundations, but require flight- and perch-aware behavior.

### Bird groups and habitat

- Urban birds use rooftops, ledges, signs, trees, parks, wires, and street-level feeding areas.
- Farm birds use coops, yards, barns, ponds, and fenced enclosures.
- Wild birds use suitable woodland, cliffs, open fields, wetlands, rivers, coastlines, and other map-authored habitats.
- Raptors need suitable hunting territory and perches; water birds need shoreline or water access where their species requires it.
- Species profiles must define habitat tags, preferred perch types, flocking tendency, flight capability, and activity periods.

### Flight and movement capabilities

Flight is a distinct movement capability and must not be treated as ordinary ground NavMesh movement. Profiles should distinguish:
- Grounded movement and walking/hopping.
- Short hops and low-distance takeoff/landing.
- Powered flight with tuned speed, acceleration, turning, and stamina/flight-duration limits.
- Gliding and soaring for species and environments that support them.
- Hovering only for species whose anatomy and flight style support it.
- Swimming or diving for suitable water birds.

Takeoff and landing require clearance, reachable destination checks, collision avoidance, and valid landing/perch surfaces. Birds must not snap or teleport between perches as a normal movement solution. If flight navigation is blocked or unavailable, use a grounded fallback only when biologically and spatially appropriate.

### Perching, nesting, and flocking

- Perch candidates include branches, roofs, ledges, poles, wires, rocks, and ground locations, each with suitability and capacity.
- Perch selection should consider reachability, height, safety, visibility, nearby threats, and crowding.
- Support resting, roosting, feeding, nesting, and returning to a nest/roost where enabled by the species profile.
- Flocks use group-level goals with individual variation, spacing, cohesion, separation, and alarm propagation.
- Flocking must avoid rigid synchronized movement; individuals can react with small delays and imperfect information.
- Seasonal migration is optional and should be implemented only if the world map, time system, and content justify it. Do not fake migration by despawning a flock without a world-state transition.

### Bird behavior states

Possible states include Grounded, Walking, Hopping, Feeding, Drinking, Alert, Fleeing, Perching, Roosting, TakingOff, Flying, Gliding, Soaring, Circling, Landing, Flocking, Nesting, and FeedingChicks. Only enable states supported by the species profile.

### Reactions and species differences

- Small urban birds generally scatter or take short flights when approached, startled by traffic, or exposed to loud sounds.
- Pigeons and similar flocking birds can take off together, but with staggered timing and varied trajectories.
- Crows and other intelligent social birds may investigate sounds, remember repeated threats at a lightweight gameplay level, and communicate alarms.
- Raptors may perch, scan, circle, and perform species-appropriate hunting dives; they should not attack the player by default.
- Waterfowl may walk, swim, paddle, take off from water, and land on suitable water surfaces.
- Domestic poultry may forage on the ground, return to a coop/roost, and scatter when startled.

### Proposed bird-specific C++ capabilities

These are provisional design responsibilities, not confirmed source files or class names:
- A flight movement component or movement mode for takeoff, powered flight, glide, and landing.
- A perch-selection capability that queries authored perch points/surfaces and validates clearance.
- A flock component for cohesion, separation, alignment, group goals, and alarm propagation.
- Optional nest/roost data and seasonal migration policy, enabled only where required.

## 4. Limited insect system

The insect feature is deliberately restricted to exactly four gameplay groups:
1. **Cockroaches (سوسک):** small ground-dwelling insects that scatter into cracks, drains, trash areas, and dark corners when disturbed. They are ambient environmental life, not combat enemies.
2. **Butterflies (پروانه):** visual ambient insects that flutter around suitable flowers and vegetation, rest on plants, and scatter when approached. Keep their movement light and non-disruptive.
3. **Bees (زنبور):** appear around flowers and designated hive/nest locations, forage between flowers and the nest, and may defend the nest when the player or another threat gets too close. Avoid treating every bee as automatically aggressive.
4. **Ants (مورچه):** move along visible ground trails between nest entrances and food sources, carry small food items where practical, and react to trail disruption or threats near the nest.

### Scope limits

- Do not add other insect types to the planned roster unless the user explicitly changes this requirement.
- No full insect ecosystem, insect breeding simulation, complex colony economy, or individual life-cycle simulation is required.
- Use lightweight behavior and low population/update budgets; distant or tiny insects may be represented by simple ambient effects rather than full AI actors.
- Insects are environmental wildlife and should not be forced into domestic ownership, riding, companion, or general animal command systems.
- Bees and ants may use simple group/nest logic; cockroaches and butterflies should remain low-cost ambient behaviors.
- Species-specific reactions must be readable but restrained, and must not create unnecessary combat or mission complexity.

### Insect acceptance criteria

- Only cockroaches, butterflies, bees, and ants are included in the approved insect scope.
- Cockroaches scatter and seek cover when disturbed.
- Butterflies flutter around suitable vegetation and flee from nearby disturbance.
- Bees forage between flowers and a nest, with defensive behavior limited to nest threats.
- Ants follow trails between a nest and food sources with simple group response.
- Insects use bounded counts and lightweight updates, with no unbounded spawning or expensive per-frame AI.

## 5. Shared species definition and runtime state

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

## 6. Behavior model

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

## 7. Perception and reactions

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

## 8. Domestic ownership, care, and work

Where supported by gameplay, domestic animals can have:
- Owner/handler and home location.
- Trust/familiarity and training level.
- Feeding, watering, rest, and shelter requirements.
- Follow, stay, return-home, guard, herd, or work commands appropriate to species.
- Injury, neglect, recovery, and care interactions.
- Stable/pen/coop or designated home areas.

Ownership and trust should be explicit state, not inferred from proximity. A stray dog does not become owned merely because the player stands beside it.

Potential gameplay uses include companion dogs, guard dogs at properties, horses for transport, and livestock at farms. These are optional content layers and should be implemented only when the related player systems exist.

## 9. Wildlife ecology and population

Wildlife should spawn in valid habitats and follow daily/seasonal activity profiles where the world supports them.

- Use authored habitat regions and spawn points/volumes with species suitability checks.
- Keep population caps per species and region.
- Use group spawning for herds, packs, and flocks; avoid placing individuals uniformly like random props.
- Represent food, water, shelter, predators, and disturbance through lightweight local suitability values.
- Allow populations to shift slowly due to hunting, traffic deaths, habitat disturbance, and reproduction only if those systems are implemented.
- Avoid unbounded reproduction, infinite respawning, or instant replacement after an animal dies.
- Distant populations may be simulated statistically; near-player animals use full actors and perception.

Do not build a full ecological research simulator. The target is believable gameplay at a controlled performance cost.

## 10. World and gameplay interactions

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

## 11. Proposed C++ architecture

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

## 12. Performance and simulation distance

- Near the player: full animal actor, animation, perception, and navigation.
- Mid-distance: lower-frequency decisions and simplified group movement.
- Far away: population and group state updated statistically, without one actor per animal.
- Use spawn caps, update intervals, significance/visibility checks, and actor pooling where appropriate.
- Do not tick every animal every frame.
- On pooling/reuse, clear owner, group, target, threat, and interaction state.
- Save only stable, meaningful state; rebuild transient perception and navigation references after loading.

## 13. Development phases

1. Confirm the actual UE project and module before creating source files.
2. Define species IDs, categories, behavior states, habitat tags, and event payloads.
3. Implement a basic animal actor/controller and data-driven species profile.
4. Add one domestic species and one wildlife species as vertical slices.
5. Add group behavior, perception, fleeing, and defensive reactions.
6. Add habitat spawning, population caps, and distance-based simulation.
7. Add domestic ownership/care and selected work roles.
8. Integrate road hazards, pedestrian reactions, gangs, crime, and save/load through interfaces.
9. Profile crowded areas and test edge cases: startled herd, animal trapped by traffic, injured owned animal, predator/prey encounter, group leader removed, and save/load during a flee state.

## 14. Acceptance criteria

A first playable animal milestone should demonstrate:
- At least one domestic and one wild species with distinct behavior.
- Species-specific perception and reactions rather than a universal attack-on-player rule.
- Group movement for at least one herd/pack species.
- At least one bird species can take off, fly, avoid obstacles, and land/perch without teleporting.
- At least one flocking bird species demonstrates group cohesion with individual variation and a shared threat response.
- The insect roster is limited to cockroaches, butterflies, bees, and ants, each with its defined lightweight ambient behavior.
- Animals spawn only in valid regions and respect population caps.
- Vehicles and pedestrians can react to animals without navigation deadlocks.
- Distant simulation is bounded and does not require every animal to remain spawned.
- Important domestic ownership and animal state survive save/load.
- Actual UE 5.8 build and test results are reported honestly.

## 15. Current status

This is a design specification only. The repository state must be checked for an actual .uproject, module, and gameplay source before implementation. No animal C++ code, Unreal build, or gameplay test is claimed.
