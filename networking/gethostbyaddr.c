#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>
#include<netdb.h>
int main(int argc,char* argv[])
{
	int i;
	struct hostent *host;
	struct sockaddr_in  addr;
	if(argc!=2)
	{
		printf("usage :%s<IP>\n ",argv[0]);
		exit(1);
	}
	memset(&addr,0,sizeof(addr));
	//addr.sin_addr.s_addr=inet_addr(argv[1]);
	//host=gethostbyaddr((char*)&addr.sin_addr,4,AF_INET);  bukeyi 
	host=gethostbyaddr(argv[1],4,AF_INET);
	if(!host)
	{
		printf("gethost error");
		exit(1);
	}
	printf("official name: %s \n",host->h_name);
	for(i=0;host->h_aliases[i];i++)
		printf("Aliases %d %s\n",i+1,host->h_aliases[i]);
	for(i=0;host->h_addr_list[i];i++)
		printf("IP addr %d %s \n",i+1,inet_ntoa(*(struct in_addr *)host->h_addr_list[i]));
	return 0;


}
