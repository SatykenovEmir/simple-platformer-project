# Simple Platformer
A basic 2D platformer built in C++ using [raylib](https://www.raylib.com). The game features multiple levels of increasing complexity, new mechanics such as double jump, and various screens (Title, Game, Pause, Victory, and Game Over).

![Platformer Preview](https://i.imgur.com/n01Q4Z8.png)

## Introduction
The goal of this project is to create a simple [Platformer](https://en.wikipedia.org/wiki/Platformer) game. The player navigates through levels by running, jumping, and collecting items, while avoiding (or fighting) enemies and solving simple puzzles. The game demonstrates structured programming principles, such as loops, selections, functions, and consistent code formatting.

## Core Requirements

1. **Title/Menu Screen**
    - Displays the game logo or text title and prompts the user to start.
    - May also include an instructions option or a quit option.

2. **Game Screen**
    - The main gameplay area where the player can move the character, collect items, and find the exit to move on to the next level.
    - At least five levels are present, each accessible by passing through the level’s exit.
    - The ultimate goal is to complete all levels.

3. **Pause Screen**
    - Activated by pressing the Escape key (or another specified key).
    - Displays a pause message; pressing Escape again resumes the game.

4. **Victory Screen**
    - Shows a congratulatory message after the player completes the final level.
    - An optional animation or background effect may be displayed to signify success.

## Feature Requirements

1. **Four Extra Levels**
    - Beyond any initial example level, add at least four more levels with increasing difficulty.

2. **Three New Elements**
    - Could be items, enemies, or obstacles. Ensure at least one is an enemy, for instance a Slime that patrols a platform.

3. **Game Over Screen**
    - Triggered if the player loses the game, such as when health is depleted or an enemy collision is fatal.
    - Allows returning to the title screen.

4. **At Least Three New Sounds**
    - For events like collecting an item, enemy collisions, final-exit passage, or other game actions.

5. **Music Track**
    - At least one royalty-free or appropriately licensed music track playing on a screen (e.g. title screen music or in-game music).

6. **New Mechanics**
    - For example, a **double jump** allowing a second jump in mid-air, a special dash, new way to collect items, or puzzle interactions.

## Additional Requirements

- Maintain clear commits in your version control history. Each feature or bug fix should be recorded, demonstrating regular progress.
- Create a `Game.md` file (this document) describing the game and listing implemented features. Even partial implementations are acceptable.
- The project must be **playable** and easy to set up. Place all assets in a `data` folder.

## Deliverables

- The code resides in a `<repository>` directory, along with:
    - A `data` subdirectory containing images, sounds, fonts, music, etc.
    - A `platformer.cpp` with the main game loop.
    - Several header files (e.g. `globals.h`, plus any needed for levels, player, assets, etc.).
    - This `Game.md` describing the game and its features.

A suggested folder structure:

```
<repository>/
├── data/
│   ├── fonts/
│   ├── images/
│   ├── music/
│   └── sounds/
├── platformer.cpp
├── globals.h
├── assets.h
├── level.h
├── player.h
├── utilities.h
└── Game.md
```

Push commits regularly (daily or after major changes), and submit your repository link before the deadline.

## Project Setup Notes

1. **Raylib Installation**  
   Set up raylib as done in previous assignments/labs.
2. **Working Directory**  
   Configure your IDE (e.g., CLion) so that the working directory points to the root project folder where the `data` folder is located.
    - Failure to do so may result in missing textures or sounds.
3. **CMake / Build Files**  
   If using CMake, ensure your `CMakeLists.txt` includes `find_package(raylib REQUIRED)` or references to the local raylib installation.

## How to Run

1. **Clone the repository** or download the project folder.
2. **Open** in your IDE or run CMake from the command line:
   ```sh
   mkdir build && cd build
   cmake ..
   make
   ./platformer
   ```
3. **Ensure the data folder** (with images, sounds, etc.) is in the correct location relative to the executable.

## Credits
- **Author**: Satykenov Emir

---

**Copy and paste** this entire text for your `Game.md`. Adapt images, assets, or references as you wish.