//Name: Tristan Bock
//Date: 2018-09-25
#include "tristanB.h"
#include <cstdlib> //Rand()
#include <unistd.h> // usleep()

//Enemy Class
void Enemy::moveLeft()
{
    posX--;
}

void Enemy::moveRight()
{
    posX++;
}

bool Enemy::findPlayer()
{
    return false;//TBD
}
/*
void Enemy::physics()
{
        if (posX > gl.camera[0] + gl.xres/2 || posX < gl.camera[0] - gl.xres/2 ||
	    posY > gl.camera[1] + gl.yres/2 || posY < gl.camera[1] - gl.yres/2)
	        return;
	this->yvel -= gl.Gravity;
	this->AI(Player p);
}
*/
//

//Player Class
std::pair<int, int> Player::getPos()
{
    return std::pair<int, int>(this->posX, this->posY);
}

void Player::moveLeft()
{
    posX--;
}

void Player::moveRight()
{
    posX++;
}

void Player::Jump()
{
	
}

void Player::Fire()
{

}
//

//Slime Class
void Slime::AI(Player p)
{
    if (rand()%2 == 0)
        this->moveLeft();
    else
        this->moveRight();
    usleep(2000);
}

void Slime::render()
{

}
//

//Zombie Class
void Zombie::AI(Player p)
{
    std::pair<int,int> playerLoc = p.getPos();

    if (playerLoc.first > posX && playerLoc.first - posX <= 5 && 
	playerLoc.second - posY <= 1 && posY - playerLoc.second <= 1) {
        this->moveRight();
    } else if (playerLoc.first < posX && posX - playerLoc.first <= 5 &&
	     playerLoc.second - posY <= 1 && posY - playerLoc.second <= 1) {
	this->moveLeft();
    }
    usleep(500);
}

void Zombie::render()
{

}
//

//Global Functions
void tristanCredits(Rect* r)
{
	ggprint8b(r, 16, 0x00ff44ff, "Tristan Bock");
}

void tristanImage(int x, int y, GLuint texid)
{
	glColor3ub(255,255,255);
	int wid = 80;
	glPushMatrix();
	glTranslatef(x, y, 0);
	glBindTexture(GL_TEXTURE_2D, texid);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid, -wid);
		glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid,  wid);
		glTexCoord2f(1.0f, 0.0f); glVertex2i( wid,  wid);
		glTexCoord2f(1.0f, 1.0f); glVertex2i( wid, -wid);
	glEnd();
	glPopMatrix();
}
//
