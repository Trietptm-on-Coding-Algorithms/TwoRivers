#include "BinarySearchTree.h"
#include "AVLRebalance.h"
void BSTMakeAndInit(BTreeNode **pRoot){
	*pRoot=NULL;
}
BSTData BSTGetNodeData(BTreeNode *bst){
	return GetData(bst);
}
BTreeNode* BSTInsert(BTreeNode **pRoot,BSTData data){
	//BTreeNode *pNode=NULL;
	//BTreeNode *cNode=*pRoot;
	//BTreeNode *nNode=NULL;

	////��ġ ã��
	//while(cNode!=NULL){
	//	if(data==GetData(cNode)) return;
	//	pNode=cNode;
	//	if(GetData(cNode)<data) cNode=GetRightSubTree(cNode);
	//	else cNode=GetLeftSubTree(cNode);
	//}
	//
	//nNode=MakeBTreeNode();
	//SetData(nNode,data);

	//if(pNode!=NULL){ //���� ��尡 ��Ʈ��尡 �ƴ� ���
	//	if(GetData(pNode)<data) MakeRightSubTree(pNode,nNode);
	//	else MakeLeftSubTree(pNode,nNode);
	//}
	//else //���� �Ǵ� ��尡 ��Ʈ ��尡 �Ǵ� ���
	//	*pRoot=nNode;

	if(*pRoot==NULL){
		*pRoot=MakeBTreeNode();
		SetData(*pRoot,data);
	}
	else if(GetData(*pRoot)>data){
		BSTInsert(&((*pRoot)->left),data);
		*pRoot=Rebalance(pRoot);
	}
	else if(GetData(*pRoot)<data){
		BSTInsert(&((*pRoot)->right),data);
		*pRoot=Rebalance(pRoot);
	}
	else
		return NULL; //Ű(data) �ߺ�

	return *pRoot;
}
BTreeNode *BSTSearch(BTreeNode *bst,BSTData target){
	BTreeNode *cNode=bst;
	BSTData cData;

	while(cNode!=NULL){
		cData=GetData(cNode);
		if(target==cData) return cNode;
		else if(target<cData) cNode=GetLeftSubTree(cNode);
		else cNode=GetRightSubTree(cNode);
	}
	return NULL;
}
BTreeNode* BSTRemove(BTreeNode** pRoot,BSTData target){
	BTreeNode *pVRoot=MakeBTreeNode();
	BTreeNode *pNode=pVRoot;
	BTreeNode *cNode=*pRoot;
	BTreeNode *dNode,*dcNode,*mNode,*mpNode;
	BSTData delData;

	//���� ����� ������ �ڽ��� ��Ʈ���
	ChangeRightSubTree(pVRoot,*pRoot);

	//���� ��� �˻�
	while(cNode!=NULL && GetData(cNode)!=target){
		pNode=cNode;
		if(target<GetData(cNode)) cNode=GetLeftSubTree(cNode);
		else cNode=GetRightSubTree(cNode);
	}

	if(cNode==NULL) return NULL;
	
	dNode=cNode;

	//�ܸ� ����� ���
	if(GetLeftSubTree(dNode)==NULL && GetRightSubTree(dNode)==NULL){
		if(GetLeftSubTree(pNode)==dNode) RemoveLeftSubTree(pNode);
		else RemoveRightSubTree(pNode);
	}
	//�ϳ��� �ڽ� ��带 ���� ���
	else if(GetLeftSubTree(dNode)==NULL || GetRightSubTree(dNode)==NULL){
		if(GetLeftSubTree(dNode)!=NULL) dcNode=GetLeftSubTree(dNode);
		else dcNode=GetRightSubTree(dNode);
		if(GetLeftSubTree(pNode)==dNode) ChangeLeftSubTree(pNode,dcNode);
		else ChangeRightSubTree(pNode,dcNode);
	}
	//�� ���� �ڽ� ��带 ���� ���
	else{
		//���� ��带 ��ü�� ���� ���� ����� ������ ����Ʈ�������� ���� ���� ���� ���� ���
		mNode=GetRightSubTree(dNode); //��ü���
		mpNode=dNode;//��ü����� �θ���
				
		//���� ����� ��ü ��带 ã��
		while(GetLeftSubTree(mNode)!=NULL){
			mpNode=mNode;
			mNode=GetLeftSubTree(mNode);
		}
		
		//��ü��忡 ����� ���� ������ ��忡 ����
		delData=GetData(dNode); //���� �� ��� �� ���
		SetData(dNode,GetData(mNode));

		//��ü����� �θ���� �ڽĳ�带 ����
		if(GetLeftSubTree(mpNode)==mNode) ChangeLeftSubTree(mpNode,GetRightSubTree(mNode));
		else ChangeRightSubTree(mpNode,GetRightSubTree(mNode));
		
		dNode=mNode;
		SetData(dNode,delData);
	}
	//������ ��尡 ��Ʈ����� ���	
	if(GetRightSubTree(pVRoot)!=*pRoot) *pRoot=GetRightSubTree(pVRoot);

	free(pVRoot);
	*pRoot=Rebalance(pRoot);
	return dNode;
}

void ShowIntData(int data){
	printf("%d ",data);
}

void BSTShowAll(BTreeNode *bst){
	InorderTraverse(bst,ShowIntData);
}