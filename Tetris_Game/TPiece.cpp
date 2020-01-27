#include "TPiece.h"



TPiece::TPiece()
{
	squares[0] = Point(-1, 0);
	squares[1] = Point(0, 0);
	squares[2] = Point(1, 0);
	squares[3] = Point(0, 1);

	x = 4;
	y = 0;
}


TPiece::~TPiece()
{
}
