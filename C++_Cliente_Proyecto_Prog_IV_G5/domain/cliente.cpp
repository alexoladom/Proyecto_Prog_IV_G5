#include "cliente.h"

	int Cliente::numClientes=0;

	Cliente::Cliente(){

		this->dni=-1;
		this->nombre="";
		this->edad=0;
		this->correo="";

		++numClientes;

	}

	Cliente::Cliente(int dni, string nombre, int edad, string correo){

		this->dni=dni;
		this->nombre=nombre;
		this->edad=edad;
		this->correo=correo;

		++numClientes;
	}

	Cliente::Cliente(const Cliente &other) {
		this->dni=other.dni;
		this->nombre=other.nombre;
		this->edad=other.edad;
		this->correo=other.correo;

		++numClientes;//Quitalo si no lo ves bien

	}

	void Cliente::setNombre(string nombre){
		this->nombre=nombre;
	}

	void Cliente::setEdad(int edad){
		this->edad=edad;
	}

	void Cliente::setCorreo(string correo){
		this->correo=correo;
	}


	int Cliente::getDni(){
		return this->dni;
	}

	string Cliente::getNombre(){
		return this->nombre;
	}

	int Cliente::getEdad(){
		return this->edad;
	}


	string Cliente::getCorreo(){
		return this->correo;
	}

	Cliente::~Cliente() {
	    --numClientes;
	}

	void Cliente::imprimir(){

		cout<<"Ciliente ( DNI: "<<dni<<", "<<nombre<<", "<<edad<<"años, "<<correo<<")\n";
	}
