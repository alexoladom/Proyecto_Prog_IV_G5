#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H
#include "../db/sqlite3.h"
//void main();
//void mostrarMenuPrincipal();
void menuCliente(sqlite3 * db);
void menuAdministrador(sqlite3 * db);

void iniciarSesionCliente(sqlite3 * db);
void registrarseCliente(sqlite3 * db);
void iniciarSesionAdmin(sqlite3 * db);

void menuTrabajo(sqlite3 * db);

void menuAnadirHabitacion(sqlite3 * db);

//void listadoClientes();
//void menuHabitaciones();
//void menuPlazaParking();
//
//void menuCompra();
//
//void reservarHabitacion();
//void reservarParking();
//void verEstadoReserva();
//void modificarReserva();
//void cancelarReserva();
//
//void verHabitacionesReservadas();
//void verHabitacionesDisponibles();
//void verHabitacionesOcupadas();
//void verEstadoLimpiezaHabitaciones();
//void menuEditarInformacionHabitaciones();
//
//void verPlazasParking();
//void editarInformacionPlazasParking();

#endif


