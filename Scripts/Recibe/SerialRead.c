#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <wiringPi.h>
#include <wiringSerial.h>


int main ()
{
  int fd ;

  if ((fd = serialOpen ("/dev/ttyAMA0", 9600)) < 0)
  {
    fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
    return 1 ;
  }

// Loop, getting and printing characters

  for (;;)
  {
    putchar (serialGetchar (fd)) ;
    fflush (stdout) ;
  }
}
