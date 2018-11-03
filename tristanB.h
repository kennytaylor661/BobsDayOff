#ifndef TRISTAN_H
#define TRISTAN_H

#include "fonts.h"
#include <GL/glx.h>
#include <utility>

class Player
{
    int posX, posY, HP, wid;
    float xvel, yvel;

public:
    std::pair<int, int> getPos();
    void moveLeft();
    void moveRight();
    void Jump();
    void Fire();
    void physics();
    void render();
};

class Enemy
{
	int id;
	static int giveID;
protected:
    int posX, posY, HP, damage;
    float xvel = 0, yvel = 0;

public:
    Enemy(int x, int y): id(giveID++), posX(x), posY(y) {}
    ~Enemy(){giveID--;}

	void moveLeft();
	void moveRight();
	virtual void AI(Player p) = 0;
	void physics();
    std::pair<int, int> getPos();
	virtual void render() = 0;
};
int Enemy::giveID = 0;

class Slime : public Enemy
{
    int HP = 1;
    int damage = 1;

public:
    void AI(Player p);
    void render();
};
class Zombie : public Enemy
{
    int HP = 5;
    int damage = 1;

public:
    void AI(Player p);
    void render();
};

class Door
{
    std::pair<int, int> upleft, downright; 
    //coordinates for the UL and LR corners
    const char* dest;

    Door(int x1, int y1, int x2, int y2, const char* dest):
        upleft(x1,y1), downright(x2, y2), dest(dest){}
public:
    void loadDest();
};

void tristanCredits(Rect* r);
void tristanImage(int x, int y, GLuint texid);

#endif
