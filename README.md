# GAS System 5.3

A first-person Unreal Engine 5.3 gameplay sandbox for learning and testing the Gameplay Ability System (GAS). The project focuses on a network-aware ability setup, replicated attributes, gameplay effects, and UI that responds to attribute changes.

> This branch is built for Unreal Engine 5.3. It adapts the earlier 5.5-oriented work so the project opens and builds with UE 5.3.

## What is included

- A custom `UTaskAbilitySystemComponent` with GAS enabled in the project module.
- A custom `UTaskAttributeSet` with replicated `Health` and `MaxHealth` attributes.
- Health clamping before changes and after gameplay-effect execution.
- A `PlayerState`-owned Ability System Component configured for mixed replication.
- Default attribute initialization through a gameplay effect.
- Default gameplay abilities granted by the authoritative character.
- A gameplay ability that creates and removes an attributes widget.
- UMG widgets that bind to the health attribute and update their health display when it changes.
- Enhanced Input actions for first-person movement, look, jump, shooting, and ability input.

## Architecture

| Area | Implementation |
| --- | --- |
| Ability System owner | `ATest_TaskPlayerState` owns `UTaskAbilitySystemComponent` and `UTaskAttributeSet`. |
| Avatar | `ATest_TaskCharacter` implements `IAbilitySystemInterface`, initializes actor info on possession and replication, grants abilities on the authority, and applies default attributes. |
| Attributes | `UTaskAttributeSet` replicates health values and keeps health within `0` and `MaxHealth`. |
| Gameplay effects | `GE_DefaultValues` initializes attributes and `GE_ReduceHealth` provides a health-reduction example. |
| UI | `UAttributesWidget`, `UInteractiveWidget`, and `ATest_TaskHUD` display and react to player health. |
| Input | The first-person template uses Enhanced Input, including the `IA_Ability` action. |

## Requirements

- Unreal Engine 5.3
- Visual Studio 2022 with the Desktop development with C++ and Game development with C++ workloads
- Windows development environment

## Getting started

1. Clone the repository.

   ```bash
   git clone https://github.com/MukundPareek15/GAS-System-5.3.git
   cd GAS-System-5.3
   ```

2. Right-click `Test_Task.uproject` and choose **Generate Visual Studio project files**.

3. Open `Test_Task.sln` in Visual Studio and build the `Test_TaskEditor` target using the `Development Editor` configuration.

4. Launch `Test_Task.uproject` with Unreal Engine 5.3.

5. Open the default map at `Content/FirstPerson/Maps/FirstPersonMap` and press Play in Editor.

## Project layout

```text
GAS-System-5.3/
├── Config/                         # Engine, game, gameplay-tag, and input settings
├── Content/
│   ├── FirstPerson/Abilities/       # Gameplay effects and Gameplay Ability assets
│   ├── FirstPerson/Blueprints/      # Character, PlayerState, controller, and GameMode Blueprints
│   ├── FirstPerson/Input/           # Enhanced Input mapping contexts and actions
│   └── Widgets/                     # Health and interaction widgets
├── Source/Test_Task/                # GAS and first-person C++ implementation
└── Test_Task.uproject
```

## Key source files

| File | Responsibility |
| --- | --- |
| `TaskAttributeSet.*` | Defines, replicates, and clamps health attributes. |
| `TaskAbilitySystemComponent.*` | Provides the project-specific Ability System Component type. |
| `Test_TaskPlayerState.*` | Stores the Ability System Component and attribute set for replication. |
| `Test_TaskCharacter.*` | Initializes GAS, grants abilities, applies default attributes, and binds input. |
| `GA_ShowWidgetAbility.*` | Shows and removes the attributes widget through a gameplay ability. |
| `AttributesWidget.*` | Subscribes to health changes and computes the health percentage for UMG. |

## Notes

This is an experimentation and learning project rather than a drop-in production framework. The code is intentionally organized around the core GAS lifecycle: create the component and attributes on the PlayerState, initialize actor information for the character, grant abilities on the server, apply gameplay effects, and surface attributes in UI.
