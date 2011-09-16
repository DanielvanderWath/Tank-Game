#include "formation.h"
#include "baddy.h"
#include "tankgame.h"
#include "explosion.h"

Formation::Formation(int width, int height, int *Coords)
{
	int spacing[3] = {25, 40, 2};
	
	velocity[0]=3;
	velocity[1]=-15;
	baddySize=50;

	for(int i=0; i<3; i++)
		coords[i]=Coords[i];
	
	for(int h=0; h<height; h++)
		for(int w=0; w<width; w++)
		{
			int formcoord[3]={(baddySize+spacing[0])*w, (baddySize+spacing[1])*h, 0};

			Baddy *temp=new Baddy(2, formcoord);
			baddies.push_back(temp);
		}
}

int Formation::getNearest(int axis)
{
	//work out where the right edge of the rightmost baddy is.
	int leftMost=GAMESIZE;
	for(list<Baddy*>::iterator i=baddies.begin(); i!=baddies.end(); i++)
	{
		if(leftMost> (*i)->getC(axis))
			leftMost=(*i)->getC(axis);
	}

	return leftMost-baddySize/2;

}
int Formation::getFurthest(int axis)
{
	//work out where the right edge of the rightmost baddy is.
	int rightMost=0;
	for(list<Baddy*>::iterator i=baddies.begin(); i!=baddies.end(); i++)
	{
		if(rightMost< (*i)->getC(axis))
			rightMost=(*i)->getC(axis);
	}

	return rightMost+baddySize/2;

}

bool Formation::checkCollision(int *bangCoords)
{
	//first check if the bullet is somewhere within the bounds of the formation
	if(bangCoords[0] > coords[0] && bangCoords[0] < coords[0]+getFurthest(0) && bangCoords[1] > coords[1] && bangCoords[1] < coords[1]+getFurthest(1))
	{
		//then see if it hit a baddy
		for(list<Baddy*>::iterator i=baddies.begin(); i!=baddies.end(); i++)
		{
			int baddyCoords[]={coords[0], coords[1], coords[2]};
			int baddyRadius=baddySize/2;	
			(*i)->addFormCoords(baddyCoords);
			if(bangCoords[0] > baddyCoords[0] - baddyRadius && bangCoords[0] < baddyCoords[0] + baddyRadius )
				if(bangCoords[1] > baddyCoords[1] - baddyRadius && bangCoords[1] < baddyCoords[1] + baddyRadius )
				{
					//collision occurred
					(*i)->hit();
					return true;
				}	
		}
	}
	return false;
}

bool Formation::allDead()
{
	return baddies.empty();
}

bool Formation::move(list<Explosion*> *explosions)
{//return true if y coordinate goes below YBOUND
	//move horizontally
	coords[0]+=velocity[0];

	
	//check for collision with the edge of the screen, if so then move down a bit
	if(coords[0]+getNearest(0) < 0 || coords[0]+getFurthest(0) > GAMESIZE)
	{
		coords[1]+=velocity[1];
		velocity[0]*=-1.0f;
	}

	if(coords[1]-getNearest(1) < YBOUND)
		return true;

	//checking for finished explosions here
	for(list<Baddy*>::iterator i=baddies.begin(); i!=baddies.end(); i++)
	{
		if((*i)->getExplosionTime()>0)
		//the below line is for baddy explosions. the above one removes them as soon as they die
		//if((*i)->getExplosionTime()==0)
		{
			int explCoords[3];
			for(int j=0; j<3; j++)
				explCoords[j]=coords[j];

			(*i)->addFormCoords(explCoords);
			explosions->push_back(new Explosion((*i)->getVBO(), explCoords, 400 ));
			delete *i;
			i=baddies.erase(i);
		}
	}

	return false;
}

