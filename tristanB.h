#ifndef TRISTAN_H
#define TRISTAN_H

#include "fonts.h"
#include <GL/glx.h>
#include <utility>
#include "global.h"
extern Global gl;

class Player
{
	int HP = 10, wid;
	bool grounded;
	float posX = 0.0f, posY = 0.0f, xvel, yvel;
	GLuint texid;

	public:
	std::pair<int, int> getPos();
	void moveLeft();
	void moveRight();
	void Jump();
	void Fire();
	void physics();
	void render();
	struct hitbox
	{
		int left, right, top, bottom;
	};
};

class Enemy
{

	protected:
		int posX, posY, HP, damage;
		float xvel = 0, yvel = 0;

	public:
		Enemy(int x, int y):posX(x), posY(y) {}
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

	public:
	Slime(int x, int y): Enemy(x, y){}
	void AI(Player p);
	void render();
	struct hitbox
	{
		int left, right, top, bottom;
	};
};
class Zombie : public Enemy
{
	int HP = 5;
	int damage = 1;
	GLuint texid = gl.zombieTexture;

	public:
	Zombie(int x, int y): Enemy(x, y) {}
	void AI(Player p);
	void render();
	struct hitbox
	{
		int left, right, top, bottom;
	};
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
	struct hitbox
	{
		int left, right, top, bottom;
	};
};

void tristanCredits(Rect* r);
void tristanImage(int x, int y, GLuint texid);

#endif
