#include "funcionesMenu.h"

#include "iostream"
using namespace std;

//Para el inicio sesion del cliente
struct Credenciales {
    string nombreUsuario;
    string contrasena;
};

Credenciales credencialesCliente;

//Para el registro del cliente
struct DatosCliente {
    string nombre;
    string apellido;
    string correoElectronico;
    string contrasena;
};

DatosCliente datosCliente;

void ingresarCredenciales() {
    cout << "Por favor, ingrese su nombre de usuario: ";
    cin >> credencialesCliente.nombreUsuario;
    cout << "Por favor, ingrese su contraseña: ";
    cin >> credencialesCliente.contrasena;
}

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

	int opcion;
	cin >> opcion;

	switch(opcion) {
		case 1:
			mostrarMenuInicioSesionCliente();
	        break;
	    case 2:
	    	mostrarMenuRegistroCliente();
	        break;
	    case 3:
	    	mostrarMenuPrincipal();
	        break;
	    default:
	        cout << "Opción no válida. Por favor, seleccione una opción válida.\n";
	        mostrarMenuInicioCliente();
	        break;
	}
}

void mostrarMenuInicioSesionCliente(){
    cout<<"----------------------\n";
    cout<<"MENU INICIO SESION CLIENTE\n";
    cout<<"1.- Ingresar credenciales del usuario\n";
    cout<<"2.- Volver al menú principal\n";
    cout<<"SELECCIONE UNA OPCION: \n";

    int opcion;
    cin >> opcion;

   	switch(opcion) {
   		case 1:
   			ingresarCredenciales();
   			//Verificación
   			cout << "Credenciales ingresadas:\n";
   			cout << "Nombre de usuario: " << credencialesCliente.nombreUsuario << endl;
            cout << "Contraseña: " << credencialesCliente.contrasena << endl;
            mostrarMenuCliente();
   	        break;
       case 2:
   	       	mostrarMenuPrincipal();
   	       	break;
       default:
   	        cout << "Opción no válida. Por favor, seleccione una opción válida.\n";
    	    mostrarMenuInicioSesionCliente();
    	    break;
    }
}

void mostrarMenuRegistroCliente(){
    cout<<"-------------------------\n";
    cout<<"MENU DE REGISTRO CLIENTE\n";
    cout<<"Por favor, ingrese los datos solicitados:\n";

    cout<<"Nombre: ";
    cin >> datosCliente.nombre;

    cout<<"Apellido: ";
    cin >> datosCliente.apellido;

    cout<<"Correo electrónico: ";
    cin >> datosCliente.correoElectronico;

    cout<<"Contraseña: ";
    cin >> datosCliente.contrasena;

    cout<<"Confirmar contraseña: ";
    cin >> datosCliente.contrasena;

    cout<<"Presione 1 para registrar, 2 para cancelar: ";

    int opcion;
    cin >> opcion;

   	switch(opcion) {
		case 1:
			//Funcion de almacenar
			cout << "Registrando al cliente...\n";
			cout << "Datos del cliente registrados:\n";
			cout << "Nombre: " << datosCliente.nombre << endl;
			cout << "Apellido: " << datosCliente.apellido << endl;
			cout << "Correo electrónico: " << datosCliente.correoElectronico << endl;
			mostrarMenuInicioSesionCliente();
			break;
		case 2:
			cout << "Cancelando registro...\n";
			mostrarMenuPrincipal();
			break;
		default:
			cout << "Opción no válida. Registro cancelado.\n";
			mostrarMenuRegistroCliente();
			break;
    }
}

void mostrarMenuCliente(){
    cout<<"------------------------------\n";
    cout<<"MENU CLIENTE\n";
    cout<<"1.- Crear una reserva\n";
    cout<<"2.- Modificar una reserva\n";
    cout<<"3.- Volver al menú principal\n";
    cout<<"4.- Cerrar\n";
    cout<<"SELECCIONE UNA OPCION:\n";

    int opcion;
    cin >> opcion;

    switch(opcion) {
    	case 1:
    		mostrarMenuCrearReserva();
            break;
    	case 2:
    		mostrarMenuModificarReserva();
    		break;
    	case 3:
    		mostrarMenuPrincipal();
            break;
        case 4:
            cout << "Cerrando...\n";
            break;
        default:
            cout << "Opción no válida. Registro cancelado.\n";
            mostrarMenuCliente();
            break;
    }
}

void mostrarMenuCrearReserva(){
    cout<<"--------------------------------\n";
    cout<<"MENU CREAR RESERVA\n";
    cout<<"1.- Reservar Habitación\n";
    cout<<"2.- Reservar Plaza de parking\n";
    cout<<"3.- Volver al menú principal\n";
    cout<<"4.- Cerrar\n";
    cout<<"SELECCIONE UNA OPCION:\n";

    int opcion;
    cin >> opcion;

    switch(opcion) {
		case 1:
			mostrarReservarHabitacion();
			break;
		case 2:
			mostrarReservarPlazaParking();
			break;
		case 3:
			mostrarMenuPrincipal();
			break;
		case 4:
			cout << "Cerrando...\n";
			break;
		default:
			cout << "Opción no válida. Registro cancelado.\n";
			mostrarMenuCrearReserva();
			break;
	}
}

void mostrarReservarHabitacion() {
    cout<<"---------------------------------\n";
    cout<<"MENU RESERVA HABITACION\n";
    cout<<"Por favor, ingrese los detalles de la reserva:\n";
    cout<<"Fecha de llegada (DD/MM/AAAA): ";
    string fechaLlegada;
    cin >> fechaLlegada;

    cout<<"Fecha de salida (DD/MM/AAAA): ";
    string fechaSalida;
    cin >> fechaSalida;

    cout<<"1.- Mostrar numeros de habitaciones libres\n";
    cout<<"2.- Numero de la habitacion: \n";
    cout<<"3.- Volver al menu principal\n";
    cout<<"4.- Cerrar\n";
    cout<<"SELECCIONE UNA OPCION:\n";

    int opcion;
    cin >> opcion;

    switch(opcion) {
        case 1:
            //metodoListarHabitaciones();
            break;
        case 2: {
            int numHabitacion;
            cout << "Ingrese el número de la habitación: ";
            cin >> numHabitacion;
            cout << "Reservando habitación " << numHabitacion << " desde " << fechaLlegada << " hasta " << fechaSalida << endl;
            //Falta implementar el metodo para reservar la habitacion
            break;
        }
        case 3:
            mostrarMenuPrincipal();
            break;
        case 4:
            cout << "Cerrando...\n";
            break;
        default:
            cout << "Opción no válida. Registro cancelado.\n";
            mostrarReservarHabitacion();
            break;
    }
}

void mostrarReservarPlazaParking() {
    cout<<"---------------------------------\n";
    cout<<"MENU RESERVA PLAZA DE PARKING\n";
    cout<<"Por favor, ingrese los detalles de la reserva:\n";
    cout<<"Fecha de llegada (DD/MM/AAAA): ";
    string fechaLlegada;
    cin >> fechaLlegada;

    cout<<"Fecha de salida (DD/MM/AAAA): ";
    string fechaSalida;
    cin >> fechaSalida;

    cout<<"1.- Mostrar numero de plazas de parking libres\n";
    cout<<"2.- Numero de la plaza de parking: \n";
    cout<<"3.- Volver al menu principal\n";
    cout<<"4.- Cerrar\n";
    cout<<"SELECCIONE UNA OPCION:\n";

    int opcion;
    cin >> opcion;

    switch(opcion) {
        case 1:
            //metodoListarPlazasParkingLibres();
            break;
        case 2: {
            int numPlazaParking;
            cout << "Ingrese el número de la plaza de parking: ";
            cin >> numPlazaParking;
            cout << "Reservando plaza de parking " << numPlazaParking << " desde " << fechaLlegada << " hasta " << fechaSalida << endl;
            //Falta implementar el metodo para reservar la plaza de parking
            break;
        }
        case 3:
            mostrarMenuPrincipal();
            break;
        case 4:
            cout << "Cerrando...\n";
            break;
        default:
            cout << "Opción no válida. Registro cancelado.\n";
            mostrarReservarPlazaParking();
            break;
    }
}

void mostrarMenuModificarReserva(){
    cout<<"---------------------------------\n";
    cout<<"MENU MODIFICAR RESERVA\n";
    cout<<"Por favor, seleccione la reserva que desea modificar:\n";
    int numeroReserva;
    cin >> numeroReserva;
    //Falta como hacerlo
    cout<<"Fecha de llegada: DD/MM/AAAA\n";
    string fechaLlegada;
    cin >> fechaLlegada;

    cout<<"Fecha de salida: DD/MM/AAAA\n";
    string fechaSalida;
    cin >> fechaSalida;

    cout<<"1.- Modificar Habitación\n";
    cout<<"2.- Modificar Plaza de parking\n";
    cout<<"3.- Volver al menú principal\n";
    cout<<"4.- Cerrar\n";
    cout<<"SELECCIONE UNA OPCION:\n";
    int opcion;
	cin >> opcion;

	switch(opcion) {
		case 1:
			int numHabitacionAntes;
			int numHabitacionAhora;
			cout << "Ingrese el número de la habitación que tenia: ";
			cin >> numHabitacionAntes;
			//Checkear si es verdad
			//Liberar habitacion antes
			//metodoListarHabitacionLibres();
			cout << "Ingrese el número de la habitación que desea: ";
			cin >> numHabitacionAhora;
			cout << "Reservando habitación " << numHabitacionAhora << " desde " << fechaLlegada << " hasta " << fechaSalida << endl;
			//Falta implementar el metodo para reservar la habitacion
			break;
		case 2: {
			int numPlazaParkingAntes;
			int numPlazaParkingAhora;
			cout << "Ingrese el número de la plaza de parking que tenias antes: ";
			cin >> numPlazaParkingAntes;
			//Checkear si es verdad
			//Liberar plaza antes
			//metodoListarPlazasParkingLibres();
			cout << "Ingrese el número de la plaza de parking que desea: ";
			cin >> numPlazaParkingAhora;
			cout << "Reservando plaza de parking " << numPlazaParking << " desde " << fechaLlegada << " hasta " << fechaSalida << endl;
			//Falta implementar el metodo para reservar la plaza de parking
			break;
		}
		case 3:
			mostrarMenuPrincipal();
			break;
		case 4:
			cout << "Cerrando...\n";
			break;
		default:
			cout << "Opción no válida. Registro cancelado.\n";
			mostrarMenuModificarReserva();
			break;
	}
}

//Parde del Administrador
void mostrarMenuInicioAdmin(){//Viene del menu principal
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

//Falta
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

//Falta
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



//Main que luego se borrara
int main() {
	mostrarMenuPrincipal();
    return 0;
}

