#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <wiringPi.h>
#include <wiringSerial.h>

int main(int argc, const char**argv)
{
   int fd;
   
   if(wiringPiSetupGpio() == -1){
      printf("Unable to initialize wiringPi.\n");
      exit(1) ;
   }
   if((fd = serialOpen ("/dev/ttyAMA0", 9600)) < 0)
   {
      printf("Unable to open serial device: %s\n", strerror(errno));
      exit(1);
   }
   serialPutchar(fd,47);
   serialClose(fd);
   return 0;
}
