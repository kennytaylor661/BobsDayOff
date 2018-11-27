// Kenny Taylor
// Modified:  11/26/18
// Purpose:  individual work on group project

#include <GL/glx.h>
#include <iostream>
#include "fonts.h"
#include "global.h"
#include "http.h"
#include "level.h"
#include "kennyT.h"

using namespace std;

// timer.cpp functions
extern struct timespec timeStart, timeCurrent;
extern double timeDiff(struct timespec *start, struct timespec *end);
extern void timeCopy(struct timespec *dest, struct timespec *source);

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

void drawText(int x, int y, int color, char *text)
{
    Rect r;
    r.bot = y;
    r.left = x;
    r.center = 0;
    ggprint8b(&r, 16, color, text);
}

void drawImage(int x, int y, int width, int height, GLuint texid)
{
    glPushMatrix();
    glColor3ub(255,255,255);
    glTranslatef(x, y, 0); 
    glBindTexture(GL_TEXTURE_2D, texid);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2i(-width/2, -height/2);
        glTexCoord2f(1.0f, 1.0f); glVertex2i(width/2, -height/2);
        glTexCoord2f(1.0f, 0.0f); glVertex2i(width/2, height/2);
        glTexCoord2f(0.0f, 0.0f); glVertex2i(-width/2, height/2);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0); 
    glPopMatrix();
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

unsigned char *buildAlphaData(Image *img)
{
    //add 4th component to RGB stream...
    int i;
    unsigned char *newdata, *ptr;
    unsigned char *data = (unsigned char *)img->data;
    newdata = (unsigned char *)malloc(img->width * img->height * 4); 
    ptr = newdata;
    unsigned char a,b,c;
    //use the first pixel in the image as the transparent color.
    unsigned char t0 = *(data+0);
    unsigned char t1 = *(data+1);
    unsigned char t2 = *(data+2);
    //cout << "buildAlphaData() clear color is:  (" << (int)t0 << ", " << (int)t1 << ", " << (int)t2 << ")" << endl;
    for (i=0; i<img->width * img->height * 3; i+=3) {
        a = *(data+0);
        b = *(data+1);
        c = *(data+2);
        *(ptr+0) = a;
        *(ptr+1) = b;
        *(ptr+2) = c;
        *(ptr+3) = 1;
        if (a==t0 && b==t1 && c==t2)
            *(ptr+3) = 0;
        //-----------------------------------------------
        ptr += 4;
        data += 3;
    }   
    return newdata;
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

void loadTextureAlpha(GLuint *tex, Image img)
{
    glGenTextures(1, tex);
    int w = img.width;
    int h = img.height;
    glBindTexture(GL_TEXTURE_2D, *tex);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); 
    unsigned char *xData = buildAlphaData(&img);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
        GL_RGBA, GL_UNSIGNED_BYTE, xData);
    free(xData);
}

void drawHUD(struct timespec ts)
{
    unsigned int c = 0x00ffff44;
    struct timespec te;
    Rect upperLeft, upperRight;

    // Draw a background for the text in the upper-left
    glPushMatrix();
    glColor4f(0.4, 0.4, 0.4, 0.7);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glTranslated(5, gl.yres-186, 0);
    glBegin(GL_QUADS);
        glVertex2i( 0,  0);  
        glVertex2i( 0, 182); 
        glVertex2i(165, 182); 
        glVertex2i(165,  0);  
    glEnd();
    glDisable(GL_BLEND);
    glPopMatrix();

    // Draw the text in the upper-left
    upperLeft.bot = gl.yres - 20; 
    upperLeft.left = 10; 
    upperLeft.center = 0;
    ggprint8b(&upperLeft, 16, c, "W     Walk cycle");
    ggprint8b(&upperLeft, 16, c, "E     Explosion");
    ggprint8b(&upperLeft, 16, c, "C     Credits");
    ggprint8b(&upperLeft, 16, c, "[1-2] Change Level"); 
    ggprint8b(&upperLeft, 16, c, "+     faster");
    ggprint8b(&upperLeft, 16, c, "-     slower");
    ggprint8b(&upperLeft, 16, c, "D, right arrow -> walk right");
    ggprint8b(&upperLeft, 16, c, "A, left arrow  <- walk left");

    // Draw a background for the text in the upper-right
    glPushMatrix();
    glColor4f(0.4, 0.4, 0.4, 0.7);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glTranslated(gl.xres-100-5, gl.yres-50-5, 0); 
    glBegin(GL_QUADS);
        glVertex2i( 0,  0);  
        glVertex2i( 0, 50); 
        glVertex2i(100, 50); 
        glVertex2i(100,  0);  
    glEnd();
    glDisable(GL_BLEND);
    glPopMatrix();
 
    // Draw the text in the upper-left
    upperRight.bot = gl.yres - 20; 
    upperRight.left = gl.xres - 100; 
    upperRight.center = 0;
    ggprint8b(&upperRight, 16, c, "Score: %d", gl.score);
    ggprint8b(&upperRight, 16, c, "Health: %d", gl.health);

    // Draw the physics and render times (do this last)
    clock_gettime(CLOCK_REALTIME, &te);
    gl.renderTime = timeDiff(&ts, &te);
    ggprint8b(&upperLeft, 16, c, "");
    ggprint8b(&upperLeft, 16, c, "physics time: %lf sec", gl.physicsTime);
    ggprint8b(&upperLeft, 16, c, "render time:  %lf sec", gl.renderTime);
}

void showLeaderboard()
{
    // Show the top 10 scores, pulled from minons.rocket-tech.net/getscores.php

    // Draw background rectangle (center in viewport)
    glPushMatrix();
    glColor3ub(255,255,255);
    glBegin(GL_QUADS);
        glVertex2i(gl.xres/2-300, gl.yres/2-200);
        glVertex2i(gl.xres/2+300, gl.yres/2-200);
        glVertex2i(gl.xres/2+300, gl.yres/2+200);
        glVertex2i(gl.xres/2-300, gl.yres/2+200);
    glEnd();
    glPopMatrix();

    // Draw the credits title
    drawText(gl.xres/2-20, gl.yres/2+170, 0x004040ff, (char*)"High Scores:");

    // Pull the current leaders from http://minions.rocket-tech.net/getscores.php
    fetchHTTPScores((char*)"minions.rocket-tech.net", (char*)"getscores.php", gl.xres/2, gl.yres/2);
}

void showIntroScreen()
{
    // Draw background image
    glPushMatrix();
    glColor3ub(255,255,255);
    glBindTexture(GL_TEXTURE_2D, gl.introScreenTexture);
    glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 1.0f); glVertex2i(0, 0);
        glTexCoord2f(0.0f, 1.0f); glVertex2i(gl.xres, 0);
        glTexCoord2f(0.0f, 0.0f); glVertex2i(gl.xres, gl.yres);
        glTexCoord2f(1.0f, 0.0f); glVertex2i(0, gl.yres);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();

    // Draw the text
    drawImage(gl.xres/2, gl.yres-100, 492, 85, gl.introTitleTexture);
    drawImage(gl.xres/2, gl.yres-200, 351, 51, gl.introPressSpaceTexture);
}

void fetchHTTPScores(char *host, char *page, int x, int y)
{
    int sock = create_tcp_socket();
    char *ip = get_ip(host);
    //fprintf(stderr, "IP is %s\n", ip);
    struct sockaddr_in *remote = (struct sockaddr_in *) malloc(sizeof(struct sockaddr_in *));
    remote->sin_family = AF_INET;
    int tmpres = inet_pton(AF_INET, ip, (void *)(&(remote->sin_addr.s_addr)));
    remote->sin_port = htons(80);

    if (connect(sock, (struct sockaddr *)remote, sizeof(struct sockaddr)) >= 0) {
        // Connected successfully
        char *get = build_get_query(host, page);
        //fprintf(stderr, "Query is:\n<<START>>\n%s<<END>>\n", get);
        int sent = 0;
        while (sent < (int)strlen(get)) {
            tmpres = send(sock, get+sent, strlen(get)-sent, 0);
            if (tmpres == -1) {
                fprintf(stderr, "send command, Can't send query");
                exit(1);
             }
            sent += tmpres;
        }
        // Receive the page
        char buf[1000];
        memset(buf, 0, sizeof(buf));
        int htmlstart = 0;
        char *htmlcontent;
        char *line;
        while ((tmpres = recv(sock, buf, BUFSIZ, 0)) > 0) {
            if (htmlstart == 0) {
                // Skip to the body portion of the HTML response
                htmlcontent = strstr(buf, "\r\n\r\n");
                if (htmlcontent != NULL) {
                    htmlstart = 1;
                    htmlcontent += 4;
                }
            } else {
                htmlcontent = buf;
            }
            if (htmlstart) {
                // Pull the first line
                line = strtok(htmlcontent, "\n");
                drawText(x, y, 0x800080, line);
                // Pull the second line
                line = strtok(NULL, "\n");
                drawText(x, y-16, 0x800080, line);
                // Pull the third line
                line = strtok(NULL, "\n");
                drawText(x, y-32, 0x800080, line);
                // Pull the fourth line
                line = strtok(NULL, "\n");
                drawText(x, y-48, 0x800080, line);
                // Pull the fifth line
                line = strtok(NULL, "\n");
                drawText(x, y-64, 0x800080, line);
            }

            memset(buf, 0, tmpres);
        }
    }
}

// Example functions for the SomeObject class
void SomeObject::physics()
{
    //cout << "SomeObject::physics() was called.." << endl;
}

void SomeObject::render()
{
    //cout << "SomeObject::render() was called.." << endl;
}
