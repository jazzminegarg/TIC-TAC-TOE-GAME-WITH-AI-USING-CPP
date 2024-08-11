
# Tic-Tac-Toe Game in C++

## Introduction

This is a simple command-line Tic-Tac-Toe game implemented in C++. The game allows a human player to compete against an AI opponent. The AI uses the Minimax algorithm to determine the best possible move, ensuring a competitive game experience.

## Features

- **Human vs AI Gameplay**: The player can compete against the AI, which plays optimally using the Minimax algorithm.
- **Command-line Interface**: The game runs in the terminal, where players can input their moves.
- **Win, Draw, and Invalid Move Detection**: The game can detect when a player wins, when the game is a draw, or if a player has made an invalid move.
- **Smart AI**: The AI never loses and will either win or draw, depending on the player's moves.

## How to Play

1. The game initializes a 3x3 board with slots numbered 1 to 9.
2. The human player is assigned the symbol `X`, while the AI is assigned the symbol `O`.
3. The human player always makes the first move by selecting a slot number between 1 and 9.
4. After the human player moves, the AI calculates its best move using the Minimax algorithm and places `O` in the corresponding slot.
5. The game continues until either the human or the AI wins, or the board is filled, resulting in a draw.

### Controls

- **Move**: Enter the slot number (1-9) corresponding to the desired position on the board when prompted.
- **Winning Conditions**: A player wins by placing three of their symbols (`X` or `O`) in a row, column, or diagonal.
- **Draw**: The game ends in a draw if all slots are filled and no player has won.

### Example Gameplay

```
1 | 2 | 3
--|---|--
4 | 5 | 6
--|---|--
7 | 8 | 9

Player X, enter your move (1-9): 5
AI (O) moves to slot 1

O | 2 | 3
--|---|--
4 | X | 6
--|---|--
7 | 8 | 9

...
```

## Running the Game

### Prerequisites

- A C++ compiler (e.g., `g++`, `clang`).

### Compilation

To compile the game, use the following command:

```bash
g++ -o tictactoe tictactoe.cpp
```

### Running the Game

To run the game, use the following command:

```bash
./tictactoe
```

## Code Overview

### Key Functions

- `initializeBoard()`: Initializes the game board with slot numbers 1-9.
- `printBoard()`: Displays the current state of the game board.
- `isMovesLeft()`: Checks if there are any moves left on the board.
- `evaluateBoard(player, opponent)`: Evaluates the board to determine if the AI or human player has won.
- `minimax(currentPlayer, ai, human, isMaximizing)`: Implements the Minimax algorithm to calculate the best possible move for the AI.
- `findBestMove(ai, human)`: Finds and returns the best move for the AI.
- `placeMarker(slot, marker)`: Places the player's marker on the selected slot.
- `checkWin(marker)`: Checks if the given marker has won the game.
- `checkDraw()`: Checks if the game has ended in a draw.

## License

This project is open-source and available under the MIT License.
