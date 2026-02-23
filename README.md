# Tiny RPG Combat Simulator

A simple text-based combat simulator.

## GoalS
After several years working primarily in higher-level languages, I wanted to re-enforce strong C++ fundamentals and instincts.
This project represents intentional repetition and iteration toward that goal.
- [x] Object-oriented design and clear behavior ownership
- [x] Inheritance, polymorphism
- [x] Header & implementation separation, forward declarations vs full definitions
- [x] Virtual functions
- [x] Classes vs structs
- [x] References vs pointers (ownership vs non-ownership semantics)
- [x] Value vs reference semantics
- [x] Const-correctness
- [x] Custom exception types
- [x] Operator overloading
- [x] Object lifetimes
- [x] Optional ownership
- [ ] Memory management
- [ ] Smart pointers
- [ ] Unit testing

## Architecture Highlights

- `Character` base type with derived `Player` and `Enemy` 
- `CombatManager` orchestrates encounter resolution
- `Game` owns player creation & core game loop
- `EventLogger` abstracts presentation from domain logic

## Future Improvements
- Introduce unique combat abilities
- Allow player stat allocation
- Experiment with ECS-style system for buffs, gear, etc.
- Peristant player character

## Example Output
```
Combat has begun!
-----------------------------------------------
Turn 1: trollman hits OurHero for 2 damage
Turn 1: OurHero hits trollman for 2 damage
trollman was defeated!
OurHero gained 10 experience!
OurHero is now level 3!
Name: OurHero
Level: 3
HP: 11/11
Attack: 3
Dexterity: 3
```