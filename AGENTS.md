# Instructions for AI Agents

**Start here. Before doing any work, read [HANDOFF.md](HANDOFF.md) and [README.md](README.md).**

## Project boundaries
- Work only on Project Mayhem in this repository.
- Do not mix its code, architecture, assumptions, or history with the user's other projects.
- Target Unreal Engine 5.8. Gameplay implementation must be C++.
- Inspect the current repository tree and recent commits before editing anything.

## Required first steps
1. Read `HANDOFF.md` and `README.md`.
2. Inspect the complete current repository tree.
3. Verify whether a `.uproject`, `Source/` directory, and Unreal module already exist.
4. If the Unreal project/module is absent or unclear, do not invent module names, API export macros, or pretend code can be compiled. Report the blocker and ask for the project files or explicit approval to create a project skeleton.
5. Before implementing, state the concrete files and scope you intend to change.

## Engineering rules
- Prefer modular, maintainable C++ systems.
- Ordinary traffic follows a road graph and lane/intersection rules. Pedestrians use NavMesh plus vehicle-aware avoidance. Do not use character `AI MoveTo` as vehicle control.
- Vehicle movement must use steering, throttle, braking, collision/hazard checks, and stuck recovery.
- Do not route vehicles blindly over pedestrian NavMesh. Off-road routes require vehicle clearance, slope, collision, and turning-space checks.
- Keep crime detection, witnesses, wanted levels, and police response separable.
- Read files before replacing them. Preserve user changes. Never force-push or rewrite history destructively.
- Never claim a build or test succeeded unless it was actually run. If the UE editor/build environment is unavailable, say so explicitly.
- After each task, report changed files, commit(s), validation actually performed, unresolved blockers, and required manual Unreal Editor setup.

## Current project status
Documentation and planning may exist before the Unreal project itself. Verify the live repository; do not assume a playable game, C++ implementation, or successful build exists.
