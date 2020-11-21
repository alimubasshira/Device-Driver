#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#define SIZE 12
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
	ret =write(fd,buffW,sizeof(buffW));
	if(ret == sizeof(buffW))
	{
		printf("successfully wrtten %d byte to kernel\n",ret);
	}

	ret = read(fd,buffR,sizeof(buffW));

        printf("message from kernel: %s\n no of data read:%d\n",buffR,ret);
	
	close(fd);

	return 0; 
}
