#include "Piece.h"
#include "Point.h"
#include <iostream>
using namespace std;

Piece::Piece()
{
}

void Piece::drawPiece(int x, int y, int board[][24]) //Need to make this use the const
{
	for (int i = 0; i < sizeof(squares) / sizeof(squares[0]); i++) {
		Point p = squares[i];
		if (p.x + this->x < 10 && p.y + this->y < 24) {
			board[p.x + this->x][p.y + this->y] = 2;
		}
		else {
			std::cout << "Attempted to draw piece out of bounds";
		}
		
		//SDL_Rect rect = { x + p.x, y + p.y, SQUARE_SIZE, SQUARE_SIZE }; // x, y, w, h
		//SDL_FillRect(gScreenSurface, &rect, SDL_MapRGB(gScreenSurface->format, 0, 255, 0));
	}
}


int Piece::moveDown()
{
	y++;
	return y;
}

int Piece::moveDown(int dist)
{
	y += dist;
	return y;
}

bool Piece::hasCollided(int board[][24])
{
	if (this->y + 1 == 24) return true;
	for (int i = 0; i < sizeof(squares) / sizeof(squares[0]); i++) {
		if (board[this->x][this->y + 1] == 1) return true;
	}
	return false;
}



Piece::~Piece()
{
}
