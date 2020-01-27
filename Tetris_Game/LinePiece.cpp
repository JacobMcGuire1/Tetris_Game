#include "LinePiece.h"



LinePiece::LinePiece()
{
	squares[2] = Point(0, -1);
	squares[1] = Point(0, 0);
	squares[0] = Point(0, 1);
	squares[3] = Point(0, 2);

	x = 4;
	y = 0;
}


LinePiece::~LinePiece()
{
}
