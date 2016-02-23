#include<stdio.h>
#include<Windows.h>
#include<process.h>

#define NUM_THREAD 50
unsigned WINAPI threadInc(void*arg);
unsigned WINAPI threadDec(void*arg);
long long num=0;

void main(int argc,char**argv){
	HANDLE handles[NUM_THREAD];
	int i;
	printf("sizeof long long : %d \n",sizeof(long long));
	
	//������ ����ȭ �ʿ�
	for(i=0;i<NUM_THREAD;i++){
		if(i%2)
			handles[i]=(HANDLE)_beginthreadex(NULL,0,threadInc,NULL,0,NULL);
		else
			handles[i]=(HANDLE)_beginthreadex(NULL,0,threadDec,NULL,0,NULL);
	}
	WaitForMultipleObjects(NUM_THREAD,handles,TRUE,INFINITE);	//TRUE : �迭�� ��� �׸���� signaled �Ǿ�� ��ȯ.
																//FALSE : �迭�� �׸� �� �ϳ��� signaled �Ǹ� ��ȯ.
	printf("result : %lld\n",num);

}

unsigned WINAPI threadInc(void*arg){
	int i;
	for(i=0;i<50000;i++) num+=1;
	return 0;
}

unsigned WINAPI threadDec(void*arg){
	int i;
	for(i=0;i<50000;i++) num-=i;
	return 0;
}