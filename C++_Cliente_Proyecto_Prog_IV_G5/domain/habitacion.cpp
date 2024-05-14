#include "habitacion.h"


int Habitacion::numHabitaciones=0;
Habitacion::Habitacion(){
	this->numero=-1;
	this->piso=0;
	this->tipo=simple;
	this->capacidad=0;
	this->precio=0;
	this->ocupado=false;
}

Habitacion::Habitacion(int numero,
		int piso,
		enum tipoHabitacion tipo,
		int capacidad,
		float precio,
		bool ocupado){
	this->numero=numero;
	this->piso=piso;
	this->tipo=tipo;
	this->capacidad=capacidad;
	this->precio=precio;
	this->ocupado=ocupado;
}

int Habitacion::getCapacidad()  {
	return capacidad;
}

void Habitacion::setCapacidad(int capacidad) {
	this->capacidad = capacidad;
}

int Habitacion::getNumero()  {
	return numero;
}

void Habitacion::setNumero(int numero) {
	this->numero = numero;
}

bool Habitacion::isOcupado() {
	return ocupado;
}

void Habitacion::setOcupado(bool ocupado) {
	this->ocupado = ocupado;
}

int Habitacion::getPiso()  {
	return piso;
}

void Habitacion::setPiso(int piso) {
	this->piso = piso;
}

float Habitacion::getPrecio()  {
	return precio;
}

void Habitacion::setPrecio(float precio) {
	this->precio = precio;
}

enum tipoHabitacion Habitacion::getTipo()  {
	return tipo;
}

void Habitacion::setTipo(enum tipoHabitacion tipo) {
	this->tipo = tipo;
}



void Habitacion::imprimirHabitacion(){

	char tipos[][10]={"Simple","Doble","Suite"};
	char ocupadoc[][10]={"Libre","Ocupado"};
	cout<<"Habitacion (nº "<<numero<<", piso "<<piso
	<<", "<<tipos[tipo]<<", "<<capacidad<<"camas , "
	<<precio<<"€, "<<ocupadoc[ocupado]<<")\n";
}














