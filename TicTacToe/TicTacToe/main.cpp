#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <limits>

using namespace std;

const int ROWS = 3;
const int COLS = 3;

void runGame();
void printCurrentBoard(string gameBoard[ROWS][COLS]);
void getUserInput(bool xTurn, string gameBoard[ROWS][COLS]);

string getWinner(string gameBoard[ROWS][COLS]);

bool cell_IsEmpty(int row, int col, string gameBoard[ROWS][COLS]);
bool isBoardFull(string gameBoard[ROWS][COLS]);

int main()
{
    runGame();
    return 0;
}

void runGame()
{
    string gameBoard[ROWS][COLS] =
    {
        {" ", " ", " "},
        {" ", " ", " "},
        {" ", " ", " "}
    };

    srand(time(0));

    bool xTurn = rand() % 2;
    string winner = "";

    cout << (xTurn ? "X" : "O") << " starts!\n";

    while (winner == "" && !isBoardFull(gameBoard))
    {
        printCurrentBoard(gameBoard);

        if (xTurn)
            cout << "\nX's Turn\n";
        else
            cout << "\nO's Turn\n";

        getUserInput(xTurn, gameBoard);

        winner = getWinner(gameBoard);

        xTurn = !xTurn;
    }

    printCurrentBoard(gameBoard);

    if (winner != "")
    {
        cout << "\n" << winner << " wins!\n";
    }
    else
    {
        cout << "\nCat's Game! Tie!\n";
    }
}

void printCurrentBoard(string gameBoard[ROWS][COLS])
{
    cout << "\n";

    for (int i = 0; i < ROWS; i++)
    {
        cout << "|";

        for (int j = 0; j < COLS; j++)
        {
            cout << gameBoard[i][j] << "|";
        }

        cout << "\n";
    }
}



void getUserInput(bool xTurn, string gameBoard[ROWS][COLS])
{
    string player = xTurn ? "X" : "O";

    string line;
    int userRow;
    int userCol;

    while (true)
    {
        cout << "\nPlayer " << player
            << ", enter row and column (example: 1 1): ";

        getline(cin, line);

        stringstream ss(line);

        if (!(ss >> userRow >> userCol))
        {
            cout << "Invalid input.\n";
            continue;
        }

        if (userRow < 0 || userRow > 2 ||
            userCol < 0 || userCol > 2)
        {
            cout << "Coordinates must be between 0 and 2.\n";
            continue;
        }

        if (!cell_IsEmpty(userRow, userCol, gameBoard))
        {
            cout << "Cell already occupied.\n";
            continue;
        }

        gameBoard[userRow][userCol] = player;
        break;
    }
}


bool cell_IsEmpty(int row, int col, string gameBoard[ROWS][COLS])
{
    return gameBoard[row][col] == " ";
}

string getWinner(string gameBoard[ROWS][COLS])
{
    // Rows
    for (int row = 0; row < ROWS; row++)
    {
        if (gameBoard[row][0] != " " &&
            gameBoard[row][0] == gameBoard[row][1] &&
            gameBoard[row][1] == gameBoard[row][2])
        {
            return gameBoard[row][0];
        }
    }

    // Columns
    for (int col = 0; col < COLS; col++)
    {
        if (gameBoard[0][col] != " " &&
            gameBoard[0][col] == gameBoard[1][col] &&
            gameBoard[1][col] == gameBoard[2][col])
        {
            return gameBoard[0][col];
        }
    }

    // Top-left to bottom-right
    if (gameBoard[0][0] != " " &&
        gameBoard[0][0] == gameBoard[1][1] &&
        gameBoard[1][1] == gameBoard[2][2])
    {
        return gameBoard[0][0];
    }

    // Bottom-left to top-right
    if (gameBoard[2][0] != " " &&
        gameBoard[2][0] == gameBoard[1][1] &&
        gameBoard[1][1] == gameBoard[0][2])
    {
        return gameBoard[2][0];
    }

    return "";
}

bool isBoardFull(string gameBoard[ROWS][COLS])
{
    int filledCells = 0;

    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            if (gameBoard[row][col] != " ")
            {
                filledCells++;
            }
        }
    }

    return filledCells == 9;
}