
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
			Cliente * arrayClientes= new Cliente[Cliente::numClientes];

			arrayClientes = getListaClientes(bd);

			//Primero se envia el numero de clientes que hay

			strcpy(sendBuff,to_string(Cliente::numClientes).c_str());

			if(enviarMensaje(comm_socket,sendBuff)!=OK){
				return 0;
			}

			//Ahora se envian los clientes atributo por atributo

			for (int var = 0; var < Cliente::numClientes; ++var) {
				strcpy(sendBuff,to_string(arrayClientes[var].getDni()).c_str());
				if(enviarMensaje(comm_socket,sendBuff)!=OK){
					return 0;
				}
				strcpy(sendBuff,arrayClientes[var].getNombre().c_str());
				if(enviarMensaje(comm_socket,sendBuff)!=OK){
					return 0;
				}
				strcpy(sendBuff,to_string(arrayClientes[var].getEdad()).c_str());
				if(enviarMensaje(comm_socket,sendBuff)!=OK){
					return 0;
				}
				strcpy(sendBuff,arrayClientes[var].getCorreo().c_str());
				if(enviarMensaje(comm_socket,sendBuff)!=OK){
					return 0;
				}

			}

		}else if (strcmp(recvBuff, "ENVIAR LISTA RESERVAS") == 0){
			Reserva * arrayReservas= new Reserva[Reserva::numReservas];

			arrayReservas = getListaReservas(bd);

			//Primero se envia el numero de reservas que hay

			strcpy(sendBuff,to_string(Reserva::numReservas).c_str());

			if(enviarMensaje(comm_socket,sendBuff)!=OK){
				return 0;
			}

			//Ahora se envian las reservas atributo por atributo

			for (int var = 0; var < Reserva::numReservas; ++var) {
				strcpy(sendBuff,to_string(arrayReservas[var].getId()).c_str());
				if(enviarMensaje(comm_socket,sendBuff)!=OK){
					cerr<<"ERROR ENVIANDO ID DE LA RESERVA Nº"<<var<<"\n";
					return 0;
				}
				strcpy(sendBuff,arrayReservas[var].getFecha().c_str());
				if(enviarMensaje(comm_socket,sendBuff)!=OK){
					cerr<<"ERROR ENVIANDO FECHA DE LA RESERVA Nº"<<var<<"\n";
					return 0;
				}
				strcpy(sendBuff,to_string(arrayReservas[var].getDniCliente()).c_str());
				if(enviarMensaje(comm_socket,sendBuff)!=OK){
					cerr<<"ERROR ENVIANDO DNI CLIENTE DE LA RESERVA Nº"<<var<<"\n";
					return 0;
				}
				strcpy(sendBuff,to_string(arrayReservas[var].getNumeroHabitacion()).c_str());
				if(enviarMensaje(comm_socket,sendBuff)!=OK){
					cerr<<"ERROR ENVIANDO NUMERO HABITACION DE LA RESERVA Nº"<<var<<"\n";
					return 0;
				}
				strcpy(sendBuff,to_string(arrayReservas[var].getNumeroHabitacion()).c_str());
				if(enviarMensaje(comm_socket,sendBuff)!=OK){
					cerr<<"ERROR ENVIANDO NUMERO PLAZAPARKING DE LA RESERVA Nº"<<var<<"\n";
					return 0;
				}


			}

		}else if (strcmp(recvBuff, "ENVIAR LISTA HABITACIONES") == 0){

			Habitacion * arrayHabitaciones= new Habitacion[Habitacion::numHabitaciones];

			arrayHabitaciones = getListaHabitaciones(bd);

			//Primero se envia el numero de reservas que hay

			strcpy(sendBuff,to_string(Reserva::numReservas).c_str());

			if(enviarMensaje(comm_socket,sendBuff)!=OK){
				return 0;
			}

			//Ahora se envian las reservas atributo por atributo

			for (int var = 0; var < Reserva::numReservas; ++var) {
				strcpy(sendBuff,to_string(arrayReservas[var].getId()).c_str());
				if(enviarMensaje(comm_socket,sendBuff)!=OK){
					cerr<<"ERROR ENVIANDO ID DE LA RESERVA Nº"<<var<<"\n";
					return 0;
				}
				strcpy(sendBuff,arrayReservas[var].getFecha().c_str());
				if(enviarMensaje(comm_socket,sendBuff)!=OK){
					cerr<<"ERROR ENVIANDO FECHA DE LA RESERVA Nº"<<var<<"\n";
					return 0;
				}
				strcpy(sendBuff,to_string(arrayReservas[var].getDniCliente()).c_str());
				if(enviarMensaje(comm_socket,sendBuff)!=OK){
					cerr<<"ERROR ENVIANDO DNI CLIENTE DE LA RESERVA Nº"<<var<<"\n";
					return 0;
				}
				strcpy(sendBuff,to_string(arrayReservas[var].getNumeroHabitacion()).c_str());
				if(enviarMensaje(comm_socket,sendBuff)!=OK){
					cerr<<"ERROR ENVIANDO NUMERO HABITACION DE LA RESERVA Nº"<<var<<"\n";
					return 0;
				}
				strcpy(sendBuff,to_string(arrayReservas[var].getNumeroHabitacion()).c_str());
				if(enviarMensaje(comm_socket,sendBuff)!=OK){
					cerr<<"ERROR ENVIANDO NUMERO PLAZAPARKING DE LA RESERVA Nº"<<var<<"\n";
					return 0;
				}


			}

		}


		if (strcmp(recvBuff, "BYE") == 0){
			cerrarConexion(comm_socket);
			break;
		}

	}while(1);


	return 0;


}

