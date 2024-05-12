#include "reserva.h"


int Reserva::numReservas=0;
Reserva::Reserva(){
	this->id=-1;
	this->fecha="";
	this->dniCliente=0;
	this->numeroHabitacion=0;
	this->numeroPlazaParking=0;
}

int Reserva::getDniCliente()  {
	return dniCliente;
}

void Reserva::setDniCliente(int dniCliente) {
	this->dniCliente = dniCliente;
}

 string Reserva::getFecha()  {
	return fecha;
}

void Reserva::setFecha( string &fecha) {
	this->fecha = fecha;
}

int Reserva::getId() {
	return id;
}

void Reserva::setId(int id) {
	this->id = id;
}

int Reserva::getNumeroHabitacion()  {
	return numeroHabitacion;
}

void Reserva::setNumeroHabitacion(int numeroHabitacion) {
	this->numeroHabitacion = numeroHabitacion;
}

int Reserva::getNumeroPlazaParking()  {
	return numeroPlazaParking;
}

void Reserva::setNumeroPlazaParking(int numeroPlazaParking) {
	this->numeroPlazaParking = numeroPlazaParking;
}

Reserva::Reserva(int id,string fecha, int dniCliente,int numeroHabitacion,int numeroPlazaParking){

	this->id=id;
	this->fecha=fecha;
	this->dniCliente=dniCliente;
	this->numeroHabitacion=numeroHabitacion;
	this->numeroPlazaParking=numeroPlazaParking;
}


void Reserva::imprimirReserva(){
	cout<<"Reserva("<<id<<", "<<fecha
	<<", cliente "<<dniCliente<<", habitacion "
	<<numeroHabitacion<<", parking "<<numeroPlazaParking;
}
