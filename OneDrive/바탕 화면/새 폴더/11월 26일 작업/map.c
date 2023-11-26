#include "map.h"

#include "define_state.h"

#include <stdio.h>		//디버그용
#include <stdlib.h>		//rand(), srand() 함수
#include <time.h>		//time(NULL) 사용하기 위해

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

int NPCmapModel[HEIGHT][WIDTH] = { // npc가 물풍선 보고 피할 단순 배열
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

//아래와 같은 형태
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

	// 중복된 값을 확인하기 위해 test[10]배열을 만듦
	// random_num 이 하나 나오면 test배열을 확인
	// test[random_num]의 값이 1이 아니면 
	// test[random_num]의 값에 1대입 후 num배열에 random_num 값 추가
	// num 배열을 다 채울때 까지 위 과정 반복

	while (i < 5) {
		random_num = (rand() % 9);		//0 ~ 8 중에 랜덤한 수
		if (test[random_num] == 0)
		{
			test[random_num] = 1;
			num[i] = random_num;
			++i;
		}
	}

	//디버그용
	/*for (i = 0; i < 5; ++i)
		printf(" %d", num[i]);
	printf("\n");*/

	return num;
}

void resetMap()				// 왼쪽 위, 왼쪽 아래, 오른쪽 위, 오른쪽 아래 처음 시작할때, 십자가로 움직일 수 있도록 초기화
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

void generateMap()			//맵생성
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
	map의 구역을
	1 2 3
	4 5 6
	7 8 9 로 나누었을때
	*/
	// 4번구역 채우기
	for (int i = 0; i < 5; ++i)
	{
		mapModel[(num[i] / 3) + 1][3 + num[i] % 3 + 1] = STATE_BOX;
	}

	//2번구역 채우기
	num = output_random_5_num_arr();
	for (int i = 0; i < 5; ++i)
	{
		mapModel[3 + (num[i] / 3) + 1][num[i] % 3 + 1] = STATE_BOX;
	}
	free(num);

	//5번구역 채우기
	num = output_random_5_num_arr();
	for (int i = 0; i < 5; ++i)
	{
		mapModel[3 + (num[i] / 3) + 1][3 + num[i] % 3 + 1] = STATE_BOX;
	}
	free(num);

	//8번구역 채우기
	num = output_random_5_num_arr();
	for (int i = 0; i < 5; ++i)
	{
		mapModel[3 + (num[i] / 3) + 1][6 + num[i] % 3 + 1] = STATE_BOX;
	}
	free(num);

	//6번구역 채우기
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

void drawMaps()		//맵을 화면에 출력
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
				printf("■");
			}
			else if (mapModel[y][x] == STATE_WALL)
			{
				printf("▩");
			}
			else { printf("  "); }

			//draw_3_3maps(x, y, cursX, cursY);		//배열의 1칸을 화면의 3*3 크기로 표현
		}
	}
	SetCurrentCursorPos((GBOARD_ORIGIN_X/*BOARD_ORIGIN_X*/ + WIDTH * 2 + 1), HEIGHT + 1);
}

//void draw_3_3maps(int x, int y, int cursX, int cursY)
//{
//	for (int yy = 0; yy < 3; ++yy) {
//		for (int xx = 0; xx < 3; ++xx)
//		{
//			SetCurrentCursorPos(cursX + xx * 2, cursY + yy);	//네모 한칸이 커서 2개를 차지하므로 2 * xx를 하며 커서위치 변경
//
//			if (mapModel[y][x] == 1)
//			{
//				printf("■");
//			}
//			else { printf("  "); }
//		}
//	}
//}

int checkObject_can_go(int cursorX, int cursorY)		//인자로 주어진 좌표로 이동할 수 있는지
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
int checkObject_Item(int cursorX, int cursorY)			//인자로 주어진 좌표에 아이템이 있는지
{
	int x = (cursorX - GBOARD_ORIGIN_X) / 2;
	int y = cursorY - GBOARD_ORIGIN_Y;

	if (mapModel[y][x] == STATE_ITEM_BOMB_MAX || mapModel[y][x] == STATE_ITEM_BOMB_RANGE || mapModel[y][x] == STATE_ITEM_CHARACTER_MOVE)
		return (1);
	return (0);
}

int checkObject_bomb_max_Item(int cursorX, int cursorY)			//인자로 주어진 좌표에 아이템이 있는지
{
	int x = (cursorX - GBOARD_ORIGIN_X) / 2;
	int y = cursorY - GBOARD_ORIGIN_Y;

	if (mapModel[y][x] == STATE_ITEM_BOMB_MAX)
		return (1);
	return (0);
}
int checkObject_bomb_range_Item(int cursorX, int cursorY)			//인자로 주어진 좌표에 아이템이 있는지
{
	int x = (cursorX - GBOARD_ORIGIN_X) / 2;
	int y = cursorY - GBOARD_ORIGIN_Y;

	if (mapModel[y][x] == STATE_ITEM_BOMB_RANGE)
		return (1);
	return (0);
}
int checkObject_character_Move_Item(int cursorX, int cursorY)			//인자로 주어진 좌표에 아이템이 있는지
{
	int x = (cursorX - GBOARD_ORIGIN_X) / 2;
	int y = cursorY - GBOARD_ORIGIN_Y;

	if (mapModel[y][x] == STATE_ITEM_CHARACTER_MOVE)
		return (1);
	return (0);
}


int checkObject_boom(int cursorX, int cursorY)			//인자로 주어진 좌표가 폭발범위인지
{
	int x = (cursorX - GBOARD_ORIGIN_X) / 2;
	int y = (cursorY - GBOARD_ORIGIN_Y);

	if (mapModel[y][x] == STATE_BOMB_BOOM)
		return (1);
	return (0);
}
int checkObject_box(int cursorX, int cursorY)			//인자로 주어진 좌표에 부실 수 있는 장애물이 있는지
{
	int x = (cursorX - GBOARD_ORIGIN_X) / 2;
	int y = (cursorY - GBOARD_ORIGIN_Y);

	if (mapModel[y][x] == STATE_BOX)
		return (1);
	return (0);
}
int checkObject_wall(int cursorX, int cursorY)			//인자로 주어진 좌표에 부실 수 없는 장애물이 있는지
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

void gernerate_Item(int cursorX, int cursorY) // 해당 좌표에 아이템 생성
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

void draw_Item_bomb_range(int cursorX, int cursorY) // bomb max 증가 아이템 출력
{
	COORD pre = GetCurrentCursorPos();

	SetCurrentCursorPos(cursorX, cursorY);
	printf("  ");
	SetCurrentCursorPos(cursorX, cursorY);
	printf("↔");

	SetCurrentCursorPos(pre.X, pre.Y);
}
void draw_Item_chracter_move(int cursorX, int cursorY) // bomb max 증가 아이템 출력
{
	COORD pre = GetCurrentCursorPos();

	SetCurrentCursorPos(cursorX, cursorY);
	printf("  ");
	SetCurrentCursorPos(cursorX, cursorY);
	printf("▶");

	SetCurrentCursorPos(pre.X, pre.Y);
}

int get_Player_starting_point_x()
{
	int x = rand() % 2;
	// (1, 1) / (7, 1) / (1, 7) / (7, 7) 중 하나에서 시작
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
	// (1, 1) / (7, 1) / (1, 7) / (7, 7) 중 하나에서 시작
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
	printf("⊙");

	SetCurrentCursorPos(pre.X, pre.Y);
}

void set_Empty(int arrX, int arrY)				//해당 좌표 공백으로 만들기
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
	printf("♨");

	SetCurrentCursorPos(pre.X, pre.Y);
}

int checkPlayer_Killed_NPC(int npcCurPosX, int npcCurPosY, int PlayerCurPosX, int PlayerCurPosY) {
	if (npcCurPosX == PlayerCurPosX && npcCurPosY == PlayerCurPosY) {
		return (1);
	}
	return (0);
}

void set_NPC_Warning(int arrX, int arrY)		//해당 좌표에 NPC Warning update하기
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



// 수정 필요
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
//		else if (checkObject_box(arrX_to_cursorX(x), arrY_to_cursorY(y - i))) { //나무 상자라면
//			set_Empty(x, y - i);
//			gernerate_Item(arrX_to_cursorX(x), arrY_to_cursorY(y - i));
//			break;          // 나무 상자 뒤로 폭탄의 범위가 퍼지지 않게
//		}
//		else if (checkObject_Item(arrX_to_cursorX(x), arrY_to_cursorY(y - i))) { //아이템이 있다면
//			set_Empty(x, y - i);     //아이템 파괴, 공백으로 변경
//		}
//		else if (checkObject_exist_bomb(arrX_to_cursorX(x), arrY_to_cursorY(y - i))) { //만약 다른 폭탄이 있다면
//			?BombSwich_On(x, y - i); //재귀호출
//			break;
//		}
//		else
//			;
//	}
//	//아래로 터지는 범위 훑기
//	for (int i = 1; i <= len; i++)
//	{
//		if (check_over_GameBoard_HEIGHT(y + i))
//			break;
//		else if (checkObject_can_go(arrX_to_cursorX(x), arrY_to_cursorY(y + i))) {
//			set_Bomb_Boom(x, y + i);
//			w = getnode_BOOM(x, y + i, time);
//			insertitem_BOOM(w);
//		}
//		else if (checkObject_box(arrX_to_cursorX(x), arrY_to_cursorY(y + i))) { //나무 상자라면
//			set_Empty(x, y + i);
//			gernerate_Item(arrX_to_cursorX(x), arrY_to_cursorY(y + i));
//			break;          // 나무 상자 뒤로 폭탄의 범위가 퍼지지 않게
//		}
//		else if (checkObject_Item(arrX_to_cursorX(x), arrY_to_cursorY(y + i))) { //아이템이 있다면
//			set_Empty(x, y + i);     //아이템 파괴, 공백으로 변경
//		}
//		else if (checkObject_exist_bomb(arrX_to_cursorX(x), arrY_to_cursorY(y + i))) { //만약 다른 폭탄이 있다면
//			?BombSwich_On(x, y + i); //재귀호출
//			break;
//		}
//		else
//			;
//	}
//	// 좌로 터지는 범위 훑기
//	for (int i = 1; i <= len; i++)
//	{
//		if (check_over_GameBoard_Width(x - i))
//			break;
//		else if (checkObject_can_go(arrX_to_cursorX(x - i), arrY_to_cursorY(y))) {
//			set_Bomb_Boom(x - i, y);
//			w = getnode_BOOM(x - i, y, time);
//			insertitem_BOOM(w);
//		}
//		else if (checkObject_box(arrX_to_cursorX(x - i), arrY_to_cursorY(y))) { //나무 상자라면
//			set_Empty(x - i, y);
//			gernerate_Item(arrX_to_cursorX(x - i), arrY_to_cursorY(y));
//			break;          // 나무 상자 뒤로 폭탄의 범위가 퍼지지 않게
//		}
//		else if (checkObject_Item(arrX_to_cursorX(x - i), arrY_to_cursorY(y))) { //아이템이 있다면
//			set_Empty(x - i, y);     //아이템 파괴, 공백으로 변경
//		}
//		else if (checkObject_exist_bomb(arrX_to_cursorX(x - i), arrY_to_cursorY(y))) { //만약 다른 폭탄이 있다면
//			?BombSwich_On(x - i, y); //재귀호출
//			break;
//		}
//		else
//			;
//	}
//	// 우로 터지는 범위 훑기
//	for (int i = 1; i <= len; i++)
//	{
//		if (check_over_GameBoard_Width(x + i))
//			break;
//		else if (checkObject_can_go(arrX_to_cursorX(x + i), arrY_to_cursorY(y))) {
//			set_Bomb_Boom(x + i, y);
//			w = getnode_BOOM(x + i, y, time);
//			insertitem_BOOM(w);
//		}
//		else if (checkObject_box(arrX_to_cursorX(x + i), arrY_to_cursorY(y))) { //나무 상자라면
//			set_Empty(x + i, y);
//			gernerate_Item(arrX_to_cursorX(x + i), arrY_to_cursorY(y));
//			break;          // 나무 상자 뒤로 폭탄의 범위가 퍼지지 않게
//		}
//		else if (checkObject_Item(arrX_to_cursorX(x + i), arrY_to_cursorY(y))) { //아이템이 있다면
//			set_Empty(x + i, y);     //아이템 파괴, 공백으로 변경
//		}
//		else if (checkObject_exist_bomb(arrX_to_cursorX(x + i), arrY_to_cursorY(y))) { //만약 다른 폭탄이 있다면
//			?BombSwich_On(x + i, y); //재귀호출
//			break;
//		}
//		else
//			;
//	}
//}


// 11월 20일 map_box



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