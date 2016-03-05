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
using namespace std;

const int ROW = 9;
const int COL = 9;
//char board[ROW][COL];
//char board[ROW][COL] =   {{' ', ' ', ' ',' ', ' ', ' ',' ', ' ', ' '},		//2d array initialized to *
//                                            {' ', ' ', ' ',' ', ' ', ' ',' ', ' ', ' '},
//                                            {' ', ' ', ' ',' ', ' ', ' ',' ', ' ', ' '},
//                                            {' ', ' ', ' ',' ', ' ', ' ',' ', ' ', ' '},
//                                            {' ', ' ', ' ',' ', ' ', ' ',' ', ' ', ' '},
//                                            {' ', ' ', ' ',' ', ' ', ' ',' ', ' ', ' '},
//                                            {' ', ' ', ' ',' ', ' ', ' ',' ', ' ', ' '},
//                                            {' ', ' ', ' ',' ', ' ', ' ',' ', ' ', ' '},
//                                            {' ', ' ', ' ',' ', ' ', ' ',' ', ' ', ' '}};


void platform(char board[ROW][COL]);             //function display gameboard
int switchplayer(int);		 //function switching players
char marker(int);			 //function assigning player marker
int findWinner(char, char board[ROW][COL]);        //function determining winning condition
bool winHorizontal(char, char board[ROW][COL]);
bool winVertical(char, char board[ROW][COL]);
bool winDiagonal(char, char board[ROW][COL]);
bool winDiagonal2(char, char board[ROW][COL]);


int main()
{
    char board[ROW][COL];
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            board[i][j] = ' ';
        }
    }
    
    int player = 1;			 //player initialized to 1, gets first move
    int g;					 //decide game progress win(1), draw(0) or continue(-1)
    int r;					 //user input rows
    int c;					 //user input columns
    char playerMark;		 //marker for X or O
    //do loop for each turn taken
    do
    {
        platform(board);					//cout gameboard
        player=switchplayer(player);//alternate players
        playerMark=marker(player);  //assign playermarker
        
        //Ask for user input while preventing player from overwriting previous positions
        cout << "Player " << player << " please enter row followed by column:  ";
        cin >> r >> c;
        
        while ( r > 9 || r < 1 || c > 9 || c < 1 )
        {
            cout << "Player " << player << ", please re-enter row followed by column:  ";
            cin >> r >> c;
        }
        
        while(board[r-1][c-1] != ' ')
        {
            cout << "You cannot choose a spot on the grid that is taken!\n"
            << "Player " << player << ", enter row followed by column:  ";
            cin >> r >> c;
        }
        
        //Placing markers
        board[r-1][c-1] = playerMark;
        
        g = findWinner(playerMark, board);//check for winner
        player++;
        
    }while(g == -1); //-1 start next turn
    platform(board);
    if (g == 1)
        cout<<"   Player " << --player << " win!\n\n ";
    else
        cout<<"        Game draw\n\n";
    return 0;
}

//gameboard
void platform(char board[ROW][COL])
{
    system("cls");	//Clear screen
    cout << "   Lets Play Five Stones\n\n";
    
    cout << "Player 1  X  -  Computer  O" << endl << endl;
    cout << endl;
    
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
        player=1;
    else
        player=2;
    return player;
}

//Assigning player markers
char marker(int player)
{
    char playerMark;
    if (player == 1)
        playerMark = 'X';
    else
        playerMark = 'O';
    return playerMark;
}

//win, draw or continue
int findWinner(char playerMark, char board[ROW][COL])
{

    if ( winHorizontal(playerMark, board) || winVertical(playerMark, board) || winDiagonal2(playerMark, board) || winDiagonal(playerMark, board)) {
        return 1;
    }
    // check tie
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            if (board[i][j] == ' ') {
                return -1;
            }
        }
    }
    return 0;
}

bool winHorizontal(char playerMark, char board[ROW][COL]) {
    for (int i = 0; i < ROW; i++) {
        int currentStreak = 0;
        for (int j = 0; j < COL; j++) {
            const int WIN = 1;
            if (board[i][j] == playerMark && board[i][j+1] == playerMark) {
                currentStreak++;
                if (currentStreak == WIN) {
                    return true;
                }
            } else {
                currentStreak = 0;
            }
        }
    }
    return false;
}

bool winVertical(char playerMark, char board[ROW][COL]) {
    for (int i = 0; i < COL; i++) {
        int currentStreak = 0;
        for (int j = 0; j < ROW; j++) {
            const int WIN = 1;
            if (board[j][i] == playerMark && board[j+1][i] == playerMark) {
                currentStreak++;
                if (currentStreak == WIN) {
                    return true;
                }
            } else {
                currentStreak = 0;
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
        for (int j = 0; j < COL - 1; j++) {
            boardCopy[i][j] = board[i][j + count];
            boardCopy[i][COL - count] = board[i][j];
        }
        count++;
    }
    return winVertical(playerMark, boardCopy);
}
