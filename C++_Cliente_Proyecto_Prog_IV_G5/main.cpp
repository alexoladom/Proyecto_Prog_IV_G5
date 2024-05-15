
#include "sockets/funcionesSockets.h"
#include "domain/cliente.h"
#include "domain/habitacion.h"
#include "domain/plazaParking.h"
#include "domain/reserva.h"
#include "menuOutputs/funcionesMenu.h"


#define OK 1
#define NOT_OK 0

int main(int argc, char **argv) {

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
		return 0;
	}

	if(crearSocket(s,server)!=OK){
		return 0;
	}

	if(conectarCliente(s,server)!=OK){
		return 0;
	}


	do{

	mostrarMenuPrincipal();
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
		mostrarMenuInicioCliente();
		getline(cin,opcion);

		do{
		while(strcmp(opcion.c_str(),"1")!=0&&strcmp(opcion.c_str(),"2")!=0
		&&strcmp(opcion.c_str(),"3")!=0)
		{
			cout<<"Opcion no valida, introduzca una opcion de nuevo:\n";
			getline(cin,opcion);
		}
		if(strcmp(opcion.c_str(),"1")==0){
			// TODO INICIAR SESION
			mostrarMenuPrincipalCliente();
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
					//Crear una reserva TODO
				}
				if(strcmp(opcion.c_str(),"2")==0){
					//Modificar una reserva TODO
				}
				if(strcmp(opcion.c_str(),"3")==0){
					//Cancelar una reserva TODO
				}
				if(strcmp(opcion.c_str(),"4")==0){
					//Volver al menu principal
					opcion="-1";
					break;
				}
				if(strcmp(opcion.c_str(),"5")==0){
					//Cerrar
					strcpy(sendBuff,"BYE");
					if (enviarMensaje(s,sendBuff)!=OK){
					}
					cout<<"Has elegido salir\n";
					cerrarConexion(s);
					return 0;
				}

			}while(1);
			break;
		}

		if(strcmp(opcion.c_str(),"2")==0){
			// TODO REGISTRAR NUEVO CLIENTE
			mostrarMenuPrincipalCliente();
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
					//Crear una reserva TODO
				}
				if(strcmp(opcion.c_str(),"2")==0){
					//Modificar una reserva TODO
				}
				if(strcmp(opcion.c_str(),"3")==0){
					//Cancelar una reserva TODO
				}
				if(strcmp(opcion.c_str(),"4")==0){
					//Volver al menu principal
					opcion="-1";
					break;
				}
				if(strcmp(opcion.c_str(),"5")==0){
					//Cerrar
					strcpy(sendBuff,"BYE");
					if (enviarMensaje(s,sendBuff)!=OK){
					}
					cout<<"Has elegido salir\n";
					cerrarConexion(s);
					return 0;
				}

			}while(1);
		}
		if(strcmp(opcion.c_str(),"3")==0){
			//VOLVER AL MENU PRINCIPAL
			opcion="-1";
			break;
		}
		}while(1);


	}
	//Administrador
	else if (strcmp(opcion.c_str(),"2")==0){
		mostrarMenuInicioAdmin();
		getline(cin,opcion);

		while(strcmp(opcion.c_str(),"1")!=0&&strcmp(opcion.c_str(),"2")!=0)
		{
			cout<<"Opcion no valida, introduzca una opcion de nuevo:\n";
			getline(cin,opcion);
		}

		if(strcmp(opcion.c_str(),"1")==0){
			//INICIAR SESION ADMIN TODO
			mostrarMenuPrincipalAdmin();
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
				//VISUALIZAR LISTA DE CLIENTES

				arrayClientes = getListaClientes(s);


				cout<<"----------------------------\n";
				cout<<"LISTA DE CLIENTES\n";

				for (int var = 0; var < Cliente::numClientes; ++var) {
					arrayClientes[var].imprimir();
				}

				arrayClientesInicializado=true;

				mostrarMenuPrincipalAdmin();
				getline(cin,opcion);
				continue;


			}else if(strcmp(opcion.c_str(),"2")==0){
				//VISUALIZAR RESERVAS

				arrayReservas=getListaReservas(s);


				cout<<"----------------------------\n";
				cout<<"LISTA DE RESERVAS\n";

				for (int var = 0; var < Reserva::numReservas; ++var) {
					arrayReservas[var].imprimirReserva();
				}

				arrayReservasInicializado=true;
				mostrarMenuPrincipalAdmin();
				getline(cin,opcion);
				continue;

			}else if(strcmp(opcion.c_str(),"3")==0){
				//BORRAR RESERVA TODO
			}else if(strcmp(opcion.c_str(),"4")==0){
				//VER HABITACIONES TODO


				cout<<"----------------------------\n";
				cout<<"LISTA DE HABITACIONES\n";


			}else if(strcmp(opcion.c_str(),"5")==0){
				//AÑADIR HABITACIONES TODO
			}else if(strcmp(opcion.c_str(),"6")==0){
				//BORRAR HABITACIONES TODO
			}else if(strcmp(opcion.c_str(),"7")==0){
				//VER PLAZAS DE PARKING TODO
			}else if(strcmp(opcion.c_str(),"8")==0){
				//AÑADIR PLAZAS DE PARKING TODO
			}else if(strcmp(opcion.c_str(),"9")==0){
				//BORRAR PLAZAS DE PARKING TODO
			}else if(strcmp(opcion.c_str(),"10")==0){
				//VOLVER AL MENU PRINCIPAL TODO
				opcion="-1";
				break;
			}else if(strcmp(opcion.c_str(),"11")==0){
				//CERRAR
				strcpy(sendBuff,"BYE");
				if (enviarMensaje(s,sendBuff)!=OK){
					return 0;
				}
				cout<<"Has elegido salir\n";
				cerrarConexion(s);
				return 0;
			}


			}while(1);


		}

		if(strcmp(opcion.c_str(),"2")==0){
			//VOLVER AL MENU PRINCIPAL
			opcion="-1";
			continue;

		}

	}

	//Salir
	else if (strcmp(opcion.c_str(),"3")==0){
		strcpy(sendBuff,"BYE");
		if (enviarMensaje(s,sendBuff)!=OK){
		}
		cout<<"Has elegido salir\n";
		cerrarConexion(s);
		break;
	}


	}while(1);

	return 0;

}

