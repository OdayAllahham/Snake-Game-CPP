# 🐍 Snake Game — C++

A simple console-based Snake Game built with **C++** as a practical project to apply Object-Oriented Programming (OOP) concepts and game-loop fundamentals.

## 🎮 About the Game

The player controls a snake using **W, A, S, D**.

The snake moves continuously, and the player can change its direction in real time. Eating food increases the snake's length and score.

The game ends when the snake:

* Hits the board boundary.
* Collides with itself.

## 🛠️ Technologies

* C++
* Object-Oriented Programming (OOP)
* Visual Studio
* Git & GitHub

## 🧱 Project Structure

The game is divided into several classes, each with a specific responsibility:

* **Snake** — Handles movement, direction, growth, collision with itself, and score.
* **Board** — Handles the game boundaries and position validation.
* **Food** — Stores the food position and value.
* **SnakeGame** — Coordinates the game flow, input, collisions, food generation, and game state.

## 🎯 Controls

| Key | Action     |
| --- | ---------- |
| `W` | Move Up    |
| `A` | Move Left  |
| `S` | Move Down  |
| `D` | Move Right |

## ▶️ How to Run

1. Clone the repository.
2. Open `SnakeGame.slnx` with Visual Studio.
3. Build the project.
4. Run the application.
5. Use `W`, `A`, `S`, `D` to control the snake.

## 📚 What I Practiced

This project was built to practice:

* Object-Oriented Design
* Classes and Objects
* Encapsulation
* Composition
* Separation of Responsibilities
* Game Loops
* Real-time keyboard input
* Collision Detection
* Random Position Generation
* Git and GitHub workflow

## 🚧 Future Improvements

Possible improvements include:

* Preventing the snake from immediately reversing direction.
* Adding a visible game border.
* Increasing the game speed as the score increases.
* Adding different types of food.
* Improving console rendering.
* Adding a start/restart screen.

---

**Built as a C++ practice project.**
