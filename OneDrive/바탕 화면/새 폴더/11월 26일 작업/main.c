#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include "map.h"
#include "cursor.h"     //getcursor, setcursor 함수들을 파일로 따로 뺐음
#include "player.h"

#include "bomb.h"

#include "Test_Moving.h"
#include "calculatorDST.h"


unsigned long long start_game_time;
unsigned long long current_game_time;

int player_item_range;

extern BombHead* bombHead;
extern BOOMHead* boomhead;

extern int npcCurPosX, npcCurPosY;
extern unsigned long long NPC_current_Time;

extern Map_box_head* map_box_head;             //폭탄이 모두 터진 후 박스를 없애기 위한 맵 박스 구조체 배열의 헤드 선언

int main(void)
{

	RemoveCursor();

	start_game_time = clock();
	//bombHead1 = makeBombHead();
	//bombHead2 = makeBombHead();

	player_item_range = 1;


	generateMap();
	drawMaps();

	PlayerState = 1;
	PlayerCurPosX = get_Player_starting_point_x();
	PlayerCurPosY = 8;  //get_Player_starting_point_y();

	npcCurPosX = 2 * 2;
	npcCurPosY = 2;

	bombHead = (BombHead*)malloc(sizeof(bombHead));
	bombHead->next = NULL;
	boomhead = (BOOMHead*)malloc(sizeof(BOOMHead));
	boomhead->next = NULL;


	map_box_head = generate_map_box_head();

	NPC_current_Time = 0;

	while (1)
	{
		current_game_time = clock();

		TimeCheck();
		remove_generate_item_all_map_box_struct(map_box_head);
		TimeCheck_BOOM();

		if (CheckPlayerState() == 1)
			break;
		if (CheckNPCState() == 1)
			break;

		PlayerControl();

		if (CheckPlayerState() == 1)
			break;

		NpcMoving();

		if (CheckNPCState() == 1)
			break;

		//print_npc_x_y();
	}

	while (1)
	{
		Sleep(10000);
	}

	return (0);
}