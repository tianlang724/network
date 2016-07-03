#include<stdlib.h>
#include<unistd.h>
#include<sys/time.h>
#include<sys/select.h>
#define BUF_SIZE 30
int main(int argc,char *argv[])
{
	fd_set reads,temps;
	int result,str_len;
	char buf[BUF_SIZE];
	struct timeval timeout;
	FD_ZERO(&reads);
	FD_SET(0,&reads);
	while(1)
	{
		timeout.tv_sec=5;
		timeout.tv_usec=5000;
		temps=reads;
		result=select(1,&temps,0,0,&timeout);
		if(result==-1)
		{
			puts("select() error\n");
			exit(1);
		}
		else if(result==0)
		{
			puts("time out!\n");
		}
		else
		{
			if(FD_ISSET(0,&temps))
			{
				str_len=read(0,buf,BUF_SIZE);
				printf("message from console %s\n",buf);
			}
		}
		return 0;
	}



}
