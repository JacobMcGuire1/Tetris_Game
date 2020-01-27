#include "ZPiece.h"



ZPiece::ZPiece()
{
	squares[0] = Point(-1, 1);
	squares[1] = Point(0, 1);
	squares[2] = Point(0, 0);
	squares[3] = Point(1, 0);

	x = 4;
	y = 0;
}


ZPiece::~ZPiece()
{
}
