  #define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "map.h"
#include "calculatorDST.h"
#include "cursor.h"
#include "Test_Moving.h"
#include "player.h"

#include "bomb.h"

#include "define_state.h"

int one_srt_dist[101][101];
int dstX, dstY;
int kill_Mode = 0;

int visited[101][101] = { 0, };
int weight[101][101] = { 0, };

int front = 0, rear = 0;
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };

int wx[4] = { 0,1,0,-1 };
int wy[4] = { 1,0,-1,0 };

int can_Pos = 0;

void dfs(int dstX, int dstY, int npcX, int npcY) {

	one_srt_dist[dstY][dstX] = 1;

	if (one_srt_dist[npcY][npcX] == 1) return;
	if (dstY - 1 >= 0 && weight[dstY - 1][dstX] < weight[dstY][dstX] && one_srt_dist[dstY - 1][dstX] == 0
		&& weight[dstY - 1][dstX] != 0) dfs(dstX, dstY - 1, npcX, npcY);

	if (one_srt_dist[npcY][npcX] == 1) return;
	if (dstX - 1 >= 0 && weight[dstY][dstX - 1] < weight[dstY][dstX] && one_srt_dist[dstY][dstX - 1] == 0
		&& weight[dstY][dstX - 1] != 0) dfs(dstX - 1, dstY, npcX, npcY);

	if (one_srt_dist[npcY][npcX] == 1) return;
	if (dstY + 1 < HEIGHT && weight[dstY + 1][dstX] < weight[dstY][dstX] && one_srt_dist[dstY + 1][dstX] == 0
		&& weight[dstY + 1][dstX] != 0) dfs(dstX, dstY + 1, npcX, npcY);

	if (one_srt_dist[npcY][npcX] == 1) return;
	if (dstX + 1 < WIDTH && weight[dstY][dstX + 1] < weight[dstY][dstX] && one_srt_dist[dstY][dstX + 1] == 0
		&& weight[dstY][dstX + 1] != 0) dfs(dstX + 1, dstY, npcX, npcY);
}

void NPCavoidBOMB(Queue* safety, int x, int y) {

	rear++;
	safety[rear].x = x;
	safety[rear].y = y;
	safety[rear].dist = 1;

	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			visited[i][j] = 0;
		}
	}

	while (front < rear) {
		front++;
		for (int i = 0; i < 4; i++) {
			int nx = safety[front].x + dx[i];
			int ny = safety[front].y + dy[i];
			if (nx >= 0 && nx < WIDTH && ny >= 0 && ny < HEIGHT) {
				if (visited[ny][nx] == 0 && (
					mapModel[ny][nx] == STATE_EMPTY ||
					mapModel[ny][nx] == STATE_ITEM_BOMB_MAX ||
					mapModel[ny][nx] == STATE_ITEM_BOMB_RANGE ||
					mapModel[ny][nx] == STATE_ITEM_CHARACTER_MOVE ||
					NPCmapModel[ny][nx] == STATE_NPC_WARNING)) {

					rear++;
					safety[rear].x = nx;
					safety[rear].y = ny;
					safety[rear].dist = safety[front].dist + 1;
					visited[ny][nx] = 1;
					weight[ny][nx] = safety[rear].dist;

					if (mapModel[ny][nx] == 0 && NPCmapModel[ny][nx] != STATE_NPC_WARNING)
					{
						dstX = nx;
						dstY = ny;
						return;
					}
				}
			}
		}
	}
}

void bfs(Queue* q, Queue* safety, int x, int y) {

	if (NPCmapModel[y][x] == STATE_NPC_WARNING) {
		kill_Mode = 0;
		NPCavoidBOMB(safety, x, y);
	}

	else {
		rear++;
		q[rear].x = x;
		q[rear].y = y;
		q[rear].dist = 1;

		while (front < rear) {
			front++;
			for (int i = 0; i < 4; i++) {
				int nx = q[front].x + dx[i];
				int ny = q[front].y + dy[i];
				if (nx >= 0 && nx < WIDTH && ny >= 0 && ny < HEIGHT) {
					if (((mapModel[ny][nx] == STATE_EMPTY || // ������ �����ϰ� ������, ���߿� STATE_ITEM_EXIST�� �ѹ��� ��
						mapModel[ny][nx] == STATE_ITEM_BOMB_MAX ||
						mapModel[ny][nx] == STATE_ITEM_BOMB_RANGE ||
						mapModel[ny][nx] == STATE_ITEM_CHARACTER_MOVE) &&
						NPCmapModel[ny][nx] != STATE_NPC_WARNING) &&
						visited[ny][nx] == 0) {

						rear++;
						q[rear].x = nx;
						q[rear].y = ny;
						q[rear].dist = q[front].dist + 1;
						visited[ny][nx] = 1;
						weight[ny][nx] = q[rear].dist;


						if (nx * 2 == PlayerCurPosX && ny == PlayerCurPosY) { // ���� Ž���߿� �÷��̾� ��ġ�� �߰��ϸ�
							kill_Mode = 1;
						}

						if (kill_Mode == 1) { // kill_Mode �� 1�̸� �÷��̾ �Ѿƴٴ�
							dstX = PlayerCurPosX / 2;
							dstY = PlayerCurPosY;
						}
						else if (kill_Mode == 0) { // ���� �÷��̾� ��ġ�� ��ã�Ҵٸ�

							int cnt = 0; //������� �ּ� ģ ���� ���� ���� �μ� �� �ִ� ��ġ�� ���� �˰���
							for (int j = 0; j < 4; j++) {
								if (nx + wx[j] < 0) {
									continue;
								}
								if (nx + wx[j] >= WIDTH) {
									continue;
								}
								if (ny + wy[j] < 0) {
									continue;
								}
								if (ny + wy[j] >= HEIGHT) {
									continue;
								}
								if (mapModel[ny + wy[j]][nx + wx[j]] == 1) {
									cnt++;
								}
							}
							if (cnt > can_Pos) { // ��ǥ ��ġ�� ���� NPC��ġ���� ���� ���� ���� �μ� �� �ִ� ��ġ�� ������
								can_Pos = cnt;
								dstX = nx;
								dstY = ny;
							}
						}
					}
				}
			}
		}
	}
}

int ShortestDistance(int npcX, int npcY) {

	Queue* q = (Queue*)calloc(((WIDTH + 1) * (HEIGHT + 1)), sizeof(Queue));
	Queue* safety = (Queue*)calloc(((WIDTH + 1) * (HEIGHT + 1)), sizeof(Queue));
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			one_srt_dist[i][j] = 0;
			weight[i][j] = 0;
			visited[i][j] = 0;
		}
	}
	front = rear = 0;
	can_Pos = 0;				// 
	weight[npcY][npcX] = 0;

	bfs(q, safety, npcX, npcY); // ���⿡ NPC�� ���(x,y)��ǥ�� ����ִ´�.

	weight[npcY][npcX] = 1;
	int dist = q[rear].dist;
	free(q);
	free(safety);

	dfs(dstX, dstY, npcX, npcY);

	//���� one_srt_dist���� ������ ����

	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			if (weight[i][j] == 0) {
				one_srt_dist[i][j] = -1;
			}
			if (weight[i][j] == 0 && mapModel[i][j] == 0) {
				one_srt_dist[i][j] = 0;
			}
		}
	}

	//printf("\n\n");
	//for (int i = 0; i < 9; i++) {
	//	for (int j = 0; j < 9; j++) {
	//		//printf("%2d",one_srt_dist[i][j]);
	//		//printf("%2d", visited[i][j]);
	//		//printf("%3d", weight[i][j]);
	//	}
	//	printf("\n");
	//}

	return kill_Mode;
}