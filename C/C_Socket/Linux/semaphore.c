#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

void* read(void *arg);
void* sum(void*arg);
static sem_t sem_one;
static sem_t sem_two;
static int num;

int main(int argc,char**argv){
	//read �� sum ����
	pthread_t id1,id2;
	sem_init(&sem_one,0,0);
	sem_init(&sem_two,0,1);
	
	pthread_create(&id1,NULL,read,NULL);
	pthread_create(&id2,NULL,sum,NULL);

	pthread_join(id1,NULL);
	pthread_join(id2,NULL);
	
	sem_destroy(&sem_one);
	sem_destroy(&sem_two);
	return 0;
}

void* read(void*arg){
	int i;
	for(i=0;i<5;i++){
		fputs("input num : ",stdout);
		sem_wait(&sem_two);//1->0
		scanf("%d",&num);
		sem_post(&sem_one);//0->1
	}
	return NULL;
}
void* sum(void*arg){
	int sum=0,i;
	for(i=0;i<5;i++){
		sem_wait(&sem_one);//1->0
		sum+=num;
		sem_post(&sem_two);//0->1
	}
	printf("result : %d\n",sum);
	return NULL;
}
