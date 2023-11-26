#ifndef __MAP_H__
#define __MAP_H__

#include "bomb.h"

#include "define_state.h"

extern int mapModel[HEIGHT][WIDTH];
extern int NPCmapModel[HEIGHT][WIDTH];

typedef struct map {
	int state;
	Bomb* bomb;
} Map;

typedef struct map_box {
	int x;
	int y;
	struct map_box* next;
} Map_box;

typedef struct map_box_head {
	struct map_box* next;
} Map_box_head;

Map_box_head* map_box_head;

int* output_random_5_num_arr();		//맵 랜덤 배치를 위한 랜덤 숫자 5개 생성 함수
void resetMap();		//맵 초기 값 설정
void generateMap();		//맵 생성
void drawMaps();		//맵 출력
//void draw_3_3maps(int x, int y, int cursX, int cursY);		//3*3 으로 확장

int checkObject_can_go(int cursorX, int cursorY);		//인자로 주어진 좌표로 이동할 수 있는지
int checkObject_Item(int cursorX, int cursorY);			//인자로 주어진 좌표에 아이템이 있는지

int checkObject_bomb_max_Item(int cursorX, int cursorY);			//인자로 주어진 좌표에 폭탄 개수 증가 아이템이 있는지
int checkObject_bomb_range_Item(int cursorX, int cursorY);			//인자로 주어진 좌표에 폭탄 범위 증가 아이템이 있는지
int checkObject_character_Move_Item(int cursorX, int cursorY);			//인자로 주어진 좌표에 이동속도 증가 아이템이 있는지

int checkObject_boom(int cursorX, int cursorY);			//인자로 주어진 좌표가 폭발범위인지
int checkObject_box(int cursorX, int cursorY);			//인자로 주어진 좌표에 부실 수 있는 장애물이 있는지
int checkObject_wall(int cursorX, int cursorY);			//인자로 주어진 좌표에 부실 수 없는 장애물이 있는지
int checkObject_exist_bomb(int cursorX, int cursorY);	//인자라 주어진 좌표에 터지지 않은 폭탄이 존재하는지

void gernerate_Item(int cursorX, int cursorY);          // 해당 좌표에 아이템 생성
void draw_Item_bomb_max(int x, int y);       // 해당 좌표에 bomb max 증가 아이템 출력
void draw_Item_bomb_range(int x, int y);     // 해당 좌표에 bomb max 증가 아이템 출력
void draw_Item_chracter_move(int x, int y); // 해당 좌표에 bomb max 증가 아이템 출력

int get_Player_starting_point_x();			//플레이어 초기 x 위치 지정
int get_Player_starting_point_y();			//플레이어 초기 y 위치 지정

void set_Bomb(int arrX, int arrY);				//해당좌표에 폭탄놓기		
void set_Empty(int arrX, int arrY);				//해당 좌표 공백으로 만들기
void set_Bomb_Boom(int arrX, int arrY);			//해당 좌표에 폭탄 폭발하게 만들기
void set_NPC_Warning(int arrX, int arrY);		//해당 좌표에 NPC Warning update하기

// 11월 18일 추가
int cursorX_to_arrX(int cursorX);			//커서좌표를 배열의 좌표로 변환
int cursorY_to_arrY(int cursorY);			//커서좌표를 배열의 좌표로 변환

int arrX_to_cursorX(int arrX);				//배열 좌표를 커서 좌표로 변환
int arrY_to_cursorY(int arrY);				//배열 좌표를 커서 좌표로 변환

int check_over_GameBoard_Width(int arrX);		//맵을 벗어나는지
int check_over_GameBoard_HEIGHT(int arrY);		//맵을 벗어나는지

//void npc_Warning_update(int arrX, int arrY, Bomb* newbomb);
int checkPlayer_Killed_NPC(int npcCurPosX, int npcCurPosY, int PlayerCurPosX, int PlayerCurPosY);

// 11월 20일 map_box_head

Map_box_head* generate_map_box_head();
void insert_map_box_struct(Map_box_head* head, int x, int y);
void remove_generate_item_all_map_box_struct(Map_box_head* head);


#endif