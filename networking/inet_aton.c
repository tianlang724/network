#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
int main()
{
	char *addr="1.2.3.4";
	struct sockaddr_in addr_inet;
	if(!inet_aton(addr,&addr_inet.sin_addr))
		printf("error/n");
	else
		printf("nerwork ordered integer %#x\n",addr_inet.sin_addr.s_addr);
	return 0;
}
