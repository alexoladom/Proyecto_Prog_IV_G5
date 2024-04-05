#include <stdio.h>
#include "sqlite3.h"
#include <string.h>
#include "stdbool.h"
#include "../domain/cliente.h"
#include "../domain/reserva.h"
#include "../domain/habitacion.h"


sqlite3* conectarDB(){
	sqlite3 * db;
	int result1 = sqlite3_open("db/dbProgIV.sqlite", &db);
	if (result1 != SQLITE_OK) {
		printf("Error opening database\n");
	}else{
		printf("Database opened\n") ;
	}
	return db;
}


void imprimirClientes(sqlite3*db){

	sqlite3_stmt *stmt;

	char sql[] = "select * from cliente";

	int result3 = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result3 != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	printf("SQL query prepared (SELECT)\n");

	int dni;
	char nombre[20];
	int edad;
	char correo[30];


	printf("\n");
	printf("\n");
	printf("Showing clientes:\n");
	int result;
	do {

		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			dni = sqlite3_column_int(stmt, 0);
			strcpy(nombre, (char *) sqlite3_column_text(stmt, 1));
			edad = sqlite3_column_int(stmt, 2);
			strcpy(correo,(char*) sqlite3_column_text(stmt, 3));
			Cliente c = crearCliente(dni,nombre,edad,correo);
			imprimirCliente(c);
		}
	} while (result == SQLITE_ROW);

	printf("\n");
	printf("\n");

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	printf("Prepared statement finalized (SELECT)\n");
}




void imprimirReservas(sqlite3*db){

	sqlite3_stmt *stmt;

		char sql[] = "select * from reserva ";

		int result3 = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
		if (result3 != SQLITE_OK) {
			printf("Error preparing statement (SELECT)\n");
			printf("%s\n", sqlite3_errmsg(db));
		}

		printf("SQL query prepared (SELECT)\n");

		int id;
		char fecha[11];
		int dniCliente;
		int numeroHabitacion;
		int numeroPlazaParking;


		printf("\n");
		printf("\n");
		printf("Showing reservas:\n");
		int result;
		do {

			result = sqlite3_step(stmt) ;
			if (result == SQLITE_ROW) {
				id = sqlite3_column_int(stmt, 0);
				strcpy(fecha, (char *) sqlite3_column_text(stmt, 1));
				dniCliente = sqlite3_column_int(stmt, 2);
				numeroHabitacion = sqlite3_column_int(stmt, 3);
				numeroPlazaParking = sqlite3_column_int(stmt, 4);

				Reserva r =crearReserva(id,fecha,dniCliente,numeroHabitacion,numeroPlazaParking);
				imprimirReserva(r);
			}
		} while (result == SQLITE_ROW);

		printf("\n");
		printf("\n");

		result = sqlite3_finalize(stmt);
		if (result != SQLITE_OK) {
			printf("Error finalizing statement (SELECT)\n");
			printf("%s\n", sqlite3_errmsg(db));
		}

		printf("Prepared statement finalized (SELECT)\n");

}


void imprimirHabitaciones(sqlite3 * db){
	sqlite3_stmt *stmt;

			char sql[] = "select * from habitacion ";

			int result3 = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
			if (result3 != SQLITE_OK) {
				printf("Error preparing statement (SELECT)\n");
				printf("%s\n", sqlite3_errmsg(db));
			}

			printf("SQL query prepared (SELECT)\n");

			int numero;
			int piso;
			char tipoString[10];
			enum tipoHabitacion tipo;
			int capacidad;
			int precio;
			bool ocupado;


			printf("\n");
			printf("\n");
			printf("Showing habitaciones:\n");
			int result;
			do {

				result = sqlite3_step(stmt) ;
				if (result == SQLITE_ROW) {
					numero = sqlite3_column_int(stmt, 0);
					piso = sqlite3_column_int(stmt, 1);
					strcpy(tipoString, (char *) sqlite3_column_text(stmt, 2));
					if(tipoString[1]=='i'){
						tipo=simple;
					}else if(tipoString[1]=='o'){
						tipo=doble;
					}else{
						tipo=suite;
					}
					capacidad = sqlite3_column_int(stmt, 3);
					precio = sqlite3_column_int(stmt, 4);
					ocupado = sqlite3_column_int(stmt, 5);

					Habitacion h = crearHabitacion(numero,piso,tipo,capacidad,precio,ocupado);
					imprimirHabitacion(h);
				}
			} while (result == SQLITE_ROW);

			printf("\n");
			printf("\n");

			result = sqlite3_finalize(stmt);
			if (result != SQLITE_OK) {
				printf("Error finalizing statement (SELECT)\n");
				printf("%s\n", sqlite3_errmsg(db));
			}

			printf("Prepared statement finalized (SELECT)\n");

}


int main(){

	sqlite3 * db = conectarDB();

	imprimirClientes(db);
	imprimirReservas(db);
	imprimirHabitaciones(db);
}
