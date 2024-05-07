#ifndef plazaparking_h
#define plazaparking_h



#include <iostream>
using namespace std;

class PlazaParking{
private:
	int numero;
	string zona;
	bool ocupado;


public:
	PlazaParking();
	PlazaParking(int numero, string zona, bool ocupado);
	void imprimirPlazaParking();
	int getNumero() ;
	void setNumero(int numero);
	bool isOcupado() ;
	void setOcupado(bool ocupado);
	string getZona();
	void setZona(string &zona);
};


#endif
