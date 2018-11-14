

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
