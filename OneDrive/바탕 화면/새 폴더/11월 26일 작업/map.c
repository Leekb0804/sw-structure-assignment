#include "map.h"

#include "define_state.h"

#include <stdio.h>		//����׿�
#include <stdlib.h>		//rand(), srand() �Լ�
#include <time.h>		//time(NULL) ����ϱ� ����

#include "cursor.h"


int mapModel[HEIGHT][WIDTH] =
{
	{ STATE_WALL, STATE_WALL, STATE_WALL, STATE_WALL, STATE_WALL, STATE_WALL, STATE_WALL, STATE_WALL, STATE_WALL, STATE_WALL, STATE_WALL },

	{ STATE_WALL, STATE_BOX, STATE_EMPTY, STATE_BOX, STATE_EMPTY, STATE_EMPTY, STATE_EMPTY, STATE_BOX, STATE_EMPTY, STATE_BOX, STATE_WALL},
	{ STATE_WALL, STATE_EMPTY, STATE_EMPTY, STATE_EMPTY, STATE_EMPTY, STATE_EMPTY, STATE_EMPTY, STATE_EMPTY, STATE_EMPTY, STATE_EMPTY, STATE_WALL},
	{ STATE_WALL, STATE_BOX, STATE_EMPTY, STATE_BOX, STATE_EMPTY, STATE_EMPTY, STATE_EMPTY, STATE_BOX, STATE_EMPTY, STATE_BOX, STATE_WALL},

	{ STATE_WALL, STATE_EMPTY, STATE_EMPTY, STATE_EMPTY, STATE_EMPTY, STATE_EMPTY, STATE_EMPTY, STATE_EMPTY, STATE_EMPTY, STATE_EMPTY, STATE_WALL},
	{ STATE_WALL, STATE_EMPTY, STATE_EMPTY, STATE_EMPTY, STATE_EMPTY, STATE_EMPTY, STATE_EMPTY, STATE_EMPTY, STATE_EMPTY, STATE_EMPTY, STATE_WALL},
	{ STATE_WALL, STATE_EMPTY, STATE_EMPTY, STATE_EMPTY, STATE_EMPTY, STATE_EMPTY, STATE_EMPTY, STATE_EMPTY, STATE_EMPTY, STATE_EMPTY, STATE_WALL},

	{ STATE_WALL, STATE_BOX, STATE_EMPTY, STATE_BOX, STATE_EMPTY, STATE_EMPTY, STATE_EMPTY, STATE_BOX, STATE_EMPTY, STATE_BOX, STATE_WALL},
	{ STATE_WALL, STATE_EMPTY, STATE_EMPTY, STATE_EMPTY, STATE_EMPTY, STATE_EMPTY, STATE_EMPTY, STATE_EMPTY, STATE_EMPTY, STATE_EMPTY, STATE_WALL},
	{ STATE_WALL, STATE_BOX, STATE_EMPTY, STATE_BOX, STATE_EMPTY, STATE_EMPTY, STATE_EMPTY, STATE_BOX, STATE_EMPTY, STATE_BOX, STATE_WALL},

	{ STATE_WALL, STATE_WALL, STATE_WALL, STATE_WALL, STATE_WALL, STATE_WALL, STATE_WALL, STATE_WALL, STATE_WALL, STATE_WALL, STATE_WALL }
};

int NPCmapModel[HEIGHT][WIDTH] = { // npc�� ��ǳ�� ���� ���� �ܼ� �迭
	{ STATE_WALL, STATE_WALL, STATE_WALL, STATE_WALL, STATE_WALL, STATE_WALL, STATE_WALL, STATE_WALL, STATE_WALL, STATE_WALL, STATE_WALL },

	{ STATE_WALL, 0,0,0,0,0,0,0,0,0, STATE_WALL},
	{ STATE_WALL, 0,0,0,0,0,0,0,0,0, STATE_WALL},
	{ STATE_WALL, 0,0,0,0,0,0,0,0,0, STATE_WALL},

	{ STATE_WALL, 0,0,0,0,0,0,0,0,0, STATE_WALL},
	{ STATE_WALL, 0,0,0,0,0,0,0,0,0, STATE_WALL},
	{ STATE_WALL, 0,0,0,0,0,0,0,0,0, STATE_WALL},

	{ STATE_WALL, 0,0,0,0,0,0,0,0,0, STATE_WALL},
	{ STATE_WALL, 0,0,0,0,0,0,0,0,0, STATE_WALL},
	{ STATE_WALL, 0,0,0,0,0,0,0,0,0, STATE_WALL},

	{ STATE_WALL, STATE_WALL, STATE_WALL, STATE_WALL, STATE_WALL, STATE_WALL, STATE_WALL, STATE_WALL, STATE_WALL, STATE_WALL, STATE_WALL }
};

//�Ʒ��� ���� ����
/*
9  9 9 9 9 9 9 9 9 9  9

9  1 0 1 0 0 0 1 0 1  9
9  0 0 0 0 0 0 0 0 0  9
9  1 0 1 0 0 0 1 0 1  9

9  0 0 0 0 0 0 0 0 0  9
9  0 0 0 0 0 0 0 0 0  9
9  0 0 0 0 0 0 0 0 0  9

9  1 0 1 0 0 0 1 0 1  9
9  0 0 0 0 0 0 0 0 0  9
9  1 0 1 0 0 0 1 0 1  9

9  9 9 9 9 9 9 9 9 9  9
*/

int* output_random_5_num_arr()
{
	int test[10] = { 0, };
	int* num = (int*)malloc(sizeof(int) * 5);
	int random_num;
	int i = 0;

	// �ߺ��� ���� Ȯ���ϱ� ���� test[10]�迭�� ����
	// random_num �� �ϳ� ������ test�迭�� Ȯ��
	// test[random_num]�� ���� 1�� �ƴϸ� 
	// test[random_num]�� ���� 1���� �� num�迭�� random_num �� �߰�
	// num �迭�� �� ä�ﶧ ���� �� ���� �ݺ�

	while (i < 5) {
		random_num = (rand() % 9);		//0 ~ 8 �߿� ������ ��
		if (test[random_num] == 0)
		{
			test[random_num] = 1;
			num[i] = random_num;
			++i;
		}
	}

	//����׿�
	/*for (i = 0; i < 5; ++i)
		printf(" %d", num[i]);
	printf("\n");*/

	return num;
}

void resetMap()				// ���� ��, ���� �Ʒ�, ������ ��, ������ �Ʒ� ó�� �����Ҷ�, ���ڰ��� ������ �� �ֵ��� �ʱ�ȭ
{
	mapModel[2 - 1][2 - 1] = STATE_BOX;
	mapModel[2 - 1][2 + 1] = STATE_BOX;
	mapModel[2 + 1][2 - 1] = STATE_BOX;
	mapModel[2 + 1][2 + 1] = STATE_BOX;

	mapModel[HEIGHT - 3 - 1][2 - 1] = STATE_BOX;
	mapModel[HEIGHT - 3 - 1][2 + 1] = STATE_BOX;
	mapModel[HEIGHT - 3 + 1][2 - 1] = STATE_BOX;
	mapModel[HEIGHT - 3 + 1][2 + 1] = STATE_BOX;

	mapModel[2 - 1][WIDTH - 3 - 1] = STATE_BOX;
	mapModel[2 - 1][WIDTH - 3 + 1] = STATE_BOX;
	mapModel[2 + 1][WIDTH - 3 - 1] = STATE_BOX;
	mapModel[2 + 1][WIDTH - 3 + 1] = STATE_BOX;

	mapModel[HEIGHT - 3 - 1][WIDTH - 3 - 1] = STATE_BOX;
	mapModel[HEIGHT - 3 - 1][WIDTH - 3 + 1] = STATE_BOX;
	mapModel[HEIGHT - 3 + 1][WIDTH - 3 - 1] = STATE_BOX;
	mapModel[HEIGHT - 3 + 1][WIDTH - 3 + 1] = STATE_BOX;
}

void generateMap()			//�ʻ���
{
	resetMap();

	srand(time(NULL));
	int* num = output_random_5_num_arr();
	/*
	0 = 0			/ 1 = 1				/ 2 = 2
	3 = 1 * 3 + 0	/ 4 = 1 * 3 + 1		/ 5 = 1 * 3 + 2
	6 = 2 * 3 + 0	/ 7 = 2 * 3 + 1		/ 8 = 2 * 3 + 2
	*/

	/*
	map�� ������
	1 2 3
	4 5 6
	7 8 9 �� ����������
	*/
	// 4������ ä���
	for (int i = 0; i < 5; ++i)
	{
		mapModel[(num[i] / 3) + 1][3 + num[i] % 3 + 1] = STATE_BOX;
	}

	//2������ ä���
	num = output_random_5_num_arr();
	for (int i = 0; i < 5; ++i)
	{
		mapModel[3 + (num[i] / 3) + 1][num[i] % 3 + 1] = STATE_BOX;
	}
	free(num);

	//5������ ä���
	num = output_random_5_num_arr();
	for (int i = 0; i < 5; ++i)
	{
		mapModel[3 + (num[i] / 3) + 1][3 + num[i] % 3 + 1] = STATE_BOX;
	}
	free(num);

	//8������ ä���
	num = output_random_5_num_arr();
	for (int i = 0; i < 5; ++i)
	{
		mapModel[3 + (num[i] / 3) + 1][6 + num[i] % 3 + 1] = STATE_BOX;
	}
	free(num);

	//6������ ä���
	num = output_random_5_num_arr();
	for (int i = 0; i < 5; ++i)
	{
		mapModel[6 + (num[i] / 3) + 1][3 + num[i] % 3 + 1] = STATE_BOX;
	}
	free(num);


	//debug
	/*for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j)
			printf(" %d", mapModel[i][j]);
		printf("\n");
	}*/
}

void drawMaps()		//���� ȭ�鿡 ���
{
	int x, y;
	int cursX, cursY;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	for (y = 0; y < HEIGHT; y++) {
		for (x = 0; x < WIDTH; x++)
		{
			cursX = x * 2 + GBOARD_ORIGIN_X; /*GBOARD_ORIGIN_X*/;
			cursY = y + GBOARD_ORIGIN_Y; /*GBOARD_ORIGIN_Y*/;

			SetCurrentCursorPos(cursX, cursY);

			if (mapModel[y][x] == STATE_BOX)
			{
				printf("��");
			}
			else if (mapModel[y][x] == STATE_WALL)
			{
				printf("��");
			}
			else { printf("  "); }

			//draw_3_3maps(x, y, cursX, cursY);		//�迭�� 1ĭ�� ȭ���� 3*3 ũ��� ǥ��
		}
	}
	SetCurrentCursorPos((GBOARD_ORIGIN_X/*BOARD_ORIGIN_X*/ + WIDTH * 2 + 1), HEIGHT + 1);
}

//void draw_3_3maps(int x, int y, int cursX, int cursY)
//{
//	for (int yy = 0; yy < 3; ++yy) {
//		for (int xx = 0; xx < 3; ++xx)
//		{
//			SetCurrentCursorPos(cursX + xx * 2, cursY + yy);	//�׸� ��ĭ�� Ŀ�� 2���� �����ϹǷ� 2 * xx�� �ϸ� Ŀ����ġ ����
//
//			if (mapModel[y][x] == 1)
//			{
//				printf("��");
//			}
//			else { printf("  "); }
//		}
//	}
//}

int checkObject_can_go(int cursorX, int cursorY)		//���ڷ� �־��� ��ǥ�� �̵��� �� �ִ���
{
	int x = (cursorX - GBOARD_ORIGIN_X) / 2;
	int y = cursorY - GBOARD_ORIGIN_Y;

	if (mapModel[y][x] == STATE_EMPTY)
		return (1);
	if (mapModel[y][x] == STATE_ITEM_BOMB_MAX || mapModel[y][x] == STATE_ITEM_BOMB_RANGE || mapModel[y][x] == STATE_ITEM_CHARACTER_MOVE)
		return (1);
	if (mapModel[y][x] == STATE_BOMB_BOOM)
		return (1);
	return (0);
}
int checkObject_Item(int cursorX, int cursorY)			//���ڷ� �־��� ��ǥ�� �������� �ִ���
{
	int x = (cursorX - GBOARD_ORIGIN_X) / 2;
	int y = cursorY - GBOARD_ORIGIN_Y;

	if (mapModel[y][x] == STATE_ITEM_BOMB_MAX || mapModel[y][x] == STATE_ITEM_BOMB_RANGE || mapModel[y][x] == STATE_ITEM_CHARACTER_MOVE)
		return (1);
	return (0);
}

int checkObject_bomb_max_Item(int cursorX, int cursorY)			//���ڷ� �־��� ��ǥ�� �������� �ִ���
{
	int x = (cursorX - GBOARD_ORIGIN_X) / 2;
	int y = cursorY - GBOARD_ORIGIN_Y;

	if (mapModel[y][x] == STATE_ITEM_BOMB_MAX)
		return (1);
	return (0);
}
int checkObject_bomb_range_Item(int cursorX, int cursorY)			//���ڷ� �־��� ��ǥ�� �������� �ִ���
{
	int x = (cursorX - GBOARD_ORIGIN_X) / 2;
	int y = cursorY - GBOARD_ORIGIN_Y;

	if (mapModel[y][x] == STATE_ITEM_BOMB_RANGE)
		return (1);
	return (0);
}
int checkObject_character_Move_Item(int cursorX, int cursorY)			//���ڷ� �־��� ��ǥ�� �������� �ִ���
{
	int x = (cursorX - GBOARD_ORIGIN_X) / 2;
	int y = cursorY - GBOARD_ORIGIN_Y;

	if (mapModel[y][x] == STATE_ITEM_CHARACTER_MOVE)
		return (1);
	return (0);
}


int checkObject_boom(int cursorX, int cursorY)			//���ڷ� �־��� ��ǥ�� ���߹�������
{
	int x = (cursorX - GBOARD_ORIGIN_X) / 2;
	int y = (cursorY - GBOARD_ORIGIN_Y);

	if (mapModel[y][x] == STATE_BOMB_BOOM)
		return (1);
	return (0);
}
int checkObject_box(int cursorX, int cursorY)			//���ڷ� �־��� ��ǥ�� �ν� �� �ִ� ��ֹ��� �ִ���
{
	int x = (cursorX - GBOARD_ORIGIN_X) / 2;
	int y = (cursorY - GBOARD_ORIGIN_Y);

	if (mapModel[y][x] == STATE_BOX)
		return (1);
	return (0);
}
int checkObject_wall(int cursorX, int cursorY)			//���ڷ� �־��� ��ǥ�� �ν� �� ���� ��ֹ��� �ִ���
{
	int x = (cursorX - GBOARD_ORIGIN_X) / 2;
	int y = (cursorY - GBOARD_ORIGIN_Y);

	if (mapModel[y][x] == STATE_WALL)
		return (1);
	return (0);
}

int checkObject_exist_bomb(int cursorX, int cursorY)
{
	int x = (cursorX - GBOARD_ORIGIN_X) / 2;
	int y = (cursorY - GBOARD_ORIGIN_Y);

	if (mapModel[y][x] == STATE_BOMB_SETTING)
		return (1);
	return (0);
}

void gernerate_Item(int cursorX, int cursorY) // �ش� ��ǥ�� ������ ����
{
	int x = (cursorX - GBOARD_ORIGIN_X) / 2;
	int y = (cursorY - GBOARD_ORIGIN_Y);

	switch (rand() % 3)
	{
	case 0:
		mapModel[y][x] = STATE_ITEM_BOMB_MAX;
		draw_Item_bomb_max(cursorX, cursorY);
		break;
	case 1:
		mapModel[y][x] = STATE_ITEM_BOMB_RANGE;
		draw_Item_bomb_range(cursorX, cursorY);
		break;
	case 2:
		mapModel[y][x] = STATE_ITEM_CHARACTER_MOVE;
		draw_Item_chracter_move(cursorX, cursorY);
		break;
	default:
		break;
	}
}
void draw_Item_bomb_max(int cursorX, int cursorY)
{
	COORD pre = GetCurrentCursorPos();

	SetCurrentCursorPos(cursorX, cursorY);
	printf("  ");
	SetCurrentCursorPos(cursorX, cursorY);
	printf("+");

	SetCurrentCursorPos(pre.X, pre.Y);
}

void draw_Item_bomb_range(int cursorX, int cursorY) // bomb max ���� ������ ���
{
	COORD pre = GetCurrentCursorPos();

	SetCurrentCursorPos(cursorX, cursorY);
	printf("  ");
	SetCurrentCursorPos(cursorX, cursorY);
	printf("��");

	SetCurrentCursorPos(pre.X, pre.Y);
}
void draw_Item_chracter_move(int cursorX, int cursorY) // bomb max ���� ������ ���
{
	COORD pre = GetCurrentCursorPos();

	SetCurrentCursorPos(cursorX, cursorY);
	printf("  ");
	SetCurrentCursorPos(cursorX, cursorY);
	printf("��");

	SetCurrentCursorPos(pre.X, pre.Y);
}

int get_Player_starting_point_x()
{
	int x = rand() % 2;
	// (1, 1) / (7, 1) / (1, 7) / (7, 7) �� �ϳ����� ����
	if (x == 0)
	{
		x = (GBOARD_ORIGIN_X + 2) * 2;
	}
	else
	{
		x = (GBOARD_ORIGIN_X + (WIDTH - 3)) * 2;
	}

	return (x);
}

int get_Player_starting_point_y()
{
	int y = rand() % 2;
	// (1, 1) / (7, 1) / (1, 7) / (7, 7) �� �ϳ����� ����
	if (y == 0)
	{
		y = (GBOARD_ORIGIN_Y + 2);
	}
	else
	{
		y = (GBOARD_ORIGIN_Y + (HEIGHT - 3));
	}

	return (y);
}

void set_Bomb(int arrX, int arrY)
{
	COORD pre = GetCurrentCursorPos();

	int cursorX = arrX * 2 + GBOARD_ORIGIN_X;
	int cursorY = arrY + GBOARD_ORIGIN_Y;

	mapModel[arrY][arrX] = STATE_BOMB_SETTING;
	SetCurrentCursorPos(cursorX, cursorY);
	printf("");
	printf("��");

	SetCurrentCursorPos(pre.X, pre.Y);
}

void set_Empty(int arrX, int arrY)				//�ش� ��ǥ �������� �����
{
	COORD pre = GetCurrentCursorPos();

	int cursorX = arrX * 2 + GBOARD_ORIGIN_X;
	int cursorY = arrY + GBOARD_ORIGIN_Y;

	mapModel[arrY][arrX] = STATE_EMPTY;
	SetCurrentCursorPos(cursorX, cursorY);
	printf("  ");

	SetCurrentCursorPos(pre.X, pre.Y);
}

void set_Bomb_Boom(int arrX, int arrY)
{
	COORD pre = GetCurrentCursorPos();

	int cursorX = arrX * 2 + GBOARD_ORIGIN_X;
	int cursorY = arrY + GBOARD_ORIGIN_Y;

	mapModel[arrY][arrX] = STATE_BOMB_BOOM;
	SetCurrentCursorPos(cursorX, cursorY);
	printf("  ");
	SetCurrentCursorPos(cursorX, cursorY);
	printf("��");

	SetCurrentCursorPos(pre.X, pre.Y);
}

int checkPlayer_Killed_NPC(int npcCurPosX, int npcCurPosY, int PlayerCurPosX, int PlayerCurPosY) {
	if (npcCurPosX == PlayerCurPosX && npcCurPosY == PlayerCurPosY) {
		return (1);
	}
	return (0);
}

void set_NPC_Warning(int arrX, int arrY)		//�ش� ��ǥ�� NPC Warning update�ϱ�
{
	mapModel[arrY][arrX] = STATE_NPC_WARNING;
}


int cursorX_to_arrX(int cursorX)
{
	return ((cursorX - GBOARD_ORIGIN_X) / 2);
}
int cursorY_to_arrY(int cursorY)
{
	return (cursorY - GBOARD_ORIGIN_Y);
}

int arrX_to_cursorX(int arrX)
{
	return ((arrX * 2) + GBOARD_ORIGIN_X);
}
int arrY_to_cursorY(int arrY)
{
	return (arrY + GBOARD_ORIGIN_Y);
}

int check_over_GameBoard_Width(int arrX)
{
	if (0 <= arrX && arrX < WIDTH)
		return (0);
	return (1);
}
int check_over_GameBoard_HEIGHT(int arrY)
{
	if (0 <= arrY && arrY < HEIGHT)
		return (0);
	return (1);
}



// ���� �ʿ�
//void npc_Warning_update(int arrX, int arrY, Bomb* newbomb)
//{
//	int x = newbomb->x;
//	int y = newbomb->y;
//	int len = newbomb->len;
//
//
//	for (int i = 1; i <= len; i++)
//	{
//		if (check_over_GameBoard_HEIGHT(y - i))
//			break;
//		else if (checkObject_can_go(arrX_to_cursorX(x), arrY_to_cursorY(y - i))) {
//			set_Bomb_Boom(x, y - i);
//			w = getnode_BOOM(x, y - i, time);
//			insertitem_BOOM(w);
//		}
//		else if (checkObject_box(arrX_to_cursorX(x), arrY_to_cursorY(y - i))) { //���� ���ڶ��
//			set_Empty(x, y - i);
//			gernerate_Item(arrX_to_cursorX(x), arrY_to_cursorY(y - i));
//			break;          // ���� ���� �ڷ� ��ź�� ������ ������ �ʰ�
//		}
//		else if (checkObject_Item(arrX_to_cursorX(x), arrY_to_cursorY(y - i))) { //�������� �ִٸ�
//			set_Empty(x, y - i);     //������ �ı�, �������� ����
//		}
//		else if (checkObject_exist_bomb(arrX_to_cursorX(x), arrY_to_cursorY(y - i))) { //���� �ٸ� ��ź�� �ִٸ�
//			?BombSwich_On(x, y - i); //���ȣ��
//			break;
//		}
//		else
//			;
//	}
//	//�Ʒ��� ������ ���� �ȱ�
//	for (int i = 1; i <= len; i++)
//	{
//		if (check_over_GameBoard_HEIGHT(y + i))
//			break;
//		else if (checkObject_can_go(arrX_to_cursorX(x), arrY_to_cursorY(y + i))) {
//			set_Bomb_Boom(x, y + i);
//			w = getnode_BOOM(x, y + i, time);
//			insertitem_BOOM(w);
//		}
//		else if (checkObject_box(arrX_to_cursorX(x), arrY_to_cursorY(y + i))) { //���� ���ڶ��
//			set_Empty(x, y + i);
//			gernerate_Item(arrX_to_cursorX(x), arrY_to_cursorY(y + i));
//			break;          // ���� ���� �ڷ� ��ź�� ������ ������ �ʰ�
//		}
//		else if (checkObject_Item(arrX_to_cursorX(x), arrY_to_cursorY(y + i))) { //�������� �ִٸ�
//			set_Empty(x, y + i);     //������ �ı�, �������� ����
//		}
//		else if (checkObject_exist_bomb(arrX_to_cursorX(x), arrY_to_cursorY(y + i))) { //���� �ٸ� ��ź�� �ִٸ�
//			?BombSwich_On(x, y + i); //���ȣ��
//			break;
//		}
//		else
//			;
//	}
//	// �·� ������ ���� �ȱ�
//	for (int i = 1; i <= len; i++)
//	{
//		if (check_over_GameBoard_Width(x - i))
//			break;
//		else if (checkObject_can_go(arrX_to_cursorX(x - i), arrY_to_cursorY(y))) {
//			set_Bomb_Boom(x - i, y);
//			w = getnode_BOOM(x - i, y, time);
//			insertitem_BOOM(w);
//		}
//		else if (checkObject_box(arrX_to_cursorX(x - i), arrY_to_cursorY(y))) { //���� ���ڶ��
//			set_Empty(x - i, y);
//			gernerate_Item(arrX_to_cursorX(x - i), arrY_to_cursorY(y));
//			break;          // ���� ���� �ڷ� ��ź�� ������ ������ �ʰ�
//		}
//		else if (checkObject_Item(arrX_to_cursorX(x - i), arrY_to_cursorY(y))) { //�������� �ִٸ�
//			set_Empty(x - i, y);     //������ �ı�, �������� ����
//		}
//		else if (checkObject_exist_bomb(arrX_to_cursorX(x - i), arrY_to_cursorY(y))) { //���� �ٸ� ��ź�� �ִٸ�
//			?BombSwich_On(x - i, y); //���ȣ��
//			break;
//		}
//		else
//			;
//	}
//	// ��� ������ ���� �ȱ�
//	for (int i = 1; i <= len; i++)
//	{
//		if (check_over_GameBoard_Width(x + i))
//			break;
//		else if (checkObject_can_go(arrX_to_cursorX(x + i), arrY_to_cursorY(y))) {
//			set_Bomb_Boom(x + i, y);
//			w = getnode_BOOM(x + i, y, time);
//			insertitem_BOOM(w);
//		}
//		else if (checkObject_box(arrX_to_cursorX(x + i), arrY_to_cursorY(y))) { //���� ���ڶ��
//			set_Empty(x + i, y);
//			gernerate_Item(arrX_to_cursorX(x + i), arrY_to_cursorY(y));
//			break;          // ���� ���� �ڷ� ��ź�� ������ ������ �ʰ�
//		}
//		else if (checkObject_Item(arrX_to_cursorX(x + i), arrY_to_cursorY(y))) { //�������� �ִٸ�
//			set_Empty(x + i, y);     //������ �ı�, �������� ����
//		}
//		else if (checkObject_exist_bomb(arrX_to_cursorX(x + i), arrY_to_cursorY(y))) { //���� �ٸ� ��ź�� �ִٸ�
//			?BombSwich_On(x + i, y); //���ȣ��
//			break;
//		}
//		else
//			;
//	}
//}


// 11�� 20�� map_box



Map_box_head* generate_map_box_head()
{
	Map_box_head* new_map_box_head = (Map_box_head*)malloc(sizeof(Map_box_head));
	new_map_box_head->next = NULL;

	return (new_map_box_head);
}

void insert_map_box_struct(Map_box_head* head, int x, int y)
{
	if (head->next == NULL)
	{
		Map_box* new_map_box = (Map_box*)malloc(sizeof(Map_box));
		new_map_box->x = x;
		new_map_box->y = y;
		new_map_box->next = NULL;

		head->next = new_map_box;
	}
	else
	{
		Map_box* tmp = head->next;

		while (tmp->next != NULL)
		{
			if (tmp->x == x && tmp->y == y)
				return;
			tmp = tmp->next;
		}

		Map_box* new_map_box = (Map_box*)malloc(sizeof(Map_box));
		new_map_box->x = x;
		new_map_box->y = y;
		new_map_box->next = NULL;

		tmp->next = new_map_box;
	}

}

void remove_generate_item_all_map_box_struct(Map_box_head* head)
{
	Map_box* tmp = head->next;
	Map_box* previous;


	//SetCurrentCursorPos(40, 18);
	//Map_box* tmp111 = map_box_head->next;
	//while (tmp111)
	//{
	//	printf("x = %d , y = %d\n", tmp111->x, tmp111->y);
	//	tmp111 = tmp111->next;
	//}


	while (tmp != NULL)
	{
		head->next = NULL;

		set_Empty(tmp->x, tmp->y);
		gernerate_Item(arrX_to_cursorX(tmp->x), arrY_to_cursorY(tmp->y));
		previous = tmp;
		tmp = tmp->next;
		free(previous);
	}
}