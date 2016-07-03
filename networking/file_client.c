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
	int sd;
	struct sockaddr_in serv_addr;
	int read_cnt;
	FILE * fp;
	fp=fopen("receive.dat","wb");
	char message[BUF_SIZE];
	if(argc!=3)
	{
		printf("Usage:%s<IP> <port>\n",argv[0]);
		return 0;
	}
	sd=socket(PF_INET,SOCK_STREAM,0);
	if(sd==-1)
		error_handling("socket() error");
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_addr.sin_port=htons(atoi(argv[2]));
	if(connect(sd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))==-1)
		error_handling("connect() error");
	while(read_cnt=read(sd,message,BUF_SIZE)!=0) //read success return 1!!
	{
		//printf("read_cnt %d,strlrn(message) %lu",read_cnt,(unsigned long int)strlen(message));
		fwrite((void *)message,1,strlen(message)-1,fp);
		//printf("%s\n",message);
		memset(message,0,BUF_SIZE);

	}
	puts("received file data");
	write(sd,"thank you ",10);
	fclose(fp);
	close(sd);
	return 0;
}

void error_handling(char *message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}
