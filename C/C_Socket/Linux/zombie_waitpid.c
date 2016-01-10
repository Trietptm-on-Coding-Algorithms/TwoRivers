#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc,char**argv){
	int status;
	pid_t pid=fork();
	
	if(pid==0){
		sleep(10);
		return 20;
	}
	else{
		while(!waitpid(-1,&status,WNOHANG)){
			sleep(2);
			puts("sleep 2sec");
		}
		if(WIFEXITED(status))
			printf("Child send %d \n",WEXITSTATUS(status));
	}
	return 0;
}
