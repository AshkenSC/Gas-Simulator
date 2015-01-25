//	CS 408 Assignment 1
// 200356891 Shicheng Ai
//	Square.h
//

#ifndef SQUARE_H
#define SQAURE_H

#include "ObjLibrary\Vector2.h"

void square_update();
void square_draw();

class Square
{
public:
  // declare your constructor here
	Square()
	{
		init();
		age = 999999;
	}
  // declare your public member functions here
	void update();
	void draw();
	void init ();
	void init(float x, float y, float getRed, float getGreen, float getBlue, 
		float getTransparency, float getSize, float getShape, float particleSpeed, float getAngle);
	bool isAlive();

private:
  // declare your private member functions here
	float random0to1 ();
  // declare your member variables here
	Vector2 pos;
	Vector2 vel;
	double age;
	float red;
	float green;
	float blue;
	float trans;
	float size;
	float rotation;
	float shape;
	float angle;
};

#endif