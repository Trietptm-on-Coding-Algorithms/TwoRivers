#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

#define BUF_SIZE 1024

int main(int argc,char**argv){
	int sock;
	char buf[BUF_SIZE];
	struct sockaddr_in serv_addr;

	FILE *readFp;
	FILE *writeFp;
	
	sock=socket(PF_INET,SOCK_STREAM,0);
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(atoi(argv[2]));
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
	
	connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	readFp=fdopen(sock,"r");//ǥ�� �Է� �Լ� ȣ���� ���� sock�� ���� FILE ������ ����
	writeFp=fdopen(sock,"w");
	
	while(1){
		if(fgets(buf,sizeof(buf),readFp)==NULL) //���ϰ��� NULL �̸� EOF �� ���� ��.
			break;
		fputs(buf,stdout);
		fflush(stdout);
	}
	fputs("FROM Client : Thank you \n",writeFp); //������ EOF �� ���� �� ������ ���ڿ� ����.
	fflush(writeFp);
	fclose(writeFp);
	fclose(readFp);
	return 0;
}
