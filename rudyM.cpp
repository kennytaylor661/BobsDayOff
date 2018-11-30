/* 
 * Rudy Martinez
 * Modified: 11/27/18
 * Purpose:  Individual file for group project
*/
#include <iostream>
using namespace std;
#include <GL/glx.h>
#include "fonts.h"
#include "rudyM.h"
#include "global.h"

extern Global gl;

static double xVelocity = 1;
static double xOffset = 0;

void Banana::physics()
{


}

void Banana::render()
{
    // code that will draw the picture of the banana
    // reference code below for texture

    int wid = 25;
    glPushMatrix();
    glTranslatef(posx - gl.camera[0], posy, 0);
    glBindTexture(GL_TEXTURE_2D, texid);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS); 
        glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid,-wid);
       	glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, wid);
       	glTexCoord2f(1.0f, 0.0f); glVertex2i( wid, wid);
       	glTexCoord2f(1.0f, 1.0f); glVertex2i( wid,-wid);
   	glEnd();
   	glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
}

void Torch::render()
{
    // code that will draw the picture of a torch
    // reference code below for texture

    int wid = 25;
    glPushMatrix();
    glTranslatef(posx - gl.camera[0], posy, 0);
    glBindTexture(GL_TEXTURE_2D, texid);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS); 
        glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid,-wid);
       	glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, wid);
       	glTexCoord2f(1.0f, 0.0f); glVertex2i( wid, wid);
       	glTexCoord2f(1.0f, 1.0f); glVertex2i( wid,-wid);
   	glEnd();
   	glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
}

void Slimed::render()
{
    // code that will draw the picture of a slime
    // reference code below for texture
    
    int wid = 25;
    glPushMatrix();
    glTranslatef(posx - gl.camera[0], posy, 0);
    glBindTexture(GL_TEXTURE_2D, texid);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS); 
        glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid,-wid);
       	glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, wid);
       	glTexCoord2f(1.0f, 0.0f); glVertex2i( wid, wid);
       	glTexCoord2f(1.0f, 1.0f); glVertex2i( wid,-wid);
   	glEnd();
   	glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
}



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

void torchRender(int x, int y)
{
    int wid = 25;
    glPushMatrix();
    glTranslatef(x+wid, y+wid, 0);
    glBindTexture(GL_TEXTURE_2D, gl.torchTexture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS); 
        glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid,-wid);
       	glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, wid);
       	glTexCoord2f(1.0f, 0.0f); glVertex2i( wid, wid);
       	glTexCoord2f(1.0f, 1.0f); glVertex2i( wid,-wid);
   	glEnd();
   	glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
}

void slimeRender(int x, int y)
{    
    int wid = 25;
    glPushMatrix();
    glTranslatef(x+wid, y+wid, 0);
    glBindTexture(GL_TEXTURE_2D, gl.slimeTexture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS); 
        glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid,-wid);
       	glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, wid);
       	glTexCoord2f(1.0f, 0.0f); glVertex2i( wid, wid);
       	glTexCoord2f(1.0f, 1.0f); glVertex2i( wid,-wid);
   	glEnd();
   	glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
}
