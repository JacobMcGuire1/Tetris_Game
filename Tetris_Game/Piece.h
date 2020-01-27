#include "Point.h"
class Piece
{
public:
	Point squares[4];
	int x;
	int y;
	Piece();
	void drawPiece(int x, int y, int board[][24]);
	int moveDown();
	int moveDown(int dist);
	bool hasCollided(int board[][24]);
	~Piece();
};
