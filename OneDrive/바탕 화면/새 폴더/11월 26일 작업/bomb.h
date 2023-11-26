#ifndef __BOMB_H__
#define __BOMB_H__

///bomb.h 수정사항
typedef struct Bomb { //이중연결리스트 구조체
	struct Bomb* next;
	struct Bomb* prev;
	unsigned long long start_time; //생성시 게임 시간
	//float time;
	int x;
	int y;
	int len;
	int who_set;
}Bomb;

typedef struct BombHead {
	struct Bomb* next;
} BombHead;

typedef struct BOOM {
	struct BOOM* next;
	struct BOOM* prev;
	unsigned long long start_time;
	int x;
	int y;
	int len;
	int who_set;
}BOOM;

typedef struct BOOMHead {
	struct BOOM* next;
} BOOMHead;


Bomb* getBombNode(int x, int y, int who_set);
void insertitem(Bomb* w);
BOOM* getnode_BOOM(int x, int y, unsigned long long time);
void insertitem_BOOM(BOOM* w);
void PrintBomb();       ///////////////////// 필요한가?
void printBOOM();
void BombSwich_On(int x, int y);
void TimeCheck();
void TimeCheck_BOOM();
void player_set_bomb();
void npc_set_bomb();


#endif // ! __BOMB_11_18_H__