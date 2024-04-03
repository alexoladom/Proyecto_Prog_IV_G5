
#include "stdbool.h"

#ifndef reserva_h
#define reserva_h



typedef struct {

	int id;
	char fecha[11];
	int dniCliente;
	int numeroHabitacion;
	int numeroPlazaParking;

}Reserva;

Reserva crearReserva(int id, char fecha[11], int dniCliente, int numeroHabitacion, int numeroPlazaParking);
void imprimirReserva(Reserva r);


#endif
