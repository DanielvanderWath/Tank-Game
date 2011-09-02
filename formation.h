#ifndef FORMATION_H
#define FORMATION_H
#include "baddy.h"
#include <list>
#include "mylib.h"

using namespace std;

class Formation
{
private:
	int coords[3];
	int velocity[3];
	int baddySize;
	list<Baddy*> baddies;
public:
	Formation(int width, int height, int *coords);
	bool checkCollision(int *bangCoords);
	int draw(int phase);
	int getFurthest(int axis);
	int getNearest(int axis);
	bool move();
	bool allDead();
};
#endif
