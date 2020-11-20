#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#define SIZE 11
int main( )
{
	int fd,ret;
	char buffR[SIZE];          // read buffer
	char buffW[ ] ="Hi..kernel"; //write buffer 
	fd = open("/dev/dev04",O_RDWR);  //fd represents open file
	if(fd < 0)
	{
	perror("Error opening\n");
	return fd;
	}
	ret = read(fd,buffR,SIZE);

	printf("message from kernel: %s\n no of data read:%d\n",buffR,ret);

	ret =write(fd,buffW,sizeof(buffW));

	if(ret == sizeof(buffW))
	{
		printf("successfully wrtten to kernel\n");
	}
	close(fd);
	return 0; 
}
