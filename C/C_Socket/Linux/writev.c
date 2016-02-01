#include<stdio.h>
#include<sys/uio.h>

int main(int argc, char**argv){
	struct iovec vec[2];
	char buf1[]="abcdefg";
	char buf2[]="1234567";
	int str_len;
	vec[0].iov_base=buf1;
	vec[0].iov_len=3;
	vec[1].iov_base=buf2;
	vec[1].iov_len=5;
	//���ϵ�ũ����,iovec ����ü�� �迭,�迭�� ����
	//iovec ����ü ->iov_base,iov_len ���� ����
	//iov_base�� �����ּ�(void* Ÿ��)
	//iov_len �� �������� ũ��
	str_len=writev(1,vec,2);
	puts("");
	printf("Write bytes : %d \n",str_len);
	return 0;
}
