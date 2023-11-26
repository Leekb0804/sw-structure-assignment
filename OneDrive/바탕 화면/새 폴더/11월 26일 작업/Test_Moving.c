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
	printf("��");
	SetCurrentCursorPos(curPos.X, curPos.Y);
} // ������ �Ⱦ�

void ShowNpcBlock()
{
	SetCurrentCursorPos(npcCurPosX, npcCurPosY);
	printf("��");
}

void DeleteBlock()
{

	SetCurrentCursorPos(npcCurPosX, npcCurPosY);
	printf("  ");
}

int NPC_moveLeft() {

	if (mapModel[cursorY_to_arrY(npcCurPosY)][cursorX_to_arrX(npcCurPosX)] == STATE_BOMB_SETTING)
		printf("��");
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
		printf("��");
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
		printf("��");
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
		printf("��");
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
}// ������ �Ⱦ�
int FindDstY() {
	srand((unsigned int)time(NULL));
	int y = rand() % 9;
	return y;
}// ������ �Ⱦ�

int NpcMoving()
{
	int preX = 0, preY = 0;
	int npcX, npcY;

	npcX = npcCurPosX / 2;
	npcY = npcCurPosY;

	int kill_Mode = ShortestDistance(npcX, npcY); // ���⼭ one_srt_dist �迭�� ������� (�� �迭�� ���� NPC�� ������)

	int dx = npcX;
	int dy = npcY;

	SetCurrentCursorPos(npcCurPosX, npcCurPosY);


	while (1) { //�� while�� �ȿ� �ִ� clock�������� �Ű澲�� �ʾƵ� ��, ���� �׽�Ʈ��, �Ƹ� 1ĭ�� �������� �ϴϱ� while ����� ����� ���

		preX = dx;
		preY = dy;

		if (one_srt_dist[dy][dx + 1] == 1) { // NPC ������ġ ���� one_srt_dist�� �������� 1�̶�� (�����ִ±�)
			one_srt_dist[dy][dx] = 0; // ���� ��ġ�� one_srt_dist�� 0���� �ʱ�ȭ �ϰ�

			if (current_game_time - NPC_current_Time > flagTime) {
				NPC_current_Time = clock();
				NPC_moveRight(); //���������� �̵�
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

		if (dx == dstX && dy == dstY && kill_Mode == 0) { // ��ǥ ��ġ�� �����ϸ� mapModel�� �����¿츦 1�� �ʱ�ȭ �ϰ� ���� ������ (�ӽ� ��ǳ��)

			if (current_game_time - NPC_current_Time > flagTime) {
				if (npc1_bomb_exist_count < npc_bomb_max) {
					npc1_set_bomb();
				}
				NPCmapModel[dstY][dstX] = STATE_NPC_WARNING;
				NPC_current_Time = clock();
				if (dx < preX) {
					NPC_moveRight();
					/*SetCurrentCursorPos(npcCurPosX - 2, npcCurPosY);
					printf("��");*/
				}
				else if (dx > preX) {
					NPC_moveLeft();
					/*SetCurrentCursorPos(npcCurPosX + 2, npcCurPosY);
					printf("��");*/
				}
				else if (dy > preY) {
					NPC_moveUp();
					/*SetCurrentCursorPos(npcCurPosX, npcCurPosY + 1);
					printf("��");*/
				}
				else if (dy < preY) {
					NPC_moveDown();
					/*SetCurrentCursorPos(npcCurPosX, npcCurPosY - 1);
					printf("��");*/
				}
			}
		}
		return 0;
	}
}

int CheckNPCState()
{
	// ���� �÷��̾� ��ǥ�� �������� ���� PlayerState ������Ʈ
	// ������Ʈ�� PlayerState ���� �°� ó��

	////////////�߰�
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