#include "plazaParking.h"


int PlazaParking::numPlazaParkings=0;

PlazaParking::PlazaParking(){
	this->numero=-1;
	this->zona="A";
	this->ocupado=false;

	++numPlazaParkings;
}

PlazaParking::PlazaParking(int numero,string zona,bool ocupado){
	this->numero=numero;
	this->zona=zona;
	this->ocupado=ocupado;

	++numPlazaParkings;
}

PlazaParking::PlazaParking(const PlazaParking &other) {
	this->numero=other.numero;
	this->zona=other.zona;
	this->ocupado=other.ocupado;

    ++numPlazaParkings;//Ns si lo quieres poner
}

PlazaParking::~PlazaParking() {
    --numPlazaParkings;
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
	char ocupadoc[][10]={"Libre","Ocupado"};

	cout<<"PlazaParking ("<<numero<<", zona "<<zona<<", "<<ocupadoc[ocupado]<<")\n";
}
