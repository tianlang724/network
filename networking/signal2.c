#include<stdio.h>
#include<unistd.h>
#include<signal.h>
void timeout(int sig)
{
	if(sig==SIGALRM)
	{
		puts("time out\n");
		alarm(3);
	}
}
void keycontrol(int sig)
{
	if(sig==SIGINT)
	{
		puts("exit ?(Y/N)");
		char input=getchar();
		if(strcmp(input,'Y')==0)
			return;
		else
			main();
	}
}
int main(int argc,char * argv)
{
	int i;
	signal(SIGALRM,timeout);
	signal(SIGINT,keycontrol);
	alarm(2);
	for(i=0;i<1000;i++)
	{
		puts("wait...");
	    sleep(100);
	}
	return 0;
}
