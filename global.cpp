// Functions for the Global class

#include "global.h"
#include "log.h"

#define MakeVector(v, x, y, z) (v)[0]=(x),(v)[1]=(y),(v)[2]=(z)
#define rnd() (((double)rand())/(double)RAND_MAX)

Global::Global() {
    logOpen();
    camera[0] = camera[1] = 0.0;
    movie=0;
    movieStep=2;
    xres=800;
    yres=600;
    walk=0;
    walkFrame=0;
    walkImage=NULL;
    MakeVector(ball_pos, 520.0, 0, 0);
    MakeVector(ball_vel, 0, 0, 0);
    delay = 0.02;
    exp.onoff=0;
    exp.frame=0;
    exp.image=NULL;
    exp.delay = 0.02;
    exp44.onoff=0;
    exp44.frame=0;
    exp44.image=NULL;
    exp44.delay = 0.022;
    for (int i=0; i<20; i++) {
        box[i][0] = rnd() * xres;
        box[i][1] = rnd() * (yres-220) + 220.0;
        box[i][2] = 0.0;
    }
    memset(keys, 0, 65536);
};

Global::~Global() {
    logClose();
}    

