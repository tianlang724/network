#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#define BUF_SIZE 50
void error_handling(char *message);
int main(int argc,char* argv[])
{
	int serv_sd,clnt_sd;
	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size;
	FILE *fp;
	int read_cnt;

	char message[BUF_SIZE];
	if(argc!=2)
	{
		printf("Usage:%s <port>\n",argv[0]);
		return 0;
	}
	fp=fopen("file_server.c","rb");
	serv_sd=socket(PF_INET,SOCK_STREAM,0);
	if(serv_sd==-1)
		error_handling("socket() error");
	memset(&serv_addr,0,sizeof(&serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(atoi(argv[1]));
	if(bind(serv_sd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1)
		error_handling("bind() error");
	if(listen(serv_sd,5)==-1)
		error_handling("listen() error");
	clnt_addr_size=sizeof(clnt_addr);
	clnt_sd=accept(serv_sd,(struct sockaddr*)&clnt_addr,&clnt_addr_size);
	if(clnt_sd==-1)
		error_handling("accept() error");
	memset(message,0,BUF_SIZE);
	while(1)
	{
		read_cnt=fread((void*)message,1,BUF_SIZE,fp);
		if(read_cnt<BUF_SIZE)
		{
			write(clnt_sd,message,read_cnt);
			break;
		}
		write(clnt_sd,message,BUF_SIZE);
		//printf("%s\n",message);
	}
	shutdown(clnt_sd,SHUT_WR);
	memset(message,0,BUF_SIZE);
	read(clnt_sd,message,BUF_SIZE);
	printf("message from client %s\n",message);
	fclose(fp);
	close(clnt_sd);
	close(serv_sd);
	return 0;
}

void error_handling(char *message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}
