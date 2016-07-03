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
	int sock;
	int str_len;
	socklen_t adr_sz;
	struct sockaddr_in serv_addr,from_addr;
	char mesg1[]="hello1";
	char mesg2[]="hello2";
	char mesg3[]="hello3";


	if(argc!=3)
	{
		printf("Usage:%s <port>\n",argv[0]);
		return 0;
	}
	sock=socket(PF_INET,SOCK_DGRAM,0);
	if(sock==-1)
		error_handling("socket() error");
	//memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_addr.sin_port=htons(atoi(argv[2]));
	sendto(sock,mesg1,strlen(mesg1),0,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	sendto(sock,mesg2,strlen(mesg2),0,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	sendto(sock,mesg3,strlen(mesg3),0,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

	
	
	close(sock);
	return 0;
}
void error_handling(char *message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}
