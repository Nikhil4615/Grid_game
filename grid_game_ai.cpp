#include <bits/stdc++.h>
using namespace std;

void printboard(char board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool findwinner(char board[3][3], char player)
{
    // check for rows and columns
    for (int i = 0; i < 3; i++)
    {
        if (board[0][i] == player and board[1][i] == player and board[2][i] == player)
        {
            return true;
        }
        if (board[i][0] == player and board[i][1] == player and board[i][2] == player)
        {
            return true;
        }
    }
    // check for diagonals
    if (board[0][0] == player and board[1][1] == player and board[2][2] == player)
    {
        return true;
    }
    if (board[0][2] == player and board[1][1] == player and board[2][0] == player)
    {
        return true;
    }

    return false;
}

bool isfull(char board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
            {
                return false;
            }
        }
    }
    return true;
}

int evaluateboard(char board[3][3])
{
    if (findwinner(board, 'X'))
        return 1; // 'X' is the winner
    else if (findwinner(board, 'O'))
        return -1; // 'O' is the winner
    else
        return 0; // either the match is ongoing or has ended in a draw
}

int minimax(char board[3][3], bool ismaximize)
{
    int max_score = INT_MIN;
    int score = evaluateboard(board);
    if (score == 1 or score == -1)
        return score;
    if (isfull(board))
        return 0;

    if (ismaximize)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == ' ')
                {
                    board[i][j] = 'X';
                    int cur_score = minimax(board, false);
                    board[i][j] = ' ';
                    max_score = max(max_score, cur_score);
                }
            }
        }
        return max_score;
    }
    else
    {
        int min_score = INT_MAX;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == ' ')
                {
                    board[i][j] = 'O';
                    int cur_score = minimax(board, true);
                    board[i][j] = ' ';
                    min_score = min(min_score, cur_score);
                }
            }
        }
        return min_score;
    }
}

void findbestmove(char board[3][3])
{
    int bestmove = INT_MIN;
    int bestrow = -1;
    int bestcol = -1;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = 'X';
                int cur_move = minimax(board, false);
                board[i][j] = ' ';
                if (cur_move > bestmove)
                {
                    bestmove = cur_move;
                    bestrow = i;
                    bestcol = j;
                }
            }
        }
    }
    board[bestrow][bestcol] = 'X'; // Update the board with the best move for 'X'
    cout << "AI's Move: (" << bestrow << "," << bestcol << ")" << endl;
}

int main()
{
    char board[3][3] = {{' ', ' ', ' '},
                        {' ', ' ', ' '},
                        {' ', ' ', ' '}};

    cout << "Tic Tac Toe - AI vs User" << endl;
    cout << "AI is 'X', User is 'O'" << endl;
    cout << "Current board :" << endl;
    printboard(board);

    int userRow, userCol;

    while (true)
    {
        cout << "Enter your move (row and column, e.g., 1 2): ";
        cin >> userRow >> userCol;

        if (userRow < 0 || userRow >= 3 || userCol < 0 || userCol >= 3 || board[userRow][userCol] != ' ')
        {
            cout << "Invalid move. Try again." << endl;
            continue;
        }

        board[userRow][userCol] = 'O';

        if (findwinner(board, 'O'))
        {
            cout << "Congratulations! You win!" << endl;
            break;
        }
        else if (isfull(board))
        {
            cout << "The game is a draw!" << endl;
            break;
        }

        // AI's turn
        findbestmove(board);

        if (findwinner(board, 'X'))
        {
            cout << "AI wins! Better luck next time." << endl;
            break;
        }
        else if (isfull(board))
        {
            cout << "The game is a draw!" << endl;
            break;
        }

        cout << "Current board :" << endl;
        printboard(board);
    }

    return 0;
}
