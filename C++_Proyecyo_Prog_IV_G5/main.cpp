
#include "db/funcionesBD.h"
#include "sockets/funcionesSockets.h"
#include "domain/cliente.h"
#include "domain/habitacion.h"
#include "domain/plazaParking.h"
#include "domain/reserva.h"
#include "config/logger.h"

#define OK 1
#define NOT_OK 0

int main(int argc, char **argv) {


	Logger::init("config/ficheroLog.log");
	Logger::logInfo("NUEVA SESION");


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
		Logger::logError("Error inicializando Winsock");
		return 0;
	}

	Logger::logInfo("WinSock inicializado");
	if(crearSocket(conn_socket,server)!=OK){
		Logger::logError("Error creando socket");

		return 0;
	}

	Logger::logInfo("Socket creado");
	if(bindSocket(conn_socket,server)!=OK){
		Logger::logError("Error haciendo bind con el socket");

		return 0;
	}
	Logger::logInfo("Bind hecho");
	if(esperarConexion(conn_socket)!=OK){
		Logger::logError("Error esperando conexion");

		return 0;
	}

	Logger::logInfo("Esperando conexion...");
	if(aceptarConexion(conn_socket,comm_socket,client)!=OK){
		Logger::logError("Error aceptando conexion");

		return 0;
	}

	Logger::logInfo("Conexion aceptada");

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
			Logger::logError("Error recibiendo el mensaje");
			cerrarConexion(comm_socket);
			Logger::logInfo("SE CIERRA LA SESION");

			break;
		}
		Logger::logInfo("Mensaje recibido");


		if (strcmp(recvBuff, "ENVIAR LISTA CLIENTES") == 0){
			if(enviarListaClientes(comm_socket,bd)!=OK){
				cerr<<"ERROR ENVIANDO LISTA DE CLIENTES\n";
				Logger::logError("Error enviando lista de clientes");
				cerrarConexion(comm_socket);
				Logger::logInfo("SE CIERRA LA SESION");

				return 0;
		}
			Logger::logInfo("Lista de clientes enviada");


		}else if (strcmp(recvBuff, "ENVIAR LISTA RESERVAS") == 0){
			if(enviarListaReservas(comm_socket,bd)!=OK){
				cerr<<"ERROR ENVIANDO LISTA DE RESERVAS\n";
				Logger::logError("Error enviando lista de reservas");
				cerrarConexion(comm_socket);
				Logger::logInfo("SE CIERRA LA SESION");

				return 0;
			}

			Logger::logInfo("Lista de reservas enviada");

		}else if (strcmp(recvBuff, "ENVIAR LISTA HABITACIONES") == 0){

			if(enviarListaHabitaciones(comm_socket,bd)!=OK){
				cerr<<"ERROR ENVIANDO LISTA DE HABITACIONES\n";
				Logger::logError("Error enviando lista de habitaciones");
				cerrarConexion(comm_socket);
				Logger::logInfo("SE CIERRA LA SESION");

				return 0;
			}

			Logger::logInfo("Lista de habitaciones enviada");

		}else if(strcmp(recvBuff,"ENVIAR LISTA PLAZAS PARKING")==0){
			if(enviarListaPlazasParking(comm_socket,bd)!=OK){
				cerr<<"ERROR ENVIANDO LISTA DE PLAZAS PARKING\n";
				Logger::logError("Error enviando lista de plazas parking");

				cerrarConexion(comm_socket);
				Logger::logInfo("SE CIERRA LA SESION");

				return 0;
			}

			Logger::logInfo("Lista de plazas de parking enviada");


		}else if(strcmp(recvBuff,"AÑADIR CLIENTE")==0){

			if(anadirCliente(comm_socket,bd)!=OK){
				cerr<<"ERROR AÑADIENDO CLIENTE EN LA BD\n";
				Logger::logError("Error añadiendo cliente en la bd");

				cerrarConexion(comm_socket);
				Logger::logInfo("SE CIERRA LA SESION");

				return 0;
			}

			Logger::logInfo("Lista de plazas de parking enviada");



		}else if(strcmp(recvBuff,"AÑADIR HABITACION")==0){

			if(anadirHabitacion(comm_socket,bd)!=OK){
				cerr<<"ERROR AÑADIENDO CLIENTE EN LA BD\n";
				Logger::logError("Error añadiendo cliente en la bd");

				cerrarConexion(comm_socket);
				Logger::logInfo("SE CIERRA LA SESION");

				return 0;
			}

			Logger::logInfo("Habitacion añadida a la bd");



		}else if(strcmp(recvBuff,"AÑADIR PLAZA PARKING")==0){

			if(anadirPlazaPaking(comm_socket,bd)!=OK){
				cerr<<"ERROR AÑADIENDO PLAZA PARKING EN LA BD\n";
				Logger::logError("Error añadiendo plaza parking en la bd");

				cerrarConexion(comm_socket);
				Logger::logInfo("SE CIERRA LA SESION");

				return 0;
			}

			Logger::logInfo("Plaza parking añadida a la bd");



		}else if(strcmp(recvBuff,"AÑADIR RESERVA")==0){

			if(anadirReserva(comm_socket,bd)!=OK){
				cerr<<"ERROR AÑADIENDO RESERVA EN LA BD\n";
				Logger::logError("Error añadiendo reserva en la bd");

				cerrarConexion(comm_socket);
				Logger::logInfo("SE CIERRA LA SESION");

				return 0;
			}

			Logger::logInfo("Reserva añadida a la bd");



		}else if(strcmp(recvBuff, "COMPROBAR DNI") == 0){

			if(comprobarDni(comm_socket,bd)!=OK){
				cerr<<"ERROR COMPROBANDO DNI\n";
				Logger::logError("Error comprobando dni");

				cerrarConexion(comm_socket);
				Logger::logInfo("SE CIERRA LA SESION");

				return 0;
			}
			Logger::logInfo("DNI comprobado");


		}else if(strcmp(recvBuff, "COMPROBAR CONTRASEÑA") == 0){
			if(comprobarContrasena(comm_socket,bd)!=OK){
				cerr<<"ERROR COMPROBANDO CONTRASEÑA\n";
				Logger::logError("Error comprobando contraseña");

				cerrarConexion(comm_socket);
				Logger::logInfo("SE CIERRA LA SESION");

				return 0;
			}
			Logger::logInfo("Contraseña comprobada");


		}else if(strcmp(recvBuff,"AÑADIR DNI CONTRASEÑA")==0){
			if(anadirDniContrasena(comm_socket,bd)!=OK){
				cerr<<"ERROR AÑADIENDO DNI Y CONTRASEÑA\n";
					Logger::logError("Error añadiendo dni y contraseña");

					cerrarConexion(comm_socket);
					Logger::logInfo("SE CIERRA LA SESION");

					return 0;
			}

			Logger::logInfo("Dni y contraseña añadida");

		}


		if (strcmp(recvBuff, "BYE") == 0){
			Logger::logInfo("SE CIERRA LA SESION");
			cerrarConexion(comm_socket);
			break;
		}

	}while(1);


	return 0;


}

