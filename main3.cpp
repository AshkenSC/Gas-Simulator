//
//  Main3.cpp
//

//DON'T FORGET TO INITIALIZE grid_new TO 0!!!
//OTHERWISE THE GAS WILL ACCUMULATE FAST!!!
//(LINE 318)


#include <string>

#include "GetGlut.h"
#include "Sleep.h"
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
void update();
void reshape(int w, int h);
void display();

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
	glColor3f(0.0, 0.0, 0.0);

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27: // on [ESC]
		exit(0); // normal exit
		break;
	}
}

void update()
{
	//update your variables here
	
	sleep(1.0 / 60.0);
	glutPostRedisplay();
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

	// NEW
	gluOrtho2D(-x_center, w - x_center, -y_center, h - y_center);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutPostRedisplay();
}

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

	// send the current image to the screen - any drawing after here will not display
	glutSwapBuffers();
}


