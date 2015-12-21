#ifndef __FLOYD_H_

#include "Common.h"
#define INT_MAX 2147483647 //�ִ� ����
#define TRUE 1
#define FALSE 0
#define MAX_VERTICE 7 //���� ��
#define INF 9999 //������ ���� ���

typedef struct _node {
	int ver;
	struct _node *next;
}Node;

typedef struct _path {
	Node *node;
	Node *tail;
}Path; //Path �迭�� �ε����� ������� ������


void Floyd(int n,int(*weight)[MAX_VERTICE],int(*distance)[MAX_VERTICE],Path *path);

#endif