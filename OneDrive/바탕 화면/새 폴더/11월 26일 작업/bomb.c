#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "bomb.h"

#include "map.h"
#include "define_state.h"
#include "cursor.h"
#include "player.h"

//#include "debug.h"

extern int mapModel[HEIGHT][WIDTH];
extern int PlayerCurPosX; // �÷��̾� ���� ��ǥ player.h ���� ����
extern int PlayerCurPosY; // �÷��̾� ���� ��ǥ player.h ���� ����

extern int npcCurPosX;
extern int npcCurPosY;

unsigned long long cur_time;
int GameOver = 0;

BombHead* bombHead;
BOOMHead* boomhead;

extern int player_bomb_len;

extern Map_box_head* map_box_head;

extern int bomb_exist_count;
extern int npc1_bomb_exist_count;
extern int npc2_bomb_exist_count;
extern int npc3_bomb_exist_count;


Bomb* getBombNode(int x, int y, int who_set)
{
	Bomb* newbomb = (Bomb*)malloc(sizeof(Bomb));
	newbomb->prev = NULL;
	newbomb->next = NULL;
	newbomb->start_time = clock(); // ���� �ð����� �ʱ�ȭ
	//newbomb->time = 0;
	newbomb->x = x;
	newbomb->y = y;
	newbomb->len = player_bomb_len;
	if (who_set != PLAYER)
		newbomb->len = 1;
	newbomb->who_set = who_set;

	for (int i = 0; i < 4; i++) { // ��ǳ���� ��ġ�� ������ 777�� ǥ��
		for (int j = 0; j < newbomb->len; j++) {
			if (NPCmapModel[y - j - 1][x] == STATE_WALL || mapModel[y - j - 1][x] == STATE_BOX) {
				break;
			}
			NPCmapModel[y - j - 1][x] = STATE_NPC_WARNING;
		}
		for (int j = 0; j < newbomb->len; j++) {
			if (NPCmapModel[y + j + 1][x] == STATE_WALL || mapModel[y + j + 1][x] == STATE_BOX) {
				break;
			}
			NPCmapModel[y + j + 1][x] = STATE_NPC_WARNING;
		}
		for (int j = 0; j < newbomb->len; j++) {
			if (NPCmapModel[y][x - j - 1] == STATE_WALL || mapModel[y][x - j - 1] == STATE_BOX) {
				break;
			}
			NPCmapModel[y][x - j - 1] = STATE_NPC_WARNING;
		}
		for (int j = 0; j < newbomb->len; j++) {
			if (NPCmapModel[y][x + j + 1] == STATE_WALL || mapModel[y][x + j + 1] == STATE_BOX) {
				break;
			}
			NPCmapModel[y][x + j + 1] = STATE_NPC_WARNING;
		}
	}

	return newbomb;
}

void insertitem(Bomb* w)
{
	Bomb* curBomb = bombHead->next;

	if (bombHead->next == NULL)
	{
		bombHead->next = w;
	}
	else
	{
		while (curBomb->next != NULL) {
			//if (curBomb->x == w->x && curBomb->y == w->y) return //�̹� ��ǳ���� �ִ� ���� �� ��ǳ���� �������� �ϸ� ����
			curBomb = curBomb->next;
		}
		curBomb->next = w;
		w->prev = curBomb;
	}
	set_Bomb(w->x, w->y); //��ǳ�� ����.
	if (w->who_set == PLAYER)
		bomb_exist_count++;
	if (w->who_set == NPC1)
		npc1_bomb_exist_count++;
	if (w->who_set == NPC2)
		npc2_bomb_exist_count++;
	if (w->who_set == NPC3)
		npc3_bomb_exist_count++;
}

BOOM* getnode_BOOM(int x, int y, unsigned long long time)
{
	BOOM* newBOOM = (BOOM*)malloc(sizeof(BOOM));
	newBOOM->start_time = time;
	newBOOM->x = x;
	newBOOM->y = y;
	newBOOM->prev = NULL;
	newBOOM->next = NULL;
	return newBOOM;
}

void insertitem_BOOM(BOOM* w)
{
	if (boomhead->next == NULL) {
		boomhead->next = w;
		return;
	}

	BOOM* curBOOM = boomhead->next;
	while (curBOOM->next != NULL) {
		curBOOM = curBOOM->next;
	}
	curBOOM->next = w;
	w->prev = curBOOM;
}

void PrintBomb()
{ //��ź �迭 ��ġ ����ϱ�
	Bomb* curBomb = bombHead->next;
	while (curBomb->next != NULL) {
		printf("%d %d\n", curBomb->x, curBomb->y);
		curBomb = curBomb->next;
	}
}

void printBOOM()
{
	BOOM* curBOOM = boomhead->next;
	if (curBOOM == NULL) return;

	while (curBOOM != NULL) {
		printf("%d %d\n", curBOOM->x, curBOOM->y);
		curBOOM = curBOOM->next;
	}
}

void BombSwich_On(int x, int y)
{
	unsigned long long time = clock();
	Bomb* curBomb = bombHead->next;

	// x, y �� ������ ��带 ã�� �Լ� �����
	while (curBomb != NULL) {
		if (curBomb->x == x && curBomb->y == y) {
			//PBpmb = curBomb;
			break;
		}
		curBomb = curBomb->next;
	}

	if (curBomb == NULL)
		return;

	if (curBomb->who_set == PLAYER)
		bomb_exist_count--;
	if (curBomb->who_set == NPC1)
		npc1_bomb_exist_count--;
	if (curBomb->who_set == NPC2)
		npc2_bomb_exist_count--;
	if (curBomb->who_set == NPC3)
		npc3_bomb_exist_count--;

	//mapModel[curBomb->y][curBomb->x] == 0; //�� ���� ����. ��ǳ�� �ִ� �ڸ��� �ƹ��͵� ������� ����.

	set_Bomb_Boom(curBomb->x, curBomb->y);
	BOOM* w = getnode_BOOM(curBomb->x, curBomb->y, time);
	insertitem_BOOM(w);

	// ��� ���� �Լ� �����
	if (curBomb->prev == NULL)
		bombHead->next = curBomb->next;
	else
		curBomb->prev->next = curBomb->next;
	if (curBomb->next != NULL)
		curBomb->next->prev = curBomb->prev;
	int len = curBomb->len;
	free(curBomb);
	//printf("%d %d BOMB!!!\n", x, y);

	//printf("len : %d", len);



	//���� ������ ���� �ȱ�
	for (int i = 1; i <= len; i++)
	{
		if (check_over_GameBoard_HEIGHT(y - i))
			break;
		else if (checkObject_can_go(arrX_to_cursorX(x), arrY_to_cursorY(y - i))) {
			set_Bomb_Boom(x, y - i);
			w = getnode_BOOM(x, y - i, time);
			insertitem_BOOM(w);
			NPCmapModel[y - i][x] = STATE_EMPTY;
		}
		else if (checkObject_box(arrX_to_cursorX(x), arrY_to_cursorY(y - i))) { //���� ���ڶ��
			insert_map_box_struct(map_box_head, x, y - i);
			NPCmapModel[y - i][x] = STATE_EMPTY;
			break;          // ���� ���� �ڷ� ��ź�� ������ ������ �ʰ�
		}
		else if (checkObject_Item(arrX_to_cursorX(x), arrY_to_cursorY(y - i))) { //�������� �ִٸ�
			set_Empty(x, y - i);     //������ �ı�, �������� ����
		}
		else if (checkObject_exist_bomb(arrX_to_cursorX(x), arrY_to_cursorY(y - i))) { //���� �ٸ� ��ź�� �ִٸ�
			BombSwich_On(x, y - i); //���ȣ��
			break;
		}
	}
	//�Ʒ��� ������ ���� �ȱ�
	for (int i = 1; i <= len; i++)
	{
		if (check_over_GameBoard_HEIGHT(y + i))
			break;
		else if (checkObject_can_go(arrX_to_cursorX(x), arrY_to_cursorY(y + i))) {
			set_Bomb_Boom(x, y + i);
			w = getnode_BOOM(x, y + i, time);
			insertitem_BOOM(w);
			NPCmapModel[y + i][x] = STATE_EMPTY;
		}
		else if (checkObject_box(arrX_to_cursorX(x), arrY_to_cursorY(y + i))) { //���� ���ڶ��
			insert_map_box_struct(map_box_head, x, y + i);
			NPCmapModel[y + i][x] = STATE_EMPTY;
			break;          // ���� ���� �ڷ� ��ź�� ������ ������ �ʰ�
		}
		else if (checkObject_Item(arrX_to_cursorX(x), arrY_to_cursorY(y + i))) { //�������� �ִٸ�
			set_Empty(x, y + i);     //������ �ı�, �������� ����
		}
		else if (checkObject_exist_bomb(arrX_to_cursorX(x), arrY_to_cursorY(y + i))) { //���� �ٸ� ��ź�� �ִٸ�
			BombSwich_On(x, y + i); //���ȣ��
			break;
		}
	}
	// �·� ������ ���� �ȱ�
	for (int i = 1; i <= len; i++)
	{
		if (check_over_GameBoard_Width(x - i))
			break;
		else if (checkObject_can_go(arrX_to_cursorX(x - i), arrY_to_cursorY(y))) {
			set_Bomb_Boom(x - i, y);
			w = getnode_BOOM(x - i, y, time);
			NPCmapModel[y][x - i] = STATE_EMPTY;
			insertitem_BOOM(w);
		}
		else if (checkObject_box(arrX_to_cursorX(x - i), arrY_to_cursorY(y))) { //���� ���ڶ��
			insert_map_box_struct(map_box_head, x - i, y);
			NPCmapModel[y][x - i] = STATE_EMPTY;
			break;          // ���� ���� �ڷ� ��ź�� ������ ������ �ʰ�
		}
		else if (checkObject_Item(arrX_to_cursorX(x - i), arrY_to_cursorY(y))) { //�������� �ִٸ�
			set_Empty(x - i, y);     //������ �ı�, �������� ����
		}
		else if (checkObject_exist_bomb(arrX_to_cursorX(x - i), arrY_to_cursorY(y))) { //���� �ٸ� ��ź�� �ִٸ�
			BombSwich_On(x - i, y); //���ȣ��
			break;
		}
		else
			;
	}
	// ��� ������ ���� �ȱ�
	for (int i = 1; i <= len; i++)
	{
		if (check_over_GameBoard_Width(x + i))
			break;
		else if (checkObject_can_go(arrX_to_cursorX(x + i), arrY_to_cursorY(y))) {
			set_Bomb_Boom(x + i, y);
			w = getnode_BOOM(x + i, y, time);
			insertitem_BOOM(w);
			NPCmapModel[y][x + i] = STATE_EMPTY;
		}
		else if (checkObject_box(arrX_to_cursorX(x + i), arrY_to_cursorY(y))) { //���� ���ڶ��
			insert_map_box_struct(map_box_head, x + i, y);
			NPCmapModel[y][x + i] = STATE_EMPTY;
			break;          // ���� ���� �ڷ� ��ź�� ������ ������ �ʰ�
		}
		else if (checkObject_Item(arrX_to_cursorX(x + i), arrY_to_cursorY(y))) { //�������� �ִٸ�
			set_Empty(x + i, y);     //������ �ı�, �������� ����
		}
		else if (checkObject_exist_bomb(arrX_to_cursorX(x + i), arrY_to_cursorY(y))) { //���� �ٸ� ��ź�� �ִٸ�
			BombSwich_On(x + i, y); //���ȣ��
			break;
		}
		else
			;
	}

	//for (int i = -len; i <= len; i++) { //��ź�� ������ ���� �ȱ�
	//    if (i == 0) continue;
	//    int m = i + y;
	//    int n = i + x;

	//    //������ Ȯ��
	//    if (check_over_GameBoard_HEIGHT(m))
	//        ;
	//    else if (checkObject_can_go(arrX_to_cursorX(x), arrY_to_cursorY(m))) {
	//        set_Bomb_Boom(x, m);
	//        w = getnode_BOOM(x, m, time);
	//        insertitem_BOOM(w);
	//    }
	//    else if (checkObject_box(arrX_to_cursorX(x), arrY_to_cursorY(m))) { //���� ���ڶ��
	//        set_Empty(x, m);
	//        gernerate_Item(arrX_to_cursorX(x), arrY_to_cursorY(m));
	//    }
	//    else if (checkObject_Item(arrX_to_cursorX(x), arrY_to_cursorY(m))) { //�������� �ִٸ�
	//        set_Empty(x, m);     //������ �ı�, �������� ����
	//    }
	//    else if (checkObject_exist_bomb(arrX_to_cursorX(x), arrY_to_cursorY(m))) { //���� �ٸ� ��ź�� �ִٸ�
	//        ?BombSwich_On(x, m); //���ȣ��
	//    }
	//    else
	//        ;

	//    //������ Ȯ��
	//    if (check_over_GameBoard_Width(n))          //�ʹ����� ��� ���
	//        ;
	//    else if (checkObject_can_go(arrX_to_cursorX(n), arrY_to_cursorY(y))) {
	//        set_Bomb_Boom(n, y);
	//        w = getnode_BOOM(n, y, time);
	//        insertitem_BOOM(w);
	//    }
	//    else if (checkObject_box(arrX_to_cursorX(n), arrY_to_cursorY(y))) { //���� ���ڶ��
	//        set_Empty(n, y);
	//        gernerate_Item(arrX_to_cursorX(n), arrY_to_cursorY(y));
	//    }
	//    else if (checkObject_Item(arrX_to_cursorX(n), arrY_to_cursorY(y))) { //�������� �ִٸ�
	//        set_Empty(n, y); //������ �ı�
	//    }
	//    else if (checkObject_exist_bomb(arrX_to_cursorX(n), arrY_to_cursorY(y))) { //���� �ٸ� ��ź�� �ִٸ�
	//        ?BombSwich_On(n, y); //���ȣ��
	//    }

	//}

	//printBOOM();
}

void TimeCheck()
{
	Bomb* curBomb = bombHead->next;
	if (curBomb == NULL)
		return;

	Bomb* tmpBomb;

	while (curBomb != NULL) {
		cur_time = clock();
		tmpBomb = curBomb->next;
		if (cur_time - curBomb->start_time >= 3000) {
			BombSwich_On(curBomb->x, curBomb->y);
			break;
		}
		curBomb = tmpBomb;
	}
}

void TimeCheck_BOOM()
{
	BOOM* curBOOM = boomhead->next;
	if (curBOOM == NULL) return;
	BOOM* tmpBOOM = curBOOM->next;
	while (curBOOM != NULL) {
		cur_time = clock();
		tmpBOOM = curBOOM->next;
		if (cur_time - curBOOM->start_time >= 700) {
			// bomb boom ����� �Լ� ���
			set_Empty(curBOOM->x, curBOOM->y);
			// BOOM ��� ���� �Լ� ���
			if (curBOOM->prev == NULL)
				boomhead->next = curBOOM->next;
			else
				curBOOM->prev->next = curBOOM->next;
			if (curBOOM->next != NULL)
				curBOOM->next->prev = curBOOM->prev;
			free(curBOOM);

		}
		curBOOM = tmpBOOM;
	}
}


void player_set_bomb()
{
	Bomb* newbomb = getBombNode((PlayerCurPosX - GBOARD_ORIGIN_X) / 2, (PlayerCurPosY - GBOARD_ORIGIN_Y), PLAYER); //x, y��ǥ�� �� ��ź ����.

	//npc_Warning_update(cursorX_to_arrX(PlayerCurPosX), cursorY_to_arrY(PlayerCurPosY), newbomb);

	insertitem(newbomb);
}


void npc1_set_bomb()
{
	Bomb* newbomb = getBombNode((npcCurPosX - GBOARD_ORIGIN_X) / 2, (npcCurPosY - GBOARD_ORIGIN_Y), NPC1); //x, y��ǥ�� �� ��ź ����.
	insertitem(newbomb);
}