#include "baddy.h"
#include "tankgame.h"

Baddy::Baddy(int HP, int *coord)
{
	hp=HP;
	explosionTime=-1;
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

	if(explosionTime>0)
		explosionTime--;
}

int Baddy::getC(int i)
{
	return formCoords[i];
}

int Baddy::getHP()
{
	return hp;
}

float Baddy::getExplosionSize()
{
	return (float)(100-explosionTime);
}

int Baddy::getExplosionTime()
{
	return explosionTime;
}

void Baddy::hit()
{
	if(--hp <1)
		explosionTime=100;
}

