// Definition or level class

#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "kennyT.h"

using namespace std;

//defined types
typedef double Flt; 

class Level {
public:
    unsigned char arr[16][125];
    int nrows, ncols;
    int tilesize[2];
    int levelNumber;
    int levelWidth;
    Flt ftsz[2];
    Flt tile_base;
    // Create an array of the SomeObject class objects
    vector<SomeObject> someobject;

    Level();
    void load(char*);
    void removeCrLf(char *);
}; 

#endif
