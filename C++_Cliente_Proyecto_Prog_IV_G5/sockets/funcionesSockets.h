#ifndef funcionesSockets_h
#define funcionesSockets_h

#include <stdio.h>
#include <winsock2.h>
#include "string"
#include "../domain/cliente.h"
#include "../domain/reserva.h"
#include "../domain/habitacion.h"
#include "../domain/plazaParking.h"

int inicializarWinsock( WSADATA& wsa);
int crearSocket(SOCKET& s,struct sockaddr_in &server);
int conectarCliente(SOCKET& s,struct sockaddr_in &server);
int recibirMensaje(SOCKET& s,char recvBuff[]);
int enviarMensaje(SOCKET& s,char sendBuff[]);
Cliente* getListaClientes(SOCKET& s);
Reserva* getListaReservas(SOCKET& s);
Habitacion* getListaHabitaciones(SOCKET& s);
PlazaParking* getListaPlazasParking(SOCKET& s);


int comprobarDni(SOCKET& s,int dni);
int comprobarContrasena(SOCKET& s,int dni,char* contrasena);
enum tipoHabitacion stringToTipoHabi(char* s);
void cerrarConexion(SOCKET& s);



#endif
