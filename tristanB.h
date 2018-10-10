#IFNDEF TRISTAN_H
#DEFINE TRISTAN_H

#include "fonts.h"
#include <GL/glx.h>

class Enemy
{
	int posX, posY, HP, damage, id;

	Enemy(int x, int y): posx(x), posy(y){}

public:
	void moveLeft();
	void moveRight();
	bool findPlayer(player P);
	void takeAction(player P);
};

void tristanCredits(Rect* r);
void tristanImage(int x, int y, GLuint texid);

#ENDIF
