#include <bits/stdc++.h>
using namespace std;

#define playerSymbol 'X'
#define computerSymbol 'O'

void printCotainer(vector<vector<char>> grid)
{
    for (int i = 0; i < grid.size(); i++)
    {
        cout << grid[i][0] << " | " << grid[i][1] << " | " << grid[i][2] << endl;
        if (i != 2)
            cout << "- + - + -" << endl;
    }
}

bool anyOneWonTheGame(vector<vector<char>> grid, char symbol)
{
    if ((grid[0][0] == symbol and grid[0][1] == symbol and grid[0][2] == symbol) or (grid[1][0] == symbol and grid[1][1] == symbol and grid[1][2] == symbol) or (grid[2][0] == symbol and grid[2][1] == symbol and grid[2][2] == symbol) or (grid[0][0] == symbol and grid[1][0] == symbol and grid[2][0] == symbol) or (grid[0][1] == symbol and grid[1][1] == symbol and grid[2][1] == symbol) or (grid[0][2] == symbol and grid[1][2] == symbol and grid[2][2] == symbol) or (grid[0][0] == symbol and grid[1][1] == symbol and grid[2][2] == symbol) or (grid[0][2] == symbol and grid[1][1] == symbol and grid[2][0] == symbol))
    {
        return true;
    }
    else
        return false;
}

bool isFinished(vector<vector<char>> grid, int pos, char symbol)
{

    switch (pos)
    {
    case 1:
        return (grid[0][0] == ' ');
    case 2:
        return (grid[0][1] == ' ');
    case 3:
        return (grid[0][2] == ' ');
    case 4:
        return (grid[1][0] == ' ');
    case 5:
        return (grid[1][1] == ' ');
    case 6:
        return (grid[1][2] == ' ');
    case 7:
        return (grid[2][0] == ' ');
    case 8:
        return (grid[2][1] == ' ');
    case 9:
        return (grid[2][2] == ' ');
    default:
        return false;
    }
}

void putSymbol(vector<vector<char>> &grid, int pos, char symbol)
{
    switch (pos)
    {
    case 1:
        grid[0][0] = symbol;
        break;
    case 2:
        grid[0][1] = symbol;
        break;
    case 3:
        grid[0][2] = symbol;
        break;
    case 4:
        grid[1][0] = symbol;
        break;
    case 5:
        grid[1][1] = symbol;
        break;
    case 6:
        grid[1][2] = symbol;
        break;
    case 7:
        grid[2][0] = symbol;
        break;
    case 8:
        grid[2][1] = symbol;
        break;
    case 9:
        grid[2][2] = symbol;
        break;
    default:
        break;
    }
}

void playerInput(vector<vector<char>> &grid)
{
    int player;
    while (true)
    {
        cout << "Enter your position(1-9): ";
        cin >> player;
        if (isFinished(grid, player, playerSymbol))
            break;
        else
        {
            cout << "Invalid move!!" << endl;
        }
    }
    putSymbol(grid, player, playerSymbol);
}

// AI $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

char checkWiner(vector<vector<char>> grid)
{
    if (anyOneWonTheGame(grid, playerSymbol))
    {
        return playerSymbol;
    }
    else if (anyOneWonTheGame(grid, computerSymbol))
    {
        return computerSymbol;
    }
    else
    {
        bool isTie = true;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (grid[i][j] == ' ')
                    isTie = false;
        return isTie ? 'T' : NULL;
    }
}

/*
'O' = +1
'X' = -1
'T' = 0
*/
int minmax(vector<vector<char>> &grid, int depth, bool isMaximize)
{

    // terminal condition
    char winer = checkWiner(grid);
    if (winer != NULL)
    {
        if (winer == 'O')
            return 1;
        else if (winer == 'X')
            return -1;
        else
            return 0;
    }

    if (isMaximize)
    {
        // max turn
        int bestScore = INT_MIN;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (grid[i][j] == ' ')
                {
                    grid[i][j] = computerSymbol;
                    int score = minmax(grid, depth + 1, false);
                    grid[i][j] = ' ';
                    bestScore = max(score, bestScore);
                }
            }
        }
        return bestScore;
    }
    else
    {
        // min turn
        int bestScore = INT_MAX;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (grid[i][j] == ' ')
                {
                    grid[i][j] = playerSymbol;
                    int score = minmax(grid, depth + 1, true);
                    grid[i][j] = ' ';
                    bestScore = min(score, bestScore);
                }
            }
        }
        return bestScore;
    }
}

void computerInputAi(vector<vector<char>> &grid)
{
    pair<int, int> bestMove;
    int bestScore = INT_MIN;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (grid[i][j] == ' ')
            {
                grid[i][j] = computerSymbol;
                int score = minmax(grid, 0, false);
                grid[i][j] = ' ';
                if (score > bestScore)
                {
                    bestScore = score;
                    bestMove = make_pair(i, j);
                }
            }
        }
    }
    grid[bestMove.first][bestMove.second] = computerSymbol;
}
// AI $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

int main()
{
    int computer, player;
    char winStatus;
    vector<vector<char>> grid = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}};
    printCotainer(grid);
    while (true)
    {
        playerInput(grid);
        printCotainer(grid);
        if ((winStatus = checkWiner(grid)) != NULL)
        {
            break;
        }
        system("cls");
        computerInputAi(grid);
        printCotainer(grid);
        if ((winStatus = checkWiner(grid)) != NULL)
        {
            break;
        }
    }
    system("cls");
    printCotainer(grid);
    if (winStatus == playerSymbol)
    {
        cout<<"you win :)"<<endl;
    }
    else if (winStatus == computerSymbol)
    {
        cout<<"computer won :("<<endl;
    }
    else cout<<"tie"<<endl;
}