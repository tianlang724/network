#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
void error_handling(char * message);
int main(int argc,char* argv[])
{
	int sock;
	int snd_buf=1024*2,rcv_buf=1023*4,state;
	socklen_t len;
	sock=socket(PF_INET,SOCK_STREAM,0);
	len=sizeof(snd_buf);
	state=setsockopt(sock,SOL_SOCKET,SO_SNDBUF,(void*)&snd_buf,len);
	if(state)
		error_handling("getsockopt() error");
	len=sizeof(rcv_buf);
	state=setsockopt(sock,SOL_SOCKET,SO_RCVBUF,(void*)&rcv_buf,len);
	if(state)
		error_handling("getsockopt() error");
	printf("Input buffer size:%d \n",snd_buf);
	printf("Out buffer size:%d \n",rcv_buf);
	return 0;
}
void error_handling(char* message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}

