#ifndef __AVL_REBALANCE_H__
#define __AVL_REBALANCE_H__

#include "BinaryTree.h"

int GetHeight(BTreeNode *bst); //���� 
int GetHeightDiff(BTreeNode *bst); //���� ����

BTreeNode*RotateLL(BTreeNode * bst); //LL
BTreeNode*RotateRR(BTreeNode *bst); //RR
BTreeNode*RotateLR(BTreeNode *bst); //LR
BTreeNode*RotateRL(BTreeNode *bst); //RL

BTreeNode * Rebalance(BTreeNode **pRoot); //������ ����

#endif