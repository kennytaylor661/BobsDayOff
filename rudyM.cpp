/* 
 * Rudy Martinez
*/

#include <GL/glx.h>
#include "fonts.h"

void rudyCredits(Rect* r)
{
	ggprint8b(r, 16, 0x00ffff00, "Rudy Martinez");
}

void showRudyPicture(int x, int y, GLuint texid)
{
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

