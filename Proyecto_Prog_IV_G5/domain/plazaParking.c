#include "stdio.h"
#include "plazaParking.h"


PlazaParking crearPlazaParking(int numero, char zona, bool ocupado){
	PlazaParking p = {numero,zona,ocupado};
	return p;
}
void imprimirPlazaParking(PlazaParking p){

	char ocupado[][10]={"libre", "ocupado"};
	printf("Plaza Parking %i, zona: %c, %s", p.numero,p.zona,ocupado[p.ocupado]);

}



