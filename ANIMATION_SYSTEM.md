# Project Mayhem — Procedural Animation & Active-Ragdoll System

**Status:** Design specification only. No animation runtime, C++ implementation, animation assets, or Unreal tests are claimed.
**Target:** Unreal Engine 5.8, C++ gameplay systems.
**Reference direction:** Euphoria-like physical responsiveness and adaptive reactions. This is an original implementation target, not a claim to reproduce NaturalMotion's proprietary Euphoria technology.

## 1. Goals

Character motion should feel fluid, weighty, responsive, and context-aware rather than like disconnected canned animations.

The target combines:
- High-quality authored locomotion and action animation.
- Procedural adjustment to terrain, posture, reach, and nearby obstacles.
- Physics-assisted reactions to impacts, pushes, falls, and loss of balance.
- Active-ragdoll behavior for selected high-value moments.
- Smooth transitions between animation-driven movement, physical reactions, ragdoll, and recovery.
- Stable performance for crowds in an open-world game.

The system should create believable variation without making every NPC run a costly full-body physics simulation.

## 2. Core animation layers

### A. Authored animation foundation
Use authored animation sets for reliable baseline motion:
- Idle, locomotion, starts/stops, turns, strafing, crouching, jumping, climbing, and traversal.
- Combat, weapon handling, melee, hit reactions, and interaction animations.
- Contextual actions such as sitting, getting up, entering/exiting vehicles, and using objects.

Animation assets provide intended motion and timing. Runtime systems adapt them to the character and situation.

### B. Procedural pose adjustment
Apply lightweight procedural corrections for:
- Foot placement and ground alignment on uneven surfaces.
- Pelvis and body adjustment for slopes and stairs.
- Look-at and head/upper-body aim with anatomical limits.
- Hand/foot targets for reaching, bracing, and interacting with nearby surfaces.
- Additive posture changes driven by fatigue, fear, injury, weapon weight, and movement intent.

Corrections must be clamped and smoothed to avoid jitter, snapping, and unnatural joint angles.

### C. Physics-assisted response
Use physical simulation selectively:
- Impulse-aware hit reactions based on impact direction, magnitude, body region, and stance.
- Balance recovery using foot repositioning, torso counter-rotation, and arm reactions.
- Stumbles, trips, pushes, collisions, and falls that vary with momentum and environment.
- Contact-aware bracing against walls, vehicles, floors, and other characters.
- Partial-body physical response where full ragdoll is unnecessary.

### D. Active ragdoll
For selected characters and moments, use an active-ragdoll model: physics bodies are driven toward desired poses by controlled joint motors rather than being left entirely limp.

The controller should:
- Blend toward an animation target pose.
- Adjust motor strength and damping by state, joint, and impact severity.
- Preserve believable joint limits and avoid unstable energy injection.
- Use balance and contact information to attempt recovery when feasible.
- Fall back to passive ragdoll when control is lost or impact is severe.

Active ragdoll is high-cost and should be reserved for the player, nearby important NPCs, and selected gameplay events.

## 3. Euphoria-like response model

The desired quality is adaptive physical behavior, not a direct copy of proprietary middleware.

A character evaluates a compact set of signals:
- Body velocity and angular velocity.
- Center of mass and available foot/support contacts.
- Impact impulses and contact points.
- Current pose, locomotion intent, and movement direction.
- Nearby obstacles and possible support surfaces.
- Awareness, fear, pain, fatigue, injury, and current action.

These signals feed behavior policies such as:
- Maintain balance or recover from a stumble.
- Protect the head or torso.
- Reach for a nearby support.
- Brace for an expected collision.
- Redirect momentum during a fall when physically and contextually appropriate.
- Attempt to stand, kneel, crawl, or remain down based on injury and threat.

Responses should be imperfect and character-dependent. Strength, agility, fatigue, injury, and personality profiles should produce different outcomes from similar impacts.

## 4. State and transition model

Suggested high-level states:
- AnimatedLocomotion
- ProceduralAdjustment
- ReactiveHit
- Staggering
- BalanceRecovery
- Bracing
- PartialPhysics
- ActiveRagdoll
- PassiveRagdoll
- GettingUp
- InjuredLocomotion
- Disabled

Transitions need explicit conditions, blend durations, and interruption rules. Avoid hard switches that pop the skeleton between unrelated poses.

Recovery must check available support, body orientation, injury, nearby threats, and whether the character can stand. Do not force every fallen character to stand immediately.

## 5. Character variation

Use compact data profiles rather than hard-coded character-name branches:
- Mass and body proportions.
- Strength, agility, balance, and recovery ability.
- Joint/motor strength and damping multipliers.
- Pain response, fear response, and willingness to protect or fight.
- Injury effects and movement limitations.
- Animation style and locomotion tuning.

Variation should be bounded and readable. Randomness must not override physical constraints or produce chaotic motion.

## 6. Unreal Engine implementation direction

Provisional C++ responsibilities; final names depend on the confirmed project module:
- UCharacterMotionProfile: per-archetype movement and physical-response tuning.
- UProceduralPoseComponent: runtime pose offsets and target generation.
- UBalanceRecoveryComponent: support detection and recovery decisions.
- UImpactResponseComponent: impact classification and reaction requests.
- UActiveRagdollComponent: physics blend, motor targets, strength, and damping.
- UCharacterAnimationCoordinator: coordinates locomotion, procedural layers, physics, and recovery.
- UAnimationEventSubsystem: shared event routing for impacts and contextual actions where needed.

Use Unreal animation systems and physics constraints as the foundation. Keep gameplay decisions in C++; animation assets and skeleton configuration remain content data. Avoid one giant component that owns every animation decision.

## 7. Blending and stability requirements

- Smoothly blend animation pose into partial physics and active ragdoll.
- Smoothly blend back from physics to a valid recovery pose.
- Avoid visible snapping, foot sliding, joint popping, and sudden root-motion changes.
- Use controlled physics update behavior where required by the solver.
- Clamp motor targets, impulses, angular velocity, and recovery forces.
- Handle network correction and simulated proxies without repeatedly fighting local physics.
- Provide deterministic state transitions where practical, while accepting that full rigid-body simulation may not be bitwise deterministic across machines.

## 8. Open-world performance tiers

- **Near player / hero:** full procedural adjustment, detailed hit response, and active ragdoll when needed.
- **Nearby important NPCs:** procedural pose and selected partial/full physics reactions, with strict concurrency limits.
- **Crowd NPCs:** authored animation plus inexpensive hit/stumble variants; no persistent full-body active ragdoll.
- **Distant NPCs:** animation LOD or simplified state updates; no detailed physics simulation.

Use significance-based activation, pooling, physics asset quality tiers, and a hard budget for simultaneous active ragdolls. When the budget is exceeded, downgrade lower-priority characters gracefully.

## 9. Development phases

1. Confirm the actual UE 5.8 project, skeletons, physics assets, and module before source implementation.
2. Establish a clean authored locomotion baseline and animation state coordination.
3. Add procedural foot placement, slope adjustment, and look/aim offsets.
4. Add impulse-aware hit reactions and controlled stumble/balance recovery.
5. Add partial-body physics and stable blend transitions.
6. Prototype active ragdoll on one test character with motor tuning and recovery.
7. Add character profiles and reactions for different body types, injuries, and fatigue.
8. Add crowd/performance tiers, concurrency limits, and network behavior.
9. Profile and test falls, wall/vehicle impacts, stairs, uneven terrain, repeated impacts, recovery under threat, and replication edge cases as applicable.

## 10. Acceptance criteria

- Baseline locomotion transitions are smooth and do not visibly pop between common movement states.
- Foot placement and body adjustment respond to uneven ground without persistent jitter.
- Impacts produce direction- and strength-sensitive reactions rather than one identical canned flinch.
- Characters can stumble and attempt balance recovery when support is available.
- Active ragdoll blends into physics and returns to a valid pose without obvious snapping.
- Injury, fatigue, body profile, and threat context affect reactions in a controlled way.
- Crowd and distant simulation tiers respect a measurable physics/animation budget.
- Actual UE 5.8 build, runtime profiling, and test results are reported honestly.

## 11. Current status

This is a design specification only. The repository must be checked for the actual Unreal project, module, skeletons, and physics assets before implementation. No C++ animation system, animation assets, Unreal build, or runtime test is claimed.
