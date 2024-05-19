#include "funcionesMenu.h"
#include "../sockets/funcionesSockets.h"


#include <stdio.h>
#include <winsock2.h>
#include "iostream"
#include "../domain/cliente.h"
#include "../domain/reserva.h"
#include "../domain/habitacion.h"
#include "../domain/plazaParking.h"
using namespace std;

#define OK 1;
#define NOT_OK 0;


void mostrarMenuPrincipal(){
	cout<<"--------------------------\n";
	cout<<"¡BIENVENIDO AL HOTEL!\n";
	cout<<"1.- Cliente\n";
	cout<<"2.- Aministrador\n";
	cout<<"3.- Salir\n";
	cout<<"SELECIONE UNA OPCION:\n";
}

//Parte del cliente
void mostrarMenuInicioCliente(){
	cout<<"--------------------------\n";
	cout<<"MENU DE INICIO CLIENTE\n";
	cout<<"1.- Iniciar sesión\n";
	cout<<"2.- Registrarse\n";
	cout<<"3.- Volver al menú principal\n";
	cout<<"SELECIONE UNA OPCION:\n";

}



void mostrarMenuPrincipalCliente(){
    cout<<"------------------------------\n";
    cout<<"MENU CLIENTE\n";
    cout<<"1.- Crear una reserva\n";
    cout<<"2.- Modificar una reserva\n";
    cout<<"3.- Cancelar una reserva\n";
    cout<<"4.- Volver al menú principal\n";
    cout<<"5.- Cerrar\n";
    cout<<"SELECCIONE UNA OPCION:\n";

}

//Parde del Administrador
void mostrarMenuInicioAdmin(){
	cout<<"----------------------\n";
	cout<<"MENU INICIO ADMINISTRADOR\n";
	cout<<"1.- Iniciar sesión\n";
	cout<<"2.- Volver al menú principal\n";
	cout<<"3.- Cerrar\n";
	cout<<"SELECCIONE UNA OPCION: \n";

}



void mostrarMenuPrincipalAdmin(){
	cout<<"---------------------------------\n";
	cout<<"MENU PRINCIPAL ADMINISTRADOR\n";
	cout<<"1.- Visualizar la lista de clientes\n";
	cout<<"2.- Ver reservas\n";
	cout<<"3.- Borrar reserva\n";
	cout<<"4.- Ver habitaciones\n";
	cout<<"5.- Añadir habitacion\n";
	cout<<"6.- Borrar habitación\n";
	cout<<"7.- Ver plazas de parking\n";
	cout<<"8.- Añadir plazas de parking\n";
	cout<<"9.- Borrar plazas de parking\n";
	cout<<"10.- Volver al menu principal\n";
	cout<<"11.- Cerrar\n";
	cout<<"SELECCIONE UNA OPCION:\n";

}



Cliente registrarse(SOCKET & s) {

    string nombre;
    string apellido;
    string nombreCompleto;
    string correo;
    int dni;
    int edad;
    char contra[40];
    char contra2[40];

    cout << "Introduce tu nombre: ";
    cin >> nombre;
    cout << "\nIntroduce tus apellidos: ";
    cin >> apellido;
    cout << "\nIntroduce tu dni: ";
    cin >> dni;

    while(comprobarDni(s,dni)==1){
    	 cerr<<"¡El dni introducido ya esta en uso!\n\n";
    	 cout << "\nIntroduce tu dni: ";
    	 cin >> dni;
    }
    cout << "\nIntroduce tu edad: ";
    cin >> edad;
    cout << "\nIntroduce tu correo: ";
    cin >> correo;
    cout << "\nIntroduce tu contraseña: ";
    cin >> contra;
    cout << "\nConfirma tu contraseña: ";
    cin >> contra2;

    while (strcmp(contra,contra2)!=0) {
        cerr << "Error confirmando la contraseña. Inténtalo de nuevo: \n";
        cin >> contra2;
    }


    anadirDniContrasena(s,dni,contra);
    nombreCompleto = nombre + " " + apellido;
    Cliente c(dni, nombreCompleto.c_str(), edad, correo.c_str());

    anadirCliente(s,c);
    return c;
}

//Reserva crearReserva(){
//
//}

Habitacion anadirHabitacion() {
    Habitacion h;

    int numero;
    int piso;
    string tipo;
    int capacidad;
    float precio;
    bool ocupado;
    tipoHabitacion tipoHab;

    cout << "Introduce el numero de la habitación: ";
    cin >> numero;
    cout << "\nIntroduce el piso de la habitación: ";
    cin >> piso;
    cout << "\nIntroduce el tipo de habitacion (simple, doble, suite): ";
    cin >> tipo;

    while (tipo != "simple" && tipo != "doble" && tipo != "suite") {
        cout << "Error al introducir el tipo de habitación. Inténtalo de nuevo: ";
        cin >> tipo;
    }

    if (tipo == "simple") tipoHab = simple;
    else if (tipo == "doble") tipoHab = doble;
    else tipoHab = suite;

    cout << "\nIntroduce la capacidad de la habitacion: ";
    cin >> capacidad;
    cout << "\nIntroduce el precio: ";
    cin >> precio;
    cout << "\nIntroduce si está ocupada (0 para no, 1 para sí): ";
    cin >> ocupado;

  //  h = new Habitacion(numero, piso, tipoHab, capacidad, precio, ocupado);

    return h;
}
PlazaParking anadirPlazaParking(){
	PlazaParking p;

	int numero;
	string zona;
	bool ocupado;

	cout <<"Introduce el numero de la plaza de parking: ";
	cin >> numero;
	cout <<"Introduce la zona en la que estará la plaza de parking";
	cin >> zona;
	cout <<"Introduce la ocupación de la plaza de parking(Lo normal es que este libre)";
	cin >> ocupado;

//	p = new PlazaParking(numero, zona, ocupado);

	return p;
}



