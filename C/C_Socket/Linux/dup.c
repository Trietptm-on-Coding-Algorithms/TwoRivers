#include<stdio.h>
#include<unistd.h>

int main(){
	int fd1,fd2;
	char str1[]="Hello\n";
	char str2[]="good\n";
	
	fd1=dup(1); //ǥ����� ���ϵ�ũ���͸� ����.
	fd2=dup2(fd1,7); //fd1���ϵ�ũ���͸� ������ 7�� ���� ���ϵ�ũ���ͷ� ����.
	printf("fd1 : %d . fd2 : %d\n",fd1,fd2);
	write(fd1,str1,sizeof(str1));//ǥ�� ����� ������ ���ϵ�ũ����
	write(fd2,str2,sizeof(str2));
	
	close(fd1);
	close(fd2);

	write(1,str1,sizeof(str1)); //ǥ�� ���
	close(1);//ǥ�� ��� ����
	write(1,str2,sizeof(str2));//ǥ�� ����� ����Ǿ� ����� �̷����� ����.
	return 0;
}
	
