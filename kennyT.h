
#ifndef KENNY_H
#define KENNY_H

#include <GL/glx.h>
#include <utility>

void drawHUD(struct timespec ts);
void drawImage(int, int, int, int, GLuint);
void fetchHTTPScores(char*, char*);

class SomeObject 
{
    int posx, posy;
    GLuint texid;

public:
    SomeObject(int x, int y, GLuint tex): posx(x), posy(y), texid(tex) {}
    void physics();
    void render();

};

#endif
