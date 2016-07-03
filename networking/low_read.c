#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#define BUF_SIZE 6
void error_handling(char* message);

int main()
{

	int fd;
	int read_cnt;
	char buf[BUF_SIZE];
	memset(buf,0,sizeof(buf));
	fd=open("data.txt",O_RDONLY);
	if(fd==-1)
		error_handling("open() error");
	printf("file descriptor : %d\n",fd);
	if(read_cnt=read(fd,buf,sizeof(buf))==-1)
		error_handling("read() error");
	printf("file data: %s\n",buf);
	printf("read_cnt:%d\n",read_cnt);
	close(fd);
	return 0;
}

void error_handling(char* message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}
