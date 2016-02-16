#include<stdio.h>
#include<pthread.h>
void* thread_test(void *arg);
void* thread_sum(void *arg);
int sum=0; 

int main(int argc,char**argv){
	pthread_t id1,id2;
	int rang1[]={1,5};
	int rang2=10;
	int i=0;

	printf("create thread 1\n");
	pthread_create(&id1,NULL,thread_sum,(void*)rang1);
	
	printf("create thread 2\n");
	pthread_create(&id2,NULL,thread_test,(void*)&rang2);
	
	//�ּ� thread ���� ���� ������ main �� ���� �ȵ�.
	//pthread_join �� �ش� �����尡 ���� �� �� ���� ���ŷ ���� ����.
	printf("join thread 1 : %d \n",pthread_join(id1,NULL));
	//thread 2�� �۾��� �̹� �����ִ� ���� �ϼ��� ����.
	//���� ���¶�� �ٷ� pthread_join �Լ��� �ٷ� ��ȯ��.
	//�ƴ϶�� ���ŷ ���¿��� thread 2 �۾��� ������ ���� ���ŷ ��������.
	printf("join thread 2 : %d \n",pthread_join(id2,NULL));

	printf("main result : %d\n",sum);
	return 0;
}
void* thread_sum(void*arg){
	int start=((int*)arg)[0];
	int end=((int*)arg)[1];

	printf("thread_sum start!\n");
	while(start<=end){
		printf("sum += %d \n",start);
		sleep(1); // delay,�̰����� ���� thread 2 �� �۾��� ���� �Ϸ��.
		sum+=start;
		start++;
	}
	printf("end thread_sum!\n");
	return NULL;
}

void* thread_test(void*arg){
	int cnt=*((int*)arg);
	int i=0;
	for(i=0;i<cnt;i++) printf("thread_test\n");
	return NULL;
}
