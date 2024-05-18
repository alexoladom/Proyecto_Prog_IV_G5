#ifndef funcionesBD_h
#define funcionesBD_h

#include "../domain/cliente.h"
#include "../domain/reserva.h"
#include "../domain/habitacion.h"
#include "../domain/plazaParking.h"
#include "../domain/cliente.h"
extern "C" {
#include "sqlite3.h"
}
#include "string.h"

sqlite3* conectarDB();

Cliente* getListaClientes(sqlite3*db); //DONE	Checked
int comprobarDni(sqlite3* db, int dni);//DONE	Checked
int comprobarContra(sqlite3* db, int dni, char*contrasena);//DONE	Checked
int anadirDniContra(sqlite3* db, int dni, char* contra);//DONE	Checked
int anadirCliente(Cliente &c,sqlite3*db);//DONE	Cheked

Reserva* getListaReservas(sqlite3*db); //DONE	Checked
int anadirReserva(Reserva &r, sqlite3* db); //DONE	Checked
int borrarReserva(sqlite3*db,int numero); //DONE	Checked
int modificarReserva(sqlite3* db, Reserva &r);

Habitacion* getListaHabitaciones(sqlite3*db); //DONE	Checked
int borrarHabitacion(sqlite3*db,int numero); //DONE	Checked
int anadirHabitacion(sqlite3*db,Habitacion &h);//DONE	Checked
int modificarHabitacion(sqlite3*db,Habitacion &h);

PlazaParking* getListaPlazasParking(sqlite3*db);//DONE	Checked
int anadirPlazaParking(sqlite3*db,PlazaParking &p);//DONE	Checked
int borrarPlazaParking(sqlite3*db, int numero);//DONE	Checked
int modificarPlazaParking(sqlite3*db,PlazaParking &p);





#endif

