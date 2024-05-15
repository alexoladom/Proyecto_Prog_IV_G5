
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
			//Para actualizar el numero de clientes
			getListaClientes(bd);
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
			if(enviarListaReservas(comm_socket,bd)!=OK){
				cerr<<"ERROR ENVIANDO LISTA DE RESERVAS";
				return 0;
			}

		}else if (strcmp(recvBuff, "ENVIAR LISTA HABITACIONES") == 0){

			getListaHabitaciones(bd);
			Habitacion * arrayHabitaciones= new Habitacion[Habitacion::numHabitaciones];

			arrayHabitaciones = getListaHabitaciones(bd);

			//Primero se envia el numero de habitaciones que hay

			strcpy(sendBuff,to_string(Habitacion::numHabitaciones).c_str());

			if(enviarMensaje(comm_socket,sendBuff)!=OK){
				return 0;
			}

			//Ahora se envian las habitaciones atributo por atributo

			for (int var = 0; var < Habitacion::numHabitaciones; ++var) {
				strcpy(sendBuff,to_string(arrayHabitaciones[var].getNumero()).c_str());
				if(enviarMensaje(comm_socket,sendBuff)!=OK){
					cerr<<"ERROR ENVIANDO NUMERO DE LA HABITACION Nº"<<var<<"\n";
					return 0;
				}
				strcpy(sendBuff,to_string(arrayHabitaciones[var].getPiso()).c_str());
				if(enviarMensaje(comm_socket,sendBuff)!=OK){
					cerr<<"ERROR ENVIANDO PISO DE LA HABITACION Nº"<<var<<"\n";
					return 0;
				}
				strcpy(sendBuff,to_string(arrayHabitaciones[var].getTipo()).c_str());
				if(enviarMensaje(comm_socket,sendBuff)!=OK){
					cerr<<"ERROR ENVIANDO TIPO DE LA HABITACION Nº"<<var<<"\n";
					return 0;
				}
				strcpy(sendBuff,to_string(arrayHabitaciones[var].getCapacidad()).c_str());
				if(enviarMensaje(comm_socket,sendBuff)!=OK){
					cerr<<"ERROR ENVIANDO CAPACIDAD DE LA HABITACION Nº"<<var<<"\n";
					return 0;
				}
				strcpy(sendBuff,to_string(arrayHabitaciones[var].getPrecio()).c_str());
				if(enviarMensaje(comm_socket,sendBuff)!=OK){
					cerr<<"ERROR ENVIANDO PRECIO DE LA HABITACION Nº"<<var<<"\n";
					return 0;
				}
				strcpy(sendBuff,to_string(arrayHabitaciones[var].isOcupado()).c_str());
				if(enviarMensaje(comm_socket,sendBuff)!=OK){
					cerr<<"ERROR ENVIANDO OCUPACION DE LA HABITACION Nº"<<var<<"\n";
					return 0;
				}


			}

		}else if(strcmp(recvBuff, "COMPROBAR DNI") == 0){

			if(recibirMensaje(comm_socket,recvBuff)!=OK){
				cout<<"ERROR RECIBIENDO DNI PARA COMPROBACION\n";
				return 0;
			}
			int dni = stoi(recvBuff);
			if(comprobarDni(bd,dni)!=OK){
				strcpy(sendBuff,"DNI NO EXISTENTE");
				enviarMensaje(comm_socket,sendBuff);
			}else{
				strcpy(sendBuff,"DNI EXISTENTE");
				enviarMensaje(comm_socket,sendBuff);
			}

		}else if(strcmp(recvBuff, "COMPROBAR CONTRASEÑA") == 0){
			if(recibirMensaje(comm_socket,recvBuff)!=OK){
				cout<<"ERROR RECIBIENDO DNI PARA COMPROBACION\n";
				return 0;
			}
			int dni = stoi(recvBuff);
			if(recibirMensaje(comm_socket,recvBuff)!=OK){
				cout<<"ERROR RECIBIENDO CONTRASEÑA PARA COMPROBACION\n";
				return 0;
			}
			char contra[30];
			strcpy(contra,recvBuff);

			if (comprobarContra(bd,dni,contra)!=OK){
				strcpy(sendBuff,"CONTRASEÑA INCORRECTA");
				enviarMensaje(comm_socket,sendBuff);
			}else{
				strcpy(sendBuff,"CONTRASEÑA CORRECTA");
				enviarMensaje(comm_socket,sendBuff);
			}

		}


		if (strcmp(recvBuff, "BYE") == 0){
			cerrarConexion(comm_socket);
			break;
		}

	}while(1);


	return 0;


}

