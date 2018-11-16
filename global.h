// Global class definition

#ifndef GLOBAL_H
#define GLOBAL_H

#include "image.h"
#include "rudyM.h"
#include "sprite.h"

typedef double Flt;
typedef Flt Matrix[4][4];
typedef double Vec[3];

class Global {
public:
    unsigned char keys[65536];
    int xres, yres;
    int movie, movieStep;
    int walk;
    int walkFrame;
    int render = 1; 
    double delay;
    double physicsTime = 0.0, renderTime = 0.0; 
    double backgroundXoffset = 0.0; 
    bool creditsFlag = 0; 
    Image *walkImage;
    GLuint walkTexture;
    GLuint backgroundTexture;
    GLuint gray1Texture;
    GLuint kennyCreditsTexture;
    GLuint tristanTexture;
    GLuint rudyTexture;
    GLuint bananaTexture;
    GLuint tileTexture[10];
    int bananaCount = 0; 
    Banana *ban;
    Vec box[20];
    Sprite exp; 
    Sprite exp44;
    Vec ball_pos;
    Vec ball_vel;
    //camera is centered at (0,0) lower-left of screen. 
    Flt camera[2];
    ~Global();
    Global();
};

#endif
