#include <iostream>
#include <limits.h>

using namespace std;

const int SIZE = 3;
char board[SIZE][SIZE];

// Function to initialize the board
void initializeBoard() {
    char start = '1';
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = start++;
        }
    }
}

// Function to print the board
void printBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << board[i][j];
            if (j < SIZE - 1) cout << " | ";
        }
        cout << endl;
        if (i < SIZE - 1) cout << "--|---|--" << endl;
    }
}

// Function to check if there are moves left on the board
bool isMovesLeft() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return true;
    return false;
}

// Function to evaluate the board and return a score
int evaluateBoard(char player, char opponent) {
    // Check rows and columns
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            if (board[i][0] == player)
                return +10;
            else if (board[i][0] == opponent)
                return -10;
        }
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            if (board[0][i] == player)
                return +10;
            else if (board[0][i] == opponent)
                return -10;
        }
    }

    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == player)
            return +10;
        else if (board[0][0] == opponent)
            return -10;
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == player)
            return +10;
        else if (board[0][2] == opponent)
            return -10;
    }

    // If no one has won, return 0
    return 0;
}

// Minimax function
int minimax(char currentPlayer, char ai, char human, bool isMaximizing) {
    int score = evaluateBoard(ai, human);

    // If AI has won, return the evaluated score
    if (score == 10)
        return score;

    // If Human has won, return the evaluated score
    if (score == -10)
        return score;

    // If there are no more moves and no winner, return 0
    if (!isMovesLeft())
        return 0;

    // If it's the AI's turn (maximizing player)
    if (isMaximizing) {
        int best = INT_MIN;

        // Traverse all cells
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                // If the cell is empty
                if (board[i][j] != 'X' && board[i][j] != 'O') {
                    // Make the move
                    char backup = board[i][j];
                    board[i][j] = ai;

                    // Call minimax recursively and choose the maximum value
                    best = max(best, minimax(currentPlayer, ai, human, !isMaximizing));

                    // Undo the move
                    board[i][j] = backup;
                }
            }
        }
        return best;
    }
    // If it's the Human's turn (minimizing player)
    else {
        int best = INT_MAX;

        // Traverse all cells
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                // If the cell is empty
                if (board[i][j] != 'X' && board[i][j] != 'O') {
                    // Make the move
                    char backup = board[i][j];
                    board[i][j] = human;

                    // Call minimax recursively and choose the minimum value
                    best = min(best, minimax(currentPlayer, ai, human, !isMaximizing));

                    // Undo the move
                    board[i][j] = backup;
                }
            }
        }
        return best;
    }
}

// Find the best move for the AI
int findBestMove(char ai, char human) {
    int bestValue = INT_MIN;
    int bestMove = -1;

    // Traverse all cells
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            // If the cell is empty
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                // Make the move
                char backup = board[i][j];
                board[i][j] = ai;

                // Compute the minimax value for this move
                int moveValue = minimax(ai, ai, human, false);

                // Undo the move
                board[i][j] = backup;

                // If the value of the current move is better than the best move, update bestMove
                if (moveValue > bestValue) {
                    bestMove = i * SIZE + j + 1;
                    bestValue = moveValue;
                }
            }
        }
    }

    return bestMove;
}

bool placeMarker(int slot, char marker) {
    int row = (slot - 1) / SIZE;
    int col = (slot - 1) % SIZE;

    if (board[row][col] != 'X' && board[row][col] != 'O') {
        board[row][col] = marker;
        return true;
    }
    else {
        return false;
    }
}

bool checkWin(char marker) {
    // Check rows and columns
    for (int i = 0; i < SIZE; i++) {
        if ((board[i][0] == marker && board[i][1] == marker && board[i][2] == marker) ||
            (board[0][i] == marker && board[1][i] == marker && board[2][i] == marker)) {
            return true;
        }
    }
    // Check diagonals
    if ((board[0][0] == marker && board[1][1] == marker && board[2][2] == marker) ||
        (board[0][2] == marker && board[1][1] == marker && board[2][0] == marker)) {
        return true;
    }
    return false;
}

bool checkDraw() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                return false;
            }
        }
    }
    return true;
}

int main() {
    char human = 'X';
    char ai = 'O';
    char currentPlayer = human;

    initializeBoard();

    while (true) {
        printBoard();
        int slot;

        if (currentPlayer == human) {
            cout << "Player " << currentPlayer << ", enter your move (1-9): ";
            cin >> slot;
        }
        else {
            slot = findBestMove(ai, human);
            cout << "AI (" << ai << ") moves to slot " << slot << endl;
        }

        if (slot < 1 || slot > 9 || !placeMarker(slot, currentPlayer)) {
            if (currentPlayer == human) {
                cout << "Invalid move. Try again." << endl;
            }
            continue;
        }

        if (checkWin(currentPlayer)) {
            printBoard();
            if (currentPlayer == human) {
                cout << "Player " << currentPlayer << " wins!" << endl;
            }
            else {
                cout << "AI (" << ai << ") wins!" << endl;
            }
            break;
        }

        if (checkDraw()) {
            printBoard();
            cout << "It's a draw!" << endl;
            break;
        }

        // Switch players
        currentPlayer = (currentPlayer == human) ? ai : human;
    }


    return 0;
}
