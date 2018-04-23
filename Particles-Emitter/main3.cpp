<<<<<<< HEAD
//
//  Main3.cpp
//

//DON'T FORGET TO INITIALIZE grid_new TO 0!!!
//OTHERWISE THE GAS WILL ACCUMULATE FAST!!!
//(LINE 318)

=======
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
>>>>>>> Particles-Emitter/master

#include <string>

#include "GetGlut.h"
#include "Sleep.h"
<<<<<<< HEAD
#include "time.h"
#include <cstdlib>

#define MAXTIME 60
#define MAXCOLS 200
#define MAXROWS 200

using namespace std;

const int cellSize = 4;

class Cell
{public:
	float x;		//x coordinate
	float y;		//y coordinate
	double veloX;	//velocity x
	double veloY;	//velocity y
	double mass;		//mass, 0-100

	/*void InitialCell ()
	{
		veloX = 0;
		veloY = 0;
		mass = 0;

		// Every cell should have a 1/20 chance 
		//of having some nonzero amount of gas in it.
		if (rand()%100 < 5)
		{
			mass = rand() % 100;
			veloX = rand() % 6 - 3;
			veloY = rand() % 6 - 3;
		}
	}*/
	Cell()
	{
		mass = 0;
		veloX = 0;
		veloY = 0;
	}

	void DrawCell (/*int x, int y, float mass*/)
	{
		glBegin(GL_POLYGON);
			glColor3f(mass/100, 
					  mass*mass*0.05/100, 
					  mass*mass*mass*0.0001/100);
			glVertex2f(-400 + cellSize * x, -400 + cellSize * y);
			glVertex2f(-400 + cellSize * x, -400 + cellSize * (y+1));
			glVertex2f(-400 + cellSize * (x+1), -400 + cellSize * (y+1));
			glVertex2f(-400 + cellSize * (x+1), -400 + cellSize * y);
		glEnd();
	}

	friend void UpdateCell(int x, int y);
	friend void UpdateFromInflow(int x, int y, double m2, double vx2, double vy2);
	friend void DisplayGrid();
	friend void InitGridOld();
	friend void InitGridNew();
	friend void CopyArray(int, int);
};

// prototypes
void initDisplay();
void keyboard(unsigned char key, int x, int y);
=======
#include "ObjLibrary/Vector2.h"
#include "Square.h"

using namespace std;

// prototypes
void initDisplay();
void keyboard(unsigned char key, int x, int y);
void special(int special_key, int x, int y);
>>>>>>> Particles-Emitter/master
void update();
void reshape(int w, int h);
void display();

<<<<<<< HEAD
//declare global variables
Cell grid_old[MAXROWS][MAXCOLS];
Cell grid_new[MAXROWS][MAXCOLS];

int main (int argc, char** argv)
{
	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(0, 0);

	srand(time(NULL));
	InitGridOld();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutCreateWindow("Gas Simulator");
	glutKeyboardFunc(keyboard);
=======
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
>>>>>>> Particles-Emitter/master
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
<<<<<<< HEAD
	glColor3f(0.0, 0.0, 0.0);
=======
	glColor3f(0, 0, 0);
>>>>>>> Particles-Emitter/master

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27: // on [ESC]
		exit(0); // normal exit
		break;
<<<<<<< HEAD
	}
}

void update()
{
	//update your variables here
	
	sleep(1.0 / 60.0);
	glutPostRedisplay();
=======
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
>>>>>>> Particles-Emitter/master
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

<<<<<<< HEAD
	// NEW
=======
	// NEW: Jan. 11, 2015, 8:10 pm
>>>>>>> Particles-Emitter/master
	gluOrtho2D(-x_center, w - x_center, -y_center, h - y_center);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutPostRedisplay();
}

<<<<<<< HEAD
/**** Grid Processing Functions ****/
void InitGridOld()
{
	for (int i = 0; i < MAXROWS; i++)
		for (int j = 0; j < MAXCOLS; j++)
		{
			grid_old[i][j].x = j;
			grid_old[i][j].y = i;

			// Every cell should have a 1/20 chance 
			//of having some nonzero amount of gas in it.
			if (rand()%100 < 5)
			{
				grid_old[i][j].mass = rand() % 10000 / 100.0;
				grid_old[i][j].veloX = rand() % 6000 / 1000.0 - 3;
				grid_old[i][j].veloY = rand() % 6000 / 1000.0 - 3;
			}
		}
}

void UpdateCell(int x, int y)
{
	int intx, inty;
    double newx, newy, fractionx, fractiony;
 
    /* First figure out where the mass from this cell is going, based */
	/* on its velocity.  Assume that its new location is a cell-sized shape, with */
    /* coordinates of lower left hand corner given by newx and newy. */
	newx = x + grid_old[y][x].veloX;
    newy = y + grid_old[y][x].veloY;

	/* If the point is outside the grid, move it back inside the grid */
    /* using wraparound. */
    while (newy >= MAXROWS)			newy = newy - MAXROWS;
    while (newy < 0.0)				newy = newy + MAXROWS;
    while (newx >= MAXCOLS)			newx = newx - MAXCOLS;
    while (newx < 0.0)				newx = newx + MAXCOLS;

	/* Since the velocity may not be an integer, the new location may */
	/* straddle several adjacent cells.  Find which cells the shape */
	/* overlaps and the fractions of each of these cells that it overlaps. */
	/* These cells are called the destination cells. */
    intx = (int) newx;
    inty = (int) newy;
    fractionx = newx - intx;
    fractiony = newy - inty;

	/* The outflow from the current cell (x y) becomes the  */
    /* inflow to the destination cells. It is divided according to  */
    /* the fraction of the shape that overlaps each of these cells. */
	UpdateFromInflow(
                intx,
                inty,
				(1.0 - fractionx) * (1.0 - fractiony) * grid_old[y][x].mass,
				grid_old[y][x].veloX,
				grid_old[y][x].veloY);
    UpdateFromInflow(
            intx,
            inty + 1,
            (1.0 - fractionx) * fractiony * grid_old[y][x].mass,
			grid_old[y][x].veloX,
			grid_old[y][x].veloY);
    UpdateFromInflow(
            intx + 1,
            inty,
            fractionx * (1.0 - fractiony) * grid_old[y][x].mass,
			grid_old[y][x].veloX,
			grid_old[y][x].veloY);
    UpdateFromInflow(
            intx + 1,
            inty + 1,
            fractionx * fractiony * grid_old[y][x].mass,
			grid_old[y][x].veloX,
			grid_old[y][x].veloY);
 
}

// add mass m2, which has velocity [vx2, vy2]T, to the existing new mass at location [y, x]
void UpdateFromInflow(int x, int y, double m2, double vx2, double vy2)
{
	double m1, vx1, vy1;
 
        /* If the point is outside the grid, move it back inside the grid */
        
		/* If the point is outside the grid, move it back inside the grid */
		/* using wraparound. */
		/*while (newy >= MAXROWS)			newy = newy - MAXROWS;
		while (newy < 0.0)				newy = newy + MAXROWS;
		while (newx >= MAXCOLS)			newx = newx - MAXCOLS;
		while (newx < 0.0)				newx = newx + MAXCOLS;*/

 
        /* current conditions in this cell before adding the inflow */
        m1 = grid_new[y][x].mass;
		vx1 = grid_new[y][x].veloX;
		vy1 = grid_new[y][x].veloY;
 
        if (m1 + m2 == 0.0)    /* avoid dividing by zero */
        {
			grid_new[y][x].mass = 0.0;
			grid_new[y][x].veloX = 0.0;
			grid_new[y][x].veloY = 0.0;
        }
        else
        {
            /* Compute new mass as the sum of the existing and inflowing gases */
            grid_new[y][x].mass = m1 + m2;
 
			/* Calculate the new velocity as the weighted average of the velocities  */
			/* of the existing and inflowing gases.  The weighting is done according */
			/* to the masses.  */
			grid_new[y][x].veloX = (m1 * vx1 + m2 * vx2) / (m1 + m2);
			grid_new[y][x].veloY = (m1 * vy1 + m2 * vy2) / (m1 + m2);
        }
}

void DisplayGrid()
{
	for (int i = 0; i < MAXROWS; i++)
		for (int j = 0; j < MAXCOLS; j++)
		{
			grid_old[i][j].x = j;
			grid_old[i][j].y = i;
			grid_old[i][j].DrawCell();
		}
}
/**** Grid Processing Functions ****/


/**** Array Processing Functions *******/
void InitGridNew()
{
	for (int i = 0; i < MAXROWS; i++)
		for (int j = 0; j < MAXCOLS; j++)
		{
			grid_new[i][j].mass = 0;
			grid_new[i][j].veloX = 0;
			grid_new[i][j].veloY = 0;
		}
}

void CopyArray(int i, int j)
{
	grid_old[i][j].veloX = grid_new[i][j].veloX;
	grid_old[i][j].veloY = grid_new[i][j].veloY;
	grid_old[i][j].mass = grid_new[i][j].mass;
}
/**** Array Processing Functions *******/



void display (void)
{
	// clear the screen - any drawing before here will not display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	DisplayGrid();
		
	//grid_new Initialization
	InitGridNew();

	//For each cell in the grid, calculate its outflow and the resulting inflows for other cells
	for (int y = 0; y < MAXROWS; y++)
		for (int x = 0; x < MAXCOLS; x++)
			UpdateCell(x, y);

	//Copy new mass and velocity values into old arrays 
	for (int y = 0; y < MAXROWS; y++)
		for (int x = 0; x < MAXCOLS; x++)
			CopyArray(x, y);
 
    DisplayGrid();
=======
void display (void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// clear the screen - any drawing before here will not display

	// draw a white square
	for (int i = 0; i < SQUARE_COUNT; i++)
	{
		squares[i].draw();
	}
>>>>>>> Particles-Emitter/master

	// send the current image to the screen - any drawing after here will not display
	glutSwapBuffers();
}

<<<<<<< HEAD

=======
>>>>>>> Particles-Emitter/master
