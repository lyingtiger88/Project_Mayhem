# Project Mayhem — Gang System Design

**Status:** Design specification only. No gameplay code has been implemented or tested by this document.
**Target:** Unreal Engine 5.8, C++ gameplay logic.
**Scope:** A systemic open-world gang/faction simulation, independent from other projects.

## 1. Design goals

Gangs should behave like persistent organizations, not just hostile NPC groups spawned near the player. Each gang has identity, members, territory interests, resources, relationships, memory of player actions, and goals. The system creates believable conflict without simulating every member at full cost when far from the player.

Core requirements:
- Multiple gangs coexist and compete, cooperate, make temporary truces, and retaliate.
- Territory control changes from gameplay events, not merely a static map color.
- NPC behavior reflects gang affiliation, local influence, alert state, personality, and orders.
- Player choices affect reputation; reputation is separate from police wanted level.
- Gang activity supports missions, crime reporting, police response, shops/economy, vehicles, and save/load through interfaces/events.
- Gameplay rules live in C++; avoid Blueprint graphs as the implementation target.
- AI is data-driven, modular, and scalable.

## 2. Core gameplay loop

1. World simulation evaluates gang goals at a low frequency.
2. Gangs assign members to local activities: patrol, hang out, guard a location, collect income, escort, investigate, retaliate, or attack a rival.
3. Territory and relationship state influence which activities are allowed and how risky they are.
4. Encounters create events: threat spotted, member injured, crime witnessed, territory challenged, deal completed, or rival attacked.
5. The gang updates alertness, local response, relationship with involved factions, and memory of the player.
6. Police/crime systems receive relevant evidence independently; police heat and gang reputation remain separate.
7. Mission and save systems use public interfaces rather than directly manipulating gang internals.

## 3. Main concepts and state

### Gang definition
Mostly static configuration for a faction:
- Stable GangId (Gameplay Tag or project-defined ID).
- Display name, color/marking, preferred districts and home locations.
- Member archetypes, outfit/style references, default weapons and vehicles where allowed.
- Personality profile: discipline, aggression, risk tolerance, loyalty, territoriality, willingness to flee.
- Economic profile: income sources, operating costs, reserve threshold.
- Default relations and response policy.
- Spawn and activity budgets.

Use C++-defined data models with configuration assets or data tables for content values. Configuration assets do not replace C++ gameplay logic.

### Runtime gang state
- Current strength: active members, available backup, resources.
- Alert level: Calm, Suspicious, Alerted, Combat, Retreating, Recovering.
- Strategic goal and current operation.
- Territory influence/control values by territory.
- Resource reserve and income trend.
- Relations and recent events.
- Last known player threat information, with confidence and age.
- Cooldowns and activity budgets.

### Member state
Each member has:
- Gang affiliation and optional squad assignment.
- Role: Leader, Enforcer, Lookout, Recruit, Driver, Dealer, Guard, or Civilian-facing member.
- Individual traits and combat confidence.
- Current task, alertness, morale, injuries, equipment, and last known threats.
- Relationship to player based on gang memory and individual witness confidence.

Do not give every member a permanent heavyweight behavior tree. Use a small state machine or utility decision layer and activate detailed perception and tactical logic only when relevant.

## 4. Territory model

A territory is a world region or authored zone, not an arbitrary circular radius around every NPC.

Each territory stores:
- Stable TerritoryId, display name, bounds/zone reference, and district.
- Candidate controlling gang and current control/influence per gang.
- Strategic value, income potential, traffic/population profile, and spawn/activity limits.
- Key locations such as safehouses, businesses, hangouts, stash sites, and mission locations.
- Pressure from rivals, police presence, and recent violence.

Suggested influence values range from 0 to 100 per gang. Avoid treating this as a simple health bar: influence changes from multiple weighted events, decays slowly where a gang is absent, and may remain contested. Control is derived from influence plus a minimum lead threshold and stability duration, preventing ownership from flipping every few seconds.

Territory events:
- Presence/patrol can slowly reinforce influence.
- Successful protection or local activity can reinforce it.
- Public violence may increase short-term fear/influence but also raise police pressure and damage business income.
- Losing members, failed operations, and rival activity can reduce influence.
- A challenge can trigger a contested state before control changes.

Use spatial queries and authored territory volumes/IDs. Do not make every AI actor poll every territory every frame.

## 5. Relationship system

Relationships are directional only if the design explicitly needs asymmetric behavior; otherwise store each pair once.

Suggested relation score: -100 to +100:
- -100 to -60: open war
- -59 to -20: hostile
- -19 to +19: neutral/uneasy
- +20 to +59: friendly/trading
- +60 to +100: alliance

A relation score alone is insufficient. Store a relationship state and recent context:
- Neutral, Tense, Truce, Trade, Allied, Rivalry, War.
- Current truce/contract expiry if relevant.
- Recent attacks, assistance, betrayals, and disputed territory.
- Confidence/source of information: confirmed, witnessed, rumor.

Actions affect relations through configurable event weights. A single minor incident should not automatically trigger permanent gang war. Use thresholds, cooldowns, escalation steps, and a de-escalation path.

## 6. Player reputation and gang memory

Maintain a separate reputation value for each gang, for example -100 to +100. Also track event-specific memory:
- Helped a member or completed a job.
- Attacked or killed members.
- Stole or damaged gang property.
- Betrayed a deal.
- Was witnessed committing a crime against the gang.
- Was merely suspected based on rumor.

Reputation influences greetings, prices, access, recruitment, backup willingness, ambush likelihood, and mission availability. Reputation must not act as a magical omniscient global flag: an NPC should react only if the gang has a plausible information path, such as direct witness, radio report, shared encounter, or a rumor with uncertainty and age.

Gang reputation is not police wanted level. A player may be wanted by police but welcomed by a gang, or disliked by a gang without being wanted by police.

## 7. Member AI and squad tactics

Use layered decision-making.

### Strategic layer (gang-level, low frequency)
Chooses broad goals: defend home turf, expand influence, earn resources, reduce heat, retaliate, negotiate, recover strength, or stay quiet.

### Tactical layer (squad-level)
Chooses patrol routes, guards, lookout placement, escort routes, fallback locations, and whether to call backup.

### Individual layer
Chooses movement, cover, aim, warning, pursuit, flee, surrender, or help an ally. Individual decisions are constrained by squad orders and personality.

Example alert progression:
- Calm: idle/hang out, normal patrol.
- Suspicious: look around, alert nearby allies, seek more information.
- Alerted: move to cover, warn members, protect important locations.
- Combat: engage according to role and confidence, coordinate flanking only when a viable path exists.
- Retreating: disengage toward a safe fallback, request backup if available.
- Recovering: regroup, tend to injured members if supported, reassess threats and resume lower-risk activities.

Avoid perfect coordination. Lookouts may fail, members can panic, drivers can flee, and a squad can lose cohesion. Enforce collision, navigation, weapon-safety, and performance constraints.

## 8. Encounters, escalation, and cooldown

Use a central event flow rather than direct hard-coded calls between every system.

Example events:
- GangThreatSpotted
- GangMemberDowned
- GangPropertyDamaged
- GangTerritoryChallenged
- GangDealCompleted
- GangMemberRequestedBackup
- GangRelationChanged
- GangReputationChanged

Events should include relevant gang/member/territory IDs, instigator if known, location, severity, timestamp, and confidence. Do not broadcast expensive data to every actor indiscriminately; use subsystem routing and relevant listeners.

Escalation should consider:
- Severity and recency.
- Number of witnesses and confidence in identification.
- Gang discipline, aggression, and available strength.
- Police pressure and current activity.
- Distance, travel time, available vehicles, and viable routes.
- Whether the player or target is still in the area.
- Cooldowns and whether the gang is already committed to another operation.

## 9. Spawning, simulation, and performance

Use a UGangSimulationSubsystem (provisional name) to manage faction-level state and low-frequency decisions. Use separate territory and relationship services where separation improves testability.

- Near the player: spawn/activate full NPCs and detailed perception.
- Mid-distance: update squad-level intent and approximate travel/activity state.
- Far away: simulate abstract outcomes with bounded timers and deterministic/random-seed-friendly calculations.
- Use per-gang and per-territory activity budgets.
- Avoid ticking every gang and every member every frame.
- Pool or reuse NPCs when appropriate, but clear stale affiliation, squad, target, and perception state before reuse.
- All off-screen simulation must have bounded rates and save-safe transitions.

## 10. Proposed C++ architecture

Names are provisional until the actual Unreal module name is confirmed.

- UGangSimulationSubsystem: owns active gang runtime records and low-frequency strategic updates.
- UGangRelationshipSubsystem: stores relation states, scores, and transition events.
- UTerritoryControlSubsystem: territory definitions, influence, contested state, and ownership transitions.
- UGangReputationComponent: player-to-gang reputation and known event memory.
- UGangAffiliationComponent: gang ID, role, squad ID, member traits.
- AGangSquadCoordinator or a squad runtime object: tactical orders, members, morale, backup requests.
- AGangMemberAIController: individual movement and tactical decisions.
- UGangDefinition data asset or equivalent data-table row: faction configuration.
- UGangSaveData or save-game records: persistent relationships, territory state, resources, and relevant memory.

Keep interfaces between systems event-based and testable. Do not let the gang subsystem own police logic, all vehicle physics, all mission state, or the complete pedestrian AI.

## 11. Integration contracts

- Crime/wanted: gang incidents may submit crime evidence to the crime system; gang hostility does not automatically create police wanted level.
- Police: police pressure may affect gang strategy and activity risk; gang AI does not directly spawn police without going through the response system.
- Vehicles: gang drivers use the shared vehicle-control interface and road network. Never move cars with pedestrian AI MoveTo.
- Missions: missions query gang state through interfaces and send events/commands, not mutate private internals.
- Economy: businesses and resource income are represented by explicit transactions/ticks; avoid generating infinite money from offline simulation.
- Save/load: persist stable IDs and essential state, not transient pointers or perception actors. Rebuild transient runtime links on load.

## 12. Suggested development phases

1. Confirm the real .uproject and module name; inspect existing code.
2. Define stable IDs, gang definitions, member roles, alert states, relationship states, and event payloads.
3. Implement relationship and reputation storage with unit-testable transition rules.
4. Implement territory influence and contested/control transitions.
5. Add member affiliation and a simple gang member state machine.
6. Add squad coordination and backup requests.
7. Add player memory, witness confidence, rumor propagation, and encounter reactions.
8. Integrate crime/police, missions, economy, and save/load through interfaces.
9. Add distance-based simulation and profiling.
10. Test edge cases: rival gangs both retreat, leader dies, squad loses route, witness misidentifies player, territory tie, save during combat, and gang activity while off-screen.

## 13. Acceptance criteria

The first playable milestone should demonstrate:
- Two or more gangs with stable IDs and configurable relationships.
- At least one territory whose influence changes from events without rapid ownership flicker.
- NPCs identify their affiliation and respond to a local threat.
- A witnessed player action changes reputation/relationship while an unwitnessed action does not magically inform everyone.
- Gang and police response remain distinct but can exchange crime evidence.
- NPCs and vehicles use appropriate navigation/control systems.
- Off-screen activity is bounded and save/load-safe.
- Build/test results are reported honestly from the actual UE 5.8 project.

## 14. Current status

This file is a design specification only. The inspected repository currently contains documentation but no confirmed .uproject, Unreal module, or gameplay C++ implementation. No code compilation or gameplay test is claimed.
