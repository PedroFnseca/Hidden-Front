# Folder Structure

This project follows a **feature-based architecture**, where each directory is responsible for a specific part of the application. Source (`.c`) and header (`.h`) files should remain together within their respective modules.

```text
project/
├── assets/
│   ├── fonts/         # Fonts
│   ├── images/
│   │   ├── cards/     # Card sprites
│   │   ├── characters/# Character sprites and animations
│   │   ├── maps/      # Tilesets and map textures
│   │   ├── ui/        # Interface elements
│   │   └── effects/   # Visual effects
│   ├── sounds/        # Sound effects
│   ├── music/         # Background music
│   └── shaders/       # Shader files (optional)
│
├── data/
│   └── config.txt     # User configuration (language, volume, etc.)
│
├── src/
│   ├── core/          # Engine initialization and core systems
│   ├── game/          # Game flow and match state
│   ├── entities/      # Players, units, and game objects
│   ├── cards/         # Card definitions and deck management
│   ├── systems/       # Combat, movement, visibility, turns, etc.
│   ├── multiplayer/   # Networking and synchronization
│   ├── scenes/        # Menu, lobby, gameplay, results
│   ├── ui/            # User interface and HUD
│   ├── utils/         # Shared utilities and helpers
│   └── main.c         # Application entry point
│
├── docs/              # Project documentation
```

## Guidelines

* Organize files by **feature**, not by file type.
* Keep `.c` and `.h` files together in the same module.
* Each directory should have a **single responsibility**.
* Avoid large source files; split them into smaller modules when necessary.
* Minimize dependencies between modules to keep the architecture modular and maintainable.
* Store assets in folders based on their purpose (characters, cards, UI, audio, etc.).
* Aways avoid use comments in the code, instead use documentation files to explain the architecture and design decisions.
* Use `snake_case` as the standard naming convention for functions and variables.
* When using constant values (like screen dimensions, timers, button sizes), use `#define` in the respective `.h` file to maintain organization and avoid magic numbers in `.c` files.
* Always use `get_font` from the internal **Font Manager** (`font_manager_t`) to load `.ttf` files dynamically instead of manual loading, ensuring memory caching and auto-cleanup.
* **Do not use `switch-case` statements.** Use hashmaps or lookup tables (arrays) to map states and values in `O(1)` time complexity for better performance.
* **Localization and configuration:** Must use `LocalizationManager` for texts and `ConfigManager` for persisting settings. The localization implementation strictly uses `O(1)` array lookups instead of `switch-case`.