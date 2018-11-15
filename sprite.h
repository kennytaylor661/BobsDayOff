// Sprite class definition

#ifndef SPRITE_H
#define SPRITE_H

#include "image.h"

typedef double Vec[3];

class Sprite {
public:
    int onoff;
    int frame;
    double delay;
    Vec pos; 
    Image *image;
    GLuint tex; 
    struct timespec time;
    Sprite() {
        onoff = 0; 
        frame = 0; 
        image = NULL;
        delay = 0.1; 
    }    
};

#endif
