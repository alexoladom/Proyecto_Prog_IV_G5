#include <stdio.h>
#include <stdlib.h>
#include "MenuPrincipal.h"



void mostrarMenuPrincipal() {
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
            menuCliente();
            break;
        case 2:
        	printf("Introduce el codigo de acceso admin: ");
        	fflush(stdout);
        	scanf("%d", &numerin);
        	if(numerin == 123){
        		menuAdministrador();
        	}else{
        		printf("El numero de acceso no es correcto.");
        		fflush(stdout);
        		mostrarMenuPrincipal();
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
            mostrarMenuPrincipal();
            break;
    }
}

void menuCliente() {
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
            iniciarSesionCliente();
            break;
        case 2:
            registrarseCliente();
            break;
        case 3:
            mostrarMenuPrincipal();
            break;
        default:
            printf("Opción no válida. Por favor, ingrese una opción válida.\n");
            fflush(stdout);
            menuCliente();
            break;
    }
}

void iniciarSesionCliente() {//Funcion semifuncional hasta que haya bases de datos o ficheros
	char nomUser[50];
	int contra;

    printf("Iniciando sesión como cliente...\n");
    fflush(stdout);
    printf("Introduce tu usuario: ");
    fflush(stdout);
    scanf("%s", nomUser);

    if (strcmp(nomUser, "Jorge") == 0) {
        printf("Introduce tu contraseña: ");
        fflush(stdout);
        scanf("%d", &contra);
        if (contra == 123) {
            menuCompra();
        } else {
            printf("Contraseña incorrecta.\n");
        }
    } else {
        printf("Usuario incorrecto.\n");
    }
}

void registrarseCliente() {//Funcion semifuncional hasta que haya bases de datos o ficheros
	char nomUser[50];
    int contra;

    printf("Registrando nuevo cliente...\n");
    fflush(stdout);
    printf("Introduce tu nuevo usuario: ");
    fflush(stdout);
    scanf("%s", nomUser);
    printf("Introduce tu contraseña: ");
    fflush(stdout);
    scanf("%d", &contra);

    printf("Registro exitoso.\n");

    iniciarSesionCliente();
}

void menuAdministrador() {
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
	            iniciarSesionAdmin();
	            break;
	        case 2:
	            mostrarMenuPrincipal();
	            break;
	        default:
	            printf("Opción no válida. Por favor, ingrese una opción válida.\n");
	            fflush(stdout);
	            menuAdministrador();
	            break;
	    }
}

void iniciarSesionAdmin() {//Funcion semifuncional hasta que haya bases de datos o ficheros
	char nomUser[50];
	int contra;

    printf("Iniciando sesión como administrador...\n");
    fflush(stdout);
    printf("Introduce tu usuario de Trabajador: ");
    fflush(stdout);
    scanf("%c", &nomUser);

    if(strcmp(nomUser, "Jorge") == 0){
    	printf("Introduce tu contraseña: ");
    	fflush(stdout);
    	scanf("%d", &contra);
    	if(contra == 123){
    		menuTrabajo();
    	}else {
            printf("Contraseña incorrecta.\n");
        }
    } else {
        printf("Usuario incorrecto.\n");
    }
}

void menuTrabajo(){
	int opcion;

	printf("Este es el menu de trabajo");
	fflush(stdout);
	printf("1. Ver lista de clientes\n");
	fflush(stdout);
    printf("2. Gestionar reservas de habitaciones\n");
    fflush(stdout);
    printf("3. Gestionar reservas de plazas de parking\n");
    fflush(stdout);
    printf("4. Cerrar\n");
    fflush(stdout);
    printf("Seleccione una opción: ");
    fflush(stdout);
    scanf("%d", &opcion);

    switch(opcion) {
    	case 1:
    		listadoClientes();
    		break;
        case 2:
        	menuHabitaciones();
        	break;
        case 3:
        	menuPlazaParking();
        	break;
        case 4:
        	printf("Vuelva pronto\n");
        	fflush(stdout);
            break;
        default:
        	printf("Opción no válida. Por favor, ingrese una opción válida.\n");
        	fflush(stdout);
        	menuTrabajo();
        	break;
   	}
}

void menuCompra(){
	int opcion;

	    printf("Bienvenido al menú del Cliente:\n");
	    fflush(stdout);
	    printf("1. Reservar habitación\n");
	    fflush(stdout);
	    printf("2. Reservar plaza de parking\n");
	    fflush(stdout);
	    printf("3. Ver estado de reserva\n");
	    fflush(stdout);
	    printf("4. Modificar reserva\n");
	    fflush(stdout);
	    printf("5. Cancelar reserva\n");
	    fflush(stdout);
	    printf("6. Volver al menú principal\n");
	    fflush(stdout);
	    printf("Seleccione una opción: ");
	    fflush(stdout);
	    scanf("%d", &opcion);

	    switch(opcion) {
	        case 1:
	            reservarHabitacion();
	            break;
	        case 2:
	            reservarParking();
	            break;
	        case 3:
	            verEstadoReserva();
	            break;
	        case 4:
	            modificarReserva();
	            break;
	        case 5:
	            cancelarReserva();
	            break;
	        case 6:
	            printf("Volviendo al menú principal...\n");
	            fflush(stdout);
	            mostrarMenuPrincipal();
	            break;
	        default:
	            printf("Opción no válida. Por favor, ingrese una opción válida.\n");
	            fflush(stdout);
	            menuCompra();
	            break;
	    }

}

//Parte del menu del trabajador///////////////
void listadoClientes(){
	//Por inplementar, será una lista con informacion de los clientes y la habitacion y parking que tienen
}


void menuHabitaciones() {
    int opcion;

    printf("Menú de Habitaciones:\n");
    fflush(stdout);
    printf("1. Ver habitaciones reservadas\n");
    fflush(stdout);
    printf("2. Ver habitaciones disponibles\n");
    fflush(stdout);
    printf("3. Ver habitaciones ocupadas\n");
    fflush(stdout);
    printf("4. Ver estado de limpieza de habitaciones\n");
    fflush(stdout);
    printf("5. Editar información de habitaciones\n");
    fflush(stdout);
    printf("6. Volver al menú de trabajo\n");
    fflush(stdout);
    printf("Seleccione una opción: ");
    fflush(stdout);
    scanf("%d", &opcion);

    switch(opcion) {
        case 1:
            verHabitacionesReservadas();
            break;
        case 2:
            verHabitacionesDisponibles();
            break;
        case 3:
            verHabitacionesOcupadas();
            break;
        case 4:
            verEstadoLimpiezaHabitaciones();
            break;
        case 5:
            menuEditarInformacionHabitaciones();
            break;
        case 6:
            printf("Volviendo al menú de trabajo...\n");
            fflush(stdout);
            menuTrabajo();
            break;
        default:
            printf("Opción no válida. Por favor, ingrese una opción válida.\n");
            fflush(stdout);
            menuHabitaciones();
            break;
    }
}

void menuPlazaParking() {
    int opcion;

    printf("Menú de Plazas de Parking:\n");
    fflush(stdout);
    printf("1. Ver Plazas\n");
    fflush(stdout);
    printf("2. Editar Información de Plazas de Parking\n");
    fflush(stdout);
    printf("3. Volver al Menú de Trabajo\n");
    fflush(stdout);
    printf("Seleccione una opción: ");
    fflush(stdout);
    scanf("%d", &opcion);

    switch(opcion) {
        case 1:
            verPlazasParking();
            break;
        case 2:
            editarInformacionPlazasParking();
            break;
        case 3:
            printf("Volviendo al Menú de Trabajo...\n");
            menuTrabajo();
            fflush(stdout);
            break;
        default:
            printf("Opción no válida. Por favor, ingrese una opción válida.\n");
            fflush(stdout);
            menuPlazaParking();
            break;
    }
}

//Parte del menu de compra del cliente///////////////
void reservarHabitacion(){
	//Por inplementar, funcion que reserva una habitacion dado su codigo y algun campo más
}
void reservarParking(){
	//Por inplementar, funcion que reserva unaplaza de parking dado su codigo y algun campo más
}
void verEstadoReserva(){
	//Por inplementar, devolverá la info de lo que se ha reservado, si lo hay
}
void modificarReserva(){
	//Por inplementar, dará opción cambiar el dia o la duracion de la reserva
}
void cancelarReserva(){
	//Por inplementar, dará opcion a cancelar una reserva
}


//Parte del menu de las habitaciones////////////////
void verHabitacionesReservadas() {
    //Por inplementar, para mostrar las habitaciones reservadas
}

void verHabitacionesDisponibles() {
    //Por inplementar, para mostrar las habitaciones disponibles
}

void verHabitacionesOcupadas() {
    //Por inplementar, para mostrar las habitaciones ocupadas
}

void verEstadoLimpiezaHabitaciones() {
    //Por inplementar, para mostrar el estado de limpieza de las habitaciones
}

void menuEditarInformacionHabitaciones() {
    //Por inplementar, para editar la información de las habitaciones
}


//Parte del menu del parking////////////
void verPlazasParking() {
    //Por inplementar, para mostrar las plazas de parking
}

void editarInformacionPlazasParking() {
    //Por inplementar, para editar la información de las plazas de parking
}


