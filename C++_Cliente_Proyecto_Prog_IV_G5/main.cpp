#include "sockets/funcionesSockets.h"
#include "domain/cliente.h"
#include "domain/habitacion.h"
#include "domain/plazaParking.h"
#include "domain/reserva.h"
#include "menuOutputs/funcionesMenu.h"
#include "config/logger.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 1
#define NOT_OK 0

typedef struct {
    char ip[16];
    int port;
    char db_address[256];
} Config;

Config readConfig(const char* filename) {
    Config config;
    FILE* file = fopen(filename, "r");

    if (!file) {
        fprintf(stderr, "No se puede cargar el archivo de configuración %s\n", filename);
        exit(1);
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char* equals = strchr(line, '=');
        if (equals) {
            *equals = '\0';
            char* key = line;
            char* value = equals + 1;

            // Quitar espacios en blanco alrededor de key y value
            while (isspace((unsigned char)*key)) key++;
            while (isspace((unsigned char)*value)) value++;
            char* end = key + strlen(key) - 1;
            while (end > key && isspace((unsigned char)*end)) end--;
            end[1] = '\0';
            end = value + strlen(value) - 1;
            while (end > value && isspace((unsigned char)*end)) end--;
            end[1] = '\0';

            if (strcmp(key, "ip") == 0) {
                strncpy(config.ip, value, sizeof(config.ip) - 1);
            } else if (strcmp(key, "port") == 0) {
                config.port = atoi(value);
            } else if (strcmp(key, "db_address") == 0) {
                strncpy(config.db_address, value, sizeof(config.db_address) - 1);
            }
        }
    }
    fclose(file);
    return config;
}

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

			//INICIAR SESION ADMIN


			string dni;
			cout<<"Introduzca el dni del administrador: (introduzca 0 para salir)\n";
			getline(cin,dni);

			if (strcmp(dni.c_str(),"0")==0){
				break;
			}

			while(strcmp(dni.c_str(),"123")!=0){
				cerr<<"¡DNI introducido incorrecto!\n\n";
				cout<<"Introduzca el dni del administrador: (introduzca 0 para salir)\n";
				getline(cin,dni);
				if (stoi(dni)==0){
					break;
				}
			}

			if (strcmp(dni.c_str(),"0")==0){
				break;
			}


			string clave;
			cout<<"Introduzca la clave de administrador: (introduzca 0 para salir)\n";
			getline(cin,clave);

			if (strcmp(clave.c_str(),"0")==0){
				break;
			}
			while(strcmp(clave.c_str(),"claveadmin")!=0){
				cerr<<"¡Clave introducida incorrecta!\n\n";
				cout<<"Introduzca la clave de administrador: (introduzca 0 para salir)\n";
				getline(cin,clave);
				if (strcmp(clave.c_str(),"0")==0){
					break;
				}
			}

			if (strcmp(clave.c_str(),"0")==0){
				break;
			}


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

				//VER PLAZAS DE PARKING

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

				//VOLVER AL MENU PRINCIPAL
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
