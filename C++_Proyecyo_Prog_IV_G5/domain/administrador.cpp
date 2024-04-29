#include "administrador.h"

Administrador::Administrador(int dni, string nombre,int edad, string correo, enum funcionAdministrador funcion){

	this->dni=dni;
	this->nombre=nombre;
	this->edad=edad;
	this->correo=correo;
	this->funcion=funcion;
}

Administrador::Administrador(){
	this->dni=-1;
	this->nombre="";
	this->edad=0;
	this->correo="";
	this->funcion=recepcion;
}


void Administrador::setNombre(string nombre){
	this->nombre=nombre;
}
void Administrador::setEdad(int edad){
	this->edad=edad;
}
void Administrador::setCorreo(string correo){
	this->correo=correo;
}
void Administrador::setFuncion(enum funcionAdministrador funcion){
	this->funcion= funcion;
}

int Administrador::getDni(){
	return this->dni;
}

string Administrador::getNombre(){
	return this->nombre;
}
int Administrador::getEdad(){
	return this->edad;
}

string Administrador::getCorreo(){
	return this->correo;
}

enum funcionAdministrador Administrador::getFuncion(){
	return this->funcion;
}

