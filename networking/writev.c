#include<stdio.h>
#include<sys/uio.h>
int main(int argc,char *argv)
{
	struct iovec vec[2];
	char buf1[]="ASDFG";
	char buf2[]="12345";
	int str_len;
	vec[0].iov_base=buf1;
	vec[0].iov_len=3;
	vec[1].iov_base=buf2;
	vec[1].iov_len=4;
	str_len=writev(1,vec,2);
	puts("");
	printf("write bytes:%d \n",str_len);
	return 0;
}
