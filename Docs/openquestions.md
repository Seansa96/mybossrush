# Open Questions

These are unresolved design questions. They should not block implementation unless directly relevant to the current task.

## Combat

- What is the exact global cooldown duration?
- Does Haste reduce the global cooldown, cast time, or both?
- How long is the ability queue window?
- Do all offensive abilities require a selected target?
- Can abilities be cast while out of range and then fire when in range, or do they fail immediately?
- Should auto-attacks continue during dodge rolls?
- Should auto-attacks trigger their full animation during all actions, or can they resolve mechanically without animation?

## Ability System

- Are resources consumed at cast start or cast completion?
- Does an ability enter cooldown at cast start or cast completion?
- Can cooldowns be refunded if a cast is canceled?
- Can damage-over-time effects critically strike?
- Can lifesteal apply to damage-over-time effects?
- How should “next auto-attack” effects be stored and consumed?
- Can multiple “next auto-attack” effects stack?

## Health and Shield

- Does shield have a maximum value?
- Does shield decay over time?
- Can negative shield anti-heal debt stack without limit?
- Should negative shield be visible in debug UI?

Current assumption for first implementation:
- Shield has no maximum.
- Shield does not decay.
- Negative shield is allowed.
- Negative shield is debug-visible only if needed.

## Gear and Stats

- What does each stat do mechanically?
- Which stats can appear on gear first?
- Can gear have multiple stat modifiers?
- Are gear upgrades linear or stat-specific?
- Should gear upgrades cost only gold or also materials?

## Inventory

- Does sending full-inventory loot to storage happen automatically or by player choice?
- Is storage chest capacity limited?
- Can deleted gear be recovered?
- Can gear be sold from storage or only from inventory?

## Vendor

- Does the vendor sell fixed items, unlock items after bosses, or both?
- Can the vendor upgrade equipped gear only, or any gear in inventory?
- Is there buyback for sold gear?

## Boss Progression

- Are bosses fought in a fixed sequence or selected from a menu?
- Does defeating a boss permanently unlock the next boss?
- Are boss rewards fixed, random, or mixed?
- Do bosses respawn for farming?

## Testing Branch

- How will “testing branch” behavior be represented?
  - Separate Git branch?
  - Debug flag?
  - Developer-only vendor?