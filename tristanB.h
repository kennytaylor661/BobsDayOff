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

	bool isCollidingDebug(Hitbox other)
	{
        cout << "enemy: left=" << left << ", right=" << right << ", bottom=" << bottom << ", top=" << top << endl;
        cout << "bullet: left=" << other.left << ", right=" << other.right << ", bottom=" << other.bottom << ", top=" << other.top << endl;
		return ((left <= other.right && right >= other.left)  ||
				(right >= other.left && left <= other.right)) &&
			   ((bottom <= other.top && top >= other.bottom)  ||
				(top >= other.bottom && bottom <= other.top));
	}
};

class Player
{
	int HP = 100, wid;
	bool grounded;
	float posX = gl.xres/2, posY = 0.0f, xvel = 0, yvel = 0;
	GLuint texid;
	Hitbox hitbox;
	int iframes = 0;
	public:
	Player()
	{
		hitbox.top = posY + 64;
		hitbox.bottom = posY - 64;
		hitbox.left = posX - 32;
		hitbox.right = posX + 32;
	}

	int bananaCount = 0;
	int getHP(){return this->HP;}
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
		float posX, posY, xvel = 0, yvel = 0;
        Hitbox hitbox;

	public:
		Enemy(float x, float y): posX(x), posY(y) {}
		~Enemy(){}

        int HP;
		void moveLeft();
		void moveRight();
		virtual void AI(Player p) = 0;
		void physics();
		std::pair<int, int> getPos();
		virtual void render() = 0;
        Hitbox getHitbox(){return this->hitbox;}
};

class Slime : public Enemy
{
	GLuint texid = gl.slimeEnemyTexture;

	public:
	Slime(float x, float y): Enemy(x, y)
	{
		hitbox.top = posY + 25;
		hitbox.bottom = posY - 25;
		hitbox.left = posX - 25;
		hitbox.right = posX + 25;
	}
	int HP = 1;
	int damage = 10;
	void AI(Player p);
	void render();
	Hitbox getHitbox(){return this->hitbox;}
};
class Zombie : public Enemy
{
	GLuint texid = gl.zombieTexture;
    int lastFacing;

	public:
	Zombie(float x, float y): Enemy(x, y)
	{
		hitbox.top = posY + 50;
		hitbox.bottom = posY - 50;
		hitbox.left = posX - 50;
		hitbox.right = posX + 50;

	}
	int HP = 5;
	int damage = 10;
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
