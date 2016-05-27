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
	int i=0;
	char buffer [20];
	char d[20]="";
	int n=2048;

	if ((fd = serialOpen ("/dev/ttyAMA0", 9600)) < 0)
	{
    //fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ; 
		return 1 ;
	}

// Loop, getting and printing characters

	while(serialDataAvail(fd)){ //Serialavailable
			i=serialGetchar (fd); // byte entero leido //detecta caracter nulo por defecto

			if(i!=0){
			if(i==02){//caracter de inicio de dato
				do{	
				i=serialGetchar (fd); // byte entero leido
				if(i>47 && i<58){ // rangos de un numero en ascii
			//fprintf(stderr, " IDDDD\n" );
			//fprintf(stderr, " num %d \n",i );
			snprintf(buffer, 10, "%c", i); //convierte el entero a caracter
			strcat(d,buffer); //junta todo los caracteres recibido en una cadena
		}				
			}while(i!=03);//carracter  de finalizacion
		}
		n=atoi(d); //converte la cadena en un entero 
		//fprintf(stderr, "%s\n",d );
		serialClose(fd);
		return n;
	}else{
 	return -1;
	}

}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void sendSerial(char *dato) //Funcion para enviar datos seriales
{	int fd=0;
	if (fd = serialOpen ("/dev/ttyAMA0", 9600))
	{
    //fprintf (stderr, "Unable to open serial device: $

	}

	serialPuts (fd,dato) ;
      //  serialPuts (fd,"  4 ") ; funciona
	serialClose(fd);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void testEnvia(){
	
	while(1){
		sendSerial("4");
		//delay(1000);
		//si recibe x70 codigo de error
		//1,2,3,4,5 OPciones generales
		//existe 1.1 ,1.2
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TestRecibe(){
	int dato=0;
	while(1){
		dato=ReadSerial();
		if (dato!=-1){
			printf("%d\n",dato );
		}
		//delay(2000);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int main(int argc, char const *argv[])
{
	if(wiringPiSetupGpio() == -1){
      //printf("Unable to initialize wiringPi.\n");
		exit(1) ;
	}

	if(Humedad()>700 && Luz()<900){
     Enciende_Bomba(PinB);
     delay(100);
     Abre_Valvula(PinValve1);
  }else{
     Apaga_Bomba(PinB);
     Cierra_Valvula(PinValve1);
  }
	return 0;
} 


/* Notas
Falta validar caracter "/n" en recibe *******

**/
