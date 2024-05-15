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


int crearSocket(SOCKET& conn_socket, struct sockaddr_in &server){

	if ((conn_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
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

int bindSocket(SOCKET& conn_socket, struct sockaddr_in &server){

	if (bind(conn_socket, (struct sockaddr*) &server,
				sizeof(server)) == SOCKET_ERROR) {
			printf("Bind failed with error code: %d", WSAGetLastError());
			closesocket(conn_socket);
			WSACleanup();
			return NOT_OK;
		}

		printf("Bind done.\n");
		return OK;
}


int esperarConexion(SOCKET& conn_socket){
	if (listen(conn_socket, 1) == SOCKET_ERROR) {
		printf("Listen failed with error code: %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return NOT_OK;
	}
	return OK;
}


int aceptarConexion(SOCKET& conn_socket, SOCKET& comm_socket, struct sockaddr_in &client){
	printf("Waiting for incoming connections...\n");
	int stsize = sizeof(struct sockaddr);

	comm_socket = accept(conn_socket, (struct sockaddr*) &client, &stsize);

	if (comm_socket == INVALID_SOCKET) {
		printf("accept failed with error code : %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return NOT_OK;
	}
	printf("Incomming connection from: %s (%d)\n", inet_ntoa(client.sin_addr),
	ntohs(client.sin_port));


	closesocket(conn_socket);
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



int enviarListaReservas(SOCKET& comm_socket,sqlite3* bd){
	char sendBuff[512];

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
			return NOT_OK;
		}
		strcpy(sendBuff,arrayClientes[var].getNombre().c_str());
		if(enviarMensaje(comm_socket,sendBuff)!=OK){
			return NOT_OK;
		}
		strcpy(sendBuff,to_string(arrayClientes[var].getEdad()).c_str());
		if(enviarMensaje(comm_socket,sendBuff)!=OK){
			return NOT_OK;
		}
		strcpy(sendBuff,arrayClientes[var].getCorreo().c_str());
		if(enviarMensaje(comm_socket,sendBuff)!=OK){
			return NOT_OK;
		}

	}
	return OK;
}

void cerrarConexion(SOCKET& comm_socket){
	closesocket(comm_socket);
	WSACleanup();
	cout<<"Socket cerrado\n";
}





