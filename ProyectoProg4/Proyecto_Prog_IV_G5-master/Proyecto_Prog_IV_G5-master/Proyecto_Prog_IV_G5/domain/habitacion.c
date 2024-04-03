#include "habitacion.h"
#include "stdio.h"
#include "stdbool.h"


Habitacion crearHabitacion(int numero, int piso, enum tipoHabitacion tipo, int capacidad, float precio, bool ocupado){
	if(precio<0 || piso<0 || capacidad<0){
		printf("Error al crear habitacion, algun atributo <0\n");
		Habitacion c= {-1,0,tipo,0,0,false};
		return c;

	}
	Habitacion h= {numero,piso,tipo,capacidad,precio,ocupado};
	return h;
}


void imprimirHabitacion(Habitacion h){

	char tipos[][10]={"Simple","Doble","Suite"};
	char ocupado[][10]={"libre", "ocupado"};

	printf("Habitacion %i, piso: %i, tipo: %s, capacidad: %i, precio: %.2f, %s.\n",
			h.numero,h.piso,tipos[h.tipo],h.capacidad,h.precio, ocupado[h.ocupado]);

}



