#ifndef funcionesSockets_h
#define funcionesSockets_h

#include <stdio.h>
#include <winsock2.h>
#include "string"
#include "../domain/cliente.h"
#include "../domain/reserva.h"
#include "../domain/habitacion.h"
#include "../domain/plazaParking.h"
#include "../db/funcionesBD.h"
#include "../config/config.h"

int inicializarWinsock( WSADATA& wsa);
int crearSocket(SOCKET& conn_socket,struct sockaddr_in &server);
int bindSocket(SOCKET& conn_socket, struct sockaddr_in &server);
int esperarConexion(SOCKET& conn_socket);
int aceptarConexion(SOCKET& conn_socket, SOCKET& comm_socket, struct sockaddr_in &client);
int recibirMensaje(SOCKET& comm_socket,char recvBuff[]);
int enviarMensaje(SOCKET& comm_socket,char sendBuff[]);

int enviarListaReservas(SOCKET& comm_socket,sqlite3* bd);
int enviarListaClientes(SOCKET& comm_socket,sqlite3* bd);
int enviarListaHabitaciones(SOCKET& comm_socket,sqlite3* bd);
int enviarListaPlazasParking(SOCKET& comm_socket,sqlite3* bd);


int anadirCliente(SOCKET& comm_socket,sqlite3* bd);
int anadirHabitacion(SOCKET& comm_socket,sqlite3* bd);
int anadirPlazaPaking(SOCKET& comm_socket,sqlite3* bd);
int anadirReserva(SOCKET& comm_socket,sqlite3* bd);
int borrarReserva(SOCKET& comm_socket,sqlite3* bd);
int borrarHabitacion(SOCKET& comm_socket,sqlite3* bd);
int borrarPlazaParking(SOCKET& comm_socket,sqlite3* bd);

int comprobarDni(SOCKET& comm_socket,sqlite3* bd);
int comprobarContrasena(SOCKET& comm_socket,sqlite3* bd);
int anadirDniContrasena(SOCKET& comm_socket,sqlite3* bd);

void cerrarConexion(SOCKET& comm_socket);



#endif