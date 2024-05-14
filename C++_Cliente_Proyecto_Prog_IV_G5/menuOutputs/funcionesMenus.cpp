#include "funcionesMenu.h"

#include "iostream"
using namespace std;


void mostrarMenuPrincipal(){
	cout<<"--------------------------\n";
	cout<<"¡BIENVENIDO AL HOTEL!\n";
	cout<<"1.- Cliente\n";
	cout<<"2.- Aministrador\n";
	cout<<"3.- Salir\n";
	cout<<"SELECIONE UNA OPCION:\n";

	int opcion;
	    cin >> opcion;

	    switch(opcion) {
	        case 1:
	        	mostrarMenuInicioCliente();
	            break;
	        case 2:
	        	mostrarMenuInicioAdmin();
	            break;
	        case 3:
	            cout << "Saliendo del programa...\n";
	            break;
	        default:
	            cout << "Opción no válida. Por favor, seleccione una opción válida.\n";
	            mostrarMenuPrincipal();
	            break;
	    }
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

void mostrarMenuInicioSesionCliente(){
    cout<<"----------------------\n";
    cout<<"MENU INICIO SESION CLIENTE\n";
    cout<<"1.- Ingresar credenciales\n";
    cout<<"2.- Volver al menú principal\n";
    cout<<"SELECCIONE UNA OPCION: \n";
}

void mostrarMenuRegistroCliente(){
    cout<<"-------------------------\n";
    cout<<"MENU DE REGISTRO CLIENTE\n";
    cout<<"Por favor, ingrese los datos solicitados:\n";

    cout<<"Nombre: ";

    cout<<"Apellido: ";

    cout<<"Correo electrónico: ";

    cout<<"Contraseña: ";

    cout<<"Confirmar contraseña: ";

    cout<<"Presione 1 para registrar, 2 para cancelar: ";
}

void mostrarMenuCliente(){
    cout<<"------------------------------\n";
    cout<<"MENU CLIENTE\n";
    cout<<"1.- Crear una reserva\n";
    cout<<"2.- Modificar una reserva\n";
    cout<<"3.- Volver al menú principal\n";
    cout<<"4.- Cerrar\n";
    cout<<"SELECCIONE UNA OPCION:\n";
}

void mostrarMenuCrearReserva(){
    cout<<"--------------------------------\n";
    cout<<"MENU CREAR RESERVA\n";
    cout<<"Por favor, ingrese los detalles de la reserva:\n";
    cout<<"Fecha de llegada (DD/MM/AAAA): ";

    cout<<"Fecha de salida (DD/MM/AAAA): ";

    cout<<"1.- Reservar Habitación\n";
    cout<<"2.- Reservar Plaza de parking\n";
    cout<<"3.- Volver al menú principal\n";
    cout<<"4.- Cerrar\n";
    cout<<"SELECCIONE UNA OPCION:\n";
}

void mostrarReservarHabitacion() {
	cout<<"---------------------------------\n";
	cout<<"MENU RESERVA HABITACION\n";
	cout<<"1.- Mostrar numero de habitaciones libres\n";

	cout<<"2.- Numero de la habitacion: \n";

	cout<<"3.- Volver al menu principal\n";
	cout<<"4.- Cerrar\n";
	cout<<"SELECCIONE UNA OPCION:\n";
}

void mostrarReservarPlazaParking() {
	cout<<"---------------------------------\n";
	cout<<"MENU RESERVA PLAZA DE PARKING\n";
	cout<<"1.- Mostrar numero de plazas de parking libres\n";

	cout<<"2.- Numero de la plaza de parking: \n";

	cout<<"3.- Volver al menu principal\n";
	cout<<"4.- Cerrar\n";
	cout<<"SELECCIONE UNA OPCION:\n";
}

void mostrarMenuModificarReserva(){
    cout<<"---------------------------------\n";
    cout<<"MENU MODIFICAR RESERVA\n";
    cout<<"Por favor, seleccione la reserva que desea modificar:\n";
    //Falta como hacerlo
    cout<<"Fecha de llegada: DD/MM/AAAA\n";

    cout<<"Fecha de salida: DD/MM/AAAA\n";

    cout<<"1.- Reservar Habitación\n";
    cout<<"2.- Reservar Plaza de parking\n";
    cout<<"3.- Volver al menú principal\n";
    cout<<"4.- Cerrar\n";
    cout<<"SELECCIONE UNA OPCION:\n";
}

//Parde del Administrador
void mostrarMenuInicioAdmin(){
	cout<<"----------------------\n";
	cout<<"MENU INICIO ADMINISTRADOR\n";
	cout<<"1.- Iniciar sesión\n";
	cout<<"2.- Volver al menú principal\n";
	cout<<"SELECCIONE UNA OPCION: \n";

}

void mostrarMenuInicioSesionAdmin(){
    cout<<"----------------------\n";
    cout<<"INICIO SESION ADMINISTRADOR\n";
    cout<<"Por favor, ingrese sus datos:\n";
    cout<<"Nombre de usuario del administrador: ";

    cout<<"Contraseña: ";

    cout<<"Presione 1 para iniciar sesión, 2 para cancelar: ";
}

void mostrarMenuAdmin(){
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

void mostrarMenuAñadirHabitacion() {
	cout<<"---------------------------------\n";
	cout<<"MENU AÑADIR HABITACION\n";
	cout<<"1.- Numero de la habitacion: \n";

	cout<<"2.- Piso de la habitacion: \n";

	cout<<"3.- Tipo de la habitación: \n";

	cout<<"4.- Capacidad de la habitacion: \n";

	cout<<"5.- Precio de la habitacion: \n";

	cout<<"6.- Habitacion ocupada: \n";

	cout<<"7.- Volver al menu principal\n";
	cout<<"8.- Cerrar\n";
	cout<<"SELECCIONE UNA OPCION:\n";
}

void mostrarMenuAñadirPlazaParking() {
	cout<<"---------------------------------\n";
	cout<<"MENU AÑADIR PLAZA DE PARKING\n";
	cout<<"1.- Numero de la plaza de parking: \n";

	cout<<"2.- Zona de la plaza de parking: \n";

	cout<<"3.- Plaza de parking ocupada: \n";

	cout<<"4.- Volver al menu principal\n";
	cout<<"5.- Cerrar\n";
	cout<<"SELECCIONE UNA OPCION:\n";
}





