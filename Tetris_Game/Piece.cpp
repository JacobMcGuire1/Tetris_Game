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
		if (p.x + this->x < 10 && p.y + this->y < 24 && p.y + this->y >= 0) {
			board[p.x + this->x][p.y + this->y] = 2;
		}
		else {
			std::cout << "Attempted to draw square out of bounds";
		}
	}
}

void Piece::remove(int board[][24]) //Need to make this use the const
{
	for (int i = 0; i < sizeof(squares) / sizeof(squares[0]); i++) {
		Point p = squares[i];
		if (p.x + this->x < 10 && p.y + this->y < 24 && p.y + this->y >= 0) {
			//std::cout << board[p.x + this->x][p.y + this->y];
			board[p.x + this->x][p.y + this->y] = 0;
			
		}
		else {
			std::cout << "Attempted to remove piece out of bounds";
		}
	}
}

void Piece::rotateClockwise(int board[][24])
{
	int lowest = 0;
	int newlowest = 0;
	for (int i = 0; i < sizeof(squares) / sizeof(squares[0]); i++) {
		Point p = squares[i];
		if (p.y > lowest) lowest = p.y;
		int h = p.x;
		int k = p.y;
		
		squares[i].x = k;
		squares[i].y = 0 - h;
		if (p.y > newlowest) newlowest = p.y;

	}
	moveHor(hasTouchedSide(board));
	moveDown(lowest - newlowest);
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

int Piece::playerMoveHor(int dist, int board[][24])
{
	
	moveHor(dist);
	if (hasCollided(board) || hasTouchedSide(board) != 0) moveHor(-dist);
	return x;
}

int Piece::moveHor(int dist) {
	x += dist;
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

int Piece::hasTouchedSide(int board[][24])
{
	int correction = 0;
	for (int i = 0; i < sizeof(squares) / sizeof(squares[0]); i++) {
		Point p = squares[i];
		if (this->x + 1 + p.x >= 11) {
			if (abs(this->x + 1 + p.x - 10) > abs(correction)) correction = -(this->x + 1 + p.x - 10);
			//return (this->x + 1 + p.x - 10);
		}
		if (this->x + 1 + p.x <= 0) {
			//return (this->x + 2 + p.x);
			if (abs(this->x + 2 + p.x) > abs(correction)) correction = this->x + 2 + p.x;
		}
	}
	if (correction != 0) cout << correction << "correction\n";
	return correction;
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
