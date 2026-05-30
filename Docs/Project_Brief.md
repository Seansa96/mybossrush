# MyBossRush

Third-person boss rush game.

# Core Loop:

Kill Boss
→ Earn Gold and Gear
→ Buy Gear or Upgrades
→ Unlock Abilities
→ Fight Harder Bosses

# Combat

Tab target based.

Abilities can be queued.

Abilities trigger a global cooldown, which may be affected by modifiers, and may or may not have their own cooldown periods as well.

Casts can be canceled.

Players can dodge during casts and cast recovery.

Auto-Attack is not reset by casts generally, and it's frequency is controlled by the Attack Speed stat.
Some abilities may specifically occur on next Auto-Attack.
For the Yet-to-be-Implemented Hunter class, auto-attacks will continue no matter the current ability sequence or action, but will not neccessarily trigger the auto-attack animation, just the particle effect and projectile animations.

# Health and Shielding

# Inventory

Maximum inventory Size of 30

All gear can be sold for gold.

Slot-based, no stacking.

Inventory only holds gear. Gold is just its own tracked currency that functions as a value to be added and subtracted, but cannot be negative.

Inventory can be accessed in all contexts while the Game is in session outside of transition periods like loading a new map, but gear can only be sold while at or near a vendor or in the main lobby area.

Inventory items can be moved around,equipped, and deleted anywhere the player can open the inventory.

If inventory is full, the player will be notified and may either choose to wait and clear their bag, or have it sent to their storage chest, which is in the main lobby area.

# Death/Reset

Death fires once only.

Damage dealt after death by the player is calculated as normal. Damage dealt by an enemy NPC is multiplied by 0 but still fires.

Healing cannot affect dead actors.

Death of the player is caused by the HealthComponentDepleted event. This event triggers if the HealthComponent for the player is reduced below 1, if the player's hasDeathProtection boolean is set to false, and if the actor which reduced the HealthComponent of the player below 1 has the canKillPlayer boolean set to true on that frame.

Death of a boss is also triggered by the HealthComponentDepleted event, but this version of the event triggers if the HealthComponent of the NPC is reduced below 1 and if their hasDeathProtection boolean is set to false.

If a player dies, they respawn at the arena entrance, and the Boss resets to full health after 2 seconds.

# Ability Unlocks

Intended to come from defeating bosses, but for testing purposes will also be purchaseable in the testing branch from the vendor for 0 gold.

# Explicit Classes

All classes have health and shield. Shield set to 0 by default and not visible on health bar unless > 0. Healing absorbs work as anti-heal debt, and put shield value below 0 and forces healing affects to add to Shield value first until it is >= 0.

Classes share auto-attack, jump, and dodge roll.

Have primary resource like mana or energy, secondary resource like combo points or holy power.

# Gear Slots

Weapon
Helmet
Chest
Boots
Hands
Legs

# Character Stats

- To be expanded
Stamina
Armor
Intellect
Strength
Agility
Critical Strike
Attack Speed
Haste
Cooldown Reduction
Mastery
Lifesteal

# First Class - Adventurer

Purpose:

- Baseline Combat Testing
- No specialization
- No class selection

Primary Resource:
- Mana (100 Total, regenerates at 5 mana per second base)

Secondary Resource:
- None

Shared Abilities: - Auto Attack
- Auto Attack
- Jump
- Dodge Roll

Starting Active Abilities:
- Auto Attack
- Adventurer's Strike -Deals 5 Damage - Costs 10 Mana. No cooldown.
- Adventurer's Flourish - 0 mana - Deals 20 Damage, usable after two Adventurer's Strikes then goes on a 10 second Cooldown

## Starting Values

Health 100/100 upon spawn or respawn unless otherwise explicitly determined by another ability or circumstance

Bosses should have a base starting value of 1000 for now.

Healing does not exceed Max Health value unless the healing has an "Overhealing" modifier.

Shield absorbs damage before health unless the ability has a "Shield Piercing" modifier

Shielding is capped to 10 times that of the player character's max health, before bonus health from other sources is applied (like from the Stamina stat).

Shield does not decay over time unless explicitly stated, typically in the case where the source has a "Decay" modifier.

Negative shield anti-heal debt is capped to 10 times that of the player character's max health, before bonus health from other sources is applied (like from the Stamina stat).

Damage will be reduced by armor and other mitigation. These reductions shall be calculated multiplicatively.

Damage types will exist but assume only physical and bleed for now. 

Physical damage is reduced by armor and any damage reductions provided from Buffs or Debuffs.

Bleed damage is only affected by damage reductions provided from Buffs or Debuffs.

## Unlockeable Abilities - Adventurer

- Adventurer's Rage - 0 Mana - 1 minute cooldown. Increases attack speed by 100%, reduces mana cost of all abilities by 10 if their cost is greater than or equal to 10, increases mana regeneration rate by 100%, movement speed by 30%, damage of all abilities by 50%, and causes attacks to heal the player for 50% of damage dealt for 15 seconds.

- Dash - 30 Mana - Increaes movement speed by 70%. 30 second cooldown.

- Adventurer's Defense - 20 Mana - 1 minute cooldown.

- Adventurer's Interrupt - 0 Mana - Off the global cooldown, has a 12 second cooldown. Interrupts the cast of an enemy target.

- Adventurer's Rend - Inflicts a bleed on the enemy that deals 30 damage over 10 seconds. Costs 20 Mana. No cooldown.

- Adventurer's Poise - Increases the player's attack speed by 30%, and causes any ability that costs mana to also increase the next auto attack's damage by 2. Lasts 30 seconds. No cooldown. Costs 50 Mana.

# Dodge and Cast Interruption Rules

By default, dodge roll cancels the player's current cast.

Some abilities may ignore this rule.

Each ability should support interruption flags:

- CanBeUsedWhileCasting
- CancelsCurrentCast
- CanContinueDuringDodge

Default behavior:

- Normal casted abilities cannot be used while casting.
- Dodge roll can be used while casting.
- Dodge roll cancels the current cast.
- Mobility abilities may optionally be allowed while casting.
- Some casted abilities may continue during dodge or mobility action

## Examples

Fireball:
- CanBeUsedWhileCasting: false
- CancelsCurrentCast: false
- CanContinueDuringDodge: false

Dodge Roll:
- CanBeUsedWhileCasting: true
- CancelsCurrentCast: true

Blink:
- CanBeUsedWhileCasting: true
- CancelsCurrentCast: false

Mobile Channel:
- CanContinueDuringDodge: true

# Current Priorities:

- Movement
- Combat
- Boss Encounters
- Inventory
- Gear
- Vendor