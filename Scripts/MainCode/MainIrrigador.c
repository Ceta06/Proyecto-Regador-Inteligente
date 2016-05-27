/*
Proyecto Final 
Sistema de irrigacion inteligente
Utilizando enfoque de tiempo Real
20 /may/2016
Merida Yucatan Mexico
 */


#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <wiringPi.h>
#include <wiringSerial.h>






int ReadSerial () //Funcion para recibir datos seriales
{
	int fd ;
	int dato;
	if ((fd = serialOpen ("/dev/ttyAMA0", 9600)) < 0)
	{
    //fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ; 
		return 1 ;
	}

// Loop, getting and printing characters

	while(serialDataAvail(int fd)){
		dato=serialGetchar (fd)) ; //**********
  //  fflush (stdout) ;
		}
}




void sendSerial(int dato) //Funcion para enviar datos seriales
{
	int fd;

	if(wiringPiSetupGpio() == -1){
      //printf("Unable to initialize wiringPi.\n");
		exit(1) ;
	}
	if((fd = serialOpen ("/dev/ttyAMA0", 9600)) < 0)
	{
      //printf("Unable to open serial device: %s\n", strerror(errno));
		exit(1);
	}
	serialPutchar(fd,dato);
	serialClose(fd);
}





int main(int argc, char const *argv[])
{
	while(true){
		sendSerial(1);
		delay(5000);
		sendSerial(2);
		delay(5000);
		sendSerial(1);
		delay(5000);
		sendSerial(1);
		delay(5000);
		sendSerial(1);
		//si recibe x70 codigo de error
		//1,2,3,4,5 OPciones generales
		//existe 1.1 ,1.2
	}

	return 0;
} 

/* Notas
Falta validar caracter "/n" en recibe *******

**/