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

void iniciarSesionCliente() {
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
            menuCompra(); // Saltar al menú de compra si la contraseña es correcta
        } else {
            printf("Contraseña incorrecta.\n");
        }
    } else {
        printf("Usuario incorrecto.\n");
    }
}

void registrarseCliente() {
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

void iniciarSesionAdmin() {
	char nomUser[50];
	int contra;

    printf("Iniciando sesión como administrador...\n");
    fflush(stdout);
    printf("Introduce tu usuario de Trabajador: ");
    fflush(stdout);
    scanf("%s", &nomUser);
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
	printf("Este es el menu de trabajo");
}

void menuCompra(){
	printf("Este es el menu del cliente una vez accede");
}
