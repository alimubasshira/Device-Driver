#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#define SIZE 16
int main( )
{
	int fd,ret;
	char buffW[ ] ="hello"; //write buffer 
	fd = open("/dev/dev04",O_RDWR); //fd represents open file
	if(fd<0){
	perror("Error opening\n");
	return fd;
	}
	ret =write(fd,buffW,sizeof(buffW));
	printf("Wrote %d bytes\n",ret);
	return 0; // close will be called implicitly by OS
}
