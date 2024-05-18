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
	int dniCliente;
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

			dniCliente=iniciarSesion(s);
			if(dniCliente==-1){
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
					cout<<opcion<<"Opcion no valida, introduzca una opcion de nuevo:\n";
					getline(cin,opcion);
				}

				if(strcmp(opcion.c_str(),"1")==0){
					Logger::logInfo("Opcion 1 elegida");

					//Crear una reserva
					cout<<"CREANDO RESERVA...\n";
					if(arrayHabitacionesInicializado==false){
						arrayHabitaciones=getListaHabitaciones(s);
					}
					for (int var = 0; var < Habitacion::numHabitaciones; ++var) {
						if(arrayHabitaciones[var].isOcupado()==false){
							arrayHabitaciones[var].imprimirHabitacion();
						}
					}
					cout<<"\nSELECCIONE LA HABITACION QUE DESEA RESERVAR\n";
					string numHabs;
					int numHab;
					Habitacion h;
					getline(cin,numHabs);

					numHab=stoi(numHabs);

					boolean existeHab=false;

					for (int var = 0; var < Habitacion::numHabitaciones; ++var) {
						if(arrayHabitaciones[var].getNumero()==numHab){
							if(arrayHabitaciones[var].isOcupado()==false){
								h=arrayHabitaciones[var];
								existeHab=true;
							}

						}
					}


					while(existeHab==false){
						cerr<<"LA HABITACION SELECIONADA NO ESTÁ DISPONIBLE\n";
						cout<<"\nSELECCIONE LA HABITACION QUE DESEA RESERVAR\n";
						getline(cin,numHabs);
						numHab=stoi(numHabs);
						for (int var = 0; var < Habitacion::numHabitaciones; ++var) {
							if(arrayHabitaciones[var].getNumero()==numHab){
								if(arrayHabitaciones[var].isOcupado()==false){
									h=arrayHabitaciones[var];
									existeHab=true;
								}

							}
						}
					}

					h.setOcupado(true);
					if(anadirHabitacion(s,h,true)!=OK){
						Logger::logError("Error modificando habitacion en la bd");
						cerr<<"ERROR MODIFICANDO HABITACION EN LA BD";
						return 0;
					}



					if(arrayPlazaParkingInicializado==false){
						arrayPlazaParking=getListaPlazasParking(s);
					}
					for (int var = 0; var < PlazaParking::numPlazaParkings; ++var) {
						if(arrayPlazaParking[var].isOcupado()==false){
							arrayPlazaParking[var].imprimirPlazaParking();
						}
					}

					cout<<"\nSELECCIONE LA PLAZA DE PARKING QUE DESEA RESERVAR\n";
					string numPls;
					int numPl;
					getline(cin,numPls);
					numPl=stoi(numPls);
					boolean existePl=false;
					PlazaParking p;


					for (int var = 0; var < PlazaParking::numPlazaParkings; ++var) {
						if(arrayPlazaParking[var].getNumero()==numPl){
							if(arrayPlazaParking[var].isOcupado()==false){
								existePl=true;
								p=arrayPlazaParking[var];

							}
						}
					}

					while(existePl==false){
						cerr<<"LA PLAZA DE PARKING SELECIONADA NO ESTÁ DISPONIBLE\n";
						cout<<"\nSELECCIONE LA PLAZA DE PARKING QUE DESEA RESERVAR\n";
						getline(cin,numPls);
						numPl=stoi(numPls);
						for (int var = 0; var < PlazaParking::numPlazaParkings; ++var) {
							if(arrayPlazaParking[var].getNumero()==numPl){
								if(arrayPlazaParking[var].isOcupado()==false){
									p=arrayPlazaParking[var];
									existePl=true;
								}
							}
						}
					}

					p.setOcupado(true);
					if(anadirPlazaParking(s,p,true)!=OK){
						Logger::logError("Error modificando plaza parking en la bd");
						cerr<<"ERROR MODIFICANDO PLAZA PARKING EN LA BD";
						return 0;
					}
					string date= Logger::currentDateTime();



					Reserva r(0,date,dniCliente,numHab,numPl);
					if(anadirReserva(s,r,false)!=OK){
						Logger::logError("Error añadiendo nueva reserva");
						cerr<<"ERROR AÑADIENDO NUEVA RESERVA\n";
						return 0;
					}

					cout<<"RESERVA CREADA CON ÉXITO\n";
					break;


				}
				if(strcmp(opcion.c_str(),"2")==0){
					Logger::logInfo("Opcion 2 elegida");

					//Modificar una reserva

					/*
					 * Se selecciona la reserva
					 *
					 */
					cout<<"MODIFICANDO RESERVA...\n";
					string numReservastr;
					int numReserva;
					boolean existeReserva=false;
					Reserva r;

					if(arrayReservasInicializado==false){
						arrayReservas=getListaReservas(s);
					}
					for (int var = 0; var < Reserva::numReservas; ++var) {
						if(arrayReservas[var].getDniCliente()==dniCliente){
							arrayReservas[var].imprimirReserva();
						}
					}

					cout<<"INTRODUZCA EL ID DE LA RESERVA QUE DESEA MODIFICAR:\n";
					getline(cin,numReservastr);
					numReserva=stoi(numReservastr);


					for (int var = 0; var < Reserva::numReservas; ++var) {
						if(arrayReservas[var].getId()==numReserva){
							if(arrayReservas[var].getDniCliente()==dniCliente){
								r=arrayReservas[var];
								existeReserva=true;
							}

						}
					}


					while(existeReserva==false){
						cerr<<"LA RESERVA SELECIONADA NO ESTÁ DISPONIBLE\n";
						cout<<"\nSELECCIONE LA RESERVA QUE DESEA MODIFICAR\n";
						getline(cin,numReservastr);
						numReserva=stoi(numReservastr);
						for (int var = 0; var < Reserva::numReservas; ++var) {
							if(arrayReservas[var].getId()==numReserva){
								if(arrayReservas[var].getDniCliente()==dniCliente){
									r=arrayReservas[var];
									existeReserva=true;
								}

							}
						}
					}

					for (int var = 0; var < Habitacion::numHabitaciones; ++var) {
						if(arrayHabitaciones[var].getNumero()==r.getNumeroHabitacion()){
							arrayHabitaciones[var].setOcupado(false);
							if(anadirHabitacion(s,arrayHabitaciones[var],true)!=OK){
								Logger::logError("Error modificando habitacion en la bd");
								cerr<<"ERROR MODIFICANDO HABITACION EN LA BD";
								return 0;
							}
						}
					}
					for (int var = 0; var < PlazaParking::numPlazaParkings; ++var) {
						if(arrayPlazaParking[var].getNumero()==r.getNumeroPlazaParking()){
							arrayPlazaParking[var].setOcupado(false);
							if(anadirPlazaParking(s,arrayPlazaParking[var],true)!=OK){
								Logger::logError("Error modificando plaza parking en la bd");
								cerr<<"ERROR MODIFICANDO PLAZA PARKING EN LA BD";
								return 0;
							}
						}
					}


					/*
					 *
					 * Se elige la habitacion
					 *
					 */


					if(arrayHabitacionesInicializado==false){
						arrayHabitaciones=getListaHabitaciones(s);
					}
					for (int var = 0; var < Habitacion::numHabitaciones; ++var) {
						if(arrayHabitaciones[var].isOcupado()==false){
							arrayHabitaciones[var].imprimirHabitacion();
						}
					}
					cout<<"\nSELECCIONE LA HABITACION QUE DESEA RESERVAR\n";
					string numHabs;
					int numHab;
					Habitacion h;
					getline(cin,numHabs);

					numHab=stoi(numHabs);

					boolean existeHab=false;

					for (int var = 0; var < Habitacion::numHabitaciones; ++var) {
						if(arrayHabitaciones[var].getNumero()==numHab){
							if(arrayHabitaciones[var].isOcupado()==false){
								h=arrayHabitaciones[var];
								existeHab=true;
							}

						}
					}


					while(existeHab==false){
						cerr<<"LA HABITACION SELECIONADA NO ESTÁ DISPONIBLE\n";
						cout<<"\nSELECCIONE LA HABITACION QUE DESEA RESERVAR\n";
						getline(cin,numHabs);
						numHab=stoi(numHabs);
						for (int var = 0; var < Habitacion::numHabitaciones; ++var) {
							if(arrayHabitaciones[var].getNumero()==numHab){
								if(arrayHabitaciones[var].isOcupado()==false){
									h=arrayHabitaciones[var];
									existeHab=true;
								}

							}
						}
					}

					h.setOcupado(true);
					if(anadirHabitacion(s,h,true)!=OK){
						Logger::logError("Error modificando habitacion en la bd");
						cerr<<"ERROR MODIFICANDO HABITACION EN LA BD";
						return 0;
					}


					/*
					 *
					 * Se elige la plaza de parking
					 *
					 */

					if(arrayPlazaParkingInicializado==false){
						arrayPlazaParking=getListaPlazasParking(s);
					}
					for (int var = 0; var < PlazaParking::numPlazaParkings; ++var) {
						if(arrayPlazaParking[var].isOcupado()==false){
							arrayPlazaParking[var].imprimirPlazaParking();
						}
					}

					cout<<"\nSELECCIONE LA PLAZA DE PARKING QUE DESEA RESERVAR\n";
					string numPls;
					int numPl;
					getline(cin,numPls);
					numPl=stoi(numPls);
					boolean existePl=false;
					PlazaParking p;


					for (int var = 0; var < PlazaParking::numPlazaParkings; ++var) {
						if(arrayPlazaParking[var].getNumero()==numPl){
							if(arrayPlazaParking[var].isOcupado()==false){
								existePl=true;
								p=arrayPlazaParking[var];

							}
						}
					}

					while(existePl==false){
						cerr<<"LA PLAZA DE PARKING SELECIONADA NO ESTÁ DISPONIBLE\n";
						cout<<"\nSELECCIONE LA PLAZA DE PARKING QUE DESEA RESERVAR\n";
						getline(cin,numPls);
						numPl=stoi(numPls);
						for (int var = 0; var < PlazaParking::numPlazaParkings; ++var) {
							if(arrayPlazaParking[var].getNumero()==numPl){
								if(arrayPlazaParking[var].isOcupado()==false){
									p=arrayPlazaParking[var];
									existePl=true;
								}
							}
						}
					}

					p.setOcupado(true);
					if(anadirPlazaParking(s,p,true)!=OK){
						Logger::logError("Error modificando plaza parking en la bd");
						cerr<<"ERROR MODIFICANDO PLAZA PARKING EN LA BD";
						return 0;
					}
					string date= Logger::currentDateTime();



					r.setNumeroHabitacion(numHab);
					r.setNumeroPlazaParking(numPl);

					if(anadirReserva(s,r,true)!=OK){
						Logger::logError("Error modificando nueva reserva");
						cerr<<"ERROR MODIFICANDO NUEVA RESERVA\n";
						return 0;
					}

					cout<<"RESERVA MODIFICADA CON ÉXITO\n";
					break;
				}

		/*
		 *
		 * Cancelar reserva
		 *
		 *
		 */



				if(strcmp(opcion.c_str(),"3")==0){
					Logger::logInfo("Opcion 3 elegida");

					//Cancelar una reserva
					cout<<"CANCELANDO RESERVA...\n";
					string numReservastr;
					int numReserva;
					boolean existeReserva=false;
					Reserva r;

					if(arrayReservasInicializado==false){
						arrayReservas=getListaReservas(s);
					}
					for (int var = 0; var < Reserva::numReservas; ++var) {
						if(arrayReservas[var].getDniCliente()==dniCliente){
							arrayReservas[var].imprimirReserva();
						}
					}

					cout<<"INTRODUZCA EL ID DE LA RESERVA QUE DESEA CANCELAR:\n";
					getline(cin,numReservastr);
					numReserva=stoi(numReservastr);


					for (int var = 0; var < Reserva::numReservas; ++var) {
						if(arrayReservas[var].getId()==numReserva){
							if(arrayReservas[var].getDniCliente()==dniCliente){
								r=arrayReservas[var];
								existeReserva=true;
							}

						}
					}


					while(existeReserva==false){
						cerr<<"LA RESERVA SELECIONADA NO ESTÁ DISPONIBLE\n";
						cout<<"\nSELECCIONE LA RESERVA QUE DESEA CANCELAR\n";
						getline(cin,numReservastr);
						numReserva=stoi(numReservastr);
						for (int var = 0; var < Reserva::numReservas; ++var) {
							if(arrayReservas[var].getId()==numReserva){
								if(arrayReservas[var].getDniCliente()==dniCliente){
									r=arrayReservas[var];
									existeReserva=true;
								}

							}
						}
					}


					if(borrarReserva(s,r)!=OK){
						cerr<<"ERROR BORRANDO LA RESERVA EN LA BD\n";
						Logger::logError("Error borrando la reserva");
						return 0;
					}

					for (int var = 0; var < Habitacion::numHabitaciones; ++var) {
						if(arrayHabitaciones[var].getNumero()==r.getNumeroHabitacion()){
							arrayHabitaciones[var].setOcupado(false);
							if(anadirHabitacion(s,arrayHabitaciones[var],true)!=OK){
								Logger::logError("Error modificando habitacion en la bd");
								cerr<<"ERROR MODIFICANDO HABITACION EN LA BD";
								return 0;
							}
						}
					}
					for (int var = 0; var < PlazaParking::numPlazaParkings; ++var) {
						if(arrayPlazaParking[var].getNumero()==r.getNumeroPlazaParking()){
							arrayPlazaParking[var].setOcupado(false);
							if(anadirPlazaParking(s,arrayPlazaParking[var],true)!=OK){
								Logger::logError("Error modificando plaza parking en la bd");
								cerr<<"ERROR MODIFICANDO PLAZA PARKING EN LA BD";
								return 0;
							}
						}
					}


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
		}if(strcmp(opcion.c_str(),"2")==0){

			Logger::logInfo("Opcion 2 elegida");

			// REGISTRAR NUEVO CLIENTE

			Cliente c= registrarse(s);
			Logger::logInfo("Se registra nuevo usuario");

			dniCliente =c.getDni();

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
			break;

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
