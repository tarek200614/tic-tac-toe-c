# 🎮 Tic-Tac-Toe in C

> A console-based Tic-Tac-Toe game developed in C featuring modular architecture, move validation, player time tracking, game history logging, and a clean terminal interface.

![Language](https://img.shields.io/badge/Language-C-blue.svg)
![Build](https://img.shields.io/badge/Build-CMake-success)
![License](https://img.shields.io/badge/License-MIT-green)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-lightgrey)

---

# 📖 Overview

This project is a complete implementation of the classic Tic-Tac-Toe game using the C programming language.

The application was designed to reinforce fundamental programming concepts including:

- Structured programming
- Modular design
- Functions and procedures
- Structures
- File handling
- Input validation
- Game algorithms
- Time measurement
- Console interface development

The game allows two players to compete while recording every move and measuring each player's total thinking time.

---

# ✨ Features

- 🎮 Two-player gameplay
- 🧩 3×3 game board
- ✅ Move validation
- 🏆 Automatic winner detection
- 🤝 Draw detection
- ⏱ Player thinking time tracking
- 📝 Automatic game history logging
- 📂 History file generation
- 📊 Match summary
- 🖥 Clean console interface
- 🔄 Turn-based gameplay
- ❌ Prevents invalid moves

---

# 🏗 Project Structure

```
tic-tac-toe-c/
│
├── game/
│   ├── main.c
│   ├── game.c
│   ├── board.c
│   ├── board.h
│   ├── menu.c
│   ├── menu.h
│   ├── timer.c
│   ├── utils.c
│   ├── game-history.txt
│   └── CMakeLists.txt
│
├── docs/
│   └── project-specification.pdf
│
├── assets/
│   └── screenshots/
│
├── README.md
├── LICENSE
└── .gitignore
```

---

# 🎯 Gameplay

1. Launch the application.
2. Enter both player names.
3. Players alternate turns.
4. Enter board coordinates.
5. The game validates every move.
6. The board updates automatically.
7. The winner (or draw) is detected.
8. The game history is saved.
9. Player statistics are displayed.

---

# 📋 Rules

- Two players compete.
- Player 1 uses **X**.
- Player 2 uses **O**.
- Each turn requires entering:
  - Row (1–3)
  - Column (1–3)
- Occupied cells cannot be selected.
- The first player to align three symbols horizontally, vertically, or diagonally wins.
- If the board becomes full without a winner, the match ends in a draw.

---

# ⚙ Technologies

- C
- Standard Library
- CMake
- File I/O
- Structures
- Modular Programming

---

# 🚀 Build

## Using CMake

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

---

## Using GCC

```bash
gcc *.c -o tic-tac-toe
```

Run:

```bash
./tic-tac-toe
```

Windows:

```bash
tic-tac-toe.exe
```

---

# 📁 Game History

Each completed game is automatically recorded.

The history contains:

- Player names
- Winner
- Total moves
- Coordinates played
- Match result

Example:

```
Game #1

Winner : Player X

Moves

1. Player X -> (1,1)
2. Player O -> (2,2)
3. Player X -> (1,2)
...
---
```

---
# 📈 Future Improvements

- Single-player mode (AI)
- Minimax algorithm
- Difficulty levels
- Colored terminal output
- Undo move
- Save and load games
- Scoreboard
- Better UI
- Cross-platform compatibility
- Unit tests

---

# 📚 Learning Objectives

This project demonstrates:

- C programming
- Functions
- Modular architecture
- Structures
- Arrays
- Loops
- Conditions
- File handling
- Input validation
- Time management
- Algorithm implementation

---

# 👨‍💻 Author

**MEGHARI Abderrahmane Tarek**

AI Engineering Student

---

# ⭐ If you like this project

Give the repository a ⭐ on GitHub!
