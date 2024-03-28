#include "reserva.h"
#include "stdio.h"
#include "stdbool.h"
#include "string.h"

Reserva crearReserva(int id, char *fecha, int dniCliente, int numeroHabitacion, int numeroPlazaParking){
	if(dniCliente<0 || numeroHabitacion<0 || numeroPlazaParking <0){

		Reserva s ={-1,*fecha,-1,-1,-1};
		printf("a");
		return s;
	}else{
		Reserva r={id,*fecha,dniCliente,numeroHabitacion,numeroPlazaParking};
		return r;
	}
}
void imprimirReserva(Reserva r){
	printf("Reserva %i, fecha: %s, cliente: %i, habitacion: %i, plaza de parking: %i\n", r.id,r.fecha,r.dniCliente,r.numeroHabitacion,r.numeroPlazaParking);
}


int main(){


	Reserva h = crearReserva(-1,"asd",0,6,0);
	imprimirReserva(h);

	return 0;
}
