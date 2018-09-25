#IFNDEF ENEMY_H
#DEFINE ENEMY_H
//Header file for enemy type declaration and basic AI

class Enemy
{
	int posx;
	int posy;
	int HP;
	int damage;
	int id;
	Enemy(int x, int y): posx(x), posy(y){}

public:
	void moveLeft() {posx--;}
	void moveRight() {posx++;}
	bool findPlayer(player P) {return P.x > posx;}
};

#ENDIF
