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

Cliente * getListaClientes(SOCKET& s){

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

Reserva* getListaReservas(SOCKET& s){
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

enum tipoHabitacion stringToTipoHabi(char* s){
	if(strcmp(s,"Simple")==0){
		return simple;
	}else if(strcmp(s,"Doble")==0){
		return doble;
	}else if(strcmp(s,"Suite")==0){
		return suite;
	}
	return simple;
}
Habitacion* getListaHabitaciones(SOCKET& s){
	char sendBuff[512], recvBuff[512];

	strcpy(sendBuff,"ENVIAR LISTA HABITACIONES");
	if (enviarMensaje(s,sendBuff)!=OK){
		cerr<<"ERROR ENVIANDO SOLICITUD DE LISTA DE HABITACIONES\n";
		return 0;
	}

	if(recibirMensaje(s,recvBuff)!=OK){
		cerr<<"ERROR RECIBIENDO LISTA DE HABITACIONES\n";
		return 0;
	}

	int numHabitaciones =stoi(recvBuff);
	Habitacion::numHabitaciones=numHabitaciones;
	Habitacion* arrayHabitaciones =new Habitacion[numHabitaciones];
	int numero;
	int piso;
	enum tipoHabitacion tipo;
	int capacidad;
	float precio;
	bool ocupado;

	for (int var = 0; var < numHabitaciones; ++var) {
		if(recibirMensaje(s,recvBuff)!=OK){
			cerr<<"ERROR RECIBIENDO NUMERO DE LA HABITACION Nº"<<var<<"\n";
			return 0;
		}
		numero=stoi(recvBuff);
		if(recibirMensaje(s,recvBuff)!=OK){
			cerr<<"ERROR RECIBIENDO PISO DE LA HABITACION Nº"<<var<<"\n";
			return 0;
		}
		piso=stoi(recvBuff);
		if(recibirMensaje(s,recvBuff)!=OK){
			cerr<<"ERROR RECIBIENDO TIPO DE LA HABITACION Nº"<<var<<"\n";
			return 0;
		}
		tipo=stringToTipoHabi(recvBuff);
		if(recibirMensaje(s,recvBuff)!=OK){
			cerr<<"ERROR RECIBIENDO CAPACIDAD DE LA HABITACION Nº"<<var<<"\n";
			return 0;
		}
		capacidad=stoi(recvBuff);
		if(recibirMensaje(s,recvBuff)!=OK){
			cerr<<"ERROR RECIBIENDO PRECIO DE LA HABITACION Nº"<<var<<"\n";
			return 0;
		}
		precio= atof(recvBuff);
		if(recibirMensaje(s,recvBuff)!=OK){
			cerr<<"ERROR RECIBIENDO OCUPACION DE LA HABITACION Nº"<<var<<"\n";
			return 0;
		}
		ocupado=stoi(recvBuff);

		Habitacion h(numero,piso,tipo,capacidad,precio,ocupado);
		arrayHabitaciones[var]=h;

	}
	return arrayHabitaciones;
}

int comprobarDni(SOCKET& s,int dni){
	char sendBuff[512], recvBuff[512];

	strcpy(sendBuff,"COMPROBAR DNI");
	if (enviarMensaje(s,sendBuff)!=OK){
		cerr<<"ERROR ENVIANDO SOLICITUD PARA COMPROBAR DNI\n";
		return 0;
	}

	string dnis = to_string(dni);

	strcpy(sendBuff,dnis.c_str());
	if (enviarMensaje(s,sendBuff)!=OK){
		cerr<<"ERROR ENVIANDO DNI PARA COMPROBAR DNI\n";
		return 0;
	}

	if(recibirMensaje(s,recvBuff)!=OK){
		cerr<<"ERROR RECIBIENDO RESULTADO DE LA COMPROBACIONE DE DNI\n "<<dni;
		return 0;
	}
	if (strcmp(recvBuff,"DNI EXISTENTE")==0){
		return OK;
	}else{
		return NOT_OK;
	}

}

int comprobarContrasena(SOCKET& s,int dni,char* contrasena){
	char sendBuff[512], recvBuff[512];

		strcpy(sendBuff,"COMPROBAR CONTRASEÑA");
		if (enviarMensaje(s,sendBuff)!=OK){
			cerr<<"ERROR ENVIANDO SOLICITUD PARA COMPROBAR CONTRASEÑA\n";
			return 0;
		}
		string dnis = to_string(dni);
		strcpy(sendBuff,dnis.c_str());
		if (enviarMensaje(s,sendBuff)!=OK){
			cerr<<"ERROR ENVIANDO DNI PARA COMPROBAR CONTRASEÑA\n";
			return 0;
		}
		strcpy(sendBuff,contrasena);
		if (enviarMensaje(s,sendBuff)!=OK){
			cerr<<"ERROR ENVIANDO CONTRASEÑA PARA COMPROBAR CONTRASEÑA\n";
			return 0;
		}

		if(recibirMensaje(s,recvBuff)!=OK){
			cerr<<"ERROR RECIBIENDO RESULTADO DE LA COMPROBACIONE DE CONTRASENA\n "<<dni;
			return 0;
		}
		if (strcmp(recvBuff,"CONTRASEÑA CORRECTA")==0){
			return OK;
		}else{
			return NOT_OK;
		}
}



int iniciarSesion(SOCKET& s){//0 bien; 1 mal
	int dni;
	char dnic[20];
	char contrasena[50];

	cout <<"Introduce el dni de usuario: ";
	cin >> dnic; //Falta hacerlo a tu manera en todos los cin
	dni = stoi(dnic);
	cout <<"\nIntroduce tu contraseña: ";
	cin >> contrasena;

	if(comprobarDni(s,dni)!=OK){
		return NOT_OK;
	}else if(comprobarContrasena(s,dni,contrasena)!=OK){
		return OK;
	}

	return NOT_OK;
}


