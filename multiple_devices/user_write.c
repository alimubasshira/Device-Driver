#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#define SIZE 16

int main( )
{
	int fd,ret;
	char buffW[ ] ="FromUser"; //write buffer 
	fd = open("/dev/sample0",O_RDWR); //sample0 c 42 0 //fd represents open file
	if(fd<0)
	{
		perror("Error opening\n");
		return fd;
	}
	ret =write(fd,buffW,sizeof(buffW));
	printf("Wrote %d bytes\n",ret);
	return 0; // close will be called implicitly by OS
}
