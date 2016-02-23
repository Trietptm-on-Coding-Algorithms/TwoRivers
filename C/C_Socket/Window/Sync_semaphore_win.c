#include<stdio.h>
#include<Windows.h>
#include<process.h>

unsigned WINAPI Read(void*arg);
unsigned WINAPI Accu(void*arg);

static HANDLE semOne;
static HANDLE semTwo;
static int num;

void main(int argc,char**argv){
	HANDLE thread1,thread2;

	//������� 0�̸� non-signaled
	//������� 0���� ũ�� signaled
	semOne=CreateSemaphore(NULL,0,1,NULL); //�ʱⰪ : 0 , �ִ밪 : 1
	semTwo=CreateSemaphore(NULL,1,1,NULL); //�ʱⰪ : 1 , �ִ밪 : 1

	thread1=(HANDLE)_beginthreadex(NULL,0,Read,NULL,0,NULL);
	thread2=(HANDLE)_beginthreadex(NULL,0,Accu,NULL,0,NULL);

	WaitForSingleObject(thread1,INFINITE);
	WaitForSingleObject(thread2,INFINITE);

	CloseHandle(thread1);
	CloseHandle(thread2);
}

unsigned WINAPI Read(void*arg){
	int i;
	for(i=0;i<5;i++){
		fputs("Input num : ",stdout);
		WaitForSingleObject(semTwo,INFINITE);
		scanf("%d",&num);
		ReleaseSemaphore(semOne,1,NULL);
	}
	return 0;
}

unsigned WINAPI Accu(void*arg){
	int i,sum=0;
	for(i=0;i<5;i++){
		WaitForSingleObject(semOne,INFINITE);
		sum+=num;
		ReleaseSemaphore(semTwo,1,NULL);
	}
	printf("result : %d\n",sum);
	return 0;
}