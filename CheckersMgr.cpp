//Comments:
// Great work!
// 45/45

#include "stdafx.h"
#include "CheckersMgr.h"

const int WIDTH = 8; //constants for the array
const int HEIGHT = 8;
const int colorLight = RGB(255,255,128); //color of the board
const int colorDark = RGB(128,64,0);
int Upiece = 12;
int Opiece = 12;

char board[WIDTH][HEIGHT]; //the array for the board
bool uMove; //a boolean that checks whose turn it is
bool gameOver; //a boolean that checks if the game is over or not
bool piecePlace = false; //a boolean that tells the function that the user is picking up a piece and putting it down

bool validspace(int i, int j) // function for validity
{
	return i%2 != j%2;
}

void GameReset(char user) //resets the game and applies the choices of the user
{
	gameOver = false;
	uMove = true;
	for(int i = 0; i < WIDTH; i++) //initializes the board to '\0'
	{
		for(int j = 0; j < HEIGHT; j++)
		{
			board[i][j] = EMPTY;
		}
	}
	drawpieceU(user); //draws the pieces that the user chose
	drawpieceC(user); //draws the pieces for the user's opponent
}

void GameDrawBoard(HWND hwnd, HDC hdc, char user) //draws the whole board including the pieces and the background color
{
	MoveToEx(hdc, 30, 30, NULL); LineTo(hdc, 30, 670);
	MoveToEx(hdc, 110, 30, NULL); LineTo(hdc, 110, 670);
	MoveToEx(hdc, 190, 30, NULL); LineTo(hdc, 190, 670);
	MoveToEx(hdc, 270, 30, NULL); LineTo(hdc, 270, 670);
	MoveToEx(hdc, 350, 30, NULL); LineTo(hdc, 350, 670);
	MoveToEx(hdc, 430, 30, NULL); LineTo(hdc, 430, 670);
	MoveToEx(hdc, 510, 30, NULL); LineTo(hdc, 510, 670);
	MoveToEx(hdc, 590, 30, NULL); LineTo(hdc, 590, 670);
	MoveToEx(hdc, 670, 30, NULL); LineTo(hdc, 670, 670);

	MoveToEx(hdc, 30, 30, NULL); LineTo(hdc, 670, 30);
	MoveToEx(hdc, 30, 110, NULL); LineTo(hdc, 670, 110);
	MoveToEx(hdc, 30, 190, NULL); LineTo(hdc, 670, 190);
	MoveToEx(hdc, 30, 270, NULL); LineTo(hdc, 670, 270);
	MoveToEx(hdc, 30, 350, NULL); LineTo(hdc, 670, 350);
	MoveToEx(hdc, 30, 430, NULL); LineTo(hdc, 670, 430);
	MoveToEx(hdc, 30, 510, NULL); LineTo(hdc, 670, 510);
	MoveToEx(hdc, 30, 590, NULL); LineTo(hdc, 670, 590);
	MoveToEx(hdc, 30, 670, NULL); LineTo(hdc, 670, 670);

	colorback(hdc); //color of the board
	
	for(int i = 0; i < WIDTH; i++) //The loop that draws the pieces
	{
		for(int j = 0; j < HEIGHT; j++)
		{
			if(board[i][j] == 'b')
				{
					GameDrawBPiece(hdc, i, j);
				}
			else if(board[i][j] == 'w')
				{
					GameDrawWPiece(hdc, i, j);
				}
		}
	}

	if(gameOver == true) //declares the winner of the game
	{
		if(Upiece == 5) //the condition to declare who the winner is
		{
			HGDIOBJ fnt = GetStockObject(SYSTEM_FONT);
			HGDIOBJ fntOld = SelectObject(hdc, fnt);

			TextOut(hdc, 250, 450, _T("Congrats Player 2 Wins!"), 23);
			SelectObject(hdc, fntOld);
		}

		if(Opiece == 5)
		{
			HGDIOBJ fnt = GetStockObject(SYSTEM_FONT);
			HGDIOBJ fntOld = SelectObject(hdc, fnt);

			TextOut(hdc, 250, 450, _T("Congrats Player 1 Wins!"), 23);
			SelectObject(hdc, fntOld);
		}
	}
}

void GameSetMove(int i, int j, char user, char opponent) //function that allows the user to move the pieces
{
	static int tempPlaceI; // static variables save the value of tempPlace so we can use them when the pieceMove function is called again 
	static int tempPlaceJ;
	
	if(gameOver == false)
	{
		//Player 1's moves
		if(uMove)
		{
			if (piecePlace == false) //conditional that allows the user to pick a piece up
			{
				if (board[i][j] == user)
				{
					board[i][j] = EMPTY;
			
					tempPlaceI=i;
					tempPlaceJ=j;
					piecePlace = true;
				}
			}
			else if(piecePlace == true) //conditional that allows the user to place a piece
				{	
					if(board[i][j] == EMPTY && validspace(i,j)) //a condition that restricts the user to place pieces in valid spaces
					{
						if((i==tempPlaceI+1 && j==tempPlaceJ-1) || (i==tempPlaceI-1 && j==tempPlaceJ-1))
						{
							board[i][j] = user;
							piecePlace = false;
							uMove =! uMove;
						}
						else if(i == tempPlaceI && j == tempPlaceJ)
						{
							board[i][j] = user;
							piecePlace = false;
							uMove = uMove;
						}
						else if(board[tempPlaceI+1][tempPlaceJ-1] == opponent)//if there is an opponents piece where user would be able to move
						{
								if(i==tempPlaceI+2&&j==tempPlaceJ-2 && board[tempPlaceI+2][tempPlaceJ-2] == EMPTY)//and if they click on the space to jump to
								{

									board[i][j]=user;
									board[tempPlaceI+1][tempPlaceJ-1] = EMPTY; //makes oppoents piece disappear
									Opiece--;
									piecePlace = false;
									uMove =! uMove;
								}
									
						}
						else if (board[tempPlaceI-1][tempPlaceJ-1] == opponent)
						{
							if(i==tempPlaceI-2&&j==tempPlaceJ-2 && board[tempPlaceI-2][tempPlaceJ-2] == EMPTY)//and if they click on the space to jump to
							{

								board[i][j]=user;
								board[tempPlaceI-1][tempPlaceJ-1] = EMPTY; //makes oppoents piece disappear
								Opiece--;
								piecePlace = false;
								uMove =! uMove;//we need to take away piece 
							}
						}
					} 
				}
			}
			//pieceMove(i, j, user); //User move
			
		//player 2's moves
		else
		{
			if (piecePlace == false) //conditional that allows the user to pick a piece up
			{
				if (board[i][j] == opponent)
				// then highlight the piece because it is valid 
				{
					board[i][j] = EMPTY;
			
					tempPlaceI=i;
					tempPlaceJ=j;
					piecePlace = true;
				}
			}
			else if(piecePlace == true) //conditional that allows the user to place a piece
			{
				if(board[i][j] == EMPTY && validspace(i,j)) //a condition that restricts the opponent to place pieces in valid spaces
				{
					if((i==tempPlaceI+1 && j==tempPlaceJ+1) || (i==tempPlaceI-1 && j==tempPlaceJ+1))
					{
			
						board[i][j] = opponent;
						piecePlace = false;
						uMove =! uMove;
					}
					else if(i == tempPlaceI && j == tempPlaceJ)
					{
						board[i][j] = opponent;
						piecePlace = false;
						uMove = uMove;
					}
					else if(board[tempPlaceI+1][tempPlaceJ+1] == user)//if there is a user piece where opponent would be able to move
					{
						if(i==tempPlaceI+2&&j==tempPlaceJ+2 && board[tempPlaceI+2][tempPlaceJ+2] == EMPTY)//and if they click on the space to jump to
						{

							board[i][j]=opponent;
							board[tempPlaceI+1][tempPlaceJ+1] = EMPTY; //makes user piece disappear
							Upiece--;
							piecePlace = false;
							uMove =! uMove;
						}
					}
					else if (board[tempPlaceI-1][tempPlaceJ+1]==user)
					{
						if(i==tempPlaceI-2 && j==tempPlaceJ+2 && board[tempPlaceI-2][tempPlaceJ+2] == EMPTY)
						{
							board[i][j]=opponent;
							board[tempPlaceI-1][tempPlaceJ+1] = EMPTY; //makes piece disappear
							Upiece--;
							piecePlace = false;
							uMove =! uMove;
						}
					}
				}
			}
			//pieceMove(i, j, opponent); //Opponents move... can be changed into AI later if we want
		}
	}
}

void GameCheckWinner(HWND hwnd) //checks who won the game
{
	if(Upiece == 5) //condition that checks then declares the game to be over
		gameOver = true;
	else if(Opiece == 5)
		gameOver = true;
}

void GameDrawBPiece(HDC hdc, int i, int j) //function that draws the black piece
{
	HPEN pen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
	HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
	HGDIOBJ penOld, brushOld;

	penOld = SelectObject(hdc, pen);
	brushOld = SelectObject(hdc, brush);

	Ellipse(hdc, 40 + (80*(i)), 40 + (80*(j)), 100 + (80*(i)), 100 + (80*(j)));
	

	SelectObject(hdc, brushOld);
	SelectObject(hdc, penOld);

	DeleteObject(brush);
	DeleteObject(pen);

}

void GameDrawWPiece(HDC hdc, int i, int j) //function that draws the white piece
{
	HPEN pen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
	HBRUSH brush = CreateHatchBrush(HS_DIAGCROSS, RGB(254, 254, 254));
	HGDIOBJ penOld, brushOld;

	penOld = SelectObject(hdc, pen);
	brushOld = SelectObject(hdc, brush);

	Ellipse(hdc, 40 + (80*(i)), 40 + (80*(j)), 100 + (80*(i)), 100 + (80*(j)));

	SelectObject(hdc, brushOld);
	SelectObject(hdc, penOld);

	DeleteObject(brush);
	DeleteObject(pen);

}

void colorback(HDC hdc) //function that colors the background
{
	for(int i = 0; i < WIDTH; i++)
	{
		for(int j = 0; j < HEIGHT; j++)
		{
			
			int color = colorDark; // initializes the color of the whole board
			if(validspace(i,j)) //colors the valid spaces of the board
			{
				color = colorLight;
			}
		
			HBRUSH b = CreateSolidBrush(color);
			RECT r;
			r.left = 30 + 80*j;
			r.right = 30 + 80*(j+1);
			r.top = 30 + 80*i;
			r.bottom = 30 + 80*(i+1);
			FillRect(hdc, &r, b);
		}
	}
}

void drawpieceU(char user) //inputs the users choice in the arrays
{
	for(int j = WIDTH-3; j < WIDTH; j++)
	{
		for(int i = 0; i < HEIGHT; i++)
		{
			
			if(validspace(i,j))
			{
				if(user == 'b')
				{
					board[i][j] = 'b';
					
				}
				else if(user == 'w')
				{
					board[i][j] = 'w';
					
				}
			}
			
		}
	}
	
}

void drawpieceC(char user) //inputs the opponents characters depending on the user choice
{
	for(int j = 0; j < WIDTH-5; j++)
	{
		for(int i = 0; i < HEIGHT; i++)
		{
			if(validspace(i,j))
			{
				if(user == 'b')
				{
					board[i][j] = 'w';
				}

				else if(user == 'w')
				{
					board[i][j] = 'b';
				}

			}
			
		}
	}
}

void pieceMove(int i, int j, char piece) //a back-up function but absolutely unneeded at the moment
{

	static int tempPlaceI; // static variables save the value of tempPlace so we can use them when the pieceMove function is called again 
	static int tempPlaceJ;

	if (piecePlace == false) //conditional that allows the user to pick a piece up
	{
		if (board[i][j] == piece)
		// then highlight the piece because it is valid 
		{
			board[i][j] = EMPTY;
			
			tempPlaceI=i;
			tempPlaceJ=j;
			piecePlace = true;
		}
	}

	else if(piecePlace == true) //conditional that allows the user to place a piece
	{
		if(board[i][j] == EMPTY && validspace(i,j)) //a condition that restricts the user to place pieces in valid spaces
		{
			if((i==tempPlaceI+1 && j==tempPlaceJ-1) || (i==tempPlaceI-1 && j==tempPlaceJ-1))
			{
			
			board[i][j] = piece;
			piecePlace = false;
			uMove =! uMove;
			}
			
		}
	}
}