#include "reserva.h"
#include "stdio.h"
#include "stdbool.h"
#include "string.h"
#include "stdlib.h"

Reserva crearReserva(int id, char *fecha, int dniCliente, int numeroHabitacion, int numeroPlazaParking){
	if(dniCliente<0 || numeroHabitacion<0 || numeroPlazaParking <0){

		Reserva s ={-1,(char*)malloc(11*sizeof(char)),-1,-1,-1};
		s.fecha = strcpy(s.fecha,fecha);

		return s;
	}else{
		Reserva r={id,(char*)malloc(11*sizeof(char)),dniCliente,numeroHabitacion,numeroPlazaParking};
		r.fecha = strcpy(r.fecha,fecha);
		return r;
	}
}
void imprimirReserva(Reserva r){
	printf("Reserva %i, fecha: %s, cliente: %i, habitacion: %i, plaza de parking: %i\n",
			r.id,r.fecha,r.dniCliente,r.numeroHabitacion,r.numeroPlazaParking);


}


