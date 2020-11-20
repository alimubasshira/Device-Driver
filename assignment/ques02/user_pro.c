#include<fcntl.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>


int main ()
{
   char ubuffer [10]="Hi there";
   char kbuffer [20];
   int fd;
   fd= open("/dev/my_device", O_RDWR);
   if(fd<0)
   {
   	printf("error in opening file\n");
	return -1;
   }
   printf("message send to driver :%s\n",ubuffer);
   write (fd ,ubuffer ,sizeof(ubuffer));
   read (fd , kbuffer ,sizeof(kbuffer));
   printf("message receive from driver : %s\n", kbuffer);
   close (fd);
   return 0;
}
