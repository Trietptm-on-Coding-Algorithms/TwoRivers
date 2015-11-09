#include "QuickSort.h"

void Swap(int arr[],int idx1,int idx2){
	int tmp=arr[idx1];
	arr[idx1]=arr[idx2];
	arr[idx2]=tmp;
}

int Partition(int arr[],int left,int right){
	//pivot�� ���� �������� ����
	int pivot=arr[left];
	int low=left+1;
	int high=right;

	if(low<=high){
		while(pivot>=arr[low] && low<=right) low++;
		while(pivot<=arr[high] && high>=(left+1)) high--;
		if(low<=high) Swap(arr,low,high);
	}
	Swap(arr,left,high);
	return high; //���� ���ؿ� �˸´� ��ġ�� �̵��� pivot�� index
}

void QuickSort(int arr[],int left,int right){
	int pivot;
	if(left<=right){
		pivot=Partition(arr,left,right);
		QuickSort(arr,left,pivot-1); //����
		QuickSort(arr,pivot+1,right); //������
	}
}