# Guillaud_CSCI2270_FinalProject

Part 1:

This project will be a connect four game, consisting of a 6 by 7 board and allowing two players to play on their turn. The structure that will take care of remembering the position of each of the player tokens will consist of a linked list with different pointers: top, bottom, right, left and key. Everytime a column is chosen by a player, the program will find the lowest open slot in that column, set the key as 1 or 2, depending on the turn of the player, and will check if 4 tokens are connected by checking the node->bottom, node->top, node->right, node->left along with a combination of those such as node->top->left. Once the game is finished, the players will have to option to play again or quit the game. If they decided to play again, the player who won gets one point.

Part 2:

This is a connect four game and requires two players to play. The game starts by prompting the players for their name, choose randomly who will start, and will then proceed to repeatedly ask the players in turn which columns to drop their token into. In order to simulate gravity, the program will find the lowest point in the column before putting the 'discs'. Once a player gets four tokens in a row, diagonally, vertically or horizontally, the game ends displaying the winner.

In order to run, please download "main.cpp", "BoardGame.h" and "BoardGame.cpp". These files can then be opened with any c++ compatible IDE platform.

There is no external libraries, all of those used should already be included. The project should be able to run on any system.

Issues:
- If board is full, the game will be stuck.
- If inputting non-numbers in the column selector, the game will crash.
