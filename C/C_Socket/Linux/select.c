#include<stdio.h>
#include<unistd.h>
#include<sys/time.h>
#include<sys/select.h>
#define BUF_SIZE 30

int main(int argc,char**argv){
	fd_set reads,temps;
	int result,str_len;
	char buf[BUF_SIZE];
	struct timeval timeout;
	
	FD_ZERO(&reads);
	FD_SET(0,&reads);
	
	while(1){
		temps=reads;
		timeout.tv_sec=5;
		timeout.tv_usec=0;
		//���� ��ũ���� �ִ� 1��
		//0,1,2,3,4, ...
		//�׷��Ƿ� 0 �� ���� ��ũ���� ����.
		result=select(1,&temps,0,0,&timeout);
		if(result==-1){
			puts("select error");
			break;
		}
		else if(result==0){
			puts("time out");
		}
		else{
			//temps ���� 0 ��ũ���Ͱ� 1�� �Ǿ��ִ��� Ȯ��.
			if(FD_ISSET(0,&temps)){
				str_len=read(0,buf,BUF_SIZE);
				buf[str_len]=0;
				printf("message from console : %s",buf);
			}
		}
	}
	return 0;
}
