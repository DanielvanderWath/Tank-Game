#include "bullet.h"
#include "tankgame.h"

Bullet::Bullet(int *startCoords, int *initVel)
{
	for(int i=0; i<3; i++)
	{
		coords[i]=startCoords[i];
		velocity[i]=initVel[i];
	}
	phase=rand()%90;
	alive=true;
}

GLuint Bullet::getVBO()
{
	return VBO;
}

float Bullet::getSpin()
{
	return phase;
}

void Bullet::setTriCount( unsigned int tricount)
{
	//VBO=vbo;
	triCount=tricount;
}

bool Bullet::isAlive()
{
	return alive;
}

void Bullet::checkCollision(Formation *form)
{	//kill this bullet if the formation says a collision has taken place
	if(form->checkCollision(coords))	
		alive=false;
}

void Bullet::move()
{
	phase+=0.3f;
	fori0to3
		coords[i]+=velocity[i];
	
	//bounce off the walls
	if(coords[0] < 0 || coords[0] > GAMESIZE)
		velocity[0]*=-1;

	//destroy if it goes off the top (or bottom? if that ever happens) of the screen.
	if(coords[1] < 0 || coords[1] > GAMESIZE)
		alive=false;
}

unsigned int Bullet::getTriCount()
{
	return triCount;
}

void Bullet::getPosition(int *position)
{
	fori0to3
		position[i]=coords[i];
}
