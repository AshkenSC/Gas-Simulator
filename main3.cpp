//	CS 408 Assignment 1
// 200356891 Shicheng Ai
//  Main3.cpp
//

//Questions
//1. Particles are unable to vanish if I do as lab notes (next_square part)
//2. if I set posX, posY as class members, the position is unable to be changed.
//	 I have to set them as global variables.
//3. Using large array seems not the best idea to produce infinite particles.
//	 What is the best way then?
//4. function init() has too many arguments, which seems not very good. Is there
//	 any better solution?

#include <string>

#include "GetGlut.h"
#include "Sleep.h"
#include "ObjLibrary/Vector2.h"
#include "Square.h"

using namespace std;

// prototypes
void initDisplay();
void keyboard(unsigned char key, int x, int y);
void special(int special_key, int x, int y);
void update();
void reshape(int w, int h);
void display();

//declare global variables here
const unsigned long SQUARE_COUNT = 200000;
const float SPEED = 10.0;			//emitter movement speed
const float RGB_SPEED = 0.1;		//RGB modification speed
const float SIZE_SPEED = 2;			//Particle size modification speed
const float TRANS_SPEED = 0.1;		//Transparency modification speed
const float PARTICLE_SPEEDSTEP = 1;	//particle speed modification speed
const float SHAPE_SPEED = 0.1;		//shape modification speed
const float ANGLE_SPEED = 10.0;		//angle modification speed

Square squares[SQUARE_COUNT];
unsigned int next_square = 0;
bool emitter_on = true;

//parameters to control the emitter
float posX = 0, posY = 0;
float getRed = 0.25, getGreen = 0.25, getBlue = 0.25;
float getTransparency = 1.0;
float getSize = 100;
float getShape = 1.0;
float particleSpeed = 5;
float getAngle = 0;


int main (int argc, char** argv)
{
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutCreateWindow("Third OpenGL Program");
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutIdleFunc(update);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);

	initDisplay();

	glutMainLoop();

	return 1;
}

void initDisplay()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(0, 0, 0);

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27: // on [ESC]
		exit(0); // normal exit
		break;
	case ' ': // on [SPACEBAR]
       emitter_on = !emitter_on;
	//squares[next_square].posY += SPEED;
       break;
	case 'w':
		if (posY + SPEED < 120 || posY + SPEED == 120)
			posY += SPEED;
		break;
	case 's':
		if (posY - SPEED > -120 || posY - SPEED == -120)
			posY -= SPEED;
		break;
	case 'a':
		if (posX - SPEED > -160 || posX - SPEED == -160)
			posX -= SPEED;
		break;
	case 'd':
		if (posX + SPEED < 160 || posX + SPEED == -160)
			posX += SPEED;
		break;
	case 'R':
		if (getRed + RGB_SPEED < 1.0 || getRed + RGB_SPEED == 1.0)
			getRed += RGB_SPEED;
		break;
	case 'r':
		if (getRed - RGB_SPEED > 0.0 || getRed - RGB_SPEED == 0.0)
			getRed -= RGB_SPEED;
		break;
	case 'G':
		if (getGreen + RGB_SPEED < 1.0 || getGreen + RGB_SPEED == 1.0)
			getGreen += RGB_SPEED;
		break;
	case 'g':
		if (getGreen - RGB_SPEED > 0.0 || getGreen - RGB_SPEED == 0.0)
			getGreen -= RGB_SPEED;
		break;
	case 'B':
		if (getBlue + RGB_SPEED < 1.0 || getBlue + RGB_SPEED == 1.0)
			getBlue += RGB_SPEED;
		break;
	case 'b':
		if (getBlue - RGB_SPEED > 0 || getBlue - RGB_SPEED == 0)
			getBlue -= RGB_SPEED;
		break;
	case 'H':
		if (getShape + SHAPE_SPEED < 3.0 || getShape + SHAPE_SPEED == 3.0)
			getShape += SHAPE_SPEED;
		break;
	case 'h':
		if (getShape - SHAPE_SPEED > 0.5 || getShape - SHAPE_SPEED == 0.5)
			getShape -= SHAPE_SPEED;
		break;
	case 'T':
		if (getTransparency + TRANS_SPEED < 1 || getTransparency + TRANS_SPEED == 1)
			getTransparency += TRANS_SPEED;
		break;
	case 't':
		if (getTransparency - TRANS_SPEED > 0 || getTransparency - TRANS_SPEED == 0)
			getTransparency -= TRANS_SPEED;
		break;
	case '+':
		if (getSize + SIZE_SPEED < 200 || getSize + SIZE_SPEED == 200)
			getSize += SIZE_SPEED;
		break;
	case '-':
		if (getSize - SIZE_SPEED > 1 || getSize + SIZE_SPEED == 1)
			getSize -= SIZE_SPEED;
		break;
	}
}

void special(int special_key, int x, int y)
{
  switch(special_key)
  {
	case GLUT_KEY_LEFT:
		//if(getAngle + ANGLE_SPEED < 360.0 || getAngle + ANGLE_SPEED == 360.0)
			getAngle += ANGLE_SPEED;
		break;
	case GLUT_KEY_RIGHT:
		//if(getAngle - ANGLE_SPEED > -360.0 || getAngle - ANGLE_SPEED == -360.0)
			getAngle -= ANGLE_SPEED;
		break;
	case GLUT_KEY_UP:
		if(particleSpeed + PARTICLE_SPEEDSTEP < 10 || particleSpeed + PARTICLE_SPEEDSTEP == 10)
			particleSpeed += PARTICLE_SPEEDSTEP;
		break;
	case GLUT_KEY_DOWN:
		if(particleSpeed - PARTICLE_SPEEDSTEP > 1 || particleSpeed - PARTICLE_SPEEDSTEP == 1)
			particleSpeed -= PARTICLE_SPEEDSTEP;
		break;
  }
}

void update()
{
	//update your variables here
	for (int i = 0; i < SQUARE_COUNT; i++)
	{
		squares[i].update();
	}
	sleep(1.0 / 60.0);
	glutPostRedisplay();
	

	//next_square++;
	if (next_square <= SQUARE_COUNT)
		next_square ++;

	//Below is the original version
	/*next_square++;
	if (next_square >= SQUARE_COUNT){
		next_square = 0;}
		squares[next_square].init();*/

	if (emitter_on)
			squares[next_square].init(posX, posY, getRed, getGreen, getBlue, 
			getTransparency, getSize, getShape, particleSpeed, getAngle);
}

void reshape(int w, int h)
{
	glViewport (0, 0, w, h);

	int x_center = w / 2;
	int y_center = h / 2;

	// set up a 2D view
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// OLD
	// gluOrtho2D(-x_center, w - x_center, h - y_center, -y_center);

	// NEW: Jan. 11, 2015, 8:10 pm
	gluOrtho2D(-x_center, w - x_center, -y_center, h - y_center);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutPostRedisplay();
}

void display (void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// clear the screen - any drawing before here will not display

	// draw a white square
	for (int i = 0; i < SQUARE_COUNT; i++)
	{
		squares[i].draw();
	}

	// send the current image to the screen - any drawing after here will not display
	glutSwapBuffers();
}

