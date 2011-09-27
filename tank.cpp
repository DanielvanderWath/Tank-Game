#include "tank.h"
#include "tankgame.h"

extern GLuint VBOs[numVBOs];
  

Tank::Tank()
{
	coord[0]=GAMESIZE/2;
	coord[1]=GAMESIZE/10;
	coord[2]=0;

	bulletSpeed=10;
	gunCoolDown=0;
	bombCoolDown=0;
	aim=0.0f;
	VBO=0;
	triCount=0;	
}

void Tank::tick()
{
	if(gunCoolDown > 0)
		gunCoolDown--;
	if(bombCoolDown > 0)
		bombCoolDown--;
}

void Tank::shoot()
{
	if(gunCoolDown == 0)
	{
		int bulletVel[3]={(int)(-sin(RADS(aim))*bulletSpeed), (int)(cos(RADS(aim))*bulletSpeed), 0};
	
		Bullet *b= new Bullet(coord, bulletVel);
		b->setTriCount(BULLET_SIZE);
		
		bullets.push_back(b);
		
		gunCoolDown=25;
	}
}

void Tank::shootBomb()
{
	if(bombCoolDown == 0)
	{
		int bombSpeed=5;
		int bombVel[3]={ (int)(-sin(RADS(aim))*bombSpeed), (int)(cos(RADS(aim)*bulletSpeed), bombSpeed*2)};

		Bullet *b=new Bullet(coord, bombVel);//, 200);
		bombs.push_back(b);

		bombCoolDown=100;
	}
}

void Tank::moveBullets(Formation *form)
{
	//bullets
	for(list<Bullet*>::iterator i=bullets.begin(); i!=bullets.end(); i++)
	{
		(*i)->move();
		(*i)->checkCollision(form);
		if(!(*i)->isAlive())
		{
			delete *i;
			i=bullets.erase(i);
		}
	}

	//bombs
	for(list<Bullet*>::iterator i=bombs.begin(); i!=bombs.end(); i++)
	{
		(*i)->move();
	}
}

void Tank::getPosition(int *position)
{
	for(int i=0; i<3; i++)
		position[i]=coord[i];
}

float Tank::getRotationZ()
{
	return (aim/180)*PI;
}

void Tank::setVBO(GLuint vbo, unsigned int tricount)
{
	VBO=vbo;
	triCount=tricount;	
}


GLuint Tank::getVBO()
{
	return VBO;
}

unsigned int Tank::getTriCount()
{
	return triCount;
}

void Tank::moveiv(int *vector)
{
	//we're going to assume that no one retarded passes in the wrong sized array
	for(int i=0; i<3; i++)
		coord[i]=vector[i];
	
	//clamp to screen boundaries
	clamp3i(0, coord, GAMESIZE);
}

void Tank::move3i(int x, int y, int z)
{
	coord[0]+=x;
	coord[1]+=y;
	coord[2]+=z;
	

	//clamp to screen boundaries
	clamp3i(0, coord, GAMESIZE);

}

void Tank::rotate(float angle)
{
	aim+=angle;
	clamp(-70.0f, &aim, 70.0f); 
}
