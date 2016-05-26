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
#include <string.h>


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ReadSerial () //Funcion para recibir datos seriales
{
	int fd =0;
	int n=0;
	int i=0;
    char buffer [10];
    char d[20]="";

	if ((fd = serialOpen ("/dev/ttyAMA0", 9600)) < 0)
	{
    //fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ; 
		return 1 ;
	}

// Loop, getting and printing characters
	while(serialDataAvail(fd)){
		i=serialGetchar (fd); // byte entero leido
		snprintf(buffer, 10, "%d", i); //convierte el entero a caracter
		//itoa (i,buffer,10)
		strcat(d,buffer); //junta todo los caracteres recibido en una cadena
		}

		 n=atoi(d); //converte la cadena en un entero
		return n;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void sendSerial(int dato,int fd) //Funcion para enviar datos seriales
{
	  if (fd = serialOpen ("/dev/ttyAMA0", 9600))
        {
    //fprintf (stderr, "Unable to open serial device: $
               
        }

        serialPuts (fd,"  4 ") ;
	    serialClose(fd);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void testEnvia(){
	 int fd;

        
        if((fd = serialOpen ("/dev/ttyAMA0", 9600)) < 0)
        {
      //printf("Unable to open serial device: %s\n", strerror(errno));
                exit(1);
        }

	while(1){
		sendSerial(4,fd);
		delay(1000);
		//si recibe x70 codigo de error
		//1,2,3,4,5 OPciones generales
		//existe 1.1 ,1.2
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TestRecibe(){
	int dato=0;
	while(1){
		if(dato=ReadSerial()!=0){
		printf("%d\n",dato );
		}
		
	
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int main(int argc, char const *argv[])
{
	if(wiringPiSetupGpio() == -1){
      //printf("Unable to initialize wiringPi.\n");
                exit(1) ;
        }

	// testEnvia();
	
	TestRecibe();
	delay(2000);
	return 0;
} 


/* Notas
Falta validar caracter "/n" en recibe *******

**/ 
