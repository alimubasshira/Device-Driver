#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#define SIZE 20
int main( )
{
	int fd,ret;
	char buffR[SIZE];          // read buffer
	char buffW[ ] ="Hi..kernel"; //write buffer 
	fd = open("/dev/dev04",O_RDWR); //sample0 c -- 0 //fd represents open file
	if(fd<0)
	{
	perror("Error opening\n");
	return fd;
	}
	ret = read(fd,buffR,SIZE);
//	ret =write(fd,buffW,sizeof(buffW));
	close(fd);
	return 0; 
}
