#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/wait.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUF_SIZE 20
void error_handling(char*message);
void read_childproc(int sig);
int main(int argc,char* argv [])
{
	int serv_sock,clnt_sock;
	pid_t pid;
	struct sockaddr_in serv_addr,clnt_addr;
	struct sigaction act;
	socklen_t addr_sz;
	char buf[BUF_SIZE];
	int str_len,status;
	if(argc!=2)
	{
		printf("Usage :%s <port>\n",argv[0]);
		exit(1);
	}
	act.sa_handler=read_childproc;
	sigemptyset(&act.sa_mask);
	act.sa_flags=0;
	status=sigaction(SIGCHLD,&act,0);
	serv_sock=socket(PF_INET,SOCK_STREAM,0);
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(atoi(argv[1]));

	if(bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1)
		error_handling("bind() error");
	if(listen(serv_sock,5)==-1)
		error_handling("listen() error");

	int fds[2];
	pipe(fds);
	pid=fork();
	if(pid==0)
	{
		FILE *fp=fopen("echo.txt","wt");
		char msgbuf[BUF_SIZE];
		int i,len;
		for(i=0;i<10;i++)
		{
			memset(&msgbuf,0,BUF_SIZE);
			len=read(fds[0],msgbuf,BUF_SIZE);
			fwrite((void *)msgbuf,1,strlen(msgbuf)-1,fp);
			
			printf("message from client pipe %s,len is%d,strlen is %lu\n",msgbuf,len,(unsigned long int)(strlen(msgbuf)));
		}
		fclose(fp);
		return 0;
	}

	while(1)
	{
		printf("wait connect...\n");
		addr_sz=sizeof(clnt_addr);
		clnt_sock=accept(serv_sock,(struct sockaddr*)&clnt_addr,&addr_sz);
		if(clnt_sock==-1)
			continue;
		else
			puts("new clnt connect...\n");
		pid=fork();
		if(pid==-1)
		{
			close(clnt_sock);
			continue;
		}
		if(pid==0)
		{
			close(serv_sock);
			while(str_len=read(clnt_sock,buf,sizeof(buf))!=0)
			{
				
			   printf("message from client  %s\n",buf);
				write(clnt_sock,buf,strlen(buf));
				write(fds[1],buf,strlen(buf));
				memset(&buf,0,BUF_SIZE);
			}
			close(clnt_sock);
			puts("client disconnect...\n");
			return 0;
		}
		else
			close(clnt_sock);
	}
	close(serv_sock);
}
void read_childproc(int sig)
{
	pid_t pid;
	int status;
	pid=waitpid(-1,&status,WNOHANG);
	printf("remove proc id :%d\n",pid);
}
void error_handling(char * message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}

