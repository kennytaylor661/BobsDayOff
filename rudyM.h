/*
 *Rudy Martinez
 *Modified on: 11/27/18
 *
*/
#ifndef RUDY_H
#define RUDY_H

#include <GL/glx.h>
#include <utility>
typedef double Flt;

void torchRender(int, int);
void slimeRender(int, int);
void drawWallDecorations(Flt dd, int ncols_to_render, Flt offx, Flt offy);
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
    Torch(int x, int y, GLuint tex): posx(x), posy(y), texid(tex) {}
    void physics();
    void render();
};

class Slimed
{
    int posx, posy;
    GLuint texid;

    public:
    Slimed(int x, int y, GLuint tex): posx(x), posy(y), texid(tex) {}
    void physics();
    void render();
};
#endif
