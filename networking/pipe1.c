#include<stdio.h>
#include<unistd.h>
#define BUF_SIZE 30
 int main(int argc,char* argv[])
{
	int fd[2];
	char str[]="Who are you?";
	char buf[BUF_SIZE];
	pid_t pid;
	pipe(fd);
	pid=fork();
	if(pid==0)
	{
		write(fd[1],str,sizeof(str));
	}
	else
	{
		read(fd[0],buf,BUF_SIZE);
		puts(buf);
	}
	return 0;
}
