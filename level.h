// Definition or level class

#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "kennyT.h"
#include "tristanB.h"
#include "rudyM.h"
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

    //Create an arry of Slime Class
    //vector<Slimed> slm;

	//Create an array of Slime(Enemy) Class
	vector<Slime> slmE;

	//Create an array of Zombie(Enemy) Class
	vector<Zombie> zmb;

	//Create an array of Door Class
	vector<Door> dor;

    Level();
    void load(char*);
    void removeCrLf(char *);
}; 

#endif
