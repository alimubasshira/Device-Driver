#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#define SIZE 16
int main( )
{
	int fd,ret;
	char buffR[SIZE];          // read buffer
	fd = open("/dev/dev04",O_RDWR); 
	if(fd<0){
	perror("Error opening\n");
	return fd;
	}
	ret = read(fd,buffR,SIZE);
	printf("Got: %s\n No of Bytes Read:%d\n",buffR,ret);
	return 0; // close will be called implicitly by OS
}