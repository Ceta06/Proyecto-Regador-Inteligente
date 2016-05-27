//// poner en codigo original filtro para caracter nulo
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	int size=50;
	char string[] = {0, 0, 0, 10, 02, 49, 49, 03}; // assumes ASCII codigo 02 inici a 03 fin
	int cont=0;
	int i;
	char buffer [3];
	char d[5]="";
	int n=0;

	while(cont<50){ //Serialavailable
		i=string[cont]; //borrar en futur
		//fprintf(stderr, "%d ",i );
		if(i==02){//caracter de inicio
			do{
				cont++;
				i=string[cont]; //borrar en futur
				if(i>47 && i<58){
			//fprintf(stderr, " IDDDD\n" );
			//fprintf(stderr, " num %d \n",i );
			snprintf(buffer,3, "%c", i); //convierte el entero a caracter
			strcat(d,buffer); //junta todo los caracteres recibido en una cadena
		}
			}while(i!=03);//carracter  de finalizacion
		}
	cont++;
}
		n=atoi(d); //converte la cadena en un entero 
		fprintf(stderr, " %d\n",n );
		return 0;
	}
