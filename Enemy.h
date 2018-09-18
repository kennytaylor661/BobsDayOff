#IFNDEF ENEMY_H
#DEFINE ENEMY_H
//Header file for enemy type declaration and basic AI

class Enemy
{
	int posx;
	int posy;
	Enemy(int x, int y): posx(x), posy(y){}

public:
	void moveLeft() {posx--;}
	void moveRight() {posx++;}

};

#ENDIF
