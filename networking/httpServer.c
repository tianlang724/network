#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<pthread.h>
#include<arpa/inet.h>

#define BUF_SIZE 2048
#define BUF_SMALL 100
void* RequestHandler(void * arg);
char* ContentType(char * file);
void SendData(FILE *fp, char* ct, char* filename);
void SendErrorMSG(FILE* file);
void ErrorHandling(char *messsage);

int main(int argc, char* argv[])
{
	int hServSock, hClntSock;
	struct sockaddr_in servAdr, clntAdr;
	int clntAdrSize;
	char buf[BUF_SIZE];
	pthread_t t_id;
	if (argc != 2)
	{
		printf("Usage:%s <port> \n",argv[0]);
		exit(1);
	}
	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&servAdr, 0, sizeof(struct sockaddr_in));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAdr.sin_port = htons(atoi(argv[1]));
	if (bind(hServSock, (struct sockaddr*)&servAdr, sizeof(servAdr)) == -1)
	{
		ErrorHandling("bind() error!");
	}
	if (listen(hServSock, 5) == -1)
	{
		ErrorHandling("listen() error");
	}
	while (1)
	{
		clntAdrSize = sizeof(clntAdr);
		hClntSock = accept(hServSock, (struct sockaddr*)&clntAdr, &clntAdrSize);
		printf("connect Request : %s:%d\n", inet_ntoa(clntAdr.sin_addr), ntohs(clntAdr.sin_port));
		pthread_create(&t_id,NULL,RequestHandler,&hClntSock);
		pthread_detach(t_id);
	}
	close(hServSock);
	return 0;
}

void * RequestHandler(void * arg)
{
	int clntSock =*((int*)arg);
	char req_line[BUF_SMALL];
	FILE* clnt_read;
	FILE* clnt_write;
	char method[10];
	char ct[15];
	char filename[30];

	clnt_read=fdopen(clntSock,"r");
	clnt_write=fdopen(dup(clntSock),"w");
	fgets(req_line,BUF_SMALL,clnt_read);
	if (strstr(req_line, "HTTP/") == NULL)
	{
		SendErrorMSG(clnt_write);
		fclose(clnt_read);
		fclose(clnt_write);
		return ;
	}
	strcpy(method, strtok(req_line, " /"));
	strcpy(filename,strtok(NULL," /"));
	strcpy(ct,ContentType(filename));
	if (strcmp(method, "GET")!=0)
	{
		SendErrorMSG(clnt_write);
		fclose(clnt_read);
		fclose(clnt_write);
		return;
	}
	SendData(clnt_write, ct, filename);
	return 0;
}

void SendData(FILE * fp, char* ct, char* filename)
{
	char protocol[] = "HTTP/1.0 200 OK/r/n";
	char servName[] = "Server:simple web server/r/n";
	char cntlen[] = "Content-length:2048/r/n";
	char cntType[BUF_SMALL];
	char buf[BUF_SIZE];
	FILE * sendFile;
	sprintf(cntType, "Content-type;%s：/r/n/r/n", ct);
	sendFile = fopen(filename, "r");
	if (sendFile  == NULL)
	{
		SendErrorMSG(fp);
		return;
	}
	fputs(protocol,fp);
	fputs(servName,fp);
	fputs(cntlen,fp);
	fputs(cntType,fp);
	while (fgets(buf, BUF_SIZE, sendFile) != NULL)
	{
		fputs(buf,fp);
		fflush(fp);
	}
	fflush(fp);
	fclose(fp);
}
void SendErrorMSG(FILE * fp)
{
	char protocol[] = "HTTP/1.0 400 bad Request/r/n";
	char servName[] = "Server:simple web server/r/n";
	char cntLen[] = "Content-length :2048/r/n";
	char cntType[] = "Content-type :text/html/r/n/r/n";
	char content[] = "<html><head><title>NETWORK</title></head><body><font size=+5><br>发生错误，查看请求文件名和请求方式</font></body></html>";
	fputs(protocol,fp);
	fputs(servName,fp);
	fputs(cntLen,fp);
	fputs(cntType,fp);
	fputs(content,fp);
	fflush(fp);
}

char* ContentType(char* file)
{
	char extionsion[BUF_SIZE];
	char fileName[BUF_SMALL];
	strcpy(fileName, file);
	strtok(fileName, ".");
	strcpy(extionsion, strtok(NULL, "."));
	if (!strcpy(extionsion, "html") || !strcpy(extionsion, "htm"))
		return "text/html";
	else
		return "text/plain";
}
void ErrorHandling(char * message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);

}
