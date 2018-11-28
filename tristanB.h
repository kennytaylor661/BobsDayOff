#ifndef TRISTAN_H
#define TRISTAN_H

#include "fonts.h"
#include <GL/glx.h>
#include <utility>
#include "global.h"
extern Global gl;

struct Hitbox
{
	float top, bottom, left, right;
	
	Hitbox() {top = 0; bottom = 0; left = 0; right = 0;}

	Hitbox(float t, float b, float l, float r):
		top(t), bottom(b), left(l), right(r){}

	bool isColliding(Hitbox other)
	{
		return ((left <= other.right && right >= other.left)  ||
				(right >= other.left && left <= other.right)) &&
			   ((bottom <= other.top && top >= other.bottom)  ||
				(top >= other.bottom && bottom <= other.top));
	}
};

class Player
{
	int HP = 10, wid;
	bool grounded;
	float posX = 0.0f, posY = 0.0f, xvel, yvel;
	GLuint texid;
	Hitbox hitbox;

	public:
	std::pair<int, int> getPos();
	void moveLeft();
	void moveRight();
	void Jump();
	void Fire();
	void physics();
	void render();
	Hitbox getHitbox(){return this->hitbox;}
};

class Enemy
{

	protected:
		int HP, damage;
		float posX, posY, xvel = 0, yvel = 0;

	public:
		Enemy(float x, float y): posX(x), posY(y) {}
		~Enemy(){}

		void moveLeft();
		void moveRight();
		virtual void AI(Player p) = 0;
		void physics();
		std::pair<int, int> getPos();
		virtual void render() = 0;
};

class Slime : public Enemy
{
	int HP = 1;
	int damage = 1;
	GLuint texid = gl.slimeEnemyTexture;
	Hitbox hitbox;

	public:
	Slime(float x, float y): Enemy(x, y)
	{
		hitbox.top = posY + 25;
		hitbox.bottom = posY - 25;
		hitbox.left = posX - 25;
		hitbox.right = posX + 25;
	}
	void AI(Player p);
	void render();
	Hitbox getHitbox(){return this->hitbox;}
};
class Zombie : public Enemy
{
	int HP = 5;
	int damage = 1;
	GLuint texid = gl.zombieTexture;
	Hitbox hitbox;

	public:
	Zombie(float x, float y): Enemy(x, y)
	{
		hitbox.top = posY + 50;
		hitbox.bottom = posY - 50;
		hitbox.left = posX - 50;
		hitbox.right = posX + 50;

	}
	void AI(Player p);
	void render();
	Hitbox getHitbox(){return this->hitbox;}
};

class Door
{
	std::pair<int, int> upleft, downright; 
	//coordinates for the UL and LR corners
	char* dest;
	GLuint texid = gl.doorTexture;

	Door(int x1, int y1, int x2, int y2, char* dest, GLuint texture):
		upleft(x1,y1), downright(x2, y2), dest(dest), texid(texture){}
	public:
	void loadDest();
	void render();
};

void tristanCredits(Rect* r);
void tristanImage(int x, int y, GLuint texid);

#endif
