#include<stdio.h>
#include<arpa/inet.h>
int main()
{
	char *addr="1.2.3.4";
	char *addr2="1.2.3.256";
	unsigned long conv_addr=inet_addr(addr);
	if(conv_addr==INADDR_NONE)
		printf("error");
	else
		printf("network ordered integer %#lx \n",conv_addr);
	conv_addr=inet_addr(addr2);
	if(conv_addr==INADDR_NONE)
		printf("error\n");
	else
		printf("right\n");
	return 0;
}


