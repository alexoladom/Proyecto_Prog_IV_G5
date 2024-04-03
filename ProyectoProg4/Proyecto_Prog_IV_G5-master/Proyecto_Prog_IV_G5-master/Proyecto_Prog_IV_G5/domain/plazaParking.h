#include "stdbool.h"


#ifndef plazaParking_h
#define plazaParking_h



typedef struct {

	int numero;
	char zona;
	bool ocupado;

}PlazaParking;


PlazaParking crearPlazaParking(int numero, char zona, bool ocupado);
void imprimirPlazaParking(PlazaParking p);

#endif
