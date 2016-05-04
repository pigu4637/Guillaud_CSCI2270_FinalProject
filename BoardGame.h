#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <string>
#include <vector>

// This project uses a grid of linked lists, each node linked
// to its adjacent and top and bottom
struct bCounter
{
    int col[7];
    bool full;
    bCounter()
    {
        for(int i = 0; i < 7;i++)
            col[i] = 0;
        full = false;
    }
};

struct BoardElem
{
    int status;
    int used;
    BoardElem *right;
    BoardElem *left;
    BoardElem *top;
    BoardElem *bottom;
    BoardElem() {};
    BoardElem(int in_status, int in_used)
    {
        status = in_status;
        used = in_used;
        right = NULL;
        left = NULL;
        top = NULL;
        bottom = NULL;
    }
};

class BoardGame
{
public:
    BoardGame();
    ~BoardGame();
    // to insert a new "token"
    void insertNode(int column);
    // to print the board
    void printBoard();
    // to create/reset the board
    void createBoard(int t);
    // those values need to be accessed by the main function and
    // are therefore public
    std::string player1;
    std::string player2;
    int turn;
    bool won;
    bool checkBoard(BoardElem *node, int turn);
    void increment(int column);

    bCounter * b;
private:
    BoardElem *root;
};

#endif // HASHTABLE_H
