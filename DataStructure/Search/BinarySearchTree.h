#ifndef __BINARY_SEARCH_TREE_H__
#define __BINARY_SEARCH_TREE_H__

#include "BinaryTree.h"
#include "common.h"

typedef BTData BSTData;

void BSTMakeAndInit(BTreeNode **pRoot); //�ʱ�ȭ �� ����
BSTData BSTGetNodeData(BTreeNode *bst); //��� ������ ����
BTreeNode* BSTInsert(BTreeNode **pRoot,BSTData data); //������ ����
BTreeNode* BSTSearch(BTreeNode *bst,BSTData target); //������ �˻�
BTreeNode* BSTRemove(BTreeNode** pRoot,BSTData target); //��� ����
void BSTShowAll(BTreeNode *bst); //������ ���

#endif