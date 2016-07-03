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
	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size;
	FILE *readfp;
	FILE *writefp;
	char message[BUF_SIZE];
	if(argc!=2)
	{
		printf("Usage:%s <port>\n",argv[0]);
		return 0;
	}
	serv_sock=socket(PF_INET,SOCK_STREAM,0);
	if(serv_sock==-1)
		error_handling("socket() error");
	memset(&serv_addr,0,sizeof(&serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(atoi(argv[1]));
	clnt_addr_size=sizeof(clnt_addr);
	if(bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1)
		error_handling("bind() error");
	if(listen(serv_sock,5)==-1)
		error_handling("listen() error");
	clnt_addr_size=sizeof(clnt_addr);
	clnt_sock=accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_size);
	if(clnt_sock==-1)
		error_handling("accept() error");
	readfp=fdopen(clnt_sock,"r");
	writefp=fdopen(clnt_sock,"w");
	
	fputs("from server: hi client?\n",writefp);
	fputs("from server: i love the world\n",writefp);
	fputs("from server: you are awesom\n",writefp);
	fclose(writefp);
	fgets(message,BUF_SIZE,readfp);
	fputs(message,stdout);
	fclose(readfp);
	close(serv_sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}

