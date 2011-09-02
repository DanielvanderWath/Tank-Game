#ifndef BULLET_H 
#define BULLET_H
#include "mylib.h"
#include "formation.h"

class Bullet
{
	private:
		int coords[3];
		int velocity[3];
		GLuint VBO;
		unsigned int triCount;
		float phase;
		bool alive;
	public:
		Bullet(int *startCoords, int *initVel);
		void move();
		GLuint getVBO();
		void setTriCount(/*GLuint vbo,*/ unsigned int triCount);
		bool isAlive();
		float getSpin();
		void getPosition(int *position);
		void checkCollision(Formation *form);
		unsigned int getTriCount();
};
#endif
