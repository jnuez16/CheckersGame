#include "stdafx.h"

const char EMPTY = '\0';
const char userPiece = 'u';
const char compPiece = 'c';


bool validspace(int i, int j); //function for validity of space

void colorback(HDC hdc); //function to color the board

void drawpieceU(char user); //draws the piece the user chooses

void drawpieceC(char user); //draws the opponent's piece
void pieceMove(int i, int j, char piece); //function for piece pick up and placement

//Start the game over
void GameReset(char user);

//Draw the game board, with userPiece and compPiece
void GameDrawBoard(HWND hwnd, HDC hdc, char user);

//Set the next move
void GameSetMove(int i, int j, char user, char opponent);

//Check for Winner
void GameCheckWinner(HWND hwnd);

void GameDrawBPiece(HDC hdc, int i, int j); //draws the black piece
void GameDrawWPiece(HDC hdc, int i, int j); //draws the white piece
