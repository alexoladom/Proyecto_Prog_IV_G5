#include "stdbool.h"

#ifndef habitaciones_h
#define habitaciones_h


enum tipoHabitacion {simple, doble, suite};

typedef struct {

	int numero;
	int piso;
	enum tipoHabitacion tipo;
	int capacidad;
	float precio;
	bool ocupado;

}Habitacion;


Habitacion crearHabitacion(int numero, int piso, enum tipoHabitacion tipo, int capacidad, float precio, bool ocupado);
void imprimirHabitacion(Habitacion h);

#endif
