#ifndef cliente_h
#define cliente_h

#include <iostream>
using namespace std;

class Cliente {

private:
	int dni;
	string nombre;
	int edad;
	string correo;

public:
	Cliente();
	Cliente(int dni, string nombre, int edad, string correo);

	void setNombre(string nombre);
	void setEdad(int edad);
	void setCorreo(string correo);

	int getDni();
	string getNombre();
	int getEdad();
	string getCorreo();


	void imprimir();


};

#endif
