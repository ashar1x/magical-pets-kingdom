# Magical Pets Kingdom

A fantasy pet battle game with a full graphical interface, built in C++ using SFML as an OOP semester project. You pick your pets, train them, fight in the arena, manage a guild, and buy items from the shop.

---

## What is this?

A proper GUI game, not a console app. It has backgrounds, sprites, animated screens, and a working game loop with multiple states. Four fantasy pets to choose from, three arena battle modes, a training system, a shop, and a guild feature.

It was built as a second-semester OOP project and honestly went pretty far for that.

---

## Features

- **4 fantasy pets** with unique abilities: Dragon, Phoenix, Unicorn, Griffin
- **Arena battles** in 1v1, 2v2, and 4v4 formats
- **Training system** to level up your pet's stats (health, attack, defense, speed)
- **Item shop** with healing potions, buff potions, shields, and stamina items
- **Guild system** for player management
- **Full inheritance hierarchy** with a base Pet class and derived types, including a pure virtual `useAbility` method
- **State machine game loop** managing transitions across all screens smoothly
- **Custom backgrounds and sprite textures** for every screen

---

## OOP Concepts Used

This project was specifically built around OOP principles taught in the course:

- Inheritance (Pet base class, Dragon/Phoenix/Unicorn/Griffin as derived)
- Polymorphism (virtual `useAbility` and `clone` methods)
- Encapsulation (private/protected members with getters and setters)
- Operator overloading (`=`, `==` for Pet and Player)
- Copy constructors and destructors
- `unique_ptr` and dynamic memory management for pet collections
- Friend classes (Item accessing Pet internals)

---

## How to Run

> Windows only. Requires SFML 2.x which is already bundled in the External folder.

Open `Projecttt.sln` in Visual Studio and build in Debug mode. The SFML DLLs are already in the project folder so it should run out of the box.

Make sure you build as **x86 (32-bit)** since the included SFML libraries are compiled for x86.

---

## Project Structure

```
Projecttt/
├── main.cpp                 # game loop and state machine
├── Pet.h / Pet.cpp          # base class for all pets
├── Dragon / Phoenix /
│   Unicorn / Griffin        # derived pet classes with unique abilities
├── Player.h / Player.cpp    # player data, inventory, pet management
├── Guild.h / Guild.cpp      # guild system
├── Item.h / Item.cpp        # item types and effects
├── Shop.h / Shop.cpp        # shop logic
├── GameManager.h            # game state definitions
├── menus.h                  # all menu screens
├── ArenaBattleScreen.h      # arena combat screen
├── train.h                  # training screen
├── textures/                # pet and item sprites
├── backgrounds/             # screen backgrounds
└── External/SFML/           # bundled SFML library
```

---

## Notes

Second semester OOP project. The game has a lot going on for a course project: a real state machine, SFML rendering, sprite-based UI, and a reasonably clean class hierarchy. Some things are rough around the edges but the core loop works and it's actually playable.

---

## License

Feel free to use or learn from this. Credit appreciated but not required.
