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
	struct sockaddr_in serv_addr;
	int str_len;
	FILE *readfp;
	FILE *writefp;

	char message[BUF_SIZE];
	if(argc!=3)
	{
		printf("Usage:%s<IP> <port>\n",argv[0]);
		return 0;
	}
	sock=socket(PF_INET,SOCK_STREAM,0);
	if(sock==-1)
		error_handling("socket() error");
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_addr.sin_port=htons(atoi(argv[2]));
	if(connect(sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr))==-1)
		error_handling("connect() error");
	readfp=fdopen(sock,"r");
	writefp=fdopen(sock,"w");
	while(1)
	{
		if(fgets(message,BUF_SIZE,readfp)==NULL)
			break;
		fputs(message,stdout);
		fflush(stdout);
	}
	fputs("from client: thank you !\n",writefp);
	fflush(writefp);
	fclose(readfp);
	fclose(writefp);
	return 0;
}

void error_handling(char *message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}
