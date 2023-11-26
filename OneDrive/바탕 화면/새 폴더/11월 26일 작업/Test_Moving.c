#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "Test_Moving.h"
#include "cursor.h"
#include "map.h"
#include "calculatorDST.h"
#include "player.h"

#include "bomb.h"

#define flagTime 800

int npcCurPosX, npcCurPosY;
unsigned long long NPC_current_Time;
extern unsigned long long current_game_time;

extern int npc1_bomb_exist_count = 0;
extern int npc2_bomb_exist_count = 0;
extern int npc3_bomb_exist_count = 0;
extern int npc_bomb_max = 1;

void ShowNpcBlock();

void SetNpcPos() {

	npcCurPosX = 2;
	npcCurPosY = 8;

	SetCurrentCursorPos(npcCurPosX, npcCurPosY);

	ShowNpcBlock();
}

void block_break() {


	SetCurrentCursorPos(npcCurPosX + 2, npcCurPosY);
	printf("  ");
	SetCurrentCursorPos(npcCurPosX, npcCurPosY);

	SetCurrentCursorPos(npcCurPosX - 2, npcCurPosY);
	printf("  ");
	SetCurrentCursorPos(npcCurPosX, npcCurPosY);

	SetCurrentCursorPos(npcCurPosX, npcCurPosY + 1);
	printf("  ");
	SetCurrentCursorPos(npcCurPosX, npcCurPosY);

	SetCurrentCursorPos(npcCurPosX, npcCurPosY - 1);
	printf("  ");
	SetCurrentCursorPos(npcCurPosX, npcCurPosY);
}

void ShowDstBlock(int x, int y) {
	COORD curPos = GetCurrentCursorPos();
	SetCurrentCursorPos(x * 2, y);
	printf("☆");
	SetCurrentCursorPos(curPos.X, curPos.Y);
} // 지금은 안씀

void ShowNpcBlock()
{
	SetCurrentCursorPos(npcCurPosX, npcCurPosY);
	printf("★");
}

void DeleteBlock()
{

	SetCurrentCursorPos(npcCurPosX, npcCurPosY);
	printf("  ");
}

int NPC_moveLeft() {

	if (mapModel[cursorY_to_arrY(npcCurPosY)][cursorX_to_arrX(npcCurPosX)] == STATE_BOMB_SETTING)
		printf("⊙");
	else
		DeleteBlock();
	npcCurPosX -= 2;
	set_Empty(npcCurPosX / 2, npcCurPosY);
	SetCurrentCursorPos(npcCurPosX, npcCurPosY);
	ShowNpcBlock();
	return 0;

}

int NPC_moveRight() {

	if (mapModel[cursorY_to_arrY(npcCurPosY)][cursorX_to_arrX(npcCurPosX)] == STATE_BOMB_SETTING)
		printf("⊙");
	else
		DeleteBlock();
	npcCurPosX += 2;
	set_Empty(npcCurPosX / 2, npcCurPosY);
	SetCurrentCursorPos(npcCurPosX, npcCurPosY);
	ShowNpcBlock();

	return 0;

}

int NPC_moveUp() {

	if (mapModel[cursorY_to_arrY(npcCurPosY)][cursorX_to_arrX(npcCurPosX)] == STATE_BOMB_SETTING)
		printf("⊙");
	else
		DeleteBlock();
	npcCurPosY -= 1;
	set_Empty(npcCurPosX / 2, npcCurPosY);
	SetCurrentCursorPos(npcCurPosX, npcCurPosY);
	ShowNpcBlock();

	return 0;
}

int NPC_moveDown() {

	if (mapModel[cursorY_to_arrY(npcCurPosY)][cursorX_to_arrX(npcCurPosX)] == STATE_BOMB_SETTING)
		printf("⊙");
	else
		DeleteBlock();
	npcCurPosY += 1;
	set_Empty(npcCurPosX / 2, npcCurPosY);
	SetCurrentCursorPos(npcCurPosX, npcCurPosY);
	ShowNpcBlock();

	return 0;
}

int FindDstX() {
	srand((unsigned int)time(NULL));
	int x = rand() % 9;
	return x;
}// 지금은 안씀
int FindDstY() {
	srand((unsigned int)time(NULL));
	int y = rand() % 9;
	return y;
}// 지금은 안씀

int NpcMoving()
{
	int preX = 0, preY = 0;
	int npcX, npcY;

	npcX = npcCurPosX / 2;
	npcY = npcCurPosY;

	int kill_Mode = ShortestDistance(npcX, npcY); // 여기서 one_srt_dist 배열을 만들어줌 (이 배열을 보고 NPC가 움직임)

	int dx = npcX;
	int dy = npcY;

	SetCurrentCursorPos(npcCurPosX, npcCurPosY);


	while (1) { //이 while문 안에 있는 clock변수들은 신경쓰지 않아도 됨, 아직 테스트중, 아마 1칸씩 움직여야 하니까 while 지우는 방법도 고려

		preX = dx;
		preY = dy;

		if (one_srt_dist[dy][dx + 1] == 1) { // NPC 현재위치 기준 one_srt_dist의 오른쪽이 1이라면 (갈수있는길)
			one_srt_dist[dy][dx] = 0; // 현재 위치의 one_srt_dist를 0으로 초기화 하고

			if (current_game_time - NPC_current_Time > flagTime) {
				NPC_current_Time = clock();
				NPC_moveRight(); //오른쪽으로 이동
			}
			dx += 1;
		}
		else if (one_srt_dist[dy][dx - 1] == 1) {
			one_srt_dist[dy][dx] = 0;

			if (current_game_time - NPC_current_Time > flagTime) {
				NPC_current_Time = clock();
				NPC_moveLeft();
			}
			dx -= 1;
		}
		else if (one_srt_dist[dy + 1][dx] == 1) {
			one_srt_dist[dy][dx] = 0;

			if (current_game_time - NPC_current_Time > flagTime) {
				NPC_current_Time = clock();
				NPC_moveDown();
			}
			dy += 1;
		}
		else if (one_srt_dist[dy - 1][dx] == 1) {
			one_srt_dist[dy][dx] = 0;

			if (current_game_time - NPC_current_Time > flagTime) {
				NPC_current_Time = clock();
				NPC_moveUp();
			}
			dy -= 1;
		}

		if (dx == dstX && dy == dstY && kill_Mode == 0) { // 목표 위치에 도착하면 mapModel의 상하좌우를 1로 초기화 하고 블럭을 지워줌 (임시 물풍선)

			if (current_game_time - NPC_current_Time > flagTime) {
				if (npc1_bomb_exist_count < npc_bomb_max) {
					npc1_set_bomb();
				}
				NPCmapModel[dstY][dstX] = STATE_NPC_WARNING;
				NPC_current_Time = clock();
				if (dx < preX) {
					NPC_moveRight();
					/*SetCurrentCursorPos(npcCurPosX - 2, npcCurPosY);
					printf("⊙");*/
				}
				else if (dx > preX) {
					NPC_moveLeft();
					/*SetCurrentCursorPos(npcCurPosX + 2, npcCurPosY);
					printf("⊙");*/
				}
				else if (dy > preY) {
					NPC_moveUp();
					/*SetCurrentCursorPos(npcCurPosX, npcCurPosY + 1);
					printf("⊙");*/
				}
				else if (dy < preY) {
					NPC_moveDown();
					/*SetCurrentCursorPos(npcCurPosX, npcCurPosY - 1);
					printf("⊙");*/
				}
			}
		}
		return 0;
	}
}

int CheckNPCState()
{
	// 현재 플레이어 좌표의 정보값에 따라 PlayerState 업데이트
	// 업데이트된 PlayerState 값에 맞게 처리

	////////////추가
	if (checkObject_boom(npcCurPosX, npcCurPosY) == 1)
	{
		SetCurrentCursorPos(3, 16);
		//printf("NPC down    Game Over!\n");
		return (1);
	}
	if (checkPlayer_Killed_NPC(npcCurPosX, npcCurPosY, PlayerCurPosX, PlayerCurPosY) == 1) {
		SetCurrentCursorPos(3, 16);
		//printf("Player down    Game Over!\n\n\n");

		/*for (int i = 0; i < WIDTH; i++) {
			for (int j = 0; j < HEIGHT; j++) {
				printf("%4d", mapModel[i][j]);
			}
			printf("\n");
		}*/

		return (1);
	}
	return (0);
}