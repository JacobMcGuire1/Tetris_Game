#pragma once
#include "Point.h"
class Piece
{
public:
	Point squares[4];
	int x;
	int y;
	Piece();
	void drawPiece(int board[][24]);
	int moveDown();
	int moveDown(int dist);
	int moveHor(int dist);
	int playerMoveHor(int dist, int board[][24]);
	bool hasCollided(int board[][24]);
	int hasTouchedSide(int board[][24]);
	void collide(int board[][24]); //rename this
	void remove(int board[][24]);
	void rotateClockwise(int board[][24]);
	~Piece();
};
