#include "HeapSort.h"

void HeapSort(int arr[],int len,PriorityComp pc){
	Heap heap;
	int i;
	HeapInit(&heap,pc);

	//����
	for(i=0;i<len;i++) HInsert(&heap,arr[i]);
	//����, �����鼭 PriorityComp �� �°� ���ĵǾ� ����.
	for(i=0;i<len;i++) arr[i]=HDelete(&heap);
}