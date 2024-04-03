#include "cliente.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"

Cliente crearCliente(int dni, char*nombre,int edad ,char*correo){

	if(edad<0){
		Cliente c ={-1,(char*)malloc(20*sizeof(char)),0,(char*)malloc(30*sizeof(char))};
		c.nombre= strcpy(c.nombre,nombre);
		c.correo = strcpy(c.correo,correo);
		printf("Error creando el cliente, edad incorrecta");
		return c;
	}else{
		Cliente c ={dni,(char*)malloc(20*sizeof(char)),edad,(char*)malloc(30*sizeof(char))};
		c.nombre= strcpy(c.nombre,nombre);
		c.correo = strcpy(c.correo,correo);
		return c;
	}

}


void imprimirCliente(Cliente c){

	printf("Cliente %i, nombre: %s, edad: %i, correo: %s", c.dni,c.nombre,c.edad,c.correo);


}
