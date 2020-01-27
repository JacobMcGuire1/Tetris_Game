/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include "Square.h"
#include <iostream>
using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;
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

			Square* square = new Square();
			for (int i = 0; i < 100; i++) {
				
				square->drawPiece(board);
				//Apply the image
				drawBoard();

				//Update the surface
				SDL_UpdateWindowSurface(gWindow);

				printBoard();
				square->remove(board);
				square->moveDown();
				if (square->hasCollided(board)) {
					
					std::cout << "collision";
					square->collide(board);
					delete square;
					square = new Square();
					
				}
				

				clearScreen();


				//Wait .1 secondsw
				SDL_Delay(100);

			}
			
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}

