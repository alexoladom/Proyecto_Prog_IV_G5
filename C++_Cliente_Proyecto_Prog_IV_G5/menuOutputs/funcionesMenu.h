#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H


#include <stdio.h>
#include <winsock2.h>

#include "../domain/cliente.h"
#include "../domain/reserva.h"
#include "../domain/habitacion.h"
#include "../domain/plazaParking.h"

void mostrarMenuPrincipal();

void mostrarMenuInicioCliente();

void mostrarMenuPrincipalCliente();

void mostrarMenuInicioAdmin();

void mostrarMenuPrincipalAdmin();

Cliente registrarse(SOCKET & s);
Habitacion anadirHabitacion(SOCKET & s);
PlazaParking anadirPlazaParking(SOCKET & s);

#endif
