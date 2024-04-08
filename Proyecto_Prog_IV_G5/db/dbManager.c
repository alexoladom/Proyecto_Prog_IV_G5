#include <stdio.h>
#include <string.h>
#include "stdbool.h"
#include "sqlite3.h"
#include "../domain/cliente.h"
#include "../domain/reserva.h"
#include "../domain/habitacion.h"
#include "../domain/plazaParking.h"

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
}

void imprimirPlazasParking(sqlite3*db){

	sqlite3_stmt *stmt;

				char sql[] = "select * from plazaparking ";

				int result3 = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
				if (result3 != SQLITE_OK) {
					printf("Error preparing statement (SELECT)\n");
					printf("%s\n", sqlite3_errmsg(db));
				}

				int numero;
				char zona;
				bool ocupado;


				printf("\n");
				printf("\n");
				printf("Showing plazas de parking:\n");
				int result;
				do {

					result = sqlite3_step(stmt) ;
					if (result == SQLITE_ROW) {
						numero = sqlite3_column_int(stmt, 0);
						zona = *sqlite3_column_text(stmt, 1);
						ocupado = sqlite3_column_int(stmt, 2);

						PlazaParking p = crearPlazaParking(numero,zona,ocupado);
						imprimirPlazaParking(p);
					}
				} while (result == SQLITE_ROW);

				printf("\n");
				printf("\n");

				result = sqlite3_finalize(stmt);
				if (result != SQLITE_OK) {
					printf("Error finalizing statement (SELECT)\n");
					printf("%s\n", sqlite3_errmsg(db));
				}

};



void anadirCliente(Cliente c, sqlite3*db){

	sqlite3_stmt *stmt1;

			char sql1[] = "insert into cliente (dni,nombre,edad,correo) values (?,?,?,?) ";

			int result = sqlite3_prepare_v2(db, sql1, -1, &stmt1, NULL) ;
			sqlite3_bind_int(stmt1, 1, c.dni);
			sqlite3_bind_text(stmt1, 2, c.nombre, strlen(c.nombre),SQLITE_STATIC);
			sqlite3_bind_int(stmt1, 3, c.edad);
			sqlite3_bind_text(stmt1, 4, c.correo, strlen(c.correo),SQLITE_STATIC);


			if (result != SQLITE_OK) {
				printf("Error preparing statement (Insert)\n");
				printf("%s\n", sqlite3_errmsg(db));
			}


			result = sqlite3_step(stmt1);
				if (result != SQLITE_DONE) {
					printf("Error inserting new data into cliente table\n");
				}

				result = sqlite3_finalize(stmt1);
				if (result != SQLITE_OK) {
					printf("Error finalizing statement (INSERT)\n");
					printf("%s\n", sqlite3_errmsg(db));
				}

				printf("Cliente añadido con éxito");
}

void anadirReserva(Reserva r, sqlite3* db){

	sqlite3_stmt *stmt1;

				char sql1[] = "insert into reserva (fecha,dniCliente,numeroHabitacion,numeroPlazaParking) values (?,?,?,?) ";

				int result = sqlite3_prepare_v2(db, sql1, -1, &stmt1, NULL) ;
				sqlite3_bind_text(stmt1, 1, r.fecha, strlen(r.fecha),SQLITE_STATIC);
				sqlite3_bind_int(stmt1, 2, r.dniCliente);
				sqlite3_bind_int(stmt1, 3, r.numeroHabitacion);
				sqlite3_bind_int(stmt1, 4, r.numeroPlazaParking);



				if (result != SQLITE_OK) {
					printf("Error preparing statement (Insert)\n");
					printf("%s\n", sqlite3_errmsg(db));
				}


				result = sqlite3_step(stmt1);
					if (result != SQLITE_DONE) {
						printf("Error inserting new data into reserva table\n");
					}

					result = sqlite3_finalize(stmt1);
					if (result != SQLITE_OK) {
						printf("Error finalizing statement (INSERT)\n");
						printf("%s\n", sqlite3_errmsg(db));
					}

					printf("Reserva añadida con éxito\n");


}

void anadirHabitacion(sqlite3*db,Habitacion h){
	sqlite3_stmt *stmt1;

					char sql1[] = "insert into habitacion (numero,piso,tipo,capacidad,precio,ocupado) values (?,?,?,?,?,?) ";

					int result = sqlite3_prepare_v2(db, sql1, -1, &stmt1, NULL) ;
					char tipos[][10]= {"simple","doble","suite"};
					sqlite3_bind_int(stmt1, 1, h.numero);
					sqlite3_bind_int(stmt1, 2,h.piso);
					sqlite3_bind_text(stmt1, 3, tipos[h.tipo], strlen(tipos[h.tipo]),SQLITE_STATIC);
					sqlite3_bind_int(stmt1, 4,h.capacidad);
					sqlite3_bind_int(stmt1, 5,h.precio);
					sqlite3_bind_int(stmt1, 6,h.ocupado);


					if (result != SQLITE_OK) {
						printf("Error preparing statement (Insert)\n");
						printf("%s\n", sqlite3_errmsg(db));
					}


					result = sqlite3_step(stmt1);
						if (result != SQLITE_DONE) {
							printf("Error inserting new data into habitacion table\n");
						}

						result = sqlite3_finalize(stmt1);
						if (result != SQLITE_OK) {
							printf("Error finalizing statement (INSERT)\n");
							printf("%s\n", sqlite3_errmsg(db));
						}

						printf("Habitacion añadida con éxito\n");


}

void borrarReserva(sqlite3*db,int numero){

	sqlite3_stmt *stmt1;

		char sql1[] = "delete from reserva where id = ?";

		int result = sqlite3_prepare_v2(db, sql1, -1, &stmt1, NULL) ;
		sqlite3_bind_int(stmt1, 1,numero);
		if (result != SQLITE_OK) {
			printf("Error preparing statement (Insert)\n");
			printf("%s\n", sqlite3_errmsg(db));
		}


		result = sqlite3_step(stmt1);
			if (result != SQLITE_DONE) {
				printf("Error borrando reserva %i table\n", numero);
			}

			result = sqlite3_finalize(stmt1);
			if (result != SQLITE_OK) {
				printf("Error finalizing statement (INSERT)\n");
				printf("%s\n", sqlite3_errmsg(db));
			}

			printf("Reserva %i borrada con exito\n", numero);

}

void borrarHabitacion(sqlite3*db,int numero){
	sqlite3_stmt *stmt1;

		char sql1[] = "delete from habitacion where numero = ?";

		int result = sqlite3_prepare_v2(db, sql1, -1, &stmt1, NULL) ;
		sqlite3_bind_int(stmt1, 1,numero);
		if (result != SQLITE_OK) {
			printf("Error preparing statement (Insert)\n");
			printf("%s\n", sqlite3_errmsg(db));
		}


		result = sqlite3_step(stmt1);
			if (result != SQLITE_DONE) {
				printf("Error borrando habitacion %i table\n", numero);
			}

			result = sqlite3_finalize(stmt1);
			if (result != SQLITE_OK) {
				printf("Error finalizing statement (INSERT)\n");
				printf("%s\n", sqlite3_errmsg(db));
			}

			printf("Habitacion %i borrada con éxito\n", numero);


}




