//
//  FiveStones.cpp
//  Lab8
//
//  Created by Jun Yuan on 2016-03-02.
//  Copyright © 2016 Jun Yuan. All rights reserved.
//

// PROGRAMMER:  Jun Yuan CPSC 1103	 Section: S11
// This is a Tic Tac Toe Game
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <regex>
#include <string>
using namespace std;

const int ROW = 9;
const int COL = 9;
const int WIN = 5; // the number of sequence to win
const char EMPTY = ' ';
const char PLAYER = 'X';
const char COMPUTER = 'O';
int turn = 1;

void platform(char board[ROW][COL]);             //function display gameboard
int switchplayer(int);		 //function switching players
char marker(int);			 //function assigning player marker
int findWinner(char, char board[ROW][COL]);        //function determining winning condition
bool winHorizontal(char, char board[ROW][COL]);
bool winVertical(char, char board[ROW][COL]);
bool winDiagonal(char, char board[ROW][COL]);
bool winDiagonal2(char, char board[ROW][COL]);
void aiHeuristics(char, char board[ROW][COL], int);
bool doRecursiveMove(char, char board[ROW][COL], int);
bool checkHorizontalStreak(char, char board[ROW][COL], int);
bool checkVerticalStreak(char, char board[ROW][COL], int);
bool checkDiagonalStreak1(char, char board[ROW][COL], int);
bool checkDiagonalStreak2(char, char board[ROW][COL], int);
bool doBestInitialMove(char, char board[ROW][COL]);
bool takeWinningMove(char, char board[ROW][COL]);
bool blockWinningMove(char, char board[ROW][COL]);
bool winningHorizontalStreak(char, char board[ROW][COL]);
bool winningVerticalStreak(char, char board[ROW][COL]);
bool winningDiagonalStreak1(char, char board[ROW][COL]);
bool winningDiagonalStreak2(char, char board[ROW][COL]);
void parseInput(string, string);

int main()
{
    char board[ROW][COL];
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            board[i][j] = ' ';
        }
    }
    
    int player = 1;			 //player initialized to 1, gets first move
    int gamestate = -1;					 //decide game progress win(1), draw(0) or continue(-1)
    string r;					 //user input rows
    string c;					 //user input columns
    char playerMark;		 //marker for X or O
    //do loop for each turn taken
    do
    {
        platform(board);					//cout gameboard
        player = switchplayer(player);//alternate players
        playerMark = marker(player);  //assign playermarker
        
        if (player % 2 == 1) {
            
            bool match = false;
            
            while (!match) {
                regex yo( "^[0-9]$");
                
                cout << "Player " << player << " please enter row(1-9), then press space, then enter column(1-9):  ";
                cin >> r >> c;
                
                match = regex_match(r, yo) && regex_match(c, yo);
            }

            
            while(board[stoi(r)-1][stoi(c)-1] != EMPTY)
            {
                cout << "You cannot choose a spot on the grid that is taken!\n"
                << "please enter row(1-9), then press space, then enter column(1-9):  ";
                cin >> r >> c;
            }
            
            //Placing markers
            board[stoi(r)-1][stoi(c)-1] = playerMark;
            
        } else {
            aiHeuristics(playerMark, board, WIN);
        }
        
        if (turn >= WIN*2 - 1) {
            gamestate = findWinner(playerMark, board);//check for winner
        }
        turn++;
        player++;
        
    } while(gamestate == -1); //-1 start next turn
    platform(board);
    if (gamestate == 1)
        if (player - 1 == 2) {
            cout<<"   Computer" << " win!\n\n ";
        } else if (player - 1 == 1) {
            cout<<"   Player 1" << " win!\n\n ";
        } else {
            cout<<"        Game draw\n\n";
        }
    return 0;
}

//gameboard
void platform(char board[ROW][COL])
{
    //system("cls");	//Clear screen
    cout << "   Lets Play Five Stones\n\n";
    
    cout << "Player 1  X  -  Computer  O" << endl << endl;
    cout << "          Turn: " << turn << "              " << endl << endl << endl;
    
    cout << "      " << "C1" << "    " << "C2" << "    " "C3" <<  "    " "C4" << "    " << "C5" << "    " "C6" <<  "    " "C7" << "    " << "C8" << "    " "C9" << endl;
    cout << "         |     |     |     |     |     |     |     |     " <<endl;
    cout << " R1   " << board[0][0] << "  |  " << board[0][1] << "  |  " << board[0][2] << "  |  " << board[0][3] << "  |  " << board[0][4] << "  |  " << board[0][5] << "  |  " << board[0][6] << "  |  " << board[0][7] << "  |  " << board[0][8] << endl;
    
    cout << "    _____|_____|_____|_____|_____|_____|_____|_____|_____" << endl;
    cout << "         |     |     |     |     |     |     |     |     " <<endl;
    
    cout << " R2   " << board[1][0] << "  |  " << board[1][1] << "  |  " << board[1][2] << "  |  " << board[1][3] << "  |  " << board[1][4] << "  |  " << board[1][5] << "  |  " << board[1][6] << "  |  " << board[1][7] << "  |  " << board[1][8] << endl;
    
    cout << "    _____|_____|_____|_____|_____|_____|_____|_____|_____" << endl;
    cout << "         |     |     |     |     |     |     |     |     " <<endl;
    
    cout << " R3   " << board[2][0] << "  |  " << board[2][1] << "  |  " << board[2][2] << "  |  " << board[2][3] << "  |  " << board[2][4] << "  |  " << board[2][5] << "  |  " << board[2][6] << "  |  " << board[2][7] << "  |  " << board[2][8] << endl;
    
    cout << "    _____|_____|_____|_____|_____|_____|_____|_____|_____" << endl;
    cout << "         |     |     |     |     |     |     |     |     " <<endl;
    
    cout << " R4   " << board[3][0] << "  |  " << board[3][1] << "  |  " << board[3][2] << "  |  " << board[3][3] << "  |  " << board[3][4] << "  |  " << board[3][5] << "  |  " << board[3][6] << "  |  " << board[3][7] << "  |  " << board[3][8] << endl;
    
    cout << "    _____|_____|_____|_____|_____|_____|_____|_____|_____" << endl;
    cout << "         |     |     |     |     |     |     |     |     " <<endl;
    
    cout << " R5   " << board[4][0] << "  |  " << board[4][1] << "  |  " << board[4][2] << "  |  " << board[4][3] << "  |  " << board[4][4] << "  |  " << board[4][5] << "  |  " << board[4][6] << "  |  " << board[4][7] << "  |  " << board[4][8] << endl;
    
    cout << "    _____|_____|_____|_____|_____|_____|_____|_____|_____" << endl;
    cout << "         |     |     |     |     |     |     |     |     " <<endl;
    
    cout << " R6   " << board[5][0] << "  |  " << board[5][1] << "  |  " << board[5][2] << "  |  " << board[5][3] << "  |  " << board[5][4] << "  |  " << board[5][5] << "  |  " << board[5][6] << "  |  " << board[5][7] << "  |  " << board[5][8] << endl;
    
    cout << "    _____|_____|_____|_____|_____|_____|_____|_____|_____" << endl;
    cout << "         |     |     |     |     |     |     |     |     " <<endl;
    
   cout << " R7   " << board[6][0] << "  |  " << board[6][1] << "  |  " << board[6][2] << "  |  " << board[6][3] << "  |  " << board[6][4] << "  |  " << board[6][5] << "  |  " << board[6][6] << "  |  " << board[6][7] << "  |  " << board[6][8] << endl;
    
    cout << "    _____|_____|_____|_____|_____|_____|_____|_____|_____" << endl;
    cout << "         |     |     |     |     |     |     |     |     " <<endl;
    
    cout << " R8   " << board[7][0] << "  |  " << board[7][1] << "  |  " << board[7][2] << "  |  " << board[7][3] << "  |  " << board[7][4] << "  |  " << board[7][5] << "  |  " << board[7][6] << "  |  " << board[7][7] << "  |  " << board[7][8] << endl;
    
    cout << "    _____|_____|_____|_____|_____|_____|_____|_____|_____" << endl;
    cout << "         |     |     |     |     |     |     |     |     " <<endl;
    
    cout << " R9   " << board[8][0] << "  |  " << board[8][1] << "  |  " << board[8][2] << "  |  " << board[8][3] << "  |  " << board[8][4] << "  |  " << board[8][5] << "  |  " << board[8][6] << "  |  " << board[8][7] << "  |  " << board[8][8] << endl;

    cout << "         |     |     |     |     |     |     |     |     " << endl << endl;
}

//player switch
int switchplayer(int player)
{
    if(player%2)
        player = 1;
    else
        player = 2;
    return player;
}

//Assigning player markers
char marker(int player)
{
    char playerMark;
    if (player == 1)
        playerMark = PLAYER;
    else
        playerMark = COMPUTER;
    return playerMark;
}

//win, draw or continue
int findWinner(char playerMark, char board[ROW][COL])
{
    if ( winHorizontal(playerMark, board) || winVertical(playerMark, board) || winDiagonal2(playerMark, board) || winDiagonal(playerMark, board)) {
        return 1;
    }
    // check tie
//    for (int i = 0; i < ROW; i++) {
//        for (int j = 0; j < COL; j++) {
//            if (board[i][j] == ' ') {
//                return -1;
//            }
//        }
//    }
    if (turn >= 81) {
        return 0;
    }
    return -1;
}

bool winHorizontal(char playerMark, char board[ROW][COL]) {
    for (int i = 0; i < ROW; i++) {
        int currentStreak = 1;
        for (int j = 0; j < COL; j++) {
            if (board[i][j] == playerMark && board[i][j+1] == playerMark) {
                currentStreak++;
                if (currentStreak == WIN) {
                    return true;
                }
            } else {
                currentStreak = 1;
            }
        }
    }
    return false;
}

bool winVertical(char playerMark, char board[ROW][COL]) {
    for (int i = 0; i < COL; i++) {
        int currentStreak = 1;
        for (int j = 0; j < ROW; j++) {
            if (board[j][i] == playerMark && board[j+1][i] == playerMark) {
                currentStreak++;
                if (currentStreak == WIN) {
                    return true;
                }
            } else {
                currentStreak = 1;
            }
        }
    }
    return false;
}

bool winDiagonal(char playerMark, char board[ROW][COL]) {
    char boardCopy[ROW][COL];

    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL - 1; j++) {
            boardCopy[i][j] = board[i][j + i];
            boardCopy[i][COL - i] = board[i][j];
        }
    }
    return winVertical(playerMark, boardCopy);
}

bool winDiagonal2(char playerMark, char board[ROW][COL]) {
    char boardCopy[ROW][COL];
    
    int count = 0;
    for (int i = ROW - 1; i >= 0; i--) {
        for (int j = 0; j < COL + 1; j++) {
            boardCopy[i][j] = board[i][j + count];
            boardCopy[i][COL - count] = board[i][j];
        }
        count++;
    }
    return winVertical(playerMark, boardCopy);
}

void aiHeuristics(char playerMark, char board[ROW][COL], int streak) {
    if (turn == 2) {
        doBestInitialMove(playerMark, board);
    } else if (takeWinningMove(COMPUTER, board)) {
        return;
    } else if (blockWinningMove(PLAYER, board)) {
        return;
    } else {
        if (streak == 1) {
            return;
        } else {
            if  (doRecursiveMove(playerMark, board, streak)) {
                return;
            } else {
                return aiHeuristics(playerMark, board, streak-1);
            }
        }
    }
}

bool checkHorizontalStreak(char playerMark, char board[ROW][COL], int win) {
    for (int i = 0; i < ROW; i++) {
        int currentStreak = 1;
        int p = 2;
        for (int j = 0; j < COL; j++) {
            if (board[i][j] == playerMark && board[i][j+1] == playerMark) {
                currentStreak++;
                if (currentStreak == win - 1) {
                    if (j+2 < COL && board[i][j+2] == EMPTY) {
                        board[i][j+2] = COMPUTER;
                        return true;
                    }
                }
            } else if (board[i][j] == playerMark && board[i][j+1] == EMPTY) {
                board[i][j+1] = COMPUTER;
                return true;
            } else {
                // different markers then switch
                if (board[i][j] != EMPTY && board[i][j+1] != EMPTY) {
                    playerMark = marker(p++);
                }
                currentStreak = 1;
            }
        }
    }
    
    if (win - 1 == 1) {
        bool flag = false;
        do {
            srand(time(0));
            int randROW = rand() % ROW;
            int randCOL = rand() % COL;
            if (board[randROW][randCOL] == EMPTY) {
                board[randROW][randCOL] = COMPUTER;
                return true;
            }
        } while (!flag);
    }
    
    return false;
}

bool checkVerticalStreak(char playerMark, char board[ROW][COL], int win) {
    for (int i = 0; i < COL; i++) {
        int currentStreak = 1;
        int p = 2;
        for (int j = 0; j < ROW; j++) {
            if (board[j][i] == playerMark && board[j+1][i] == playerMark) {
                currentStreak++;
                if (currentStreak == win - 1) {
                    if (j+2 < ROW && board[j+2][i] == EMPTY) {
                        board[j+2][i] = COMPUTER;
                        return true;
                    }
                }
            } else if (board[j][i] == playerMark && board[j+1][i] == EMPTY) {
                board[j+1][i] = COMPUTER;
                return true;
            } else {
                 // diifferent markers then switch
                if (board[j][i] != EMPTY && board[j+1][i] != EMPTY) {
                    playerMark = marker(p++);
                }
                currentStreak = 1;
            }
        }
    }
    
    if (win - 1 == 1) {
        bool flag = false;
        do {
            srand(time(0));
            int randROW = rand() % ROW;
            int randCOL = rand() % COL;
            if (board[randROW][randCOL] == EMPTY) {
                board[randROW][randCOL] = COMPUTER;
                return true;
            }
        } while (!flag);
    }
    
    return false;
}

bool checkDiagonalStreak1(char playerMark, char board[ROW][COL], int win) {
    char boardCopy[ROW][COL];
    
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL -+1; j++) {
            boardCopy[i][j] = board[i][j + i];
            boardCopy[i][COL - i] = board[i][j];
        }
    }
    return checkVerticalStreak(playerMark, boardCopy, win);
}

bool checkDiagonalStreak2(char playerMark, char board[ROW][COL], int win) {
    char boardCopy[ROW][COL];
    
    int count = 0;
    for (int i = ROW - 1; i >= 0; i--) {
        for (int j = 0; j < COL + 1; j++) {
            boardCopy[i][j] = board[i][j + count];
            boardCopy[i][COL - count] = board[i][j];
        }
        count++;
    }
    return checkVerticalStreak(playerMark, boardCopy, win);
}

bool doRecursiveMove(char playerMark, char board[ROW][COL], int win) {
    return (checkHorizontalStreak(playerMark, board, win) || checkVerticalStreak(playerMark, board, win) || checkDiagonalStreak1(playerMark, board, win) || checkDiagonalStreak2(playerMark, board, win));
}

bool doBestInitialMove(char playerMark, char board[ROW][COL]) {
    if (board[4][4] == EMPTY) {
        board[4][4] = playerMark;
        return true;
    } else if (board[0][4] == EMPTY) {
        board[0][4] = playerMark;
        return true;
    } else if  (board[4][8] == EMPTY) {
        board[4][8] = playerMark;
        return true;
    } else if (board[0][8] == EMPTY) {
        board[0][8] = playerMark;
        return true;
    } else {
        board[8][4] = playerMark;
        return true;
    }
}

bool takeWinningMove(char playerMark, char board[ROW][COL]) {
    return (winningHorizontalStreak(COMPUTER, board) || winningVerticalStreak(COMPUTER, board) || winningDiagonalStreak1(COMPUTER, board) || winningDiagonalStreak2(COMPUTER, board));
}

bool blockWinningMove(char playerMark, char board[ROW][COL]) {
    return (winningHorizontalStreak(PLAYER, board) || winningVerticalStreak(PLAYER, board) || winningDiagonalStreak1(PLAYER, board) || winningDiagonalStreak2(PLAYER, board));
}

bool winningHorizontalStreak(char playerMark, char board[ROW][COL]) {
    for (int i = 0; i < ROW; i++) {
        int currentStreak = 1;
        int index = 0;
        for (int j = 1; j < COL; j++) {
            if (board[i][j] == playerMark && board[i][j-1] == playerMark) {
                currentStreak++;
                if (currentStreak == WIN - 1) {
                    if (j+1 < COL && board[i][j+1] == EMPTY)  {
                        board[i][j+1] = COMPUTER;
                        return true;
                    }
                    if (index-1 >= 0 && board[i][index-1] == EMPTY)  {
                        board[i][index-1] = COMPUTER;
                        return true;
                    }
                    
                }
            } else {
                index = j;
                currentStreak = 1;
            }
        }
    }
    return false;
}

bool winningVerticalStreak(char playerMark, char board[ROW][COL]) {
    for (int i = 0; i < COL; i++) {
        int currentStreak = 1;
        int index = 0;
        for (int j = 1; j < ROW; j++) {
            if (board[j][i] == playerMark && board[j-1][i] == playerMark) {
                currentStreak++;
                if (currentStreak == WIN - 1) {
                    if (j+1 < ROW && board[j+1][i] == EMPTY)  {
                        board[j+1][i] = COMPUTER;
                        return true;
                    }
                    if (index-1 >= 0 && board[index-1][i] == EMPTY)  {
                        board[index-1][i] = COMPUTER;
                        return true;
                    }
                }
            } else {
                index = j;
                currentStreak = 1;
            }
        }
    }
    return false;
}

bool winningDiagonalStreak1(char playerMark, char board[ROW][COL]) {
    char boardCopy[ROW][COL];
    
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL + 1; j++) {
            boardCopy[i][j] = board[i][j + i];
            boardCopy[i][COL - i] = board[i][j];
        }
    }
    return winningVerticalStreak(playerMark, boardCopy);
}

bool winningDiagonalStreak2(char playerMark, char board[ROW][COL]) {
    char boardCopy[ROW][COL];
    
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL + 1; j++) {
            boardCopy[i][j] = board[i][j + i];
            boardCopy[i][COL - i] = board[i][j];
        }
    }
    return winningVerticalStreak(playerMark, boardCopy);
}
