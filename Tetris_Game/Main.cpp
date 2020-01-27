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

bool loadMedia()
{
	//Loading success flag
	bool success = true;

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

void drawSquare(int x, int y, int r, int g, int b) {
	SDL_Rect rect = { x, y, SQUARE_SIZE, SQUARE_SIZE }; // x, y, w, h
	SDL_FillRect(gScreenSurface, &rect, SDL_MapRGB(gScreenSurface->format, r, g, b));
	//SDL_RenderDrawRect(gWindow, &rect);
}

void clearScreen() {
	SDL_Rect rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }; // x, y, w, h
	SDL_FillRect(gScreenSurface, &rect, SDL_MapRGB(gScreenSurface->format, 0, 0, 0));
	//SDL_RenderDrawRect(gWindow, &rect);
}

void drawBoard() {
	
	for (int j = 0; j < BOARD_HEIGHT; j++) {
		for (int i = 0; i < BOARD_WIDTH; i++) {
			//std::cout << board[i][j];
			switch (board[i][j])
			{
			case 0: //Empty square
				drawSquare((SQUARE_SIZE + 1) * i, (SQUARE_SIZE + 1) * j, 50, 50, 50);
				break;
				//implement this as nothing then add a break
			case 1: //Normal square
				drawSquare((SQUARE_SIZE + 1) * i, (SQUARE_SIZE + 1) * j, 255, 0, 0);
				break;
			case 2:  //A square from the piece currently being dropped
				drawSquare((SQUARE_SIZE + 1) * i, (SQUARE_SIZE + 1) * j, 0, 0, 255);
				break;
			default:
				break;
			}
		}
		//std::cout << endl;
	}
}
void eachRow(void(*f)(int[])) {
	//for (int j = 0; j < BOARD_HEIGHT; j++) {
	//	f(board[j]);
	//}
	//std::transform(board[0], board[BOARD_HEIGHT - 1], board[0], f);
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
}

int doSomething(int val) {
	if (val == 0) return 1;
}

void printBoard() { //Should check for row completion in this 
	
	for (int j = 0; j < BOARD_HEIGHT; j++) {
		for (int i = 0; i < BOARD_WIDTH; i++) {
			std::cout << board[i][j];
		}
		std::cout << endl;
	}
	std::cout << endl;
	std::cout << endl;
}

bool checkCompleteRow(int row[], int j) {
	for (int i = 0; i < sizeof(row) / sizeof(row[0]); i++) {
		if (board[i][j] == 0) {
			return false;
		}
	}
	std::cout << "row complete \n";
	return true;
}

void shiftRows(int row) {
	for (int j = row; j > 0; j--) {
		//*board[j] = *board[j - 1];
		for (int i = 0; i < BOARD_WIDTH; i++) {
			board[i][j] = board[i][j - 1];
		}
	}
	for (int i = 0; i < BOARD_WIDTH; i++) {
		board[i][0] = 0; //Set top row to 0
	}
}

void shiftBoard() {
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
			cout << score << "\n";
			shiftRows(j);
		}
	}
}

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

bool checkIfLost() {
	for (int i = 0; i < BOARD_WIDTH; i++) {
		if (board[i][0] == 1) return true;
	}
	return false;
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
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{

			//LinePiece* square = new LinePiece(); // Make global?
			newPiece();
			bool finished = false;

			//Event handler
			SDL_Event e;

			int counter = 0;

			int gamespeed = 100;

			while (!finished) {

				

				int movespeed = 4;

				while (SDL_PollEvent(&e) != 0)
				{
					
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						finished = true;
					}
					else if (e.type == SDL_KEYDOWN) {
						switch (e.key.keysym.sym)
						{
						case SDLK_UP:
							piece->rotateClockwise(board);
							break;
						case SDLK_DOWN:
							movespeed = 1;
							break;
						case SDLK_LEFT:
							piece->playerMoveHor(-1, board);
							break;

						case SDLK_RIGHT:
							piece->playerMoveHor(1, board);
							break;

						default:
							//gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
							break;
						}
					}
				}
				counter++;
				
				piece->drawPiece(board);
				//Apply the image
				drawBoard();

				//Update the surface
				SDL_UpdateWindowSurface(gWindow);

				//printBoard();
				
				piece->remove(board);
				if (counter % movespeed == 0) {
					piece->moveDown();
					if (piece->hasCollided(board)) {

						//std::cout << "collision";
						piece->collide(board);
						delete piece;
						newPiece();
						shiftBoard();

						if (gamespeed > 10) {
							gamespeed -= 2;
						}
					}
					if (checkIfLost()) {
						finished = true;
					}
				}
				
				

				clearScreen();


				//Wait .1 secondsw
				SDL_Delay(gamespeed);

			}
			
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}

