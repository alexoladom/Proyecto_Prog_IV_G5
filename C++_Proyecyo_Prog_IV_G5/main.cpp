
#include "db/funcionesBD.h"
#include "sockets/funcionesSockets.h"
#include "domain/cliente.h"
#include "domain/habitacion.h"
#include "domain/plazaParking.h"
#include "domain/reserva.h"

#define OK 1
#define NOT_OK 0

int main(int argc, char **argv) {


	WSADATA wsa;
	SOCKET conn_socket;
	SOCKET comm_socket;
	struct sockaddr_in server;
	struct sockaddr_in client;
	char sendBuff[512], recvBuff[512];

	/*
	 * Inicializacion y conexion de sockets
	 *
	 */
	cout<<"------------------------------------\n\n";
	cout<<"INICIALIZANDO SOCKETS DE SERVIDOR...\n\n";

	if(inicializarWinsock(wsa)!=OK){
		return 0;
	}

	if(crearSocket(conn_socket,server)!=OK){
		return 0;
	}

	if(bindSocket(conn_socket,server)!=OK){
		return 0;
	}

	if(esperarConexion(conn_socket)!=OK){
		return 0;
	}

	if(aceptarConexion(conn_socket,comm_socket,client)!=OK){
		return 0;
	}

	cout<<"CONEXION CREADA CON ÉXITO\n\n";

	/*
	 * Inicializacion de la bd
	 *
	 */

	sqlite3* bd = conectarDB();

	/*
	 *
	 * Bucle con el protocolo
	 *
	 */

	do{
		if(recibirMensaje(comm_socket,recvBuff)!=OK){
			cerr<<"ERROR RECIBIENDO EL MENSAJE (MENSAJE VACIO)\n";
			break;
		}

		if (strcmp(recvBuff, "ENVIAR LISTA CLIENTES") == 0){
			if(enviarListaClientes(comm_socket,bd)!=OK){
				cerr<<"ERROR ENVIANDO LISTA DE CLIENTES";
				return 0;
			}

		}else if (strcmp(recvBuff, "ENVIAR LISTA RESERVAS") == 0){
			if(enviarListaReservas(comm_socket,bd)!=OK){
				cerr<<"ERROR ENVIANDO LISTA DE RESERVAS";
				return 0;
			}

		}else if (strcmp(recvBuff, "ENVIAR LISTA HABITACIONES") == 0){

			if(enviarListaHabitaciones(comm_socket,bd)!=OK){
				cerr<<"ERROR ENVIANDO LISTA DE HABITACIONES";
				return 0;
			}

		}else if(strcmp(recvBuff, "COMPROBAR DNI") == 0){

			if(comprobarDni(comm_socket,bd)!=OK){
				cerr<<"ERROR COMPROBANDO DNI";
				return 0;
			}

		}else if(strcmp(recvBuff, "COMPROBAR CONTRASEÑA") == 0){
			if(comprobarContrasena(comm_socket,bd)!=OK){
				cerr<<"ERROR COMPROBANDO CONTRASEÑA";
				return 0;
			}

		}


		if (strcmp(recvBuff, "BYE") == 0){
			cerrarConexion(comm_socket);
			break;
		}

	}while(1);


	return 0;


}

