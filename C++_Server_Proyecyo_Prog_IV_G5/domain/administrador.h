#ifndef administrador_h
#define administrador_h

#include <iostream>
using namespace std;

enum funcionAdministrador{
	recepcion,direccion,contabilidad,seguridad
};

class Administrador{

private:
	int dni;
	string nombre;
	int edad;
	string correo;
	enum funcionAdministrador funcion;

public:

Administrador(int dni, string nombre,int edad, string correo, enum funcionAdministrador funcion);
Administrador();
~Administrador();

void setNombre(string nombre);
void setEdad(int edad);
void setCorreo(string correo);
void setFuncion(enum funcionAdministrador funcion);

int getDni();
string getNombre();
int getEdad();
string getCorreo();
enum funcionAdministrador getFuncion();

};

#endif
