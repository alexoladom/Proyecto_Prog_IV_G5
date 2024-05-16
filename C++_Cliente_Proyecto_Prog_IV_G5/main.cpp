
#include "sockets/funcionesSockets.h"
#include "domain/cliente.h"
#include "domain/habitacion.h"
#include "domain/plazaParking.h"
#include "domain/reserva.h"
#include "menuOutputs/funcionesMenu.h"
#include "config/logger.h"


#define OK 1
#define NOT_OK 0

int main(int argc, char **argv) {


	Logger::init("config/ficheroLog.log");
	Logger::logInfo("NUEVA SESION");


	WSADATA wsa;
	SOCKET s;
	struct sockaddr_in server;
	char sendBuff[512], recvBuff[512];
	Cliente* arrayClientes;
	boolean arrayClientesInicializado=false;
	Reserva* arrayReservas;
	boolean arrayReservasInicializado=false;
	Habitacion* arrayHabitaciones;
	boolean arrayHabitacionesInicializado=false;
	PlazaParking* arrayPlazaParking;
	boolean arrayPlazaParkingInicializado=false;
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

	Logger::logInfo("Winsock inicializado");

	if(crearSocket(s,server)!=OK){
		Logger::logError("Error creando socket");
		return 0;
	}

	Logger::logInfo("Socket creado");

	if(conectarCliente(s,server)!=OK){
		Logger::logError("Error conectando cliente");
		return 0;
	}

	Logger::logInfo("Cliente conectado");




	do{

	mostrarMenuPrincipal();
	Logger::logInfo("Se muestra el menu principal");

	string opcion;
	getline(cin,opcion);


	while(strcmp(opcion.c_str(),"1")!=0&&strcmp(opcion.c_str(),"2")!=0
	&&strcmp(opcion.c_str(),"3")!=0)
	{
		cout<<"Opcion no valida, introduzca una opcion de nuevo:\n";
		getline(cin,opcion);
	}

	//Cliente
	if (strcmp(opcion.c_str(),"1")==0){
		Logger::logInfo("Opcion 1 elegida");

		mostrarMenuInicioCliente();
		Logger::logInfo("Se muestra menu de inicio del cliente");

		getline(cin,opcion);

		do{
		while(strcmp(opcion.c_str(),"1")!=0&&strcmp(opcion.c_str(),"2")!=0
		&&strcmp(opcion.c_str(),"3")!=0)
		{
			cout<<"Opcion no valida, introduzca una opcion de nuevo:\n";
			getline(cin,opcion);
		}
		if(strcmp(opcion.c_str(),"1")==0){
			// INICIAR SESION
			Logger::logInfo("Opcion 1 elegida");

			if(iniciarSesion(s)==-1){
				break;
			}

			Logger::logInfo("Inicio de sesión completado");

			mostrarMenuPrincipalCliente();
			Logger::logInfo("Se muestra el menu principal del cliente");

			getline(cin,opcion);
			//MENU PRINCIPAL CLIENTE
			do{
				while(strcmp(opcion.c_str(),"1")!=0&&strcmp(opcion.c_str(),"2")!=0
				&&strcmp(opcion.c_str(),"3")!=0&&strcmp(opcion.c_str(),"4")!=0&&strcmp(opcion.c_str(),"5")!=0)
				{
					cout<<opcion<<"  Opcion no valida, introduzca una opcion de nuevo:\n";
					getline(cin,opcion);
				}

				if(strcmp(opcion.c_str(),"1")==0){
					Logger::logInfo("Opcion 1 elegida");

					//Crear una reserva TODO


				}
				if(strcmp(opcion.c_str(),"2")==0){
					Logger::logInfo("Opcion 2 elegida");

					//Modificar una reserva TODO
				}
				if(strcmp(opcion.c_str(),"3")==0){
					Logger::logInfo("Opcion 3 elegida");

					//Cancelar una reserva TODO
				}
				if(strcmp(opcion.c_str(),"4")==0){
					Logger::logInfo("Opcion 4 elegida");

					//Volver al menu principal
					opcion="-1";
					break;
				}
				if(strcmp(opcion.c_str(),"5")==0){
					Logger::logInfo("Opcion 5 elegida");

					//Cerrar
					strcpy(sendBuff,"BYE");
					if (enviarMensaje(s,sendBuff)!=OK){
					}
					cout<<"Has elegido salir\n";
					cerrarConexion(s);
					Logger::logInfo("SE CIERRA LA SESION");

					return 0;
				}

			}while(1);
			break;
		}

		if(strcmp(opcion.c_str(),"2")==0){
			Logger::logInfo("Opcion 2 elegida");

			// TODO REGISTRAR NUEVO CLIENTE
			mostrarMenuPrincipalCliente();
			Logger::logInfo("Se muestra el menu principal de cliente");

			getline(cin,opcion);

			//MENU PRINCIPAL CLIENTE
			do{
				while(strcmp(opcion.c_str(),"1")!=0&&strcmp(opcion.c_str(),"2")!=0
				&&strcmp(opcion.c_str(),"3")!=0&&strcmp(opcion.c_str(),"4")!=0&&strcmp(opcion.c_str(),"5")!=0)
				{
					cout<<"Opcion no valida, introduzca una opcion de nuevo:\n";
					getline(cin,opcion);
				}

				if(strcmp(opcion.c_str(),"1")==0){
					Logger::logInfo("Opcion 1 elegida");

					//Crear una reserva TODO
				}
				if(strcmp(opcion.c_str(),"2")==0){
					Logger::logInfo("Opcion 2 elegida");

					//Modificar una reserva TODO
				}
				if(strcmp(opcion.c_str(),"3")==0){
					Logger::logInfo("Opcion 3 elegida");

					//Cancelar una reserva TODO
				}
				if(strcmp(opcion.c_str(),"4")==0){
					Logger::logInfo("Opcion 4 elegida");

					//Volver al menu principal
					opcion="-1";
					break;
				}
				if(strcmp(opcion.c_str(),"5")==0){
					Logger::logInfo("Opcion 5 elegida");

					//Cerrar
					strcpy(sendBuff,"BYE");
					if (enviarMensaje(s,sendBuff)!=OK){
					}
					cout<<"Has elegido salir\n";
					cerrarConexion(s);
					Logger::logInfo("SE CIERRA LA SESION");

					return 0;
				}

			}while(1);
		}
		if(strcmp(opcion.c_str(),"3")==0){
			Logger::logInfo("Opcion 3 elegida");

			//VOLVER AL MENU PRINCIPAL
			opcion="-1";
			break;
		}
		}while(1);


	}
	//Administrador
	else if (strcmp(opcion.c_str(),"2")==0){
		Logger::logInfo("Opcion 2 elegida");

		mostrarMenuInicioAdmin();
		Logger::logInfo("Se muestra el menu del inicio de administrador");

		getline(cin,opcion);

		while(strcmp(opcion.c_str(),"1")!=0&&strcmp(opcion.c_str(),"2")!=0)
		{
			cout<<"Opcion no valida, introduzca una opcion de nuevo:\n";
			getline(cin,opcion);
		}

		if(strcmp(opcion.c_str(),"1")==0){
			Logger::logInfo("Opcion 1 elegida");

			//INICIAR SESION ADMIN TODO


			mostrarMenuPrincipalAdmin();
			Logger::logInfo("Se muestra el menu principal de administrador");

			getline(cin,opcion);


			//Menu principal admin

			do{

			while(strcmp(opcion.c_str(),"1")!=0&&strcmp(opcion.c_str(),"2")!=0
					&&strcmp(opcion.c_str(),"3")!=0&&strcmp(opcion.c_str(),"4")!=0
					&&strcmp(opcion.c_str(),"5")!=0&&strcmp(opcion.c_str(),"6")!=0
					&&strcmp(opcion.c_str(),"7")!=0&&strcmp(opcion.c_str(),"8")!=0
					&&strcmp(opcion.c_str(),"9")!=0&&strcmp(opcion.c_str(),"10")!=0
					&&strcmp(opcion.c_str(),"11")!=0)
			{
				cout<<"Opcion no valida, introduzca una opcion de nuevo:\n";
				getline(cin,opcion);
			}

			if (strcmp(opcion.c_str(),"1")==0){
				Logger::logInfo("Opcion 1 elegida");

				//VISUALIZAR LISTA DE CLIENTES

				arrayClientes = getListaClientes(s);
				arrayClientesInicializado=true;


				cout<<"----------------------------\n";
				cout<<"LISTA DE CLIENTES\n";

				for (int var = 0; var < Cliente::numClientes; ++var) {
					arrayClientes[var].imprimir();
				}


				Logger::logInfo("Se visualizan los clientes");

				mostrarMenuPrincipalAdmin();
				Logger::logInfo("Se muestra el menu principal de administrador");

				getline(cin,opcion);
				continue;


			}else if(strcmp(opcion.c_str(),"2")==0){
				Logger::logInfo("Opcion 2 elegida");

				//VISUALIZAR RESERVAS

				arrayReservas=getListaReservas(s);
				arrayReservasInicializado=true;


				cout<<"----------------------------\n";
				cout<<"LISTA DE RESERVAS\n";

				for (int var = 0; var < Reserva::numReservas; ++var) {
					arrayReservas[var].imprimirReserva();
				}
				Logger::logInfo("Se muestra la lista de reservas");


				mostrarMenuPrincipalAdmin();
				Logger::logInfo("Se muestra el menu principal de administrador");

				getline(cin,opcion);
				continue;

			}else if(strcmp(opcion.c_str(),"3")==0){
				Logger::logInfo("Opcion 3 elegida");

				//BORRAR RESERVA TODO
			}else if(strcmp(opcion.c_str(),"4")==0){
				Logger::logInfo("Opcion 4 elegida");

				//VER HABITACIONES


				arrayHabitaciones=getListaHabitaciones(s);
				arrayHabitacionesInicializado=true;

				cout<<"----------------------------\n";
				cout<<"LISTA DE HABITACIONES\n";

				for (int var = 0; var < Habitacion::numHabitaciones; ++var) {
					arrayHabitaciones[var].imprimirHabitacion();
				}

				Logger::logInfo("Se muestra la lista de habitaciones");


				mostrarMenuPrincipalAdmin();
				Logger::logInfo("Se muestra el menu principal de administrador");

				getline(cin,opcion);
				continue;

			}else if(strcmp(opcion.c_str(),"5")==0){
				Logger::logInfo("Opcion 5 elegida");

				//AÑADIR HABITACIONES TODO
			}else if(strcmp(opcion.c_str(),"6")==0){
				Logger::logInfo("Opcion 6 elegida");

				//BORRAR HABITACIONES TODO
			}else if(strcmp(opcion.c_str(),"7")==0){
				Logger::logInfo("Opcion 7 elegida");

				//VER PLAZAS DE PARKING TODO

				cout<<"----------------------------\n";
				cout<<"LISTA DE PLAZAS DE PARKING\n";
				arrayPlazaParking=getListaPlazasParking(s);
				arrayPlazaParkingInicializado=true;



				for (int var = 0; var < PlazaParking::numPlazaParkings; ++var) {
					arrayPlazaParking[var].imprimirPlazaParking();
				}

				Logger::logInfo("Se muestra la lista de plazas de parking");


				arrayPlazaParkingInicializado=true;
				mostrarMenuPrincipalAdmin();

				Logger::logInfo("Se muestra el menu principal de administrador");

				getline(cin,opcion);
				continue;

			}else if(strcmp(opcion.c_str(),"8")==0){
				Logger::logInfo("Opcion 8 elegida");

				//AÑADIR PLAZAS DE PARKING TODO
			}else if(strcmp(opcion.c_str(),"9")==0){
				Logger::logInfo("Opcion 9 elegida");

				//BORRAR PLAZAS DE PARKING TODO
			}else if(strcmp(opcion.c_str(),"10")==0){
				Logger::logInfo("Opcion 10 elegida");

				//VOLVER AL MENU PRINCIPAL TODO
				opcion="-1";
				break;
			}else if(strcmp(opcion.c_str(),"11")==0){
				Logger::logInfo("Opcion 11 elegida");

				//CERRAR
				strcpy(sendBuff,"BYE");
				if (enviarMensaje(s,sendBuff)!=OK){
					return 0;
				}
				cout<<"Has elegido salir\n";
				cerrarConexion(s);
				Logger::logInfo("SE CIERRA LA SESION");

				return 0;
			}


			}while(1);


		}

		if(strcmp(opcion.c_str(),"2")==0){
			Logger::logInfo("Opcion 2 elegida");

			//VOLVER AL MENU PRINCIPAL
			opcion="-1";
			continue;

		}

	}

	//Salir
	else if (strcmp(opcion.c_str(),"3")==0){
		Logger::logInfo("Opcion 3 elegida");

		strcpy(sendBuff,"BYE");
		if (enviarMensaje(s,sendBuff)!=OK){
		}
		cout<<"Has elegido salir\n";
		cerrarConexion(s);
		Logger::logInfo("SE CIERRA LA SESION");

		break;
	}


	}while(1);

	return 0;

}

