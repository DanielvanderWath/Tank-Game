#ifndef TANK_H
#define TANK_H

#include <list>
#include "bullet.h"

using namespace std;

class Tank
{
	private:
		int coord[3];	
		float aim;
		GLuint VBO; 
		unsigned int triCount;
		int bulletSpeed;
		list<Bullet*> bullets;
		list<Bullet*> bombs;
		int gunCoolDown;
		int bombCoolDown;
	public:
		Tank();
		void getPosition(int *position);
		float getRotationZ();
		GLuint getVBO();
		unsigned int getTriCount();
		
		void setVBO(GLuint vbo, unsigned int tricount);
		void moveiv(int *vector);//this will do for the time being
		void move3i(int x, int y, int z);//this will do for the time being
		void tick();
		void rotate(float angle);
		void shoot();
		void shootBomb();
		void moveBullets(Formation *form);
		int drawBullets();
};
#endif
