//	CS 408 Assignment 1
// 200356891 Shicheng Ai
//	Square.cpp
//

#include "ObjLibrary\Vector2.h"
#include "GetGlut.h"
#include "Square.h"
#include <cstdlib>
#include <math.h>


void Square::update()
{
	pos += vel;
	age++;
	if (age > 100)
	{
		// restart square movement
		//age = 0.0;
		//pos.set(0.0, 0.0);
	}
}

void Square::draw()
{
	if(isAlive())
	{
		//glColor3d(1.0, 1.0, 1.0);
		glEnable(GL_BLEND);
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);	//Additive transparency
		//glColor3f(red, green, blue);
		glColor4f(red, green, blue, trans);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glTranslated(pos.x, pos.y, 0.0f);
			glRotatef(rotation, 0.0f, 0.0f, 1.0f);
			glBegin(GL_TRIANGLE_FAN);
				glVertex2f(pos.x, pos.y);	//start point
				glVertex2f(pos.x, pos.y + shape* size);
				glVertex2f(pos.x + size, pos.y + size);
				glVertex2f(pos.x + shape * size, pos.y);
				glVertex2f(pos.x + size, pos.y - size);
				glVertex2f(pos.x, pos.y - shape * size);
				glVertex2f(pos.x - size, pos.y - size);
				glVertex2f(pos.x - shape * size, pos.y);
				glVertex2f(pos.x - size, pos.y + size);
				glVertex2f(pos.x, pos.y + shape * size);
			glEnd();
			glDisable(GL_BLEND);
		glPopMatrix();
	}
}

void Square :: init ()
{
  pos.set(0.0, 0.0);
  vel.set(5.0, 0.0);
  age = 0;
  red   = 0.25;	//color dark grey (0.25, 0.25, 0.25)
  green = 0.25;
  blue  = 0.25;
  size = 100;	//size 100
  rotation = random0to1() * 360;
}

void Square :: init(float posX, float posY, float getRed, float getGreen, float getBlue, 
		float getTransparency, float getSize, float getShape, float particleSpeed, float getAngle)
{
	float velX, velY;
	angle = getAngle + random0to1() * 60 - 30;
	velY = sin(angle * 3.14 / 180);
	velX = cos(angle * 3.14 / 180);

	pos.set(posX, posY);
	vel.set(velX * particleSpeed, velY * particleSpeed);
	age = 0;
	red   = getRed;	//color dark grey (0.25, 0.25, 0.25)
	green = getGreen;
	blue  = getBlue;
	trans = getTransparency;
	size = getSize;	//default size: 100
	shape = getShape;
	rotation = 0;//random0to1() * 360;
}

bool Square :: isAlive()
{
  if (age <= 60)
       return true;
  else
       return false;
}

float Square :: random0to1 ()
{
  return (float)(rand()) / ((float)RAND_MAX + 1.0f);
}


