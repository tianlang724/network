#include<stdio.h>
#include<unistd.h>

int gval=10;
int main(int argc,char *argv[])
{
	//extern int gval;
	pid_t pid;
	int lval=20;
	gval++;
	lval+=5;
	pid=fork();
	if(pid==0)
		gval+=2,lval+=2;
	else
		gval=2,lval-=2;
	if(pid==0) //0 son   !0  father
		printf("Child Proc:[%d,%d]",gval,lval);
	else
		printf("Father Proc:[%d,%d]",gval,lval);
	return 0;
}

