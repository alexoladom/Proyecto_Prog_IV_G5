#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionesCarga.h"


void cargarHabitacionesDesdeArchivo(const char* nombreArchivo, Habitacion habitaciones[], int* cantidad) {
    FILE* archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo %s\n", nombreArchivo);
        return;
    }

    *cantidad = 0;
    char linea[100]; // Suponiendo que cada línea del archivo tiene como máximo 100 caracteres
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        char* token = strtok(linea, ";");
        habitaciones[*cantidad].numero = atoi(token);

        token = strtok(NULL, ";");
        habitaciones[*cantidad].piso = atoi(token);

        token = strtok(NULL, ";");
        habitaciones[*cantidad].capacidad = atoi(token);

        token = strtok(NULL, ";");
        habitaciones[*cantidad].ocupado = strcmp(token, "True") == 0 ? true : false;

        (*cantidad)++;
    }

    fclose(archivo);
}


void cargarPlazasParkingDesdeArchivo(const char* nombreArchivo, PlazaParking plazas[], int* cantidad) {
    FILE* archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo %s\n", nombreArchivo);
        return;
    }

    *cantidad = 0;
    char linea[100]; // Suponiendo que cada línea del archivo tiene como máximo 100 caracteres
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        char* token = strtok(linea, ";");
        plazas[*cantidad].numero = atoi(token);

        token = strtok(NULL, ";");
        plazas[*cantidad].zona = *token;

        token = strtok(NULL, ";");
        plazas[*cantidad].ocupado = strcmp(token, "True") == 0 ? true : false;

        (*cantidad)++;
    }

    fclose(archivo);
}

void cargarClientesDesdeArchivo(const char* nombreArchivo, Cliente clientes[], int* cantidad) {
    FILE* archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo %s\n", nombreArchivo);
        return;
    }

    *cantidad = 0;
    char linea[100]; // Suponiendo que cada línea del archivo tiene como máximo 100 caracteres
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        char* token = strtok(linea, ";");
        strcpy(clientes[*cantidad].nombre, token);

        token = strtok(NULL, ";");
        clientes[*cantidad].dni = atoi(token);

        token = strtok(NULL, ";");
        clientes[*cantidad].edad = atoi(token);

        token = strtok(NULL, ";");
        strcpy(clientes[*cantidad].correo, token);

        (*cantidad)++;
    }

    fclose(archivo);
}

void cargarAdministradoresDesdeArchivo(const char* nombreArchivo, Administrador administradores[], int* cantidad) {
    FILE* archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo %s\n", nombreArchivo);
        return;
    }

    *cantidad = 0;
    char linea[100]; // Suponiendo que cada línea del archivo tiene como máximo 100 caracteres
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        char* token = strtok(linea, ";");
        strcpy(administradores[*cantidad].nombre, token);

        token = strtok(NULL, ";");
        administradores[*cantidad].dni = atoi(token);

        token = strtok(NULL, ";");
        administradores[*cantidad].edad = atoi(token);

        token = strtok(NULL, ";");
        strcpy(administradores[*cantidad].correo, token);

        token = strtok(NULL, ";");
    //    administradores[*cantidad].funcion = convertirStringAFuncion(token);

        (*cantidad)++;
    }

    fclose(archivo);
}

void cargarReservasDesdeArchivo(const char* nombreArchivo, Reserva reservas[], int* cantidad) {
    FILE* archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo %s\n", nombreArchivo);
        return;
    }

    *cantidad = 0;
    char linea[100]; // Suponiendo que cada línea del archivo tiene como máximo 100 caracteres
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        char* token = strtok(linea, ";");
        reservas[*cantidad].id = atoi(token);

        token = strtok(NULL, ";");
        strcpy(reservas[*cantidad].fecha, token);

        token = strtok(NULL, ";");
        reservas[*cantidad].dniCliente = atoi(token);

        token = strtok(NULL, ";");
        reservas[*cantidad].numeroHabitacion = atoi(token);

        token = strtok(NULL, ";");
        reservas[*cantidad].numeroPlazaParking = atoi(token);

        (*cantidad)++;
    }

    fclose(archivo);
}
