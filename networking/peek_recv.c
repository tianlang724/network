#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<signal.h>
#include<netinet/in.h>
#include<fcntl.h>
#define BUF_SIZE 30
void error_handling(char *message);
int main(int argc,char * argv[])
{
	int recv_sock,acpt_sock;
	struct sockaddr_in recv_addr,serv_addr;
	int str_len,state;
	socklen_t serv_addr_sz;
	char buf[BUF_SIZE];
	if(argc!=2)
	{
		printf("Usage:%s <Port>\n" ,argv[0]);
		exit(1);
	}
	acpt_sock=socket(PF_INET,SOCK_STREAM,0);
	memset(&recv_addr,0,sizeof(serv_addr));
	recv_addr.sin_family=AF_INET;
	recv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	recv_addr.sin_port=htons(atoi(argv[1]));
	if(bind(acpt_sock,(struct sockaddr*)&recv_addr,sizeof(recv_addr))==-1)
		error_handling("bind() error");
	listen(acpt_sock,5);
	serv_addr_sz=sizeof(serv_addr);
	recv_sock=accept(acpt_sock,(struct sockaddr*)&serv_addr,&serv_addr_sz);
	while(1)
	{
		str_len=recv(recv_sock,buf,BUF_SIZE-1,MSG_PEEK|MSG_DONTWAIT);
		if(str_len>0)
			break;
			
	}
	buf[str_len]=0;
	printf("buffering %d bytes %s\n",str_len,buf);

	str_len=recv(recv_sock,buf,BUF_SIZE-1,0);
	printf("read again %d bytes %s\n",str_len,buf);
	close(recv_sock);
	close(acpt_sock);
	return 0;
			
}
void error_handling(char *message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}

