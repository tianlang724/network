#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#define BUF_SIZE 1024
#define OPSZ 4
#define RLT_SIZE 4
void error_handling(char *message);
int main(int argc,char* argv[])
{
	int sock;
	struct sockaddr_in serv_addr;
	int str_len;
	char op[BUF_SIZE];
	int op_cnt,result,i;
    printf("op sizeof  is %lu \n",sizeof(op));
	printf("op len is %lu\n",(unsigned long int)strlen(op));
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
	fputs("input num of:",stdout);
	scanf("%d",&op_cnt);
    op[0]=(char)op_cnt;

	for(i=0;i<op_cnt;i++)
	{
		printf("Operand %d : ",i+1);
		scanf("%d",(int *)&op[i*OPSZ+1]);
	}
	fgetc(stdin);
	fputs("operator : ",stdout);
	scanf("%c",&op[op_cnt*OPSZ+1]);
	write(sock,op,op_cnt*OPSZ+2);
	printf("len %d",op_cnt*OPSZ+1);
	printf("op sizeof is %lu\n",sizeof(op));
	printf("op strlen is %lu\n",(unsigned long int)strlen(op));
	read(sock,&result,sizeof(result));
	printf("the result is %d\n",result);
	close(sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}
