#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void clearScreen()
{
    cin.clear();
    cin.ignore();
    system("cls");
}

void printBoard(int board[][7], int n)
{
    cout << "  ";
    for (int i = 1; i <= n; i++)
        cout << i << " ";
    cout << endl;

    for (int i = 0; i < n; i++)
    {
        cout << i + 1 << " ";
        for (int j = 0; j < n; j++)
        {
            if (board[i][j] == 0)
                cout << ". "; // Empty
            else if (board[i][j] == -1)
                cout << "* "; // Missed
            else
                cout << "X "; // Ship (hit or sunk)
        }
        cout << endl;
    }
}

bool isValidPlacement(int arr[][7], int x, int y, int size, int orientation, int n)
{
    if ((orientation == 0 && y + size - 1 >= n) || (orientation == 1 && x + size - 1 >= n))
        return false;

    for (int i = x - 1; i <= x + size; ++i)
        for (int j = y - 1; j <= y + size; ++j)
            if (i >= 0 && i < n && j >= 0 && j < n && arr[i][j] != 0)
                return false;

    return true;
}

void placeShip(int arr[][7], int size, int n)
{
    int x, y, orientation;
    do
    {
        x = rand() % (n - (size - 1));
        y = rand() % n;
        orientation = rand() % 2;
    } while (!isValidPlacement(arr, x, y, size, orientation, n));

    for (int i = 0; i < size; i++)
        arr[(orientation == 0) ? x : x + i][(orientation == 1) ? y : y + i] = size;
}

bool isShipSunk(int arr[][7], int playerView[][7], int x, int y, int n)
{
    int shipType = arr[x][y];
    int hit = (shipType == 3) ? 3 : 2;

    int count = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (arr[i][j] == shipType && playerView[i][j] == shipType)
                count++;

    return count == hit;
}

int main()
{
    int n = 7, game = 0, r, c, shots = 0;
    int arr[7][7] = {0};
    int playerView[7][7] = {0};

    srand(time(0));

    // Place ships
    placeShip(arr, 3, n);
    placeShip(arr, 2, n);
    placeShip(arr, 2, n);
    placeShip(arr, 1, n);
    placeShip(arr, 1, n);
    placeShip(arr, 1, n);
    placeShip(arr, 1, n);

    string playerName;
    cout << "Enter your name: ";
    cin >> playerName;
    cout << "Hello, " << playerName << "! Welcome to the game." << endl;

    while (game != 11)
    {
        printBoard(playerView, n);

        cout << "Enter the coordinates where you want to shoot: ";
        cin >> r >> c;

        if (arr[r - 1][c - 1] > 0)
        {
            clearScreen();
            cout << "Hit!";
            game++;
            shots++;
            playerView[r - 1][c - 1] = arr[r - 1][c - 1];
            if (isShipSunk(arr, playerView, r - 1, c - 1, n))
                cout << " Ship Sunk!" << endl;
            else
                cout << endl;
        }
        else
        {
            clearScreen();
            cout << "Miss!" << endl;
            shots++;
            playerView[r - 1][c - 1] = -1;
        }
    }

    clearScreen();
    cout << "You win the game! Congrats! There are the ships!" << endl;
    cout << "You made " << shots << " shots" << endl;
    printBoard(playerView, n);

    cin.get();
    return 0;
}