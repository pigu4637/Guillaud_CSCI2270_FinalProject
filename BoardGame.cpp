#include "BoardGame.h"
#include <iostream>
using namespace std;

//small structure to keep track of whether or not the board is full. (Not the greatest implementation)
BoardGame::BoardGame()
{
    root = new BoardElem(0,0);
    b = new bCounter();

}

BoardGame::~BoardGame(){}

void BoardGame::createBoard(int t)
{
    //temp_1 is the corresponding node on the root column
    //temp_2 is creating the row of temp_1
    //temp_3 is going above temp_2 to make the bottom and top elements
    root = new BoardElem(0, 0);
    BoardElem *temp_1 = root;
    // The board has 6 rows and 7 columns, and it will therefore have
    // to repeat accordingly
    for(int i = 0; i<6; i++)
    {
        BoardElem *temp_3 = NULL;
        BoardElem *temp_2 = temp_1;
        if(temp_1->top != NULL)
        {
            // creates a temp_3 only if not top row
            temp_3 = temp_1->top;
        }
        for(int j = 0; j<7; j++)
        {
            // the linked nodes are all created before the game starts,
            // and not during the game.
            BoardElem *temp = new BoardElem(0,0);
            temp->left = temp_2;
            temp_2->right = temp;
            temp_2 = temp;
            if(temp_3 != NULL)
            {
                // temp_3's bottom connects to temp_2's top
                temp_3 = temp_3->right;
                temp_3->bottom = temp_2;
                temp_2->top = temp_3;
            }
        }
        BoardElem *temp = new BoardElem(0,0);
        temp_1->bottom = temp;
        temp->top = temp_1;
        temp_1 = temp;
    }
    // inputs the names of the players and displays basic rules
    cout << "Please enter Player 1's name: ";
    getline(cin, player1);
    cout << "Please enter Player 2's name: ";
    getline(cin, player2);
    turn = t;
    won = 0;
    cout << endl;
    cout << "In order to play this game, you will" << endl;
    cout << "need to select the columns where you wish" <<endl;
    cout << "to drop your tokens in order to get four" << endl;
    cout << "in a row (it can be diagonal, horizontal" << endl;
    cout << "or vertical)" << endl << endl;
    cout << player1 << " will be [X]" << endl << player2 << " will be [O]" << endl;
}

void BoardGame::printBoard()
{
    // printboard will repeat the createboard function but simply
    // printing the nodes instead of creating them
    char wall = 179;
    // wall is a character that will separate the columns
    BoardElem *temp_1 = root;
    cout << endl <<"-----------------------------";
    cout << string( 2, '\n' );
    for(int i = 1; i<8; i++)
        cout << " " << i;
    cout << endl << endl;
    // instead of checking if the node is null, it will check if
    // it contains as a status 1 or 2 (player 1 token or p2 token)
    for(int i = 0; i<6; i++)
    {
        BoardElem *temp_2 = temp_1;
        for(int j = 0; j<7; j++)
        {
            temp_2 = temp_2->right;
            if(temp_2->status == 1)
                cout<<wall<< "X";
            else if(temp_2->status == 2)
                cout<<wall<< "O";
            else
                cout<<wall<< " ";
        }
        temp_1 = temp_1->bottom;
        cout<<wall<<endl;
    }
    cout << endl;
}

void BoardGame::insertNode(int column)
{
    BoardElem *temp = root;
    BoardElem *temp_backup;
    // repeats until looking at the right column, move right
    for(int i = 0; i<column; i++)
        temp = temp->right;
    // if the column is not filled
    if(temp->used == 0)
    {
        int n = 0;
        // find the lowest unoccupied node (to simulate gravity)
        while(n != 1)
        {
            temp_backup = temp;
            temp = temp->bottom;
            if(temp != NULL)
            {
                if(temp->used == 1)
                    n=1;
            }
            else
                n = 1;
        }
        // go back to last unoccupied space, make it occupied
        temp = temp_backup;
        temp->used = 1;
        temp->status = turn+1;
        // check if game is won by placement of token
        if(checkBoard(temp, turn)==1)
            won = 1;
        if(won == 0)
        {
            // if no one won on this turn, make it other's turn
            if(turn == 0)
                turn = 1;
            else
                turn = 0;
        }
    }
}

bool BoardGame::checkBoard(BoardElem *node, int turn)
{
    // check on the right by adding increasing n everytime
    int n = 1;
    BoardElem *temp = node;
    for(int i = 0; i < 3; i++)
    {
        if(temp->right != NULL)
        {
            temp = temp->right;
            if(temp->status == turn+1)
            {
                n++;
                if(n > 3)
                    return 1;
            }
            else
                i = 3;
        }
    }
    temp = node;
    for(int i = 0; i < 3; i++)
    {
        if(temp->left != NULL)
        {
            temp = temp->left;
            if(temp->status == turn+1)
            {
                n++;
                if(n > 3)
                    return 1;
            }
            else
                i = 3;
        }
    }

    // check diagonally
    n = 1;
    temp = node;
    for(int i = 0; i < 3; i++)
    {
        if(temp->right != NULL)
        {
            if(temp->right->top != NULL)
            {
                temp = temp->right->top;
                if(temp->status == turn+1)
                {
                    n++;
                    if(n > 3)
                        return 1;
                }
                else
                    i = 3;
            }
        }
    }
    temp = node;
    for(int i = 0; i < 3; i++)
    {
        if(temp->left != NULL)
        {
            if(temp->left->bottom != NULL)
            {
                temp = temp->left->bottom;
                if(temp->status == turn+1)
                {
                    n++;
                    if(n > 3)
                        return 1;
                }
                else
                    i = 3;
            }
        }
    }

    n = 1;
    temp = node;
    for(int i = 0; i < 3; i++)
    {
        if(temp->left != NULL)
        {
            if(temp->left->top != NULL)
            {
                temp = temp->left->top;
                if(temp->status == turn+1)
                {
                    n++;
                    if(n > 3)
                        return 1;
                }
                else
                    i = 3;
            }
        }
    }
    temp = node;
    for(int i = 0; i < 3; i++)
    {
        if(temp->right != NULL)
        {
            if(temp->right->bottom != NULL)
            {
                temp = temp->right->bottom;
                if(temp->status == turn+1)
                {
                    n++;
                    if(n > 3)
                        return 1;
                }
                else
                    i = 3;
            }
        }
    }

    // check vertically
    n = 1;
    temp = node;
    for(int i = 0; i < 3; i++)
    {
        if(temp->bottom != NULL)
        {
            temp = temp->bottom;
            if(temp->status == turn+1)
            {
                n++;
                if(n > 3)
                    return 1;
            }
            else
                i = 3;
        }
    }

    return 0;
}

/*
A message from Casey Cooter
As near as I can tell, you kind of worked yourself into a corner in terms of checking if the board is full.
You would have to check the linked list to see if it was full which is a pain.
So, instead, I created a structure that holds an array and a value called bcounter in the header. I then modified main.cpp in order to include a condition checking if the full bool in this structure was true or false.
Now, there's probably a little more fluidity to be added to just continually loop the program, but I think it's a good start.

Basically, it uses a small array of 7 locs. It works by creating a temp value full, and assuming it is true. It then loops through the array, checking if a column has less than 6 elements in it. If it does, it sets the
temporary condition to false, exits the loop, and doesn't change the structure variable. If it is technically full, it will not change the temp value to false, reach the end, and change the variable to true.
Then, when main.cpp detects that this class variable is true for full, it will skip to the end, and suggest that the user starts a new game.

I want to emphasize I don't know if this is the best solution - Linked Lists may not have been the superb solution for this (or perhaps I'm just struggling to understand it)

However, I think this is a good enough solution, and should work well enough for the way you have this implemented. Enjoy!
*/
void BoardGame::increment(int column)
{
    b->col[column - 1] = b->col[column - 1] + 1;
    bool full = true; //assume true
    for(int i =0; i < 7; i++)
    {
        if(b->col[i] < 6){
            full = false;
            break;
        }
    }
    if (full == true)
    {
        b->full = true;
    }
}
