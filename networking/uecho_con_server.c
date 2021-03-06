#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#define BUF_SIZE 20
void error_handling(char *message);
int main(int argc,char* argv[])
{
	int serv_sock,clnt_sock;
	int mesg_len;
	struct sockaddr_in serv_addr,clnt_addr;
	socklen_t clnt_addr_size;
	char message[BUF_SIZE];
	if(argc!=2)
	{
		printf("Usage:%s <port>\n",argv[0]);
		return 0;
	}
	memset(message,0,sizeof(message));
	serv_sock=socket(PF_INET,SOCK_DGRAM,0);
	if(serv_sock==-1)
		error_handling("socket() error");
	memset(&serv_addr,0,sizeof(&serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(atoi(argv[1]));
	clnt_addr_size=sizeof(clnt_addr);
	if(bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1)
		error_handling("bind() error");
	//if(listen(serv_sock,5)==-1)
		//error_handling("listen() error");
	clnt_addr_size=sizeof(clnt_addr);
	clnt_sock=accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_size);
	while(1)
	{
		mesg_len=read(clnt_sock,message,sizeof(message));
		printf("message from client %s\n",message);
		write(clnt_sock,message,mesg_len);
	
	}
	close(serv_sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}
