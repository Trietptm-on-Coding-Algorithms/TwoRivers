#include<stdio.h>
#include<string.h>
#include<WinSock2.h>

#define BUF_SIZE 100

void CompressSockets(SOCKET sockArr[],int idx,int total);
void CompressEvents(WSAEVENT eventArr[],int idx,int total);
void ErrorHandling(char*msg);

void main(int argc,char**argv){
	WSADATA wsaData;
	SOCKET serv_sock,client_sock;
	SOCKADDR_IN serv_addr,client_addr;
	
	SOCKET sockArr[WSA_MAXIMUM_WAIT_EVENTS];
	WSAEVENT eventArr[WSA_MAXIMUM_WAIT_EVENTS];
	WSAEVENT newEvent;
	WSANETWORKEVENTS netEvents;

	int numOfClientSock=0;
	int strLen,i,sigEventIdx;
	int posInfo,startIdx;
	int client_addr_len;
	char msg[BUF_SIZE];

	if(argc!=2)	{
		printf("Usage : %s <PORT> \n",argv[0]);
		exit(1);
	}

	if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0) ErrorHandling("WSAStartup error");

	serv_sock=socket(PF_INET,SOCK_STREAM,0);
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(atoi(argv[1]));
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);

	if(bind(serv_sock,(SOCKADDR*)&serv_addr,sizeof(serv_addr))==SOCKET_ERROR) ErrorHandling("bind error");
	
	if(listen(serv_sock,5)==SOCKET_ERROR) ErrorHandling("listen error");

	newEvent=WSACreateEvent();
	puts("WSAEventSelect \n");
	if(WSAEventSelect(serv_sock,newEvent,FD_ACCEPT)==SOCKET_ERROR) //���� �̺�Ʈ ����
		ErrorHandling("WSAEventSelect error");

	sockArr[numOfClientSock]=serv_sock;
	eventArr[numOfClientSock]=newEvent;
	numOfClientSock++;

	while(1){
		printf("<--WSAWaitForMultipleEvents first-->\n");//

		posInfo=WSAWaitForMultipleEvents(numOfClientSock,eventArr,FALSE,WSA_INFINITE,FALSE);//�̺�Ʈ �߻� ���� Ȯ��
																							//������ �̺�Ʈ �߻��� ���ؼ� �̺�Ʈ ������Ʈ�� signaled ���°� �Ǿ�� ��ȯ�ϴ� �Լ�
		startIdx=posInfo-WSA_WAIT_EVENT_0;//�̺�Ʈ�� �߻��� �̺�Ʈ �迭�� ù��° �ε���

		printf("posInfo : %d \n",posInfo);
		printf("numOfClientSock : %d \n",numOfClientSock);

		for(i=startIdx;i<numOfClientSock;i++){
			printf("for WSAWaitForMultipleEvents 1 \n");//
			
			sigEventIdx=WSAWaitForMultipleEvents(1,&eventArr[i],TRUE,0,FALSE);	//�ϳ��� �̺�Ʈ��
																				//�̺�Ʈ�� �߻��� �̺�Ʈ ������Ʈ�� signaled ���°� ��
			printf("for WSAWaitForMultipleEvents 2 \n");//

			if(sigEventIdx==WSA_WAIT_FAILED || sigEventIdx==WSA_WAIT_TIMEOUT){
				//�������� Ŭ���̾�Ʈ�� ������ ������ �ִ� ���¿���
				//���ο� Ŭ���̾�Ʈ�� ������ �����ϰ� �Ǹ� Ŭ���̾�Ʈ���� TIMEOUT �߻�(Ŭ���̾�Ʈ�� �ƹ��͵� ���ϴ� ���¿���)
				printf("if : %s (%d)\n",(sigEventIdx==WSA_WAIT_FAILED)?"WSA_WAIT_FAILED":"WSA_WAIT_TIMEOUT",sigEventIdx);
				continue;
			}
			else{
				sigEventIdx=i; //�߻��� �̺�Ʈ �ε���
				printf("WSAEnumNetworkEvents 1 \n");
				WSAEnumNetworkEvents(sockArr[sigEventIdx],eventArr[sigEventIdx],&netEvents); // �̺�Ʈ ����(signaled ���°��� ������ �˱� ����)
				printf("WSAEnumNetworkEvents 2 \n");

				if(netEvents.lNetworkEvents & FD_ACCEPT){ //���� �̺�Ʈ �� ��
					if(netEvents.iErrorCode[FD_ACCEPT_BIT]!=0){
						puts("Accept error");
						break;
					}
					client_addr_len=sizeof(client_addr);
					client_sock=accept(sockArr[sigEventIdx],(SOCKADDR*)&client_addr,&client_addr_len);
					newEvent=WSACreateEvent();
					WSAEventSelect(client_sock,newEvent,FD_READ|FD_CLOSE);

					eventArr[numOfClientSock]=newEvent;
					sockArr[numOfClientSock]=client_sock;
					numOfClientSock++;
					printf("connected new client(%d) ....\n",numOfClientSock);
				}

				if(netEvents.lNetworkEvents & FD_READ){ //�б� �̺�Ʈ �� ��
					if(netEvents.iErrorCode[FD_READ_BIT]!=0){
						puts("Read error");
						break;
					}
					printf("Echo Recv(%d)\n",i);
					strLen=recv(sockArr[sigEventIdx],msg,sizeof(msg),0);
					printf("Echo Send(%d)\n",i);
					send(sockArr[sigEventIdx],msg,strLen,0);
				}

				if(netEvents.lNetworkEvents & FD_CLOSE){ //���� �� �̺�Ʈ �ݱ� 
					if(netEvents.iErrorCode[FD_CLOSE_BIT]!=0){
						puts("Close error");
						break;
					}
					WSACloseEvent(eventArr[sigEventIdx]);
					closesocket(sockArr[sigEventIdx]);

					numOfClientSock--;
					CompressSockets(sockArr,sigEventIdx,numOfClientSock);
					CompressEvents(eventArr,sigEventIdx,numOfClientSock);
				}
			}
		}
	}
	WSACleanup();
}

void CompressSockets(SOCKET sockArr[],int idx,int total){
	int i;
	for(i=idx;i<total;i++) sockArr[i]=sockArr[i+1]; //�迭����
}

void CompressEvents(WSAEVENT eventArr[],int idx,int total){
	int i;
	for(i=idx;i<total;i++) eventArr[i]=eventArr[i+1]; //�迭����
}

void ErrorHandling(char*msg){
	fputs(msg,stderr);
	fputc('\n',stderr);
	exit(1);
}