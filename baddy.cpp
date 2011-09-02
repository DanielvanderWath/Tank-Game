#include "baddy.h"
#include "tankgame.h"

Baddy::Baddy(int HP, int *coord)
{
	hp=HP;
	for(int i=0; i < 3; i++)
		formCoords[i]=coord[i];

	VBO=BADDY;
	triCount=BADDY_SIZE;
	phase=rand()%90;
}

void Baddy::getDimensions(int *dims)
{
	for(int i=0; i<3; i++)
		dims[i]=dimensions[i];
}

void Baddy::addFormCoords(int *retCoords)
{
	for(int i=0; i < 3; i++)
		retCoords[i]+=formCoords[i];
}

int Baddy::getC(int i)
{
	return formCoords[i];
}

int Baddy::getHP()
{
	return hp;
}

void Baddy::hit()
{
	hp--;
}

