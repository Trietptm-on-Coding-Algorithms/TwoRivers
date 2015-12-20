#ifndef __DIJKSTRA_H__

#include "common.h"
#define INT_MAX 2147483647 //�ִ� ����
#define TRUE 1
#define FALSE 0
#define MAX_VERTICE 7 //���� ��
#define INF 9999 //������ ���� ���

//int weight[MAX_VERTICE][MAX_VERTICE]; //���� ���
int distance[MAX_VERTICE]; //���� �������� �ִ� �Ÿ�
int found[MAX_VERTICE]; //�湮�� ���� true

typedef struct _node {
	int ver;
	struct _node *next;
}Node;

typedef struct _path {
	Node *node;
	Node *tail;
}Path; //Path �迭�� �ε����� ������� ������

int Choose(int distance[],int n,int found[]); //�ִ� ��� ����
void ShortestPath(int start,int n,Path *path,int (*weight)[MAX_VERTICE]);

#endif