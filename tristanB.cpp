
//Date: 2018-09-25
#include "tristanB.h"
#include <cstdlib> //Rand()
#include <unistd.h> // usleep()
#include "global.h"
#include "level.h"

const float GRAVITY = -0.35f;
extern Global gl;
extern Player* pl;
extern Level lev;
//Enemy Class
void Enemy::moveLeft()
{
    posX--;
    hitbox.left--;
    hitbox.right--;
}

void Enemy::moveRight()
{
    posX++;
    hitbox.left++;
    hitbox.right++;
}

void Enemy::physics()
{
    //if (posX > gl.camera[0] + gl.xres/2 || posX < gl.camera[0] - gl.xres/2||
    //		posY > gl.camera[1] + gl.yres/2 || posY < gl.camera[1] - gl.yres/2)
    //	return;
    if (posY > 0) {
        this->posY += yvel;
        this->hitbox.bottom += yvel;
        this->hitbox.top += yvel;
        this->yvel += GRAVITY;
    }

    // Check for collisions with bullets
    for (unsigned int i = 0; i < lev.bullet.size(); i++)
        if (this->getHitbox().isColliding(lev.bullet[i].getHitbox())) {
            // Decrement the enemy hitpoints
            HP--;
            // Delete the bullet object
            lev.bullet.erase(lev.bullet.begin() + i);
            //cout << "  bullet collided with enemy!" << endl;
            //cout << "  new enemy HP = " << HP << endl;
        }

    this->AI(*pl);
}

std::pair<int, int> Enemy::getPos()
{
    return std::pair<int, int>(this->posX, this->posY);
}
//

//Player Class
std::pair<int, int> Player::getPos()
{
    return std::pair<int, int>(this->posX, this->posY);
}

void Player::moveLeft()
{
    posX -= 2.0/lev.tilesize[0] * (1.0 / gl.delay);
    hitbox.left = posX - 32;
    hitbox.right = posX + 32;

    // Move the background to the right
    gl.backgroundXoffset += 1.0 * (0.05 / gl.delay);
    if (gl.backgroundXoffset > 0)
        gl.backgroundXoffset = 0;
    // Move the foreground to the right
    gl.camera[0] -= 2.0/lev.tilesize[0] * (1.0 / gl.delay);
    if (gl.camera[0] < 0.0)
        gl.camera[0] = 0.0;
    if (posX < gl.xres/2)
        posX = gl.xres/2;

    gl.lastFacing = -1;

}
void Player::moveRight()
{
    posX += 2.0/lev.tilesize[0] * (1.0 / gl.delay);
    hitbox.left = posX - 32;
    hitbox.right = posX + 32;

    // Move the background to the left
    gl.backgroundXoffset -= 1.0 * (0.05 / gl.delay);
    // Move the foreground to the left
    gl.camera[0] += 2.0/lev.tilesize[0] * (1.0 / gl.delay);
    if (gl.camera[0] < 0.0)
        gl.camera[0] = 0.0;
    gl.lastFacing = 1;
}

void Player::Jump()
{
    //cout << "player jump called\n";
    if (grounded) {
        yvel += 10;
        grounded = false;
    }
}
void Player::render()
{
    float h = 128.0;
    float w = h * 0.5;
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(0, posY, 0);
    glBindTexture(GL_TEXTURE_2D, gl.walkTexture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    int ix = gl.walkFrame % 8;
    int iy = 0;
    if (gl.walkFrame >= 8)
        iy = 1;
    float fx = (float)ix / 8.0;
    float fy = (float)iy / 2.0;
    glBegin(GL_QUADS);
    // Use gl.lastFacing to track whether we should render the sprite
    // facing left or right when standing still
    float cx = gl.xres/2.0;

    if (gl.keys[XK_Left] || gl.keys[XK_a]) {
        // Draw character facing left
        glTexCoord2f(fx+.125, fy+.5); glVertex2i(cx-w, 114);
        glTexCoord2f(fx+.125, fy);    glVertex2i(cx-w, 114+2*h);
        glTexCoord2f(fx,      fy);    glVertex2i(cx+w, 114+2*h);
        glTexCoord2f(fx,      fy+.5); glVertex2i(cx+w, 114);
        gl.lastFacing = -1;
    } else if (gl.keys[XK_Right] || gl.keys[XK_d]) {
        // Draw character facing right
        glTexCoord2f(fx,      fy+.5); glVertex2i(cx-w, 114);
        glTexCoord2f(fx,      fy);    glVertex2i(cx-w, 114+2*h);
        glTexCoord2f(fx+.125, fy);    glVertex2i(cx+w, 114+2*h);
        glTexCoord2f(fx+.125, fy+.5); glVertex2i(cx+w, 114);
        gl.lastFacing = 1;
    } else if (gl.lastFacing == -1) {
        // Draw character facing left
        glTexCoord2f(fx+.125, fy+.5); glVertex2i(cx-w, 114);
        glTexCoord2f(fx+.125, fy);    glVertex2i(cx-w, 114+2*h);
        glTexCoord2f(fx,      fy);    glVertex2i(cx+w, 114+2*h);
        glTexCoord2f(fx,      fy+.5); glVertex2i(cx+w, 114);
    } else if (gl.lastFacing == 1) {
        // Draw character facing right
        glTexCoord2f(fx,      fy+.5); glVertex2i(cx-w, 114);
        glTexCoord2f(fx,      fy);    glVertex2i(cx-w, 114+2*h);
        glTexCoord2f(fx+.125, fy);    glVertex2i(cx+w, 114+2*h);
        glTexCoord2f(fx+.125, fy+.5); glVertex2i(cx+w, 114);
    }
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
}

void Player::physics()
{
    //posX += xvel;
	iframes--;
	for (unsigned int i = 0; i < lev.zmb.size(); i++)
		if (iframes <= 0 &&
			this->getHitbox().isColliding(lev.zmb[i].getHitbox())) {
			iframes = 10;
			HP -= lev.zmb[i].damage;
			xvel += 5;
		}
	for (unsigned int i = 0; i < lev.slmE.size(); i++)
		if (iframes <= 0 &&
			this->getHitbox().isColliding(lev.slmE[i].getHitbox())) {
			iframes = 10;
			HP -= lev.slmE[i].damage;
			xvel += 5;
		}
	
	for (unsigned int i = 0; i < lev.ban.size(); i++)
		if(this->getHitbox().isColliding(lev.ban[i].getHitbox())) {	
			bananaCount++;
            gl.score += 100;
			lev.ban.erase(lev.ban.begin() + i);
		}

//	posX += xvel;
//	xvel -= 1;
    posY += yvel;
    hitbox.top += yvel;
    hitbox.bottom += yvel;
    yvel += GRAVITY;
    if (posY < 0){
        yvel = 0;
        posY = 0;
        hitbox.top = 128;
        hitbox.bottom = 0; 
        grounded = true;
    }
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
    int wid = 25;
    glPushMatrix();
    glColor3ub(255,255,255);
    glTranslatef(posX - gl.camera[0], posY + 225, 0);
    glBindTexture(GL_TEXTURE_2D, texid);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid, -wid);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(wid, -wid);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(wid, wid);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, wid);
    glEnd();
    glDisable(GL_ALPHA_TEST);
    glPopMatrix();
}
//

//Zombie Class
void Zombie::AI(Player p)
{
    std::pair<int,int> playerLoc = p.getPos();

    if (playerLoc.first > posX) {
        this->moveRight();
    } else if (playerLoc.first < posX) {
        this->moveLeft();
    }
    usleep(500);
}

void Zombie::render()
{
    int wid = 50;
    glPushMatrix();
    glColor3ub(255,255,255);
    glTranslatef(posX - gl.camera[0], posY + 200, 0);
    glBindTexture(GL_TEXTURE_2D, texid);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);	
    glBegin(GL_QUADS);

    std::pair<int,int> playerLoc = pl->getPos();
    if (playerLoc.first >= posX) {
        // Draw zombie facing right
        glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid, -wid);
        glTexCoord2f(1.0f, 1.0f); glVertex2i(wid, -wid);
        glTexCoord2f(1.0f, 0.0f); glVertex2i(wid, wid);
        glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, wid);
    } else if (playerLoc.first < posX) {
        // Draw zombie facing left
        glTexCoord2f(1.0f, 1.0f); glVertex2i(-wid, -wid);
        glTexCoord2f(0.0f, 1.0f); glVertex2i(wid, -wid);
        glTexCoord2f(0.0f, 0.0f); glVertex2i(wid, wid);
        glTexCoord2f(1.0f, 0.0f); glVertex2i(-wid, wid);
    }

    glEnd();
    glDisable(GL_ALPHA_TEST);
    glPopMatrix();

}
//

//Door Class

Door::Door(int x, int y, int wid, int hgt, int levelNum)
{
    posX = x;
    posY = y;
    width = wid;
    height = hgt;
    dest = levelNum;

    hitbox.top = posY + height/2; 
    hitbox.bottom = posY - height/2; 
    hitbox.left = posX - width/2; 
    hitbox.right = posX + width/2; 
}
void Door::loadDest()
{
    lev.load(this->dest);
}

void Door::render()
{
    glPushMatrix();
    glColor3ub(255,255,255);
    glTranslatef(posX - gl.camera[0], posY + 200, 0);
    glBindTexture(GL_TEXTURE_2D, texid);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2i(-width/2, -height/2);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(width/2, -height/2);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(width/2, height/2);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(-width/2, height/2);
    glEnd();
    glPopMatrix();
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
    glTexCoord2f(1.0f, 1.0f); glVertex2i(wid, -wid);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(wid, wid);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, wid);

    glEnd();
    glPopMatrix();
}
//
