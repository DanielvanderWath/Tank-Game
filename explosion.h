#ifndef EXPLOSION_H
#define EXPLOSION_H
#include "mylib.h"

class Explosion
{
	private:
		float phase;
		float explosionSize;
		GLuint VBO;
		unsigned int triCount;
		int coords[3];
	public:
		Explosion(GLuint vbo, int *Coords, float size);
		void getDrawInfo(GLuint *vbo, unsigned int *tris);
		void getPosition(int *position);
		float getSize();
		float getPhase();
		bool tick();


};

#endif

