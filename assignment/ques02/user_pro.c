#include<fcntl.h>
#include<stdio.h>
int main ()
{
   char ubuffer [10]="Hi there";
   char kbuffer [20];
   int fd;
   fd= open("/dev/device02", O_RDWR);
   printf("message send to driver :%s\n",ubuffer);
   write (fd ,ubuffer ,sizeof(ubuffer));
   read (fd , kbuffer ,sizeof(kbuffer));
   printf("message receive from driver : %s\n", kbuffer);
   close (fd);
   return 0;
}
