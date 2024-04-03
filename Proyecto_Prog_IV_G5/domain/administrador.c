#include "administrador.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"

Administrador crearAdministrador (int dni, char*nombre, int edad, char*correo, enum funcionAdministrador funcion){

	if (edad<0){
		Administrador a = {-1,(char*)malloc(20*sizeof(char)),0,(char*) malloc(30*sizeof(char)),recepcion};
		a.nombre=strcpy(a.nombre,nombre);
		a.correo=strcpy(a.nombre,correo);

		printf("Error creando administrador, edad invalida");
		return a;
	}else{
		Administrador a = {dni,(char*)malloc(20*sizeof(char)),edad,(char*) malloc(30*sizeof(char)),funcion};
		a.nombre=strcpy(a.nombre,nombre);
		a.correo=strcpy(a.nombre,correo);

		return a;
	}


}


