#include <iostream>
#include "BoardGame.h"
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
    BoardGame bg;
    int column;
    // randomizes who starts the game and creates the board
    srand((int)time(0));
    bg.createBoard(rand()%2);

    // repeats while no one won
    while(bg.won == 0)
    {
        // print the board
        bg.printBoard();
        // prompt a column
        if(bg.turn == 0)
            cout << bg.player1 << ", please choose a column: ";
        else
            cout << bg.player2 << ", please choose a column: ";
        cin >> column;
        // insert node into column (if valid command)
        if(column < 8 && column > 0)
            bg.insertNode(column);
        else
            cout << "INVALID" << endl;
    }
    //displays final board and ends the program
    bg.printBoard();
    if(bg.turn == 0)
        cout << bg.player1 << " has won the game!" << endl;
    else
        cout << bg.player2 << " has won the game!" << endl;
}
