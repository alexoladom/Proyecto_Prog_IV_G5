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



int enviarListaClientes(SOCKET& comm_socket,sqlite3* bd){

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
	return OK;
}

int enviarListaHabitaciones(SOCKET& comm_socket,sqlite3* bd){

	char sendBuff[512];

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
	return OK;
}

int enviarListaPlazasParking(SOCKET& comm_socket,sqlite3* bd){
	char sendBuff[512];

	getListaPlazasParking(bd);
	PlazaParking * arrayPlazasParking= new PlazaParking[PlazaParking::numPlazaParkings];

	arrayPlazasParking = getListaPlazasParking(bd);

	//Primero se envia el numero de habitaciones que hay

	strcpy(sendBuff,to_string(PlazaParking::numPlazaParkings).c_str());

	if(enviarMensaje(comm_socket,sendBuff)!=OK){
		return 0;
	}

	//Ahora se envian las habitaciones atributo por atributo

	for (int var = 0; var < PlazaParking::numPlazaParkings; ++var) {
		strcpy(sendBuff,to_string(arrayPlazasParking[var].getNumero()).c_str());
		if(enviarMensaje(comm_socket,sendBuff)!=OK){
			cerr<<"ERROR ENVIANDO NUMERO DE LA PLAZA DE PARKING Nº"<<var<<"\n";
			return 0;
		}
		strcpy(sendBuff,arrayPlazasParking[var].getZona().c_str());
		if(enviarMensaje(comm_socket,sendBuff)!=OK){
			cerr<<"ERROR ENVIANDO ZONA DE LA PLAZA DE PARKING Nº"<<var<<"\n";
			return 0;
		}
		strcpy(sendBuff,to_string(arrayPlazasParking[var].isOcupado()).c_str());
		if(enviarMensaje(comm_socket,sendBuff)!=OK){
			cerr<<"ERROR ENVIANDO OCUPACION DE LA PLAZA DE PARKING Nº"<<var<<"\n";
			return 0;
		}


	}
	return OK;
}


int enviarListaReservas(SOCKET& comm_socket,sqlite3* bd){
	char sendBuff[512];

	//Para actualizar el numero de clientes
	getListaReservas(bd);
	Reserva * arrayReservas= new Reserva[Reserva::numReservas];

	arrayReservas = getListaReservas(bd);

	//Primero se envia el numero de clientes que hay

	strcpy(sendBuff,to_string(Reserva::numReservas).c_str());

	if(enviarMensaje(comm_socket,sendBuff)!=OK){
		return 0;
	}

	//Ahora se envian los clientes atributo por atributo

	for (int var = 0; var < Reserva::numReservas; ++var) {
		strcpy(sendBuff,to_string(arrayReservas[var].getId()).c_str());
		if(enviarMensaje(comm_socket,sendBuff)!=OK){
			cerr<<"ERROR ENVIANDO ID DE LA RESERVA Nº"<<var<<"\n";
			return NOT_OK;
		}

		strcpy(sendBuff,arrayReservas[var].getFecha().c_str());
		if(enviarMensaje(comm_socket,sendBuff)!=OK){
			cerr<<"ERROR ENVIANDO FECHA DE LA RESERVA Nº"<<var<<"\n";
			return NOT_OK;
		}
		strcpy(sendBuff,to_string(arrayReservas[var].getDniCliente()).c_str());
		if(enviarMensaje(comm_socket,sendBuff)!=OK){
			cerr<<"ERROR ENVIANDO DNI DEL CLIENTE DE LA RESERVA Nº"<<var<<"\n";
			return NOT_OK;
		}
		strcpy(sendBuff,to_string(arrayReservas[var].getNumeroHabitacion()).c_str());
		if(enviarMensaje(comm_socket,sendBuff)!=OK){
			cerr<<"ERROR ENVIANDO NUMERO DE LA HABITACION DE LA RESERVA Nº"<<var<<"\n";
			return NOT_OK;
		}
		strcpy(sendBuff,to_string(arrayReservas[var].getNumeroPlazaParking()).c_str());
		if(enviarMensaje(comm_socket,sendBuff)!=OK){
			cerr<<"ERROR ENVIANDO NUMERO DE LA PLAZA DE PARKING DE LA RESERVA Nº"<<var<<"\n";
			return NOT_OK;
		}

	}
	return OK;
}


int anadirCliente(SOCKET& comm_socket,sqlite3* bd){
	char recvBuff[512];


	int dni;
	string nombre;
	int edad;
	string correo;

	if(recibirMensaje(comm_socket,recvBuff)!=OK){
		cout<<"ERROR RECIBIENDO DNI PARA AÑADIR CLIENTE\n";
		return 0;
	}
	dni = stoi(recvBuff);
	if(recibirMensaje(comm_socket,recvBuff)!=OK){
		cout<<"ERROR RECIBIENDO NOMBRE PARA AÑADIR CLIENTE\n";
		return 0;
	}
	nombre=recvBuff;
	if(recibirMensaje(comm_socket,recvBuff)!=OK){
		cout<<"ERROR RECIBIENDO EDAD PARA AÑADIR CLIENTE\n";
		return 0;
	}
	edad=stoi(recvBuff);
	if(recibirMensaje(comm_socket,recvBuff)!=OK){
		cout<<"ERROR RECIBIENDO CORREO PARA AÑADIR CLIENTE\n";
		return 0;
	}
	correo=recvBuff;

	Cliente c(dni,nombre,edad,correo);

	if(anadirCliente(c,bd)!=OK){
		cerr<<"ERROR AÑADIENDO CLIENTE A LA BD\n\n";
		return NOT_OK;
	}

	Cliente::numClientes++;
	return OK;


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

int anadirHabitacion(SOCKET& comm_socket,sqlite3* bd){
	char recvBuff[512];


	int numero;
	int piso;
	enum tipoHabitacion tipo;
	int capacidad;
	float precio;
	boolean ocupado;


	if(recibirMensaje(comm_socket,recvBuff)!=OK){
		cout<<"ERROR RECIBIENDO NUMERO PARA AÑADIR HABITACION\n";
		return 0;
	}
	numero = stoi(recvBuff);
	if(recibirMensaje(comm_socket,recvBuff)!=OK){
		cout<<"ERROR RECIBIENDO PISO PARA AÑADIR HABITACION\n";
		return 0;
	}
	piso=stoi(recvBuff);
	if(recibirMensaje(comm_socket,recvBuff)!=OK){
		cout<<"ERROR RECIBIENDO TIPO PARA AÑADIR HABITACION\n";
		return 0;
	}
	tipo=stringToTipoHabi(recvBuff);
	if(recibirMensaje(comm_socket,recvBuff)!=OK){
		cout<<"ERROR RECIBIENDO CAPACIDAD PARA AÑADIR HABITACION\n";
		return 0;
	}
	capacidad=stoi(recvBuff);
	if(recibirMensaje(comm_socket,recvBuff)!=OK){
		cout<<"ERROR RECIBIENDO PRECIO PARA AÑADIR HABITACION\n";
		return 0;
	}
	precio=atoi(recvBuff);
	if(recibirMensaje(comm_socket,recvBuff)!=OK){
		cout<<"ERROR RECIBIENDO OCUPACION PARA AÑADIR HABITACION\n";
		return 0;
	}
	ocupado=stoi(recvBuff);


	Habitacion h(numero,piso,tipo,capacidad,precio,ocupado);
	if(anadirHabitacion(bd,h)!=OK){
		cerr<<"ERROR AÑADIENDO HABTIACION A LA BD\n\n";
		return NOT_OK;
	}

	Habitacion::numHabitaciones++;
	return OK;


}

int anadirPlazaPaking(SOCKET& comm_socket,sqlite3* bd){
	char recvBuff[512];


	int numero;
	string zona;
	boolean ocupado;


	if(recibirMensaje(comm_socket,recvBuff)!=OK){
		cout<<"ERROR RECIBIENDO NUMERO PARA AÑADIR PLAZAPARKING\n";
		return 0;
	}
	numero = stoi(recvBuff);
	if(recibirMensaje(comm_socket,recvBuff)!=OK){
		cout<<"ERROR RECIBIENDO ZONA PARA AÑADIR PLAZAPARKING\n";
		return 0;
	}
	zona=recvBuff;
	if(recibirMensaje(comm_socket,recvBuff)!=OK){
		cout<<"ERROR RECIBIENDO OCUPACION PARA AÑADIR PLAZAPARKING\n";
		return 0;
	}
	ocupado = stoi(recvBuff);
	PlazaParking p(numero,zona,ocupado);
	if(anadirPlazaParking(bd,p)!=OK){
		cerr<<"ERROR AÑADIENDO PLAZAPARKING A LA BD\n\n";
		return NOT_OK;
	}

	PlazaParking::numPlazaParkings++;
	return OK;
}


int anadirReserva(SOCKET& comm_socket,sqlite3* bd){

	char recvBuff[512];


	int id;
	string fecha;
	int dniCliente;
	int numeroHab;
	int numeroPlaza;


	if(recibirMensaje(comm_socket,recvBuff)!=OK){
		cout<<"ERROR RECIBIENDO ID PARA AÑADIR RESERVA\n";
		return 0;
	}
	id = stoi(recvBuff);
	if(recibirMensaje(comm_socket,recvBuff)!=OK){
		cout<<"ERROR RECIBIENDO FECHA PARA AÑADIR RESERVA\n";
		return 0;
	}
	fecha=recvBuff;
	if(recibirMensaje(comm_socket,recvBuff)!=OK){
		cout<<"ERROR RECIBIENDO DNI DEL CLIENTE PARA AÑADIR RESERVA\n";
		return 0;
	}
	dniCliente=stoi(recvBuff);
	if(recibirMensaje(comm_socket,recvBuff)!=OK){
		cout<<"ERROR RECIBIENDO NUMERO DE HABITACION PARA AÑADIR RESERVA\n";
		return 0;
	}
	numeroHab=stoi(recvBuff);
	if(recibirMensaje(comm_socket,recvBuff)!=OK){
		cout<<"ERROR RECIBIENDO NUMERO DE PLAZAPARKING PARA AÑADIR RESERVA\n";
		return 0;
	}
	numeroPlaza=stoi(recvBuff);


	Reserva s(id,fecha,dniCliente,numeroHab,numeroPlaza);
	if(anadirReserva(s,bd)!=OK){
		cerr<<"ERROR AÑADIENDO RESERVA A LA BD\n\n";
		return NOT_OK;
	}

	Reserva::numReservas++;
	return OK;
}


int comprobarDni(SOCKET& comm_socket,sqlite3 *bd){

	char sendBuff[512], recvBuff[512];


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
	return OK;

}


int comprobarContrasena(SOCKET& comm_socket,sqlite3* bd){
	char sendBuff[512], recvBuff[512];

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

	return OK;


}



int anadirDniContrasena(SOCKET& comm_socket,sqlite3* bd){

	char recvBuff[512];

	int dni;
	if(recibirMensaje(comm_socket,recvBuff)!=OK){
		cout<<"ERROR RECIBIENDO DNI PARA AÑADIRLO\n";
		return 0;
	}

	dni=stoi(recvBuff);

	char contra[40];
	if(recibirMensaje(comm_socket,recvBuff)!=OK){
		cout<<"ERROR RECIBIENDO CONTRASEÑA PARA AÑADIRLO\n";
		return 0;
	}

	strcpy(contra, recvBuff);

	anadirDniContra(bd,dni,contra);

	return OK;
}

void cerrarConexion(SOCKET& comm_socket){
	closesocket(comm_socket);
	WSACleanup();
	cout<<"Socket cerrado\n";
}





