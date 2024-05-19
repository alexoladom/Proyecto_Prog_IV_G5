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
	static int numClientes;
	Cliente();
	Cliente(int dni, string nombre, int edad, string correo);
	Cliente(const Cliente &other);


	void setNombre(string nombre);
	void setEdad(int edad);
	void setCorreo(string correo);

	int getDni();
	string getNombre();
	int getEdad();
	string getCorreo();

	~Cliente();

	void imprimir();


};

#endif
