#include "plazaParking.h"


PlazaParking::PlazaParking(){
	this->numero=-1;
	this->zona="A";
	this->ocupado=false;
}

PlazaParking::PlazaParking(int numero,string zona,bool ocupado){
	this->numero=numero;
	this->zona=zona;
	this->ocupado=ocupado;
}

int PlazaParking::getNumero()  {
	return numero;
}

void PlazaParking::setNumero(int numero) {
	this->numero = numero;
}

bool PlazaParking::isOcupado()  {
	return ocupado;
}

void PlazaParking::setOcupado(bool ocupado) {
	this->ocupado = ocupado;
}

string PlazaParking::getZona()  {
	return zona;
}

void PlazaParking::setZona( string &zona) {
	this->zona = zona;

}

void PlazaParking::imprimirPlazaParking(){
	cout<<"PlazaParking ("<<numero<<", zona "<<zona<<", "<<ocupado;
}
