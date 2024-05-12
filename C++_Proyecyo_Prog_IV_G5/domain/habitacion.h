#ifndef habitacion_h
#define habitacion_h

#include <iostream>
using namespace std;


enum tipoHabitacion {simple, doble, suite};

class Habitacion{
private:
	int numero;
	int piso;
	enum tipoHabitacion tipo;
	int capacidad;
	float precio;
	bool ocupado;

public:
	static int numHabitaciones;
	Habitacion();
	Habitacion(int numero,
	int piso,
	enum tipoHabitacion tipo,
	int capacidad,
	float precio,
	bool ocupado);



	void imprimirHabitacion();
	int getCapacidad() ;
	void setCapacidad(int capacidad);
	int getNumero() ;
	void setNumero(int numero);
	bool isOcupado() ;
	void setOcupado(bool ocupado);
	int getPiso() ;
	void setPiso(int piso);
	float getPrecio() ;
	void setPrecio(float precio);
	enum tipoHabitacion getTipo() ;
	void setTipo(enum tipoHabitacion tipo);
	void setNumHabitaciones(int num);
	int getNumHabitaciones();
};




#endif
