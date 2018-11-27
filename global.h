// Global class definition

#ifndef GLOBAL_H
#define GLOBAL_H

#include <string>
#include "image.h"
#include "kennyT.h"
#include "rudyM.h"
#include "sprite.h"

using namespace std;

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

    // Game state variables
    bool paused = 1;
    bool introScreenFlag = 1;
    bool creditsFlag = 0; 
    bool leaderboardFlag = 0;
    bool fetchLeaders = 0;

    Image *walkImage;
    GLuint introScreenTexture;
    GLuint introTitleTexture;
    GLuint introPressSpaceTexture;
    GLuint walkTexture;
    GLuint backgroundTexture;
    GLuint kennyCreditsTexture;
    GLuint tristanTexture;
    GLuint rudyTexture;
    GLuint bananaTexture;
    GLuint torchTexture;
    GLuint slimeTexture;
    GLuint someObjectTexture;
    GLuint tileTexture[10];
    Sprite exp; 
    Sprite exp44;
    Vec ball_pos;
    Vec ball_vel;
    //camera is centered at (0,0) lower-left of screen. 
    Flt camera[2];
    int lastFacing = 1;
    // Track player score and health here for the moment
    int health = 100;
    int score = 0;
    // Leaderboard values
    string leader1, leader2, leader3, leader4, leader5;

    ~Global();
    Global();
};

#endif
