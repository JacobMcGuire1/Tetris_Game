#include "LPiece.h"



LPiece::LPiece()
{
	squares[0] = Point(0, 0);
	squares[1] = Point(0, 1);
	squares[2] = Point(0, 2);
	squares[3] = Point(1, 2);

	x = 4;
	y = 0;
}


LPiece::~LPiece()
{
}
