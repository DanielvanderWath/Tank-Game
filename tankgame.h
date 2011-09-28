#ifndef TANK_GAME_H
#define TANK_GAME_H
#include <math.h>
#include <time.h>
#include "mylib.h"
#include "formation.h"
#include "bullet.h"
#include "tank.h"
#include "explosion.h"

const float SCALE=1.0f;

#define G2S(X) (X/20.0f - 10.0f)

const int GAMESIZE=1000;

const int YBOUND=100;

const int numVBOs=4;
//model indices
const unsigned int TANK=0;
const unsigned int BULLET=1;
const unsigned int BADDY=2;
const unsigned int GAMESCREEN=3;
const unsigned int TANK_SIZE=3;
const float TANKSCALE=0.3f;
const float BULLETSCALE=0.3f;
const float BADDYSCALE=0.05f;
const unsigned int BULLET_SIZE=4;
const unsigned int BADDY_SIZE=6;//verts, 8 triangles
const unsigned int GAMESCREEN_SIZE=4;//verts, 8 triangles

#endif
