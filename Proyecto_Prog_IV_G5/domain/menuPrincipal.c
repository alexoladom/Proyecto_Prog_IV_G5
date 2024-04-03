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
    printf("Hola, cliente.\n");
    fflush(stdout);
}

void menuAdministrador() {
    printf("Hola, administrador.\n");
    fflush(stdout);
}


