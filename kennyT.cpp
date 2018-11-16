// Kenny Taylor
// Modified:  11/14/18
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

void drawTexturedBackground()
{
    int bgWidth = 256, bgHeight = 256; 
    for (int i=0; i < 3; i++) {
        for (int j=0; j < 15; j++) {
            glPushMatrix();
            glColor3f(1.0, 1.0, 1.0);
            glTranslatef(j*bgWidth+bgWidth/2+gl.backgroundXoffset, 140+i*bgHeight+bgHeight/2, 0);  
            glBindTexture(GL_TEXTURE_2D, gl.backgroundTexture);
            glBegin(GL_QUADS);
                glTexCoord2f(0.0f, 1.0f); glVertex2i(-bgWidth/2, -bgHeight/2);
                glTexCoord2f(0.0f, 0.0f); glVertex2i(-bgWidth/2, bgHeight/2);
                glTexCoord2f(1.0f, 0.0f); glVertex2i(bgWidth/2, bgHeight/2);
                glTexCoord2f(1.0f, 1.0f); glVertex2i(bgWidth/2, -bgHeight/2);
            glEnd();
            glPopMatrix();
        }
    }    
    glBindTexture(GL_TEXTURE_2D, 0);
}

void drawSolidTile(float x, float y, float tilesize, float r, float g, float b)
{
    glPushMatrix();
    glColor3f(r, g, b);
    glTranslated(x, y, 0);
    glBegin(GL_QUADS);
        glVertex2i( 0,  0);  
        glVertex2i( 0, tilesize); 
        glVertex2i(tilesize, tilesize); 
        glVertex2i(tilesize,  0);  
    glEnd();
    glPopMatrix();
}

void drawTexturedTile(int index, float x, float y, float tilesize)
{
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);      
    glTranslated(x, y, 0);
    glBindTexture(GL_TEXTURE_2D, gl.tileTexture[index]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2i(0, 0);
        glTexCoord2f(0.0f, 0.0f); glVertex2i(0, tilesize);
        glTexCoord2f(1.0f, 0.0f); glVertex2i(tilesize, tilesize);
        glTexCoord2f(1.0f, 1.0f); glVertex2i(tilesize, 0);    
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
}

void loadTexture(GLuint *tex, Image img)
{
    glGenTextures(1, tex);
    int w = img.width;
    int h = img.height;
    glBindTexture(GL_TEXTURE_2D, *tex);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); 
    glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, 
        GL_RGB, GL_UNSIGNED_BYTE, img.data);
}
