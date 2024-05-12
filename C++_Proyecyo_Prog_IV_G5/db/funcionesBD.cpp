#include "funcionesBD.h"


#define OK 1
#define NOT_OK 0




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

/*
 *
 * Funciones Cliente
 *
 *
 */
Cliente* getListaClientes(sqlite3*db){


	sqlite3_stmt *stmt;

		char sql[] = "select * from cliente";

		int result3 = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
		if (result3 != SQLITE_OK) {
			printf("Error preparing statement (SELECT)\n");
			printf("%s\n", sqlite3_errmsg(db));
		}

		int contador=0;
		int result;
		do {

			result = sqlite3_step(stmt);
			if (result == SQLITE_ROW) {
				contador++;
			}
		} while (result == SQLITE_ROW);

		result = sqlite3_finalize(stmt);
		if (result != SQLITE_OK) {
			printf("Error finalizing statement (SELECT)\n");
			printf("%s\n", sqlite3_errmsg(db));
		}

		Cliente::numClientes=contador;
		/////////////////////////////////////////////////7

		sqlite3_stmt *stmt2;

		Cliente *array = new Cliente[contador];

		char sql2[] = "select * from cliente";

		result3 = sqlite3_prepare_v2(db, sql2, strlen(sql2) + 1, &stmt2, NULL);
		if (result3 != SQLITE_OK) {
			printf("Error preparing statement (SELECT)\n");
			printf("%s\n", sqlite3_errmsg(db));
		}


		int dni;
		char nombre[20];
		int edad;
		char correo[30];
		int posicion=0;

		do {

			result = sqlite3_step(stmt2);
			if (result == SQLITE_ROW) {
				dni = sqlite3_column_int(stmt2, 0);
				strcpy(nombre, (char *) sqlite3_column_text(stmt2, 1));
				edad = sqlite3_column_int(stmt2, 2);
				strcpy(correo,(char*) sqlite3_column_text(stmt2, 3));
				Cliente c (dni,nombre,edad,correo);
				array[posicion]=c;
				posicion++;
			}
		} while (result == SQLITE_ROW);

		result = sqlite3_finalize(stmt2);
		if (result != SQLITE_OK) {
			printf("Error finalizing statement (SELECT)\n");
			printf("%s\n", sqlite3_errmsg(db));
		}
		return array;
}



int comprobarDni(sqlite3* db, int dni){
	sqlite3_stmt *stmt;

		char sql[] = "select dni from contraseñas";

		int result3 = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
		if (result3 != SQLITE_OK) {
			printf("Error preparing statement (SELECT)\n");
			printf("%s\n", sqlite3_errmsg(db));
			return NOT_OK;
		}
		int dni2;
		int result;
		do {
			result = sqlite3_step(stmt) ;
			if (result == SQLITE_ROW) {
				dni2 = sqlite3_column_int(stmt, 0);
				if (dni2==dni){
					return OK;
				}
			}
		} while (result == SQLITE_ROW);

		printf("\n");
		printf("\n");
		result = sqlite3_finalize(stmt);
		if (result != SQLITE_OK) {
			printf("Error finalizing statement (SELECT)\n");
			printf("%s\n", sqlite3_errmsg(db));
			return NOT_OK;
		}
		return NOT_OK;
}
int comprobarContra(sqlite3* db, int dni, char*contrasena){
	sqlite3_stmt *stmt;

			char sql[] = "select contra from contraseñas where dni=?";

			int result3 = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
			sqlite3_bind_int(stmt, 1, dni);

			if (result3 != SQLITE_OK) {
				printf("Error preparing statement (SELECT)\n");
				printf("%s\n", sqlite3_errmsg(db));
			}
			char contra[20];
			int result;
			result = sqlite3_step(stmt) ;
			if (result == SQLITE_ROW) {
				strcpy(contra,(char*)sqlite3_column_text(stmt, 0));
				if (strcmp(contra,contrasena)==0){
					return OK;
				}
			}
			printf("\n");
			printf("\n");
			result = sqlite3_finalize(stmt);
			if (result != SQLITE_OK) {
				printf("Error finalizing statement (SELECT)\n");
				printf("%s\n", sqlite3_errmsg(db));
			}
			return NOT_OK;
}

int anadirDniContra(sqlite3* db, int dni, char* contra){
	sqlite3_stmt *stmt1;

	char sql1[] = "insert into contraseñas (dni,contra) values (?,?) ";

	int result = sqlite3_prepare_v2(db, sql1, -1, &stmt1, NULL) ;
	sqlite3_bind_int(stmt1, 1, dni);
	sqlite3_bind_text(stmt1, 2, contra, strlen(contra),SQLITE_STATIC);



	if (result != SQLITE_OK) {
		printf("Error preparing statement (Insert)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return NOT_OK;
	}


	result = sqlite3_step(stmt1);
	if (result != SQLITE_DONE) {
		printf("Error inserting new data into cliente table\n");
		return NOT_OK;
	}

	result = sqlite3_finalize(stmt1);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return NOT_OK;
	}
	return OK;
}

int anadirCliente(Cliente &c, sqlite3*db){

	sqlite3_stmt *stmt1;

	char sql1[] = "insert into cliente (dni,nombre,edad,correo) values (?,?,?,?) ";

	int result = sqlite3_prepare_v2(db, sql1, -1, &stmt1, NULL) ;
	sqlite3_bind_int(stmt1, 1, c.getDni());
	sqlite3_bind_text(stmt1, 2, c.getNombre().c_str(), strlen(c.getNombre().c_str()),SQLITE_STATIC);
	sqlite3_bind_int(stmt1, 3, c.getEdad());
	sqlite3_bind_text(stmt1, 4,c.getCorreo().c_str(), strlen(c.getCorreo().c_str()),SQLITE_STATIC);


	if (result != SQLITE_OK) {
		printf("Error preparing statement (Insert)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return NOT_OK;
	}


	result = sqlite3_step(stmt1);
		if (result != SQLITE_DONE) {
			printf("Error inserting new data into cliente table\n");
			return NOT_OK;
		}

		result = sqlite3_finalize(stmt1);
		if (result != SQLITE_OK) {
			printf("Error finalizing statement (INSERT)\n");
			printf("%s\n", sqlite3_errmsg(db));
			return NOT_OK;
		}
		int num =Cliente::numClientes;
		num++;
		Cliente::numClientes=num;
		return OK;
}



/*
 *
 * Funciones para reservas
 *
 *
 *
 */



Reserva* getListaReservas(sqlite3*db){

	sqlite3_stmt *stmt;

		char sql[] = "select * from reserva ";

		int result3 = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
		if (result3 != SQLITE_OK) {
			printf("Error preparing statement (SELECT)\n");
			printf("%s\n", sqlite3_errmsg(db));
		}

		int contador=0;

		int result;
		do {

			result = sqlite3_step(stmt) ;
			if (result == SQLITE_ROW) {
				contador++;
			}
		} while (result == SQLITE_ROW);

		result = sqlite3_finalize(stmt);
		if (result != SQLITE_OK) {
			printf("Error finalizing statement (SELECT)\n");
			printf("%s\n", sqlite3_errmsg(db));
		}

		Reserva::numReservas=contador;
		/////////////////////////////////////////////////

		Reserva* array = new Reserva[contador];
	sqlite3_stmt *stmt2;

		char sql2[] = "select * from reserva ";

		int result2 = sqlite3_prepare_v2(db, sql2, -1, &stmt2, NULL) ;
		if (result2 != SQLITE_OK) {
			printf("Error preparing statement (SELECT)\n");
			printf("%s\n", sqlite3_errmsg(db));
		}

		int id;
		char fecha[11];
		int dniCliente;
		int numeroHabitacion;
		int numeroPlazaParking;
		int posicion =0;

		do {

			result = sqlite3_step(stmt2) ;
			if (result == SQLITE_ROW) {
				id = sqlite3_column_int(stmt2, 0);
				strcpy(fecha, (char *) sqlite3_column_text(stmt2, 1));
				dniCliente = sqlite3_column_int(stmt2, 2);
				numeroHabitacion = sqlite3_column_int(stmt2, 3);
				numeroPlazaParking = sqlite3_column_int(stmt2, 4);
				Reserva r (id,fecha,dniCliente,numeroHabitacion,numeroPlazaParking);

				array[posicion]=r;
				posicion++;
			}
		} while (result == SQLITE_ROW);

		result = sqlite3_finalize(stmt2);
		if (result != SQLITE_OK) {
			printf("Error finalizing statement (SELECT)\n");
			printf("%s\n", sqlite3_errmsg(db));
		}
		return array;
}


int anadirReserva(Reserva &r, sqlite3* db){

	sqlite3_stmt *stmt1;

		char sql1[] = "insert into reserva (fecha,dniCliente,numeroHabitacion,numeroPlazaParking) values (?,?,?,?) ";

		int result = sqlite3_prepare_v2(db, sql1, -1, &stmt1, NULL) ;
		sqlite3_bind_text(stmt1, 1, r.getFecha().c_str(), strlen( r.getFecha().c_str()),SQLITE_STATIC);
		sqlite3_bind_int(stmt1, 2, r.getDniCliente());
		sqlite3_bind_int(stmt1, 3, r.getNumeroHabitacion());
		sqlite3_bind_int(stmt1, 4, r.getNumeroPlazaParking());



		if (result != SQLITE_OK) {
			printf("Error preparing statement (Insert)\n");
			printf("%s\n", sqlite3_errmsg(db));
			return NOT_OK;
		}


		result = sqlite3_step(stmt1);
		if (result != SQLITE_DONE) {
			printf("Error inserting new data into reserva table\n");
			return NOT_OK;
		}

		result = sqlite3_finalize(stmt1);
		if (result != SQLITE_OK) {
			printf("Error finalizing statement (INSERT)\n");
			return NOT_OK;
			printf("%s\n", sqlite3_errmsg(db));
		}

		return OK;
}


int borrarReserva(sqlite3*db,int numero){

	sqlite3_stmt *stmt1;

		char sql1[] = "delete from reserva where id = ?";

		int result = sqlite3_prepare_v2(db, sql1, -1, &stmt1, NULL) ;
		sqlite3_bind_int(stmt1, 1,numero);
		if (result != SQLITE_OK) {
			printf("Error preparing statement (Insert)\n");
			printf("%s\n", sqlite3_errmsg(db));
			return NOT_OK;
		}


		result = sqlite3_step(stmt1);
		if (result != SQLITE_DONE) {
			printf("Error borrando reserva %i table\n", numero);
			return NOT_OK;
		}

		result = sqlite3_finalize(stmt1);
		if (result != SQLITE_OK) {
			printf("Error finalizing statement (INSERT)\n");
			printf("%s\n", sqlite3_errmsg(db));
			return NOT_OK;
		}

		return OK;
}








