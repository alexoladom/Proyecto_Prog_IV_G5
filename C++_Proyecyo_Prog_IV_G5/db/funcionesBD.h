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

Cliente* getListaClientes(sqlite3*db); //DONE
int comprobarDni(sqlite3* db, int dni);//DONE
int comprobarContra(sqlite3* db, int dni, char*contrasena);
int anadirDniContra(sqlite3* db, int dni, char* contra);
int anadirCliente(Cliente &c,sqlite3*db);//DONE

Reserva* getListaReservas(sqlite3*db); //DONE
int anadirReserva(Reserva &r, sqlite3* db); //DONE
int borrarReserva(sqlite3*db,int numero); //DONE

Habitacion* getListaHabitaciones(sqlite3*db); //
int borrarHabitacion(sqlite3*db,int numero); //
int anadirHabitacion(sqlite3*db,Habitacion &h);//

PlazaParking* getListaPlazasParking(sqlite3*db);//
int anadirPlazaParking(sqlite3*db,PlazaParking &p);
int borrarPlazaParking(sqlite3*db, int numero);





#endif

