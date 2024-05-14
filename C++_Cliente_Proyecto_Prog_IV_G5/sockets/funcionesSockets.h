#ifndef funcionesSockets_h
#define funcionesSockets_h

#include <stdio.h>
#include <winsock2.h>
#include "string"

int inicializarWinsock( WSADATA& wsa);
int crearSocket(SOCKET& s,struct sockaddr_in &server);
int conectarCliente(SOCKET& s,struct sockaddr_in &server);
int recibirMensaje(SOCKET& s,char recvBuff[]);
int enviarMensaje(SOCKET& s,char sendBuff[]);

void cerrarConexion(SOCKET& s);



#endif
