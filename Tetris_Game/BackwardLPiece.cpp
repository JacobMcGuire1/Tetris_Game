#include "BackwardLPiece.h"



BackwardLPiece::BackwardLPiece()
{
	squares[0] = Point(0, -1);
	squares[1] = Point(0, 0);
	squares[2] = Point(0, 1);
	squares[3] = Point(-1, 1);

	x = 4;
	y = 0;
}


BackwardLPiece::~BackwardLPiece()
{
}
