#ifndef __PLAYERKJH_H_
#define __PLAYERKJH_H_

#include <stdio.h>
#include <windows.h>

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define SPACE_BAR 32

int block_id;
int PlayerCurPosX, PlayerCurPosY; // �÷��̾� ���� ��ǥ
int PlayerState;           // �÷��̾� ���� ����

int bomb_max;
int player_bomb_len;
int bomb_exist_count;

int npc_bomb_max;
int npc1_bomb_exist_count;
int npc2_bomb_exist_count;
int npc3_bomb_exist_count;

typedef struct Player // �÷��̾� ����ü
{
	int Bomb_Count;
	int Span;
}Player;

void ShowPlayerBlock();
void DeletePlayerBlock();


void PlayerMoveLeft(); // �÷��̾� �̵� (��)
void PlayerMoveRight(); // �÷��̾� �̵� (��)
void PlayerMoveDown(); // �÷��̾� �̵� (��)
void PlayerMoveUp(); // �÷��̾� �̵� (��)
int DetectCollision(int posX, int posY); // �ӽ÷� ��ֹ� GameBoardInfo�� �����Ͽ� ����

void SetPlayerBomb(); // ��ź���� �Լ�
int CheckPlayerState();

void ProcessKeyInput();

void PlayerControl();

int check_player_move_span();

void apply_Item(int cursorX, int cursorY);


#endif