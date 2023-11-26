#ifndef __TESTMOVING_H__
#define __TESTMOVING_H__

#include <windows.h>
#include "calculatorDST.h"

extern int npcCurPosX, npcCurPosY;
extern unsigned long long NPC_current_Time;


void ShowNpcBlock();
void DeleteBlock();
int NPC_moveLeft();
int NPC_moveRight();
int NPC_moveUp();
int NPC_moveDown();
int NpcMoving();
void SetNpcPos();
int CheckNPCState();

#endif