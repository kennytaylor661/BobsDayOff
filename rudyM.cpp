/* 
 * Rudy Martinez
 * Modified: 10/4/18
 * Purpose:  Individual file for group project
*/

#include <GL/glx.h>
#include "fonts.h"

static double xVelocity = 1;
static double xOffset = 0;

void rudyCredits(Rect* r)
{
	ggprint8b(r, 16, 0x002da3ce, "Rudy Martinez");
}

void showRudyPicture(int x, int y, GLuint texid)
{
	int xRange = 20;
	xOffset += xVelocity;
	if (xOffset > xRange) {
		xOffset = xRange;
		xVelocity = -1;
	} else if (xOffset < -xRange) {
		xOffset = -xRange;
		xVelocity = 1;
	}

	glColor3ub(255, 255, 255);
	int wid = 80; 
    	glPushMatrix();
    	glTranslatef(x + xOffset, y, 0); 
    	glBindTexture(GL_TEXTURE_2D, texid);
    	glBegin(GL_QUADS);
        	glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid,-wid);
        	glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, wid);
        	glTexCoord2f(1.0f, 0.0f); glVertex2i( wid, wid);
        	glTexCoord2f(1.0f, 1.0f); glVertex2i( wid,-wid);
    	glEnd();
    	glPopMatrix();
}

