
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

		while(strcmp(opcion.c_str(),"1")!=0&&strcmp(opcion.c_str(),"2")!=0
		&&strcmp(opcion.c_str(),"3")!=0)
		{
			cout<<"Opcion no valida, introduzca una opcion de nuevo:\n";
			getline(cin,opcion);
		}
		if(strcmp(opcion.c_str(),"1")==0){
			//INICIAR SESION
		}

		if(strcmp(opcion.c_str(),"2")==0){
			//REGISTRAR NUEVO CLIENTE
		}
		if(strcmp(opcion.c_str(),"3")==0){
			//VOLVER AL MENU PRINCIPAL
			opcion="-1";
			continue;
		}


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
			//INICIAR SESION
		}

		if(strcmp(opcion.c_str(),"2")==0){
			//VOLVER AL MENU PRINCIPAL
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

