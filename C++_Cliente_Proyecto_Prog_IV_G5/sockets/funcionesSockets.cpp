#include "funcionesSockets.h"

#define OK 1
#define NOT_OK 0;

#include "iostream"
using namespace std;

#define SERVER_IP "127.0.0.3"
#define SERVER_PORT 6000

int inicializarWinsock( WSADATA & wsa){
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		printf("Failed. Error Code : %d",WSAGetLastError());
		return NOT_OK;
	}

	printf("Initialised.");
	return OK;
}


int crearSocket(SOCKET& s, struct sockaddr_in &server){

	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
			printf("Could not create socket : %d", WSAGetLastError());
			WSACleanup();
			return NOT_OK;
		}

		printf("Socket created.\n");

		server.sin_addr.s_addr = inet_addr(SERVER_IP);
		server.sin_family = AF_INET;
		server.sin_port = htons(SERVER_PORT);
		return OK;
}

int conectarCliente(SOCKET& s,struct sockaddr_in &server){

	if (connect(s, (struct sockaddr*) &server, sizeof(server)) == SOCKET_ERROR) {
		printf("Connection error: %d", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return NOT_OK;
	}

	printf("Connection stablished with: %s (%d)\n", inet_ntoa(server.sin_addr),
	ntohs(server.sin_port));
	return OK;
}


int recibirMensaje(SOCKET& comm_socket,char recvBuff[]){


	int bytes = recv(comm_socket, recvBuff, sizeof(char)*512, 0);

	if (bytes > 0) {
		return OK;
	}
	return NOT_OK;

}

int enviarMensaje(SOCKET& comm_socket,char sendBuff[]){

	send(comm_socket, sendBuff, sizeof(char)*512, 0);
	return OK;
}

void cerrarConexion(SOCKET& comm_socket){
	closesocket(comm_socket);
	WSACleanup();
	cout<<"Socket cerrado\n";

}

Cliente * getListaClientes(SOCKET& s,struct sockaddr_in &server){

	char sendBuff[512], recvBuff[512];
	strcpy(sendBuff,"ENVIAR LISTA CLIENTES");
	if (enviarMensaje(s,sendBuff)!=OK){
		cerr<<"ERROR ENVIANDO SOLICITUD DE LISTA DE CLIENTES\n";
		return 0;
	}

	if(recibirMensaje(s,recvBuff)!=OK){
		cerr<<"ERROR RECIBIENDO LISTA DE CLIENTES\n";
		return 0;
	}

	cout<<"----------------------------\n";
	cout<<"LISTA DE CLIENTES\n";
	int numClientes =stoi(recvBuff);
	Cliente::numClientes=numClientes;
	Cliente* arrayClientes =new Cliente[numClientes];
	int dni;
	char nombre[20];
	int edad;
	char correo[50];

	for (int var = 0; var < numClientes; ++var) {
		if(recibirMensaje(s,recvBuff)!=OK){
			cerr<<"ERROR RECIBIENDO DNI DE CLIENTE Nº"<<var<<"\n";
			return 0;
		}
		dni=stoi(recvBuff);
		if(recibirMensaje(s,recvBuff)!=OK){
			cerr<<"ERROR RECIBIENDO NOMBRE DE CLIENTE Nº"<<var<<"\n";
			return 0;
		}
		strcpy(nombre,recvBuff);
		if(recibirMensaje(s,recvBuff)!=OK){
			cerr<<"ERROR RECIBIENDO EDAD DE CLIENTE Nº"<<var<<"\n";
			return 0;
		}
		edad=stoi(recvBuff);
		if(recibirMensaje(s,recvBuff)!=OK){
			cerr<<"ERROR RECIBIENDO CORREO DE CLIENTE Nº"<<var<<"\n";
			return 0;
		}
		strcpy(correo,recvBuff);
		Cliente c(dni,nombre,edad,correo);
		arrayClientes[var]=c;

	}
	return arrayClientes;

}

Reserva* getListaReservas(SOCKET& s,struct sockaddr_in &server){
	char sendBuff[512], recvBuff[512];

	strcpy(sendBuff,"ENVIAR LISTA RESERVAS");
	if (enviarMensaje(s,sendBuff)!=OK){
		cerr<<"ERROR ENVIANDO SOLICITUD DE LISTA DE RESERVAS\n";
		return 0;
	}

	if(recibirMensaje(s,recvBuff)!=OK){
		cerr<<"ERROR RECIBIENDO LISTA DE RESERVAS\n";
		return 0;
	}

	cout<<"----------------------------\n";
	cout<<"LISTA DE RESERVAS\n";

	int numReservas =stoi(recvBuff);
	Reserva::numReservas=numReservas;
	Reserva* arrayReservas =new Reserva[numReservas];
	int id;
	char fecha[20];
	int dniCliente;
	int numeroHabitacion;
	int numeroPlazaParking;

	for (int var = 0; var < numReservas; ++var) {
		if(recibirMensaje(s,recvBuff)!=OK){
			cerr<<"ERROR RECIBIENDO ID DE LA RESERVA Nº"<<var<<"\n";
			return 0;
		}
		id=stoi(recvBuff);
		if(recibirMensaje(s,recvBuff)!=OK){
			cerr<<"ERROR RECIBIENDO FECHA DE LA RESERVA Nº"<<var<<"\n";
			return 0;
		}
		strcpy(fecha,recvBuff);
		if(recibirMensaje(s,recvBuff)!=OK){
			cerr<<"ERROR RECIBIENDO DNI CLIENTE DE LA RESERVA Nº"<<var<<"\n";
			return 0;
		}
		dniCliente=stoi(recvBuff);
		if(recibirMensaje(s,recvBuff)!=OK){
			cerr<<"ERROR RECIBIENDO NUMERO HABITACION DE LA RESERVA Nº"<<var<<"\n";
			return 0;
		}
		numeroHabitacion=stoi(recvBuff);
		if(recibirMensaje(s,recvBuff)!=OK){
			cerr<<"ERROR RECIBIENDO NUMERO PLAZAPARKING DE LA RESERVA Nº"<<var<<"\n";
			return 0;
		}
		numeroPlazaParking= stoi(recvBuff);
		Reserva r (id,fecha,dniCliente,numeroHabitacion,numeroPlazaParking);
		arrayReservas[var]=r;

	}
	return arrayReservas;
}




