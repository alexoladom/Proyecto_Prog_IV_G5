#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H


#include "../domain/cliente.h"
#include "../domain/reserva.h"
#include "../domain/habitacion.h"
#include "../domain/plazaParking.h"

void mostrarMenuPrincipal();

void mostrarMenuInicioCliente();

void mostrarMenuPrincipalCliente();

void mostrarMenuInicioAdmin();

void mostrarMenuPrincipalAdmin();

Cliente registrarse();
Habitacion anadirHabitacion();
PlazaParking anadirPlazaParking();

#endif
