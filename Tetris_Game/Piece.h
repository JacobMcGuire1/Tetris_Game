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
	bool hasCollided(int board[][24]);
	void collide(int board[][24]); //rename this
	void remove(int board[][24]);
	~Piece();
};
