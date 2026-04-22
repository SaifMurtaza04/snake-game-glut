# 🐍 Snake Game (C++ / OpenGL / FreeGLUT)

A feature-rich Snake game implemented in **C++ using OpenGL (FreeGLUT)**.
This project enhances the classic Snake gameplay with multiple fruits, special bonus items, and randomly generated hurdles, while maintaining a modular and organized code structure.

---

## 📁 Project Structure

```
.
├── game-release.cpp     # Main game logic and gameplay loop
├── util.cpp             # Rendering utilities and helper functions
├── util.h               # Function declarations and shared resources
├── Makefile             # Build automation
├── install-libraries.sh # Script to install dependencies (Linux)
```

---

## 🎮 Features

* 🐍 Smooth snake movement with body growth mechanics
* 🍎 Multiple fruits with randomized placement
* ⭐ Special fruit with bonus scoring
* 🚧 Randomly generated hurdles (obstacles)
* 🔄 Screen wrapping (edge teleportation)
* 📊 Score and high score tracking
* 📈 Visual progress bar
* ⚡ Timer-based game loop using GLUT

---

## 🛠️ Technologies Used

* **C++**
* **OpenGL**
* **FreeGLUT**
* **Makefile (build automation)**

---

## ⚙️ Installation & Setup

### 🐧 Linux

Run the provided script:

```bash
chmod +x install-libraries.sh
./install-libraries.sh
```

Then build:

```bash
make
```

Run:

```bash
./snake
```

---

### 🪟 Windows (MSYS2 MinGW64)

Install dependencies:

```bash
pacman -S mingw-w64-x86_64-freeglut
```

Build using Makefile:

```bash
make
```

Or manually:

```bash
x86_64-w64-mingw32-gcc game-release.cpp util.cpp -o snake.exe -lfreeglut -lopengl32 -lglu32
```

Run:

```bash
./snake.exe
```

---

## 🎯 Controls

| Key | Action     |
| --- | ---------- |
| ↑   | Move Up    |
| ↓   | Move Down  |
| ←   | Move Left  |
| →   | Move Right |
| ESC | Exit Game  |

---

## 🧠 Game Mechanics

* Eating fruits:

  * Increases score (+10)
  * Increases snake length
* Special fruit:

  * Appears at intervals
  * Grants bonus score (+20)
* Hurdles:

  * Randomly generated obstacles
  * Collision results in game over
* Self-collision also ends the game

---

## 🚧 Known Issues / Improvements

* Minor collision precision inconsistencies
* No restart menu after game over
* High score is not saved persistently

---

## 🚀 Future Enhancements

* 🎵 Sound effects and background music
* 🧩 Multiple difficulty levels
* 💾 Save high score to file
* 🖥️ GUI start/restart menu
* 🎨 Improved visuals and animations

---

## 👨‍💻 Author

**Muhammad Saif Murtaza**
FAST-NUCES

---

## 📜 License

This project is open-source and available under the MIT License.
