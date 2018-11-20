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

    // Create an arry of Banana Class
    vector<Banana> ban;

    //Create an array of Torch Class
    vector<Torch> tor;

    //Create an arry of Slime Class
    vector<Slimed> slm;

    Level();
    void load(char*);
    void removeCrLf(char *);
}; 

#endif
