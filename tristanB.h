#ifndef TRISTAN_H
#define TRISTAN_H

#include "fonts.h"
#include <GL/glx.h>

class Enemy
{
	int posX, posY, HP, damage, id;

	Enemy(int x, int y);

public:
	void moveLeft();
	void moveRight();
	bool findPlayer();
	void takeAction();
};

void tristanCredits(Rect* r);
void tristanImage(int x, int y, GLuint texid);

#endif
