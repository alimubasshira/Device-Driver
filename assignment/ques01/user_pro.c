#include <fcntl.h>
#include <stdio.h>
int main ()
{
   int fd;
   fd = open ("/dev/mydev", O_RDWR );
   if(fd)
   {
	   printf("file succesfully open\n");
   }
   close(fd);
   printf ("After closing file\n");

   return 0;
}
