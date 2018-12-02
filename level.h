// Definition or level class

#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "kennyT.h"
#include "tristanB.h"
#include "kennyT.h"
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

    // Create an arry of Banana Class
    vector<Banana> ban;

	// Create an array of Slime(Enemy) Class
	vector<Slime> slmE;

	// Create an array of Zombie(Enemy) Class
	vector<Zombie> zmb;

	// Create an array of Door Class
	vector<Door> dor;

    // Create an array of Bullet() Class
    vector<Bullet> bullet;

    Level();
    void load(char*);
    void removeCrLf(char *);
}; 

#endif
