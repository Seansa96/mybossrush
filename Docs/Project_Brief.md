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

Casts can be canceled.

Players can dodge during casts and cast recovery.

# Inventory

Maximum inventory Size of 30

All gear can be sold for gold.

Slot-based, no stacking.

Inventory only holds gear. Gold is just its own tracked currency that functions as a value to be added and subtracted, but cannot be negative.

# Classes

All classes have health and shield. Shield set to 0 by default and not visible on health bar unless > 0. Healing absorbs work as anti-heal debt, and put shield value below 0 and forces healing affects to add to Shield value first until it is >= 0.

Classes share auto-attack, jump, and dodge roll.

Have primary resource like mana or energy, secondary resource like combo points or holy power.



# Current Priorities:

- Movement
- Combat
- Boss Encounters
- Inventory
- Gear
- Vendor