#include <stdio.h>
#include <stdlib.h>
#include "menuPrincipal.h"
#include "../db/dbManager.h"



void mostrarMenuPrincipal(sqlite3 * db) {////////////////////////////////////Esta
    int opcion;
    int numerin;

    printf("¡Bienvenido al Hotel!\n");
    fflush(stdout);
    printf("1. Cliente\n");
    fflush(stdout);
    printf("2. Administrador\n");
    fflush(stdout);
    printf("3. Salir\n");
    fflush(stdout);
    printf("Seleccione una opción: ");
    fflush(stdout);
    scanf("%d", &opcion);

    switch (opcion) {
        case 1:
            menuCliente(db);
            break;
        case 2:
        	printf("Introduce el codigo de acceso admin: ");
        	fflush(stdout);
        	scanf("%d", &numerin);
        	if(numerin == 123){
        		menuAdministrador(db);
        	}else{
        		printf("El numero de acceso no es correcto.");
        		fflush(stdout);
        		mostrarMenuPrincipal(db);
        		break;
        	}
            break;
        case 3:
            printf("Vuelva pronto\n");
            fflush(stdout);
            break;
        default:
            printf("Opción no válida. Por favor, ingrese una opción válida.\n");
            fflush(stdout);
            mostrarMenuPrincipal(db);
            break;
    }
}

void menuCliente(sqlite3 * db) {////////////////////////////////////Esta
	int opcion;

	printf("1. Iniciar sesión\n");
	fflush(stdout);
    printf("2. Registrarse\n");
    fflush(stdout);
    printf("3. Volver al menú principal\n");
    fflush(stdout);
    printf("Seleccione una opción: ");
    fflush(stdout);
    scanf("%d", &opcion);

    switch(opcion) {
        case 1:
            iniciarSesionCliente(db);
            break;
        case 2:
            registrarseCliente(db);
            break;
        case 3:
            mostrarMenuPrincipal(db);
            break;
        default:
            printf("Opción no válida. Por favor, ingrese una opción válida.\n");
            fflush(stdout);
            menuCliente(db);
            break;
    }
}

void iniciarSesionCliente(sqlite3 * db) {////////////////////////////////////
	char nomUser[50];
	int contra;

    printf("Iniciando sesión como cliente...\n");
    fflush(stdout);
    printf("Introduce tu usuario: ");
    fflush(stdout);
    scanf("%s", nomUser);
    if(comprobarDni(nomUser)){//Falta aplicar el metodo

    }else{
    	printf("Nombre de ususario incorrecto");
    	fflush(stdout);
    	inicioSesionCliente(db);
    }
    printf("Introduce tu contraseña: ");
    fflush(stdout);
    scanf("%i", contra);
    if(comprobarContra(contra)){//Falta aplicar el metodo

    }else{
    	printf("Contraseña incorrecta");
    	fflush(stdout);
    	inicioSesionCliente(db);
    }
}

void registrarseCliente(sqlite3 * db) {////////////////////////////////////

	//TODO falta crear un cliente y solicitar todos los datos (edad,correo...)
	char nomUser[50];
    int contra;
    int edad;
    char correo[50];
    int dni;
    char nombre[50];

    printf("Registrando nuevo cliente...\n");
    fflush(stdout);

    printf("Introduce tu nuevo usuario: \n");
    fflush(stdout);
    scanf("%c", nomUser);

    printf("Introduce tu edad: \n");
    fflush(stdout);
    scanf("%i", edad);

    printf("Introduce tu dni sin la letra: \n");
    fflush(stdout);
    scanf("%i", dni);

    printf("Introduce tu correo: \n");
    fflush(stdout);
    scanf("%c", correo);

    printf("Introduce tu nombre: \n");
    fflush(stdout);
    scanf("%c", nombre);

    printf("Introduce tu contraseña: \n");
    fflush(stdout);
    scanf("%d", &contra);

    printf("Registro exitoso.\n");

    iniciarSesionCliente(db);
    Cliente c ={dni, nomUser, edad, correo};
    imprimirCliente(c);
}

void menuAdministrador(sqlite3 * db) {////////////////////////////////////Esta
	int opcion;

	    printf("1. Iniciar sesión\n");
	    fflush(stdout);
	    printf("2. Volver al menú principal\n");
	    fflush(stdout);
	    printf("Seleccione una opción: ");
	    fflush(stdout);
	    scanf("%d", &opcion);

	    switch(opcion) {
	        case 1:
	            iniciarSesionAdmin(db);
	            break;
	        case 2:
	            mostrarMenuPrincipal(db);
	            break;
	        default:
	            printf("Opción no válida. Por favor, ingrese una opción válida.\n");
	            fflush(stdout);
	            menuAdministrador(db);
	            break;
	    }
}

void iniciarSesionAdmin(sqlite3 * db) {////////////////////////////////////
	char nomUser[50];
	int contra;

    printf("Iniciando sesión como administrador...\n");
    fflush(stdout);
    printf("Nombre usuario: Jorge, Contra:123, para poder acceder\n");/////
    fflush(stdout);
    printf("Introduce tu usuario de Trabajador: ");
    fflush(stdout);
    scanf("%c", &nomUser);

    if(strcmp(nomUser, "Jorge") == 0){
    	printf("Introduce tu contraseña: ");
    	fflush(stdout);
    	scanf("%d", &contra);
    	if(contra == 123){
    		menuTrabajo(db);
    	}else {
            printf("Contraseña incorrecta.\n");
        }
    } else {
        printf("Usuario incorrecto.\n");
    }
}

void menuTrabajo(sqlite3 * db){////////////////////////////////////Esta
	int opcion;
	//TODO arreglar problema del db
	printf("Este es el menu de trabajo\n");
	fflush(stdout);
	printf("Este es el menu de trabajo");
	fflush(stdout);
	printf("1. Ver lista de clientes\n");
	fflush(stdout);
    printf("2. Ver reservas\n");
    fflush(stdout);
    printf("3. Borrar reservas\n");
    fflush(stdout);
    printf("4. Ver habitaciones\n");
    fflush(stdout);
    printf("5. Añadir habitaciones\n");
    fflush(stdout);
    printf("6. Borrar habitaciones\n");
    fflush(stdout);
    printf("7. Ver plazas de parking\n");
    fflush(stdout);
    printf("8. Cerrar\n");
    fflush(stdout);
    printf("Seleccione una opción: ");
    fflush(stdout);
    scanf("%d", &opcion);
    int numero;
    int id;
    switch(opcion) {
    	case 1:
    		imprimirClientes(db);
    		break;
        case 2:
        	imprimirReservas(db);
        	break;
        case 3:
        	imprimirReservas(db);
        	printf("Introduzca el numero de reserva que desea borrar: \n");
            scanf("%d", &id);
            borrarReserva(db,id);
        	break;
        case 4:
        	imprimirHabitaciones(db);
        	break;
        case 5:
        	menuAnadirHabitacion(db);
        	break;
        case 6:
        	imprimirHabitaciones(db);
        	printf("Introduzca el numero de habitacion que desea borrar: \n");
        	scanf("%d", &numero);
        	borrarHabitacion(db,numero);
        	break;
        case 7:
        	imprimirPlazasParking(db);
        	break;
        case 8:
        	printf("Vuelva pronto\n");
        	fflush(stdout);
            break;
        default:
        	printf("Opción no válida. Por favor, ingrese una opción válida.\n");
        	fflush(stdout);
        	menuTrabajo(db);
        	break;
   	}
}

void menuAnadirHabitacion(sqlite3 * db){//////////////////
	int numero;
	int piso;
	float precio;
	int capacidad;
	int opcion;
	enum tipoHabitacion tipo;

	printf("Este es el menu de añadir habitación\n");
	fflush(stdout);

	printf("Introduce el numero de la habitación: \n");
	fflush(stdout);
	scanf("%i", numero);

	printf("Introduce el piso de la habitación: \n");
	fflush(stdout);
	scanf("%i", piso);

	printf("Introduce el tipo de la habitación: \n");
	fflush(stdout);
	printf("1. Habitación Simple");
	fflush(stdout);
	printf("2. Habitación Doble");
	fflush(stdout);
	printf("3. Habitación Suite");
	fflush(stdout);
	scanf("%i", opcion);
	if (opcion == 1){
		tipo = simple;
	}else if(opcion == 2){
		tipo = doble;
	}else if(opcion == 3){
		tipo = suite;
	}else{
		printf("El tipo de habitacion introducido es incorrecto");
		fflush(stdout);
		tipo = simple;
	}

	printf("Introduce la capacidad de la habitación: \n");
	fflush(stdout);
	scanf("%i", capacidad);

	printf("Introduce el precio de la habitación: \n");
	fflush(stdout);
	scanf("%f", precio);

	Habitacion h ={numero, piso, tipo, capacidad, precio, false};
	imprimirHabitacion(h);
	menuTrabajo(db);


}

//void menuCompra(){
//	int opcion;
//
//	    printf("Bienvenido al menú del Cliente:\n");
//	    fflush(stdout);
//	    printf("1. Reservar habitación\n");
//	    fflush(stdout);
//	    printf("2. Reservar plaza de parking\n");
//	    fflush(stdout);
//	    printf("3. Ver estado de reserva\n");
//	    fflush(stdout);
//	    printf("4. Modificar reserva\n");
//	    fflush(stdout);
//	    printf("5. Cancelar reserva\n");
//	    fflush(stdout);
//	    printf("6. Volver al menú principal\n");
//	    fflush(stdout);
//	    printf("Seleccione una opción: ");
//	    fflush(stdout);
//	    scanf("%d", &opcion);
//
//	    switch(opcion) {
//	        case 1:
//	            reservarHabitacion();
//	            break;
//	        case 2:
//	            reservarParking();
//	            break;
//	        case 3:
//	            verEstadoReserva();
//	            break;
//	        case 4:
//	            modificarReserva();
//	            break;
//	        case 5:
//	            cancelarReserva();
//	            break;
//	        case 6:
//	            printf("Volviendo al menú principal...\n");
//	            fflush(stdout);
//	            mostrarMenuPrincipal();
//	            break;
//	        default:
//	            printf("Opción no válida. Por favor, ingrese una opción válida.\n");
//	            fflush(stdout);
//	            menuCompra();
//	            break;
//	    }
//
//}
//
////Parte del menu del trabajador///////////////
//void listadoClientes(){
//	//Por inplementar, será una lista con informacion de los clientes y la habitacion y parking que tienen
//}
//
//
//void menuHabitaciones() {
//    int opcion;
//
//    printf("Menú de Habitaciones:\n");
//    fflush(stdout);
//    printf("1. Ver habitaciones reservadas\n");
//    fflush(stdout);
//    printf("2. Ver habitaciones disponibles\n");
//    fflush(stdout);
//    printf("3. Ver habitaciones ocupadas\n");
//    fflush(stdout);
//    printf("4. Ver estado de limpieza de habitaciones\n");
//    fflush(stdout);
//    printf("5. Editar información de habitaciones\n");
//    fflush(stdout);
//    printf("6. Volver al menú de trabajo\n");
//    fflush(stdout);
//    printf("Seleccione una opción: ");
//    fflush(stdout);
//    scanf("%d", &opcion);
//
//    switch(opcion) {
//        case 1:
//            verHabitacionesReservadas();
//            break;
//        case 2:
//            verHabitacionesDisponibles();
//            break;
//        case 3:
//            verHabitacionesOcupadas();
//            break;
//        case 4:
//            verEstadoLimpiezaHabitaciones();
//            break;
//        case 5:
//            menuEditarInformacionHabitaciones();
//            break;
//        case 6:
//            printf("Volviendo al menú de trabajo...\n");
//            fflush(stdout);
//            menuTrabajo();
//            break;
//        default:
//            printf("Opción no válida. Por favor, ingrese una opción válida.\n");
//            fflush(stdout);
//            menuHabitaciones();
//            break;
//    }
//}
//
//void menuPlazaParking() {
//    int opcion;
//
//    printf("Menú de Plazas de Parking:\n");
//    fflush(stdout);
//    printf("1. Ver Plazas\n");
//    fflush(stdout);
//    printf("2. Editar Información de Plazas de Parking\n");
//    fflush(stdout);
//    printf("3. Volver al Menú de Trabajo\n");
//    fflush(stdout);
//    printf("Seleccione una opción: ");
//    fflush(stdout);
//    scanf("%d", &opcion);
//
//    switch(opcion) {
//        case 1:
//            verPlazasParking();
//            break;
//        case 2:
//            editarInformacionPlazasParking();
//            break;
//        case 3:
//            printf("Volviendo al Menú de Trabajo...\n");
//            menuTrabajo();
//            fflush(stdout);
//            break;
//        default:
//            printf("Opción no válida. Por favor, ingrese una opción válida.\n");
//            fflush(stdout);
//            menuPlazaParking();
//            break;
//    }
//}
//
//
////Parte del menu de compra del cliente///////////////
//void reservarHabitacion(){
//	//Por inplementar, funcion que reserva una habitacion dado su codigo y algun campo más
//}
//void reservarParking(){
//	//Por inplementar, funcion que reserva unaplaza de parking dado su codigo y algun campo más
//}
//void verEstadoReserva(){
//	//Por inplementar, devolverá la info de lo que se ha reservado, si lo hay
//}
//void modificarReserva(){
//	//Por inplementar, dará opción cambiar el dia o la duracion de la reserva
//}
//void cancelarReserva(){
//	//Por inplementar, dará opcion a cancelar una reserva
//}
//
//
////Parte del menu de las habitaciones////////////////
//void verHabitacionesReservadas() {
//    //Por inplementar, para mostrar las habitaciones reservadas
//}
//
//void verHabitacionesDisponibles() {
//    //Por inplementar, para mostrar las habitaciones disponibles
//}
//
//void verHabitacionesOcupadas() {
//    //Por inplementar, para mostrar las habitaciones ocupadas
//}
//
//void verEstadoLimpiezaHabitaciones() {
//    //Por inplementar, para mostrar el estado de limpieza de las habitaciones
//}
//
//void menuEditarInformacionHabitaciones() {
//    //Por inplementar, para editar la información de las habitaciones
//}
//
//
////Parte del menu del parking////////////
//void verPlazasParking() {
//    //Por inplementar, para mostrar las plazas de parking
//}
//
//void editarInformacionPlazasParking() {
//    //Por inplementar, para editar la información de las plazas de parking
//}



void main(){
//	mostrarMenuPrincipal();
	sqlite3* db;
	db = conectarDB();
}

//void menuHabitaciones() {
//    int opcion;
//
//    printf("Menú de Habitaciones:\n");
//    fflush(stdout);
//    printf("1. Ver habitaciones reservadas\n");
//    fflush(stdout);
//    printf("2. Ver habitaciones disponibles\n");
//    fflush(stdout);
//    printf("3. Ver habitaciones ocupadas\n");
//    fflush(stdout);
//    printf("4. Ver estado de limpieza de habitaciones\n");
//    fflush(stdout);
//    printf("5. Editar información de habitaciones\n");
//    fflush(stdout);
//    printf("6. Volver al menú de trabajo\n");
//    fflush(stdout);
//    printf("Seleccione una opción: ");
//    fflush(stdout);
//    scanf("%d", &opcion);
//
//    switch(opcion) {
//        case 1:
//            verHabitacionesReservadas();
//            break;
//        case 2:
//            verHabitacionesDisponibles();
//            break;
//        case 3:
//            verHabitacionesOcupadas();
//            break;
//        case 4:
//            verEstadoLimpiezaHabitaciones();
//            break;
//        case 5:
//            menuEditarInformacionHabitaciones();
//            break;
//        case 6:
//            printf("Volviendo al menú de trabajo...\n");
//            fflush(stdout);
//            menuTrabajo(db);
//            break;
//        default:
//            printf("Opción no válida. Por favor, ingrese una opción válida.\n");
//            fflush(stdout);
//            menuHabitaciones();
//            break;
//    }
//}
//
//void menuPlazaParking() {
//    int opcion;
//
//    printf("Menú de Plazas de Parking:\n");
//    fflush(stdout);
//    printf("1. Ver Plazas\n");
//    fflush(stdout);
//    printf("2. Editar Información de Plazas de Parking\n");
//    fflush(stdout);
//    printf("3. Volver al Menú de Trabajo\n");
//    fflush(stdout);
//    printf("Seleccione una opción: ");
//    fflush(stdout);
//    scanf("%d", &opcion);
//
//    switch(opcion) {
//        case 1:
//            verPlazasParking();
//            break;
//        case 2:
//            editarInformacionPlazasParking();
//            break;
//        case 3:
//            printf("Volviendo al Menú de Trabajo...\n");
//            menuTrabajo(db);
//            fflush(stdout);
//            break;
//        default:
//            printf("Opción no válida. Por favor, ingrese una opción válida.\n");
//            fflush(stdout);
//            menuPlazaParking();
//            break;
//    }
//}
//
//
////Parte del menu de compra del cliente///////////////
//void reservarHabitacion(){
//	//Por inplementar, funcion que reserva una habitacion dado su codigo y algun campo más
//}
//void reservarParking(){
//	//Por inplementar, funcion que reserva unaplaza de parking dado su codigo y algun campo más
//}
//void verEstadoReserva(){
//	//Por inplementar, devolverá la info de lo que se ha reservado, si lo hay
//}
//void modificarReserva(){
//	//Por inplementar, dará opción cambiar el dia o la duracion de la reserva
//}
//void cancelarReserva(){
//	//Por inplementar, dará opcion a cancelar una reserva
//}
//
//
////Parte del menu de las habitaciones////////////////
//void verHabitacionesReservadas() {
//    //Por inplementar, para mostrar las habitaciones reservadas
//}
//
//void verHabitacionesDisponibles() {
//    //Por inplementar, para mostrar las habitaciones disponibles
//}
//
//void verHabitacionesOcupadas() {
//    //Por inplementar, para mostrar las habitaciones ocupadas
//}
//
//void verEstadoLimpiezaHabitaciones() {
//    //Por inplementar, para mostrar el estado de limpieza de las habitaciones
//}
//
//void menuEditarInformacionHabitaciones() {
//    //Por inplementar, para editar la información de las habitaciones
//}
//
//
////Parte del menu del parking////////////
//void verPlazasParking() {
//    //Por inplementar, para mostrar las plazas de parking
//}
//
//void editarInformacionPlazasParking() {
//    //Por inplementar, para editar la información de las plazas de parking
//}
