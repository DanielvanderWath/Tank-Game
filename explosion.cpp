#include "explosion.h"
#include "tankgame.h"

Explosion::Explosion(GLuint vbo, int *Coords, float size)
{
	phase=0.0f;
	explosionSize=size;

	VBO=vbo;
	triCount=0;//not used 
	
	for(int i=0; i<3; i++)
		coords[i]=Coords[i];
}

void Explosion::getDrawInfo(GLuint *vbo, unsigned int *tris)
{
	*vbo=VBO;
	*tris=triCount;	
}

void Explosion::getPosition(int *position)
{
	for(int i=0; i<3; i++)
		position[i]=coords[i];
}

float Explosion::getSize()
{
	return explosionSize;
}

float Explosion::getPhase()
{
	return phase;
}

bool Explosion::tick()
{
	//return true if the explosion has finished
	phase+=1.0f;		
	explosionSize-=3.0f;
	
	if(explosionSize<0.0f)
		return true;
	return false;
	
}
