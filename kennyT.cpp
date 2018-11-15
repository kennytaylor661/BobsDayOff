// Kenny Taylor
// Modified:  11/1/18
// Purpose:  individual work on group project

#include <GL/glx.h>
#include "fonts.h"
#include "global.h"
#include "level.h"

static double yVelocity = 1;
static double yOffset = 0;

extern Global gl;

void showKennyCredits(Rect *r)
{
    ggprint8b(r, 16, 0x000000ff, "Kenny Taylor");
}

void showKennyCredits(int x, int y)
{
    Rect r;
    r.bot = y;
    r.left = x;

    ggprint8b(&r, 16, 0x004040ff, "Kenny Taylor");
}

void creditsTitle(int x, int y)
{
    Rect r;
    r.bot = y;
    r.left = x;
    r.center = 0;  

    ggprint8b(&r, 16, 0x004040ff, "Game Credits");
}


void showKennyImage(int x, int y, GLuint texid)
{
    // Wiggle the image up and down between (y + yRange) and (y - yRange)
    int yRange = 20; 
    yOffset += yVelocity;
   if (yOffset > yRange) {
        yOffset = yRange;
        yVelocity = -1;
    } else if (yOffset < -yRange) {
        yOffset = -yRange;
        yVelocity = 1;
    }

    // ADDED IN CLASS 10/2/18 - Draw Kenny picture
    glColor3ub(255, 255, 255);
    int wid = 80; 
    glPushMatrix();
    glTranslatef(x, y + yOffset, 0); 
    glBindTexture(GL_TEXTURE_2D, texid);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid,-wid);
        glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, wid);
        glTexCoord2f(1.0f, 0.0f); glVertex2i( wid, wid);
        glTexCoord2f(1.0f, 1.0f); glVertex2i( wid,-wid);
    glEnd();
    glPopMatrix();
}

void loadLevel(Level *lev, char *filename)
{
    lev->load(filename);
}

void drawTexturedTile1(float x, float y)
{

}
