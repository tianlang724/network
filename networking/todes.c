#include<stdio.h>
#include<fcntl.h>
int main()
{
	FILE *fp;
	int fd=open("news.txt",O_WRONLY|O_CREAT|O_TRUNC);
	if(fd==-1)
	{
		fputs("file error",stdout);
		return -1;
	}
	printf("first file describer: %d\n",fd);
	fp=fdopen(fd,"w");
	fputs("tcp/ip socket\n",fp);
	printf("second file describer ; %d\n",fileno(fp));
	fclose(fp);
}
