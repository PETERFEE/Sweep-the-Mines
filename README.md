# Minesweeper

This is a classic implementation of the Minesweeper game built using C++ and the SFML (Simple and Fast Multimedia Library). The project features a configurable game board, a player leaderboard, and essential gameplay mechanics like pausing, debugging, and resetting the game.

---

## Features

-   **Welcome Screen:** Greets the player and prompts for a name before starting.
-   **Dynamic Board Configuration:** Board dimensions (columns, rows) and the number of mines are loaded from an external `config.cfg` file.
-   **Classic Gameplay:**
    -   **Left-click** to reveal a tile.
    -   **Right-click** to place or remove a flag.
-   **Game Timer:** Tracks the elapsed time in minutes and seconds.
-   **Mine Counter:** Displays the number of remaining mines (total mines minus flags placed).
-   **UI Controls:**
    -   **Smiley Face:** Resets the game board at any time. The face changes based on the game state (win, lose, or in-progress).
    -   **Debug Button:** Toggles a view that reveals the locations of all mines.
    -   **Pause/Play Button:** Freezes and unfreezes the game state and timer.
    -   **Leaderboard Button:** Opens a new window to display the fastest completion times.
-   **Leaderboard:** Saves the player's name and time upon winning, sorted by the fastest time.

---

## Dependencies

To compile and run this project, you will need:

-   A C++ compiler that supports C++11 or newer (like GCC/g++ or Clang).
-   The **SFML library** (version 2.5 or newer) installed on your system.

---

## How to Compile and Run

1.  **Clone the repository:**
    ```bash
    git clone <your-repository-url>
    cd <repository-directory>
    ```

2.  **Ensure SFML is linked:** Make sure your compiler knows where to find the SFML header files and libraries.

3.  **Compile the source code:**
    The following is a sample command for compiling with g++. You will need to link the SFML graphics, window, and system libraries.

    ```bash
    g++ main.cpp *.cpp -o minesweeper -lsfml-graphics -lsfml-window -lsfml-system
    ```
    *Note: The exact command may vary based on your operating system and how you installed SFML.*

4.  **Configure the game:**
    Before running, you can edit the `files/config.cfg` file to set the board dimensions and mine count. The file should contain three numbers separated by spaces:
    `[columns] [rows] [mine_count]`
    For example:
    `25 16 50`

5.  **Run the executable:**
    ```bash
    ./minesweeper
    ```

---

## File Structure
