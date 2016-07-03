#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#define BUF_SIZE 1024
#define OPSZ 4
void error_handling(char *message);
int calculate(int oopnum,int  opds[],char op);
int main(int argc,char* argv[])
{
	int serv_sock;
	int clnt_sock;
	int recv_len,recv_cnt,result,op_cnt,i;
	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size;

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
	if(bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1)
		error_handling("bind() error");
	if(listen(serv_sock,5)==-1)
		error_handling("listen() error");
	clnt_addr_size=sizeof(clnt_addr);
	clnt_sock=accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_size);
	op_cnt=0;
	recv_len=0;
	recv_cnt=read(clnt_sock,&op_cnt,1);
	while(recv_len<op_cnt*OPSZ+1)
	{
		recv_cnt=read(clnt_sock,&message[recv_len],BUF_SIZE);
		recv_len+=recv_cnt;
	}
	result=calculate(op_cnt,(int *)message,message[recv_len-1]);
	write(clnt_sock,(char*)&result,sizeof(result));
	printf("op is %c,result is %d,len is %d\n",message[recv_len-1],result,recv_len);
	close(clnt_sock);
	close(serv_sock);
	return 0;
}
int  calculate(int opnum,int opds[],char op)
{
	int result=opds[0];
	int i;
	switch(op)
	{
		case '+':
			for(i=1;i<opnum;i++)
			//	printf("op is\n",opds[i]);
				result+=opds[i];
			break;
		case '-':
			for(i=1;i<opnum;i++)
				result-=opds[i];
			break;
		case '*':
			for(i=1;i<opnum;i++)
				result*=opds[i];
			break;
	}
	return result;

}

void error_handling(char *message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}
