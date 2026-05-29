# AGENTS.md

# MyBossRush

## Project Overview

MyBossRush is a third-person action boss-rush game developed in Unreal Engine 5.

The primary goal is to refine combat, movement, boss encounters, player progression, gear upgrades, and short-session reward loops.

This is currently a boss-rush game, not an open-world RPG.

## Core Gameplay Loop

The intended loop is:

1. Fight a boss.
2. Kill the boss.
3. Receive gear and gold.
4. Use gold to buy new gear or upgrade current gear.
5. Unlock or equip stronger combat options.
6. Fight harder bosses.
7. Repeat.

All systems should support this loop first.

## Current Scope

Focus on:

- Player movement
- Combat
- Boss encounters
- Combat abilities
- Ability unlocking
- Health and damage
- Targeting
- Enemy AI
- Encounter pacing
- Gear
- Basic inventory
- Gold/currency
- Basic vendor
- Gear upgrades
- Combat stat modifiers
- Combat feedback

Do NOT introduce:

- Open world systems
- Quest systems
- Crafting systems
- Reputation systems
- Dialogue trees
- Economy simulation
- Multiplayer systems
- Complex talent trees
- Procedural itemization beyond simple test cases

## Development Philosophy

### Combat First

Combat quality is more important than feature count.

A working combat and reward loop is preferred over a large unfinished architecture.

### Small Iterations

Implement features in the smallest possible testable increments.

Avoid implementing entire systems at once.

### Explicit Ownership

Every system should have a clearly defined owner and responsibility.

Avoid god objects and monolithic managers.

### Caveman Principles

Favor:

- Simplicity
- Readability
- Explicit behavior
- Small diffs
- Low coupling

Avoid unnecessary abstraction.

Avoid designing for hypothetical future features.

Only solve problems that currently exist in the boss-rush loop.

## Agent Behavior

When given a task:

1. Understand the requested feature.
2. Identify the smallest implementation that satisfies the requirement.
3. Modify as few files as possible.
4. Avoid unrelated changes.
5. Preserve existing architecture unless instructed otherwise.

If a requested feature requires major architectural changes:

- Explain the reason.
- Propose the change.
- Wait for approval before implementing.

## Combat Design Guidelines

Combat should emphasize:

- Player agency
- Readability
- Responsive controls
- Clear telegraphs
- Meaningful decision making
- Skill expression over stat checks

Gear and upgrades may improve player power, but should not replace the need for good movement, timing, and encounter knowledge.

## Ability System Guidelines

The game uses a simple WoW-inspired ability model.

Current assumptions:

- Auto attack exists.
- Auto attack continues while a valid target exists.
- Auto attack resumes automatically when conditions become valid.
- Abilities may have cooldowns.
- Abilities may have resource costs.
- Abilities may have cast times.
- Abilities may be unlocked through progression.
- Abilities may be modified by simple stat modifiers.

Do not assume:

- Talent trees
- Large passive systems
- Class systems
- Multiple resource systems
- Complex proc systems

unless explicitly requested.

## Gear and Inventory Guidelines

The game should support a basic gear and inventory system.

Current assumptions:

- The player can receive gear from boss rewards.
- The player can hold items in an inventory.
- The player can equip gear.
- Equipped gear can modify combat stats.
- The player has gold.
- Vendors can sell gear or upgrades.
- Existing gear can be upgraded through a simple upgrade system.

Keep itemization simple.

Prefer clear test items such as:

- Sword of Damage +5
- Boots of Speed +10%
- Ring of Cooldown Reduction
- Armor of Max Health +25

Avoid complex random loot generation unless explicitly requested.

## Vendor Guidelines

Vendors should support only basic interactions at first:

- Display purchasable items.
- Check player gold.
- Purchase item.
- Add item to inventory.
- Optionally upgrade existing gear.

Do not create complex shop inventories, reputation discounts, dynamic pricing, barter systems, or economy simulation.

## Progression Guidelines

Progression should be boss-rush oriented.

Valid progression examples:

- Boss kill unlocks next boss.
- Boss kill grants gold.
- Boss kill grants gear.
- Boss kill unlocks an ability.
- Gold upgrades gear.
- Vendor sells stronger gear after boss milestones.

Avoid open-world leveling systems for now.

## Coding Guidelines

Prefer:

- Unreal Engine conventions
- Components over monolithic classes
- Blueprint accessibility where appropriate
- Data-driven configuration where appropriate

Avoid:

- Premature optimization
- Premature generalization
- Unnecessary framework creation
- Large inheritance trees

## Output Requirements

After making changes, provide:

- Files modified
- Summary of changes
- Architectural impact
- Testing recommendations

Keep explanations concise and actionable.