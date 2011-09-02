#define GLERR(X) if(CheckGLError(X, __LINE__, __FILE__))return 1;
#define SDLERR(X) SDLErrorAndDie(X, __LINE__, __FILE__)
#define WINWIDTH 640
#define WINHEIGHT 480

#include "tankgame.h"

const unsigned int VERTS=0;
const unsigned int COLOURS=1;
GLuint VBOs[numVBOs];

GLint transloc=0, rotloc=0, scaleloc=0, matloc=0;

using namespace std;

int initSDL(SDL_Window **window)
{
	if(SDL_Init(SDL_INIT_VIDEO))
	{
		printf("Failed to initialise SDL\n");
		return 1;
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); //double buffering on obviously
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3); 
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	
	*window=SDL_CreateWindow("GLCLTest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINWIDTH, WINHEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN); 
		if((window)==NULL)
			SDLERR("SDL_CreateWindow");	
	return 0;
}

void handleSDLEvent(SDL_Event *event, bool *loop, Tank *tank)
{
	switch(event->type)
	{
		case SDL_KEYDOWN:
			switch(event->key.keysym.sym)
			{
				case SDLK_ESCAPE:
					*loop=false;
					break;
				case SDLK_a:
					tank->move3i(-5, 0, 0);
					break;
				case SDLK_d:
					tank->move3i(5, 0, 0);
					break;
				case SDLK_w:
					tank->move3i(0, 5, 0);
					break;
				case SDLK_s:
					tank->move3i(0, -5, 0);
					break;
				case SDLK_e:
					tank->rotate(-5.0f);
					break;
				case SDLK_q:
					tank->rotate(5.0f);
					break;
				case SDLK_f:
					tank->shoot();
					break;
				
				default:
					break;
			}
			break;
		case SDL_QUIT:
			*loop=false;
			break;
		default:
			break;
	}
}

int setupGLBuffers()
{
	//TANK_SIZE is the number of vertices in TANK
	GLfloat tankVerts[]={	-0.3f, 0.0f, 0.0f,	1.0f, 0.0f, 0.0f,
				 0.3f, 0.0f, 0.0f,	1.0f, 0.0f, 0.0f,
				 0.0f, 0.5f, 0.0f,	1.0f, 0.0f, 0.0f,
			};
	GLfloat bulletVerts[]={	-0.2f, -0.2f, 0.0f,	1.0f, 1.0f, 1.0f,
				 0.0f,  0.1f, 0.0f,	1.0f, 1.0f, 0.0f,
				 0.0f,  0.2f, 0.0f,	1.0f, 0.0f, 1.0f,
				 0.2f, -0.2f, 0.0f,	1.0f, 0.0f, 0.0f,
				};
	GLfloat baddyVerts[]={	 0.0f,  1.0f,  0.0f,	1.0f, 0.0f, 0.0f,
				 1.0f,  0.0f,  0.0f,	0.0f, 0.0f, 1.0f,
				 0.0f,  0.0f, -1.0f,	0.0f, 0.0f, 1.0f,
				-1.0f,  0.0f,  0.0f,	0.0f, 0.0f, 1.0f,
				 0.0f,  0.0f,  1.0f,	0.0f, 0.0f, 1.0f,
				 0.0f, -1.0f,  0.0f,	1.0f, 0.0f, 0.0f,
				};
	
	size_t tankVertsSize=sizeof(GLfloat)*6*TANK_SIZE;
	size_t bulletVertsSize=sizeof(GLfloat)*6*BULLET_SIZE;
	size_t baddyVertSize=sizeof(GLfloat)*6*BADDY_SIZE;
	GLuint VAO=0;

	//VAO
	glGenVertexArrays(1, &VAO);
		GLERR("glGenVertexArrays");
	glBindVertexArray(VAO);
		GLERR("glBindVertexArray");

	glGenBuffers(numVBOs, VBOs);
		GLERR("glGenBuffers");	
	
	//Tank VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[TANK]);
		GLERR("glBindBuffer TANK");
	glBufferData(GL_ARRAY_BUFFER, tankVertsSize, tankVerts, GL_STATIC_DRAW);
		GLERR("glBufferData TANK");

	//Bullet VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[BULLET]);
		GLERR("glBindBuffer BULLET");
	glBufferData(GL_ARRAY_BUFFER, bulletVertsSize, bulletVerts, GL_STATIC_DRAW);
		GLERR("glBufferData BULLET");
	
	//Baddy VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[BADDY]);
		GLERR("glBindBuffer BADDY");
	glBufferData(GL_ARRAY_BUFFER, baddyVertSize, baddyVerts, GL_STATIC_DRAW);
		GLERR("glBufferData BADDY");

	//Set pointers up
	/*glVertexAttribPointer(VERTS, 3, GL_FLOAT, GL_FALSE, 0, 0);
		GLERR("glVertexAttribPointer");
	glVertexAttribPointer(COLOURS, 3, GL_FLOAT, GL_FALSE, 3, (void*)3);
		GLERR("glVertexAttribPointer");*/
	
	glEnableVertexAttribArray(VERTS);	
		GLERR("glEnableVertexAttrib VERTS");	
	glEnableVertexAttribArray(COLOURS);	
		GLERR("glEnableVertexAttrib COLOURS");	
	
	//unbind the last bound VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
		GLERR("glBindBuffer 0");
}

int initGL(SDL_Window *window)
{
	GLuint program, vertexShader, fragmentShader;
	if(setupGLBuffers()) return 1;

	//depth
	glEnable(GL_DEPTH_TEST);
		GLERR("glEnable GL_DEPTH_TEST");
	glDepthFunc(GL_LEQUAL);	
		GLERR("glDepthFunc");
	
	//vertex shader
	if(loadShaderFromFile("simple.vert", &vertexShader, GL_VERTEX_SHADER)) return 1;
	
	//fragment shader
	if(loadShaderFromFile("simple.frag", &fragmentShader, GL_FRAGMENT_SHADER)) return 1;

	//program
	if(createProgramWith2Shaders(&program, &vertexShader, &fragmentShader)) return 1;

	glBindAttribLocation(program, VERTS, "position");
		GLERR("glBindAttribLocation");
	glBindAttribLocation(program, COLOURS, "colour");
		GLERR("glBindAttribLocation");
	glLinkProgram(program);
		GLERR("glLinkProgram");
	
	//get the locations of the uniforms
	matloc=glGetUniformLocation(program, "matrix");
		GLERR("glGetUniformLocation matrix");
	
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);	

	SDL_GL_SwapWindow(window);
}

void gameToDraw(int *A, float *B, int count)
{
	for(int i=0; i<count; i++)
	{
		float temp=(float)A[i];
		B[i] = temp/(GAMESIZE/2) -1.0f;
		//printf("A=%d B=%f\n", A[i], B[i]);
	}
}

int Tank::drawBullets()
{
	for(list<Bullet*>::iterator i=	bullets.begin(); i!=bullets.end(); i++)
	{
	int positioni[3];
	float position[3];
	
	(*i)->getPosition(positioni);
	gameToDraw(positioni, position, 3);

	float c=cos((*i)->getSpin());
	float s=sin((*i)->getSpin());
	const GLfloat translate[]={	BULLETSCALE, 0.0f, 0.0f, position[0],
					0.0f, BULLETSCALE, 0.0f, position[1],
					0.0f, 0.0f, BULLETSCALE, position[2],
					0.0f, 0.0f, 0.0f, 1.0f,
				};
	const GLfloat rotate[]={	c,    0.0f, s,    0.0f,
					0.0f, 1.0f, 0.0f, 0.0f,
					-s, 0.0f, c, 	  0.0f,
					0.0f, 0.0f, 0.0f, 1.0f,
				};
	GLfloat matrix[]={ 	1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f,
				};
	multMatrices4x4(translate, matrix);
	multMatrices4x4(rotate, matrix);

	glUniformMatrix4fv(matloc, 1, GL_FALSE, &matrix[0]);
		GLERR("glUniformMatrix4f matrix");

	glDrawArrays(GL_TRIANGLE_STRIP, 0, (*i)->getTriCount());	
		GLERR("glDrawArrays");
	}
	return 0;
}

int drawBaddy(float *coords, int phase)
{
	GLfloat translate[]={	BADDYSCALE, 0.0f, 0.0f, coords[0],
					0.0f, BADDYSCALE, 0.0f, coords[1],
					0.0f, 0.0f, BADDYSCALE, coords[2],
					0.0f, 0.0f, 0.0f, 1.0f,
				};
	float s=sin(RADS((float)(phase)));
	float c=cos(RADS((float)(phase)));
	const GLfloat rotateY[]={	   c, 	0.0f, 	   s,	0.0f,
					0.0f, 	1.0f, 	0.0f,	0.0f,
					  -s, 	0.0f, 	   c,	0.0f,
					0.0f, 	0.0f, 	0.0f, 	1.0f,
				};
	s=sin(RADS(30.0f));
	c=cos(RADS(30.0f));
	const GLfloat rotateZ[]={	   c, 	  -s, 	0.0f,	0.0f,
					   s, 	   c, 	0.0f,	0.0f,
					0.0f, 	0.0f, 	1.0f,	0.0f,
					0.0f, 	0.0f, 	0.0f, 	1.0f,
				};
	float baddyScale=0.07f;
	GLfloat matrix[]={	1.0f, 	0.0f, 	0.0f, 0.0f,
				0.0f, 		1.0f,	0.0f, 0.0f,
				0.0f, 		0.0f, 	1.0f, 0.0f,
				0.0f, 		0.0f, 		0.0f, 1.0f,
				};

	GLuint baddyIndices[]={ 0, 1, 2,
				0, 2, 3,
				0, 3, 4,
				0, 4, 1,
				5, 2, 1, 
				5, 3, 2,
				5, 4, 3,
				5, 1, 4,
				};
	multMatrices4x4(translate, matrix);
	multMatrices4x4(rotateY, matrix);
	multMatrices4x4(rotateZ, matrix);

	glUniformMatrix4fv(matloc, 1, GL_FALSE, &matrix[0]);
		GLERR("glUniformMatrix4f matrix");

	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, baddyIndices);
		GLERR("glDrawElements BADDY");	
}

int Formation::draw(int phase)
{
	for(list<Baddy*>::iterator i=baddies.begin(); i!=baddies.end(); i++)
	{
		float drawcoords[3];

		int baddyCoords[3];
		
		//initialise baddy coords with formation coords	
		for(int j=0; j<3; j++)
			baddyCoords[j]=coords[j];

		//add the baddy's own coords
		(*i)->addFormCoords(baddyCoords);
		gameToDraw(baddyCoords, drawcoords,  3);

		if(drawBaddy(drawcoords, phase))
		{
			printf("Error when drawing baddies\n");
			return 1;
		}
	}
}

int display(SDL_Window *window, Tank *tank, Formation *baddies, int phase)
{
	//tank first
	int tankposi[3];
	float tankpos[3];

	float z=tank->getRotationZ();
	tank->getPosition(tankposi);
	
	gameToDraw(tankposi, tankpos, 3);

	const GLfloat translate[]={	TANKSCALE, 0.0f, 0.0f, tankpos[0],
					0.0f, TANKSCALE, 0.0f, tankpos[1],
					0.0f, 0.0f, TANKSCALE, tankpos[2],
					0.0f, 0.0f, 0.0f, 1.0f,
				};
	float c=cos(z);
	float s=sin(z);
	const GLfloat rotate[]={	c, 	-s, 	0.0f, 0.0f,
					s, 	 c, 	0.0f, 0.0f,
					0.0f, 	 0.0f, 	1.0f, 0.0f,
					0.0f, 	 0.0f, 	0.0f, 1.0f,
				};
	GLfloat matrix[]={ 	1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f,
				};

	multMatrices4x4(translate, matrix);
	multMatrices4x4(rotate, matrix);

	glUniformMatrix4fv(matloc, 1, GL_FALSE, &matrix[0]);
		GLERR("glUniformMatrix4f scale");

	//consider this the start of our drawing
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);	

	//draw the tank
	glBindBuffer(GL_ARRAY_BUFFER, tank->getVBO());
	glVertexAttribPointer(VERTS, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*6, 0);
		GLERR("glVertexAttribPointer");
	glVertexAttribPointer(COLOURS, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*6, (void*)(3*sizeof(GLfloat)));
		GLERR("glVertexAttribPointer");
	glDrawArrays(GL_TRIANGLE_STRIP, 0, tank->getTriCount());

	//and its bullets
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[BULLET]);
	glVertexAttribPointer(VERTS, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*6, 0);
	glVertexAttribPointer(COLOURS, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*6, (void*)(3*sizeof(GLfloat)));
		GLERR("glVertexAttribPointer");
	if(tank->drawBullets()) return 1;

	//then the baddies
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[BADDY]);
		GLERR("glBindBuffer BADDY");
	glVertexAttribPointer(VERTS, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*6, 0);
		GLERR("glVertexAttribPointer BADDY");
	
	glVertexAttribPointer(COLOURS, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*6, (void*)(sizeof(GLfloat)*3));
		GLERR("glVertexAttribPointer");
	baddies->draw(phase);
	SDL_GL_SwapWindow(window);
}

int main(int argc, char **argv)
{
	SDL_Window *window=NULL;
	SDL_GLContext contextGL=NULL;
	SDL_Event eventSDL;
	bool loop=true;
	unsigned int atick=0, btick=0;
	int wait, phase=0;
	Formation *baddies = NULL;

	//setup
	if(initSDL(&window)) return 1;
	
	contextGL=SDL_GL_CreateContext(window);
	SDL_GL_SetSwapInterval(1);

	if(initGL(window)) return 1;

	//seed random
	int seed;
	srand(time(NULL));
	
	//create our first tank
	Tank *tank = new Tank();
	tank->setVBO(VBOs[TANK], TANK_SIZE);
	
	//and a formation of baddies
	{
		int baddyCoords[3]={10, 800, 0};
		baddies= new Formation(8, 4, baddyCoords);
	}

	
	while(loop)
	{
		atick=SDL_GetTicks();
		if(SDL_PollEvent(&eventSDL))
		{
			handleSDLEvent(&eventSDL, &loop, tank);
		}
		display(window, tank, baddies, phase++);
		tank->moveBullets(baddies);
		tank->tick();

		baddies->move();		
		
		btick=SDL_GetTicks();
		wait=(1000.0f/60.0f)-(btick-atick);
		SDL_Delay(wait > 0 ? wait : 0);
	}
	

}

