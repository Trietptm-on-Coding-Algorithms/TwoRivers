#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUF_SIZE 1024

int main(int argc, char **argv){
	int serv_sock,client_sock;
	FILE *readFp;
	FILE *writeFp;
	
	struct sockaddr_in serv_addr,client_addr;
	socklen_t client_addr_size;
	char buf[BUF_SIZE];

	serv_sock=socket(PF_INET,SOCK_STREAM,0);
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(atoi(argv[1]));
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	
	if(bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1)
			exit(1);
	if(listen(serv_sock,5)==-1) exit(1);

	client_addr_size=sizeof(client_addr);
	client_sock=accept(serv_sock,(struct sockaddr*)&client_addr,&client_addr_size);
	readFp=fdopen(client_sock,"r");
	//Half-close�� ���ؼ� ���� ��ũ���� ����.
	//readFp�� writeFp�� ����Ű�� ���� ��ũ���ʹ� �ٸ�.
	writeFp=fdopen(dup(client_sock),"w");
	
	fputs("FROM Server : Hello Client \n",writeFp);
	fputs("SERVER \n",writeFp);
	fputs("Seperate Server \n",writeFp);
	fflush(writeFp);
	
	shutdown(fileno(writeFp),SHUT_WR); //��� FILE �������� ��� ���ϵ�ũ���� ����.
	//readFp�� ����Ű�� ���� ��ũ���Ͷ� �ٸ��Ƿ� Half-close ����.
	fclose(writeFp);

	fgets(buf,sizeof(buf),readFp);//Ŭ���̾�Ʈ�� EOF�� ���� �� ������ ������ ���ڿ� ����.
	fputs(buf,stdout);
	fclose(readFp);
	return 0;
}
