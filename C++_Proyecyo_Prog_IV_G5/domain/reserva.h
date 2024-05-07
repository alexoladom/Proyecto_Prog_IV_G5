#ifndef reserva_h
#define reserva_h

#include <iostream>
using namespace std;

class Reserva{

private:
	int id;
	string fecha;
	int dniCliente;
	int numeroHabitacion;
	int numeroPlazaParking;

public:
	Reserva();
	Reserva(int id, string fecha, int dniCliente, int numeroHabitacion, int numeroPlazaParking);
	void imprimirReserva();

	int getDniCliente() ;
	void setDniCliente(int dniCliente);
	 string getFecha() ;
	void setFecha( string &fecha);
	int getId() ;
	void setId(int id);
	int getNumeroHabitacion() ;
	void setNumeroHabitacion(int numeroHabitacion);
	int getNumeroPlazaParking() ;
	void setNumeroPlazaParking(int numeroPlazaParking);
};

#endif
