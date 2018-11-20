
#ifndef RUDY_H
#define RUDY_H

#include <GL/glx.h>
#include <utility>



class Banana 
{
    int posx, posy;
    GLuint texid;

public:
    Banana(int x, int y, GLuint tex): posx(x), posy(y), texid(tex) {}
    void physics();
    void render();


};

class Torch
{
    int posx, posy;
    GLuint texid;

    public:
    Torch(int x, int y, GLuint tex): pos(x), pos(y), texid(tex) {}
    void physics();
    void render();
}

#endif
