
#ifndef KENNY_H
#define KENNY_H

#include <GL/glx.h>
#include <utility>
#include "tristanB.h"

void drawHUD(struct timespec ts);
void drawImage(int, int, int, int, GLuint);
void fetchHTTPScores(char*, char*);
void showEndScreen();
void showInitialScreen();
void pushInitials(char);
void uploadScore();

class Bullet
{
    float posX, posY, xvel = 0, yvel = 0;
    int xsize, ysize;
    GLuint texid;
    Hitbox hitbox;
    public:
        Bullet(int, int, int);
        void physics();
        void render();
        Hitbox getHitbox(){return hitbox;}
};

#endif
