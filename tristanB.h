#ifndef TRISTAN_H
#define TRISTAN_H

#include "fonts.h"
#include <GL/glx.h>
#include <utility>

class Enemy
{
	int posX, posY, id;

	Enemy(int x, int y);
    
protected:
    int HP, damage;

public:
	void moveLeft();
	void moveRight();
	bool findPlayer();
};

class Player
{
    int posX, posY, HP, wid;

public:
    std::pair<int, int> getPos();
    void moveLeft();
    void moveRight();
    void Jump();
    void Fire();
};

class Slime : public Enemy
{
    Slime();
    void AI();
};
class Zombie : public Enemy
{
    Zombie();
    void AI();
};

void tristanCredits(Rect* r);
void tristanImage(int x, int y, GLuint texid);

#endif
