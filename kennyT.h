
#ifndef KENNY_H
#define KENNY_H

#include <GL/glx.h>
#include <utility>

void drawHUD(struct timespec ts);
void drawImage(int, int, int, int, GLuint);
void fetchHTTPScores(char*, char*);
void showEndScreen();


#endif
