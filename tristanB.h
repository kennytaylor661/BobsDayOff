#ifndef TRISTAN_H
#define TRISTAN_H

#include "fonts.h"
#include <GL/glx.h>
#include <utility>

class Enemy
{
	int id;

	Enemy(int x, int y);
    
protected:
    int posX, posY, HP, damage;

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
    int HP = 1;
    int damage = 1;

public:
    void AI();
};
class Zombie : public Enemy
{
    int HP = 5;
    int damage = 1;

public:
    void AI(Player p);
};

void tristanCredits(Rect* r);
void tristanImage(int x, int y, GLuint texid);

#endif
