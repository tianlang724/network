#include<stdio.h>
#include<fcntl.h>
int main()
{
	FILE *fp;
	int fd=open("read.txt",O_WRONLY|O_CREAT|O_TRUNC);
	if(fd==-1)
	{
		fputs("file error",stdout);
		return -1;
	}
	fp=fdopen(fd,"w");
	fputs("network is interesting!",fp);
	fclose(fp);
	close(fd);
	return 0;
}
