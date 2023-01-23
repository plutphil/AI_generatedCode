#include <iostream>

using namespace std;
class TicTacToeAI {
private:
    bool gameOver; // flag to check if the game is over

public:
    char aiPlayer; // the AI's chosen player (either 'X' or 'O')
    char opponentPlayer; // the opponent's player (either 'X' or 'O')
    char board[3][3]; // 2D array representing the current tic tac toe board
    // Constructor to initialize the board, AI player, and opponent player
    TicTacToeAI(char aiPlayer) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board[i][j] = '-'; // initialize all spaces to be empty
            }
        }
        this->aiPlayer = aiPlayer;
        opponentPlayer = (aiPlayer == 'X') ? 'O' : 'X'; // set the opponent player
        gameOver = false;
    }

    // Function to make a move for the AI
    void makeMove() {
        int bestMoveX, bestMoveY; // coordinates for the best move

        // Check for winning move
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '-') {
                    board[i][j] = aiPlayer;
                    if (checkWin()) {
                        bestMoveX = i;
                        bestMoveY = j;
                        board[i][j] = '-';
                        goto move;
                    }
                    board[i][j] = '-';
                }
            }
        }

        // Check for blocking move
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '-') {
                    board[i][j] = opponentPlayer;
                    if (checkWin()) {
                        bestMoveX = i;
                        bestMoveY = j;
                        board[i][j] = '-';
                        goto move;
                    }
                    board[i][j] = '-';
                }
            }
        }

        // Check for best move
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '-') {
                    bestMoveX = i;
                    bestMoveY = j;
                    goto move;
                }
            }
        }

    move:
        board[bestMoveX][bestMoveY] = aiPlayer;
    }

    // Function to check if the AI or the opponent has won
    bool checkWin() {
        // Check rows
        for (int i = 0; i < 3; i++) {
            if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && (board[i][0] == aiPlayer || board[i][0] == opponentPlayer)) {
                return true;
            }
        }

        // Check columns
        for (int i = 0; i < 3; i++) {
            if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && (board[0][i] == aiPlayer || board[0][i] == opponentPlayer)) {
                return true;
            }
        }
        // Check diagonals
        if ((board[0][0] == board[1][1] && board[1][1] == board[2][2] && (board[0][0] == aiPlayer || board[0][0] == opponentPlayer)) ||
            (board[0][2] == board[1][1] && board[1][1] == board[2][0] && (board[0][2] == aiPlayer || board[0][2] == opponentPlayer))) {
            return true;
        }

        return false;
    }

    // Function to check if the game is a draw
    bool checkDraw() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '-') {
                    return false;
                }
            }
        }
        return true;
    }

    // Function to check if the game is over
    bool isGameOver() {
        if (checkWin() || checkDraw()) {
            gameOver = true;
        }
        return gameOver;
    }

    // Function to print the current state of the board
    void printBoard() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
    }
};
int main() {
    char aiPlayer;
    cout << "Enter your player (X or O): ";
    cin >> aiPlayer;
    TicTacToeAI game(aiPlayer);

    while (!game.isGameOver()) {
        char opponentMoveX, opponentMoveY;
        cout << "Enter your opponent's move (x y): ";
        cin >> opponentMoveX >> opponentMoveY;
        int x = opponentMoveX - '0';
        int y = opponentMoveY - '0';
        game.board[x][y] = game.opponentPlayer;

        game.makeMove();
        game.printBoard();

        if (game.checkWin()) {
            if (game.aiPlayer == 'X') {
                cout << "X wins!" << endl;
            } else {
                cout << "O wins!" << endl;
            }
            break;
        } else if (game.checkDraw()) {
            cout << "It's a draw!" << endl;
            break;
        }
    }
    return 0;
}
