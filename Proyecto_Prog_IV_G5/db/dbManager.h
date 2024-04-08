

#ifndef dbManager_h
#define dbManager_h
#include <stdio.h>
#include "sqlite3.h"
#include <string.h>
#include "stdbool.h"
#include "../domain/cliente.h"
#include "../domain/reserva.h"
#include "../domain/habitacion.h"
#include "../domain/plazaParking.h"

#define OK 1
#define NOT_OK 0



sqlite3* conectarDB();

void imprimirClientes(sqlite3*db); //DONE
void anadirCliente(Cliente c,sqlite3*db);//DONE
void imprimirReservas(sqlite3*db); //DONE
void anadirReserva(Reserva r, sqlite3* db); //DONE
void borrarReserva(sqlite3*db,int numero); //DONE
void imprimirHabitaciones(sqlite3*db); //DONE
void borrarHabitacion(sqlite3*db,int numero); //DONE
void anadirHabitacion(sqlite3*db,Habitacion h);//DONE
void imprimirPlazasParking(sqlite3*db);//DONE
int comprobarContra(sqlite3* db, int dni, char*contrasena);
int comprobarDni(sqlite3* db, int dni);//DONE
void anadirDniContra(sqlite3* db, int dni, char* contra);

#endif
