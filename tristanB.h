#IFNDEF TRISTAN_H
#DEFINE TRISTAN_H
//Header file for enemy type declaration and basic AI
extern class player;
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
	bool findPlayer(player P) {return P->getx() > posx;}
	void takeAction(player P)
	{
		if (P->getx() - posx < 15 && P->gety() - posy < 10)
			if (findPlayer())
				moveLeft();
			else
				moveRight();
	}
};

#ENDIF
