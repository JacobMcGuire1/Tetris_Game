#include "Piece.h"
#include "Point.h"
#include <iostream>
using namespace std;

Piece::Piece()
{
}

void Piece::drawPiece(int board[][24]) //Need to make this use the const
{
	for (int i = 0; i < sizeof(squares) / sizeof(squares[0]); i++) {
		Point p = squares[i];
		if (p.x + this->x < 10 && p.y + this->y < 24) {
			board[p.x + this->x][p.y + this->y] = 2;
		}
		else {
			std::cout << "Attempted to draw piece out of bounds";
		}
	}
}

void Piece::remove(int board[][24]) //Need to make this use the const
{
	for (int i = 0; i < sizeof(squares) / sizeof(squares[0]); i++) {
		Point p = squares[i];
		if (p.x + this->x < 10 && p.y + this->y < 24) {
			//std::cout << board[p.x + this->x][p.y + this->y];
			board[p.x + this->x][p.y + this->y] = 0;
			
		}
		else {
			std::cout << "Attempted to remove piece out of bounds";
		}
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

int Piece::moveHor(int dist, int board[][24])
{
	
	x += dist;
	if (hasCollided(board) || hasTouchedSide(board)) x -= dist;
	return x;
}


bool Piece::hasCollided(int board[][24])
{
	for (int i = 0; i < sizeof(squares) / sizeof(squares[0]); i++) {
		Point p = squares[i];
		if (board[this->x + p.x][this->y + p.y + 1] == 1) return true;
		if (this->y + 1 + p.y == 24) return true;
	}
	return false;
}

bool Piece::hasTouchedSide(int board[][24])
{
	for (int i = 0; i < sizeof(squares) / sizeof(squares[0]); i++) {
		Point p = squares[i];
		if (this->x + 1 + p.x == 11 || this->x + 1 + p.x == 0) return true;
	}
	return false;
}

void Piece::collide(int board[][24])
{
	for (int i = 0; i < sizeof(squares) / sizeof(squares[0]); i++) {
		Point p = squares[i];
		if (p.x + this->x < 10 && p.y + this->y < 24) {
			board[p.x + this->x][p.y + this->y] = 1;
		}
	}
}



Piece::~Piece()
{
}
