#ifndef FUNCIONES_CARGA_H
#define FUNCIONES_CARGA_H

#include "../domain/habitacion.h"
#include "../domain/plazaParking.h"
#include "../domain/cliente.h"
#include "../domain/administrador.h"
#include "../domain/reserva.h"

void cargarHabitacionesDesdeArchivo(const char* nombreArchivo, Habitacion habitaciones[], int* cantidad);
void cargarPlazasParkingDesdeArchivo(const char* nombreArchivo, PlazaParking plazas[], int* cantidad);
void cargarClientesDesdeArchivo(const char* nombreArchivo, Cliente clientes[], int* cantidad);
void cargarAdministradoresDesdeArchivo(const char* nombreArchivo, Administrador administradores[], int* cantidad);
void cargarReservasDesdeArchivo(const char* nombreArchivo, Reserva reservas[], int* cantidad);


#endif /* FUNCIONES_CARGA_H */
