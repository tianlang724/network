#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<stdlib.h>
#define BUF_SIZE 50
#define NAME_SIZE 20
void *send_msg(void * arg);
void *recv_msg(void * arg);
void error_handling(char *msg);
char name[NAME_SIZE]="[DEFAULT]";
char msg[BUF_SIZE];
int main(int argc,char* argv[])
{
	int sock;
	struct sockaddr_in serv_addr;
	void * thread_return;
	pthread_t snd_id;
	pthread_t recv_id;
	if(argc!=4)
	{
		printf("usage:%s<IP><Port><Name>\n",argv[0]);
		exit(1);
	}
	sprintf(name,"[%s]",argv[3]);
	sock=socket(PF_INET,SOCK_STREAM,0);
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_addr.sin_port=htons(atoi(argv[2]));
	if(connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1)
	error_handling("connect() error");
	pthread_create(&snd_id,NULL,send_msg,(void *)&sock);
	pthread_create(&recv_id,NULL,recv_msg,(void*)&sock);
	pthread_join(snd_id,&thread_return);
	pthread_join(recv_id,&thread_return);
	close(sock);
	return 0;
}
void* send_msg(void* arg)
{
	int sock=*((int *)arg);
	char name_msg[NAME_SIZE+BUF_SIZE];
	while(1)
	{
		memset(name_msg,0,sizeof(name_msg));
		fgets(msg,BUF_SIZE,stdin);
		//printf("lalala5");
		if(!strcmp(msg,"q\n"))
		{
			close(sock);
			exit(0);
		}
	 	sprintf(name_msg,"%s %s",name,msg);
	 	write(sock,name_msg,strlen(name_msg));
	 } 
	return NULL;

 } 
 void* recv_msg(void *arg)
 {
 	int sock=*((int *)arg);
 	char name_msg[NAME_SIZE+BUF_SIZE];
 	int str_len;
 	while(1)
 	{
 		str_len=read(sock,name_msg,NAME_SIZE+BUF_SIZE-1);
 		if(str_len==-1)
 		return (void *)-1;
 		name_msg[str_len]=0;
 		fputs(name_msg,stdout);
		memset(name_msg,0,sizeof(name_msg));
	 }
	 return NULL;
 }
 void error_handling(char *message)
 {
 	fputs(message,stderr);
 	fputc('\n',stderr);
 	exit(1); 
 }
