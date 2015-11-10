#include "InterpolSearch.h"

int ISearch(int arr[],int first,int last,int target){
	int s;
	//����Ž��
	//������ ���� �����Ͱ� ����� ��ġ�� �ε��� ���� ����Ѵٰ� ����
	//���ĵ� ������ �迭
	s=((double)(target-arr[first])/(arr[last]-arr[first]) * (last-first))+first;
	if(arr[first]>target || arr[last]<target) return -1;

	if(arr[s]==target) return s;
	else if(target<arr[s]) return ISearch(arr,first,s-1,target);
	else return ISearch(arr,s+1,last,target);
}