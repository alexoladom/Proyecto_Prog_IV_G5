#ifndef funcionesSockets_h
#define funcionesSockets_h

#include <stdio.h>
#include <winsock2.h>
#include "string"

int inicializarWinsock( WSADATA& wsa);
int crearSocket(SOCKET& conn_socket,struct sockaddr_in &server);
int bindSocket(SOCKET& conn_socket, struct sockaddr_in &server);
int esperarConexion(SOCKET& conn_socket);
int aceptarConexion(SOCKET& conn_socket, SOCKET& comm_socket, struct sockaddr_in &client);
int recibirMensaje(SOCKET& comm_socket,char recvBuff[]);
int enviarMensaje(SOCKET& comm_socket,char sendBuff[]);

void cerrarConexion(SOCKET& comm_socket);



#endif
