#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>

#define BUF_SIZE 20
void error_handling(char *message);
void read_routine(int sock,char *buf);
void write_routine(int sock,char * buf);
int main(int argc,char * argv[])
{
	int serv_sock;
	pid_t pid;
	char buf[BUF_SIZE];
	struct sockaddr_in serv_addr;
	if(argc!=3)
	{
		printf("Usage : %s<IP> <Port>\n",argv[0]);
		exit(1);
	}
	serv_sock=socket(PF_INET,SOCK_STREAM,0);
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_addr.sin_port=htons(atoi(argv[2]));
	if(connect(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1)
			error_handling("connect() error");
	pid=fork();
	if(pid==0)
	write_routine(serv_sock,buf);
	else
	read_routine(serv_sock,buf);
	close(serv_sock);
	return 0;
}
void error_handling(char *message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}
void read_routine(int sock,char *buf)
{
	while(1)
	{
		int str_len=read(sock,buf,sizeof(buf));
		if(str_len==0)
			return ;
		printf("message from server:%s\n",buf);
	}
}
void write_routine(int sock,char *buf)
{
	while(1)
	{
		fgets(buf,BUF_SIZE,stdin);
		if(!strcmp(buf,"q\n"))
		{
			shutdown(sock,SHUT_WR);
			return ;
		}
		write(sock,buf,strlen(buf));
	}
}
	
