/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <ctime>

#include "Square.h"
#include "LinePiece.h"
#include "LPiece.h"
#include "BackwardLPiece.h"
#include "SPiece.h"
#include "TPiece.h"
#include "ZPiece.h"


using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 375;
const int SCREEN_HEIGHT = 625;

//Board and square dimensions
const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 24;
const int SQUARE_SIZE = 25;
//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

Piece* piece;

int score = 0;

int board[BOARD_WIDTH][BOARD_HEIGHT] = { 0 };


bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		srand((int)time(0));
		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}

	return success;
}


void close()
{
	//Deallocate surface
	//gHelloWorld = NULL;

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

//Draws a square of the chosen colour at the specified coordinates
void drawSquare(int x, int y, int r, int g, int b) {
	SDL_Rect rect = { x, y, SQUARE_SIZE, SQUARE_SIZE };
	SDL_FillRect(gScreenSurface, &rect, SDL_MapRGB(gScreenSurface->format, r, g, b));
}

//Fills the screen with black to clear it
void clearScreen() {
	SDL_Rect rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }; // x, y, w, h
	SDL_FillRect(gScreenSurface, &rect, SDL_MapRGB(gScreenSurface->format, 0, 0, 0));
	//SDL_RenderDrawRect(gWindow, &rect);
}

//Renders the Tetris board based on the 2d array storing the details of it.
void drawBoard() {
	for (int j = 0; j < BOARD_HEIGHT; j++) {
		for (int i = 0; i < BOARD_WIDTH; i++) {
			switch (board[i][j])
			{
			case 0: 
				drawSquare((SQUARE_SIZE + 1) * i, (SQUARE_SIZE + 1) * j, 50, 50, 50);
				break;
			case 1:
				drawSquare((SQUARE_SIZE + 1) * i, (SQUARE_SIZE + 1) * j, 255, 0, 0);
				break;
			case 2:
				drawSquare((SQUARE_SIZE + 1) * i, (SQUARE_SIZE + 1) * j, 0, 0, 255);
				break;
			default:
				break;
			}
		}
	}
}

//Unused functions for applying a function to each square, row or column

/*void eachRow(void(*f)(int[])) {
	for (int j = 0; j < BOARD_HEIGHT; j++) {
		f(board[j]);
	}
}
//void eachCol(int[] col, void(*f)(int, int)) {
	//for (int i = 0; i < BOARD_WIDTH; i++) {
	//	f(i, j);
	//}
//}
void eachSquare(int(*f)(int)) {
	//eachRow(bind2nd(eachCol, f));
	for (int j = 0; j < BOARD_HEIGHT; j++) {
		for (int i = 0; i < BOARD_WIDTH; i++) {
			board[i][j] = f(board[i][j]);
		}
	}
}*/

void printBoard() {
	
	for (int j = 0; j < BOARD_HEIGHT; j++) {
		for (int i = 0; i < BOARD_WIDTH; i++) {
			std::cout << board[i][j];
		}
		std::cout << endl;
	}
	std::cout << endl;
	std::cout << endl;
}

//Shifts the rows above the specified row down.
//Used when the player clears a row.
void shiftRows(int row) {
	for (int j = row; j > 0; j--) {
		for (int i = 0; i < BOARD_WIDTH; i++) {
			board[i][j] = board[i][j - 1];
		}
	}
	//Clears top row as it has been shifted down.
	for (int i = 0; i < BOARD_WIDTH; i++) {
		board[i][0] = 0; 
	}
}

//Checks the board to shift any that have been filled.
//Updates the score by 1 and prints it for each full row.
void checkAndShiftBoard() {
	for (int j = 0; j < BOARD_HEIGHT; j++) {
		bool complete = true;
		for (int i = 0; i < BOARD_WIDTH; i++) {
			if (board[i][j] == 0) {
				complete = false;
				break;
			}
		}
		if (complete) {
			score += 1;
			cout << "Current score: " << score << "\n";
			shiftRows(j);
		}
	}
}

//Randomly selects the next piece.
void newPiece() {
	int r = (rand() % 7) + 1; 
	switch (r) {
	case 1:
		piece = new Square();
		break;
	case 2:
		piece = new LinePiece();
		break;
	case 3:
		piece = new LPiece();
		break;
	case 4:
		piece = new BackwardLPiece();
		break;
	case 5:
		piece = new SPiece();
		break;
	case 6:
		piece = new ZPiece();
		break;
	case 7:
		piece = new TPiece();
		break;
	default:
		piece = new LinePiece();
		break;
	}
}

//Checks if the stacked rows have reached high enough to lose the game.
bool checkIfLost() {
	for (int i = 0; i < BOARD_WIDTH; i++) {
		if (board[i][0] == 1) return true;
	}
	return false;
}

//Handles user events.
int handleEvents() {
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		//User requests quit
		if (e.type == SDL_QUIT)
		{
			return 1;
		}
		else if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym)
			{
			case SDLK_UP:
				piece->rotateClockwise(board);
				break;
			case SDLK_DOWN:
				return 2;
				break;
			case SDLK_LEFT:
				piece->playerMoveHor(-1, board);
				break;

			case SDLK_RIGHT:
				piece->playerMoveHor(1, board);
				break;

			default:
				break;
			}
		}
	}
	return 0;
}

//Moves the pieces, updates the display and responds to events until the game is complete.
void gameLoop()
{
	newPiece();
	bool finished = false;

	//Counts the duration elapsed for game speed increases.
	int counter = 0;

	int gamespeed = 100;

	while (!finished) {

		int movespeed = 4;
		counter++;

		switch (handleEvents()) {
		case 1:
			finished = true;
			break;
		case 2:
			movespeed = 1;
		}
		
		//Puts the current piece onto the board array.
		piece->drawPiece(board);

		//Draws the board to the screen and updates the screen.
		drawBoard();
		SDL_UpdateWindowSurface(gWindow);

		//Removes the piece from the board array so it isn't rendered next time.
		piece->remove(board);

		//Moves the piece down and handles collisions.
		//Speeds up the gamespeed and generates a new random piece every time a piece touches the bottom.
		//Ends the game if the player loses.
		if (counter % movespeed == 0) {
			piece->moveDown();
			if (piece->hasCollided(board)) {
				piece->collide(board);
				delete piece;
				newPiece();
				checkAndShiftBoard();
				if (gamespeed > 10) {
					gamespeed -= 2;
				}
			}
			if (checkIfLost()) {
				finished = true;
			}
		}
		//Clears the screen then delays for a set amount of time to make the game playable.
		clearScreen();
		SDL_Delay(gamespeed);

	}
}


int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		gameLoop();
	}

	//Free resources and close SDL
	close();

	return 0;
}

