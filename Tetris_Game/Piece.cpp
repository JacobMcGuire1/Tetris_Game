#include "Piece.h"
#include "Point.h"
#include <iostream>
using namespace std;

Piece::Piece()
{
}

//Adds the piece to the board array, ensuring that it doesn't try to render any squares that are out of bounds.
void Piece::drawPiece(int board[][24])
{
	for (int i = 0; i < sizeof(squares) / sizeof(squares[0]); i++) {
		Point p = squares[i];
		if (p.x + this->x < 10 && p.y + this->y < 24 && p.y + this->y >= 0) {
			board[p.x + this->x][p.y + this->y] = 2;
		}
		else {
			//std::cout << "Attempted to draw square out of bounds";
		}
	}
}

//Removes the piece from the board so it can be rendered in its new position next term.
void Piece::remove(int board[][24])
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

//Rotates the piece, moving it to prevent it going off the screen if necessary.
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

//Moves the piece for the player, unless it would cause a collision.
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

//Checks if the bottom of the piece is touching a square or the bottom of the board.
bool Piece::hasCollided(int board[][24])
{
	for (int i = 0; i < sizeof(squares) / sizeof(squares[0]); i++) {
		Point p = squares[i];
		if (board[this->x + p.x][this->y + p.y + 1] == 1) return true;
		if (this->y + 1 + p.y == 24) return true;
	}
	return false;
}

//Checks if the piece has gone over the side of the screen and returns the movement needed to correct this.
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

//Lands the piece at the site of its collision, allowing a new piece to be generated.
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
