#include <iostream>
#include "BoardGame.h"
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;

int main()
{
    BoardGame bg;
    int column;
    string tColumn;
    // randomizes who starts the game and creates the board
    srand((int)time(0));
    bg.createBoard(rand()%2);

    // repeats while no one won
    while(bg.won == 0 && bg.b->full == false)
    {
        // print the board
        bg.printBoard();
        // prompt a column
        if(bg.turn == 0)
            cout << bg.player1 << ", please choose a column: ";
        else
            cout << bg.player2 << ", please choose a column: ";
        while(!(cin >> column) || !(column < 8 && column > 0))
        {
            cout << "Incorrect input. Please enter a number between 1 and 7: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        /*
        A message from Casey Cooter:
        So IO streams are a bit of a pain in the butt. It expects an integer, and when it doesn't get an integer, it throws up an error flag that basically ruins your cin.
        There's two ways to do this. The more I use C++, the more I realize that it's extremely easy to get messed up by the iostream, so whenever possible, I try to stick with either getline OR cin.
        If you stuck with getline, then you could use the c++11 "stoi." This isn't THAT foolproof, but if it cannot convert it to a string, it returns '0'. (I believe anyways.) So, you  could easily set a loop
        going while(column != 0) -> get the input. Another way using getline would be to put it into a stringstream, and run a while loop "while(!ss >> column)" because this has an error flag that will just pester the
        user until they get it right.

        However, that can sometimes make your code a tad messier doing all that, so I looked into another method. The issue is that when you cin the incorrect type of data, it throws up an error flag and
        everything freaks out. It can NOT accept input until you clear that error flag (hence why it never stopped for input again). This uses the limits library to clear the buffer and reset the flag. Again, since cin has an error flag up, we can
        use a loop to just say "You messed up. Do it again and I'm going to keep bugging you until you do fix it!" Now, this is why perhaps I recommended getline - if the user wanted to exit the program at any step and type "EXIT" or such,
        it wouldn't cause the whole thing to flip out and would be a pretty easy implementation. Not that I would say this is particularly important in this project (dare I say would be a waste of time to implement), but it's just something
        you might consider thinking about. Sorry about the paragraph!
        */
        // insert node into column (if valid command)

        // Checking the condition is now redundant. The program will continue to pester the user until it gets the input it is expecting!
        bg.insertNode(column);
        bg.increment(column); //checks if full;

    }
    //displays final board and ends the program
    bg.printBoard();
    if(bg.b->full == true)
        cout << "Board is full. Consider starting a new game!" << endl;
    else if(bg.turn == 0)
        cout << bg.player1 << " has won the game!" << endl;
    else
        cout << bg.player2 << " has won the game!" << endl;
}
