# The Art of Theft
A terminal-based art heist simulation game where players build their criminal reputation through strategic museum thefts. Built in C as a learning project to explore game mechanics, decision trees, risk/reward systems, and atmospheric narrative design. Inspired by the book "The Art Thief: A True Story of Love, Crime, and a Dangerous Obsession" by Michael Finkel.

## Features
**Core Gameplay**
- Plan and execute art heists across 4 unique museums with distinct security profiles
- Choose from 6 carefully crafted artworks, each with unique descriptions and risk levels
- Strategic planning system with three approach options affecting success rates and heat generation
- Progressive reputation system that unlocks access to more prestigious (and dangerous) venues
- Dynamic heat system creating escalating tension and risk throughout the game

**Atmospheric Design**
- Rich narrative descriptions for museums, artworks, and heist scenarios
- Noir-inspired writing style emphasizing tension and criminal underworld atmosphere
- Meaningful consequences for every decision affecting long-term gameplay strategy
- Multiple win/lose conditions based on heat accumulation or collection completion

## Project Structure
```
art-thief/
├── art-thief.c         # Main game logic and mechanics
└── README.md           # This documentation
```

## Installation & Usage
```bash
gcc -o art_thief art-thief.c
./art_thief
```

## Game Mechanics
**Museums & Access**
- **The Corner Gallery** - Entry-level venue with minimal security (Reputation: 1)
- **Riverside Museum** - Mid-tier target with balanced risk/reward (Reputation: 3)
- **Metropolitan Arts Center** - High-security prestigious museum (Reputation: 6)
- **The Private Collection** - Ultra-exclusive, invitation-only gallery (Reputation: 8)

**Planning System**
- **Quick & Dirty** - Higher risk, minimal preparation (-2 success bonus, +2 heat)
- **Standard Approach** - Balanced strategy (0 success bonus, +1 heat)
- **Elaborate Scheme** - Lower risk, maximum preparation (+3 success bonus, 0 heat)

**Risk Management**
- Heat accumulates with each heist based on artwork notoriety and planning approach
- Game ends at 15 heat points (caught by authorities)
- Reputation grows with successful high-risk heists, unlocking better venues
- Collection limited to 8 pieces, encouraging strategic artwork selection

## Sample Gameplay
```
THE ART OF THEFT
================

You are a discerning art thief with a taste for the extraordinary.
Build your reputation, but don't let the heat get too high...

--- STATUS ---
Reputation: 1 | Heat: 0/15 | Collection: 0/8
Portfolio Value: $0

Available targets:

1. The Corner Gallery
   A small, poorly-lit gallery where security naps during lunch
   Security: 1 | Crowds: 2 | Prestige: 1

2. [LOCKED] Riverside Museum (Reputation 3 required)

3. [LOCKED] Metropolitan Arts Center (Reputation 6 required)

4. [LOCKED] The Private Collection (Reputation 8 required)

Choose museum: 1

Available pieces:

1. "Melancholy #3" by Sarah Chen
   A haunting portrait that seems to follow you
   Value: $2500 | Risk: 2

2. "The Iron Rose" by Viktor Kozlov
   Twisted metal that somehow captures fragility
   Value: $8000 | Risk: 4

Choose artwork: 1

--- THE HEIST ---
Target: "Melancholy #3" by Sarah Chen
Location: The Corner Gallery
Description: A haunting portrait that seems to follow you

--- PLANNING PHASE ---
How do you want to approach this?

1. Quick and dirty - minimal planning, higher risk
2. Standard approach - balanced risk and reward
3. Elaborate scheme - lower risk, but more time and resources

Choose approach: 2

You spend a few days casing the joint. Standard but effective.

Executing the heist...
Difficulty: 6 | Your roll: 12

--- SUCCESS ---
The piece is yours. A haunting portrait that seems to follow you
Added to collection! Reputation increased.

Continue your criminal career? (yes/no):
```

## Technical Implementation
**Game Systems**
- Struct-based data modeling for museums, artworks, and player state
- Probability-based success calculation using dice roll mechanics
- Progressive difficulty scaling through reputation-gated content
- State management for persistent player progress throughout session

**Code Architecture**
- Modular function design with clear separation of concerns
- Input validation and error handling for robust user experience
- Clean formatting and professional output presentation
- Memory-efficient static arrays for game data storage

## Technical Concepts
- C structs and data modeling
- Random number generation and probability systems
- Boolean logic and conditional game flow
- String manipulation and formatted output
- **Game state management and progression systems**
- **Risk/reward balance and player decision psychology**
- **Atmospheric writing and narrative integration in code**

## Game Design Philosophy
**Tension Through Consequences**
- Every action has meaningful impact on future gameplay options
- Heat system creates mounting pressure and strategic decision-making
- Failed heists still advance the narrative and increase difficulty

**Atmospheric Immersion**
- Rich descriptions replace generic game mechanics exposition
- Noir-inspired tone maintains thematic consistency
- Player agency through meaningful choice rather than random outcomes

**Progressive Complexity**
- Simple early decisions build to complex late-game risk management
- Reputation system rewards bold play while increasing stakes
- Multiple win conditions allow different player strategies

## Future Enhancements
- **Expanded Content**
  - Additional museums with unique security challenges
  - Seasonal events and limited-time high-value targets
  - Art fencing mechanics and underground market simulation
  - Rival thief encounters and competitive elements

- **Advanced Mechanics**
  - Equipment system for specialized heist tools
  - Skill trees for different criminal specializations
  - Dynamic pricing based on art market fluctuations
  - Save/load functionality for persistent campaigns

- **Enhanced Narrative**
  - Branching storylines based on player reputation and choices
  - Character development through heist success/failure consequences
  - Multiple ending scenarios reflecting different criminal career paths
  - Interactive dialogue system with museum contacts and fences

## Learning Outcomes
This project provided hands-on experience with:
- Game mechanics design and balance testing
- Player psychology and decision-making motivation
- Atmospheric writing integration with code structure
- **Risk/reward system implementation and tuning**
- **Narrative-driven programming and immersive text design**
- **Progressive difficulty and content gating strategies**
- Random number generation for fair but unpredictable outcomes
- State management for complex multi-step game interactions

---
*Learning project focused on game design principles, atmospheric programming, and player engagement through meaningful choice mechanics.*