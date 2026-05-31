# Retro Snake Game (C++ & Raylib)

A lightweight, high-performance Retro Snake game developed in modern C++ utilizing the **Raylib** ecosystem. The game uses an object-oriented paradigm to modularize components into a clean game loop pipeline, incorporating graphics masking, dynamic directional asset manipulation, state mechanics, and audio feedback layers.

---

## 🎮 Gameplay Demo

🕹️ Check out the game mechanics, smooth head rotation, and boundary tracking in action:

https://github.com/user-attachments/assets/37662585-7116-491e-b5be-d7cb5dd1a70e

## 🚀 Technical Core Logic Implementations

### 1. Dynamic Head Rotation (Multi-Texture Approach)
To avoid coordinate offset errors, matrix transformations, or pixel blur caused by dynamic GPU rotation inside the render pipeline, the engine implements a **pre-baked asset matrix**. 
* During class initialization, the base `snake.png` graphic is processed on the CPU using `ImageRotate()`.
* Four separate directional orientations (`headtextureUp`, `headtextureDown`, `headtextureLeft`, `headtextureRight`) are generated and uploaded to VRAM once.
* The `draw()` loop dynamically switches between these textures using pointer selection matching the `direction` vector context.

### 2. Fast Key-Press Ghosting Prevention (Input Buffer Flag)
A standard grid-based issue involves rapid input changes (e.g., traveling right, pressing down then left quickly before the movement timer resolves), which tricks the validator into causing self-collision.
* This is solved via a gatekeeping status flag: `directionChange`.
* Once an input is certified, `directionChange` switches to `false`, intercepting and ignoring subsequent arrow triggers.
* The flag is reset to `true` exclusively inside the fixed-step `update()` sequence, ensuring only one legal programmatic directional modification is committed per execution step.

### 3. Procedural Random Food Spawning & Anti-Overlap Checks
Food generation uses a safe-allocation validation structure to ensure it never anchors on an active game entity coordinate.
* The location is derived procedurally via `GetRandomValue()`.
* The `genRandomPos()` method tests the generated vector against the entire snake body sequence using a linear scan loop (`ElementInDeque()`).
* If a collision mismatch is caught, the generation sequence re-rolls until an open grid cell is found.

### 4. Mathematical Vector-Based Movement
Instead of manually processing indexing values across coordinates, position translation is handled directly using vector space mathematics:
* The snake’s coordinate layout relies on a double-ended queue (`std::deque<Vector2>`).
* On every step trigger, the trailing entity tail segment is stripped from the stack via `pop_front()`.
* A new front element is appended to the lead head index by applying raymath vector aggregation: `Vector2Add(body[last_index], direction)`.

### 5. Boundary & Tail Collision Matrices
* **Screen Collision:** The head's vector matrix elements are matched against game bounds. If index values hit extreme values (`-1` or global `cellCount`), the application calls a terminal state interrupt.
* **Self-Collision Matrix:** The head block coordinate evaluates against every other sequence chunk inside the container. An absolute duplicate coordinates vector match instantly routes execution into the `GameOver()` pipeline.

### 6. Interactive Game States & Adaptive Re-initialization
The gameplay state machine alternates fluidly between execution and pause structures using a `running` flag state:
* When a collision trigger is logged, execution routes to `GameOver()`, resetting the score tracking metrics and spawning food inside clear cells.
* The application suspends active state updates, remaining stationary on screen until the player presses any valid control key. The first press registers a new trajectory vector and sets `running = true` to seamlessly resume play.

---

## 🎨 Asset Layer Specifications

* **Audio Pipelines:** Integrated via standard audio stream components (`InitAudioDevice()`). Handles custom high-frequency `.mp3` spatial channels for bite actions and boundary wall collisions.
* **Alpha Clipping Mask:** The snake body blocks use runtime alpha masking features. A procedural circle mask canvas is superimposed onto the original `body.png` data square using `ImageAlphaMask()` to soften edge transitions.

---

## 🛠️ Build and Compilation Structure

The compilation setup leverages the template configuration workspace, referencing specific compiler absolute paths directly on your local system drive.

### Recommended Native Workflow
1. Open the project **Root Directory** inside VS Code (`File` -> `Open Folder...`).
2. Make sure you have your main source file `snakeGame.cpp` focused on your screen workspace layout.
3. Trigger the standard task compilation macro: **`Ctrl + Shift + B`**.
4. Select **`build debug`** from the command layout console to generate the active executable binary file.
