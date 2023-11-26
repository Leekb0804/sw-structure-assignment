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
int PlayerCurPosX, PlayerCurPosY; // 플레이어 현재 좌표
int PlayerState;           // 플레이어 현재 상태

int bomb_max;
int player_bomb_len;
int bomb_exist_count;

int npc_bomb_max;
int npc1_bomb_exist_count;
int npc2_bomb_exist_count;
int npc3_bomb_exist_count;

typedef struct Player // 플레이어 구조체
{
	int Bomb_Count;
	int Span;
}Player;

void ShowPlayerBlock();
void DeletePlayerBlock();


void PlayerMoveLeft(); // 플레이어 이동 (좌)
void PlayerMoveRight(); // 플레이어 이동 (우)
void PlayerMoveDown(); // 플레이어 이동 (하)
void PlayerMoveUp(); // 플레이어 이동 (상)
int DetectCollision(int posX, int posY); // 임시로 장애물 GameBoardInfo로 설정하여 감지

void SetPlayerBomb(); // 폭탄놓는 함수
int CheckPlayerState();

void ProcessKeyInput();

void PlayerControl();

int check_player_move_span();

void apply_Item(int cursorX, int cursorY);


#endif