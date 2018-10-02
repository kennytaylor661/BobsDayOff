// Kenny Taylor
// Modified:  9/26/18
// Purpose:  individual work on group project

#include <GL/glx.h>
#include "fonts.h"

void kennyCredits(Rect *r)
{
    ggprint8b(r, 16, 0x000000ff, "Kenny Taylor");
}

void kennyCredits(int x, int y)
{
    Rect r;
    r.bot = y;
    r.left = x;
    r.center = 0; 

    ggprint8b(&r, 16, 0x000000ff, "Kenny Taylor");
}

void showKennyImage(int x, int y, GLuint texid)
{
    // ADDED IN CLASS 10/2/18 - Draw Kenny picture
    glColor3ub(255, 255, 255);
    int wid = 80; 
    glPushMatrix();
    glTranslatef(x, y, 0); 
    glBindTexture(GL_TEXTURE_2D, texid);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid,-wid);
        glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, wid);
        glTexCoord2f(1.0f, 0.0f); glVertex2i( wid, wid);
        glTexCoord2f(1.0f, 1.0f); glVertex2i( wid,-wid);
    glEnd();
    glPopMatrix();
}
