#include "funcionesBD.h"


#define OK 1
#define NOT_OK 0




sqlite3* conectarDB(){
	Config datos = readConfig("config/config.h");
	sqlite3 * db;
	int result1 = sqlite3_open("db/C++dbProgIV.sqlite", &db);
	cout<<datos.db_address;
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

		int result3 = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);// @suppress("Invalid arguments")
		if (result3 != SQLITE_OK) {
			printf("Error preparing statement (SELECT)\n");
			printf("%s\n", sqlite3_errmsg(db));// @suppress("Invalid arguments")
		}

		int contador=0;
		int result;
		do {

			result = sqlite3_step(stmt);// @suppress("Invalid arguments")
			if (result == SQLITE_ROW) {
				contador++;
			}
		} while (result == SQLITE_ROW);

		result = sqlite3_finalize(stmt);// @suppress("Invalid arguments")
		if (result != SQLITE_OK) {
			printf("Error finalizing statement (SELECT)\n");
			printf("%s\n", sqlite3_errmsg(db));// @suppress("Invalid arguments")
		}

		Cliente::numClientes=contador;
		/////////////////////////////////////////////////7

		sqlite3_stmt *stmt2;

		Cliente *array = new Cliente[contador];

		char sql2[] = "select * from cliente";

		result3 = sqlite3_prepare_v2(db, sql2, strlen(sql2) + 1, &stmt2, NULL);// @suppress("Invalid arguments")
		if (result3 != SQLITE_OK) {
			printf("Error preparing statement (SELECT)\n");
			printf("%s\n", sqlite3_errmsg(db));// @suppress("Invalid arguments")
		}


		int dni;
		char nombre[20];
		int edad;
		char correo[30];
		int posicion=0;

		do {

			result = sqlite3_step(stmt2);// @suppress("Invalid arguments")
			if (result == SQLITE_ROW) {
				dni = sqlite3_column_int(stmt2, 0);// @suppress("Invalid arguments")
				strcpy(nombre, (char *) sqlite3_column_text(stmt2, 1));// @suppress("Invalid arguments")
				edad = sqlite3_column_int(stmt2, 2);// @suppress("Invalid arguments")
				strcpy(correo,(char*) sqlite3_column_text(stmt2, 3));// @suppress("Invalid arguments")
				Cliente c (dni,nombre,edad,correo);
				array[posicion]=c;
				posicion++;
			}
		} while (result == SQLITE_ROW);

		result = sqlite3_finalize(stmt2);// @suppress("Invalid arguments")
		if (result != SQLITE_OK) {
			printf("Error finalizing statement (SELECT)\n");
			printf("%s\n", sqlite3_errmsg(db));// @suppress("Invalid arguments")
		}
		return array;
}



int comprobarDni(sqlite3* db, int dni){
	sqlite3_stmt *stmt;

		char sql[] = "select dni from contraseñas";

		int result3 = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);// @suppress("Invalid arguments")
		if (result3 != SQLITE_OK) {
			printf("Error preparing statement (SELECT)\n");
			printf("%s\n", sqlite3_errmsg(db));// @suppress("Invalid arguments")
			return NOT_OK;
		}
		int dni2;
		int result;
		do {
			result = sqlite3_step(stmt) ;// @suppress("Invalid arguments")
			if (result == SQLITE_ROW) {
				dni2 = sqlite3_column_int(stmt, 0);// @suppress("Invalid arguments")
				if (dni2==dni){
					return OK;
				}
			}
		} while (result == SQLITE_ROW);

		result = sqlite3_finalize(stmt);// @suppress("Invalid arguments")
		if (result != SQLITE_OK) {
			printf("Error finalizing statement (SELECT)\n");
			printf("%s\n", sqlite3_errmsg(db));// @suppress("Invalid arguments")
			return NOT_OK;
		}
		return NOT_OK;
}
int comprobarContra(sqlite3* db, int dni, char*contrasena){
	sqlite3_stmt *stmt;

			char sql[] = "select contra from contraseñas where dni=?";

			int result3 = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);// @suppress("Invalid arguments")
			sqlite3_bind_int(stmt, 1, dni);// @suppress("Invalid arguments")

			if (result3 != SQLITE_OK) {
				printf("Error preparing statement (SELECT)\n");
				printf("%s\n", sqlite3_errmsg(db));// @suppress("Invalid arguments")
			}
			char contra[20];
			int result;
			result = sqlite3_step(stmt) ;// @suppress("Invalid arguments")
			if (result == SQLITE_ROW) {
				strcpy(contra,(char*)sqlite3_column_text(stmt, 0));// @suppress("Invalid arguments")
				if (strcmp(contra,contrasena)==0){
					return OK;
				}
			}
			result = sqlite3_finalize(stmt);// @suppress("Invalid arguments")
			if (result != SQLITE_OK) {
				printf("Error finalizing statement (SELECT)\n");
				printf("%s\n", sqlite3_errmsg(db));// @suppress("Invalid arguments")
			}
			return NOT_OK;
}

int anadirDniContra(sqlite3* db, int dni, char* contra){
	sqlite3_stmt *stmt1;

	char sql1[] = "insert into contraseñas (dni,contra) values (?,?) ";

	int result = sqlite3_prepare_v2(db, sql1, -1, &stmt1, NULL) ;// @suppress("Invalid arguments")
	sqlite3_bind_int(stmt1, 1, dni);// @suppress("Invalid arguments")
	sqlite3_bind_text(stmt1, 2, contra, strlen(contra),SQLITE_STATIC);// @suppress("Invalid arguments")



	if (result != SQLITE_OK) {
		printf("Error preparing statement (Insert)\n");
		printf("%s\n", sqlite3_errmsg(db));// @suppress("Invalid arguments")
		return NOT_OK;
	}


	result = sqlite3_step(stmt1);// @suppress("Invalid arguments")
	if (result != SQLITE_DONE) {
		printf("Error inserting new data into cliente table\n");
		return NOT_OK;
	}

	result = sqlite3_finalize(stmt1);// @suppress("Invalid arguments")
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(db));// @suppress("Invalid arguments")
		return NOT_OK;
	}
	return OK;
}

int anadirCliente(Cliente &c, sqlite3*db){

	sqlite3_stmt *stmt1;

	char sql1[] = "insert into cliente (dni,nombre,edad,correo) values (?,?,?,?) ";

	int result = sqlite3_prepare_v2(db, sql1, -1, &stmt1, NULL) ;// @suppress("Invalid arguments")
	sqlite3_bind_int(stmt1, 1, c.getDni());// @suppress("Invalid arguments")
	sqlite3_bind_text(stmt1, 2, c.getNombre().c_str(), strlen(c.getNombre().c_str()),SQLITE_STATIC);// @suppress("Invalid arguments")
	sqlite3_bind_int(stmt1, 3, c.getEdad());// @suppress("Invalid arguments")
	sqlite3_bind_text(stmt1, 4,c.getCorreo().c_str(), strlen(c.getCorreo().c_str()),SQLITE_STATIC);// @suppress("Invalid arguments")


	if (result != SQLITE_OK) {
		printf("Error preparing statement (Insert)\n");
		printf("%s\n", sqlite3_errmsg(db));// @suppress("Invalid arguments")
		return NOT_OK;
	}


	result = sqlite3_step(stmt1);// @suppress("Invalid arguments")
		if (result != SQLITE_DONE) {
			printf("Error inserting new data into cliente table\n");
			return NOT_OK;
		}

		result = sqlite3_finalize(stmt1);// @suppress("Invalid arguments")
		if (result != SQLITE_OK) {
			printf("Error finalizing statement (INSERT)\n");
			printf("%s\n", sqlite3_errmsg(db));// @suppress("Invalid arguments")
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

		int result3 = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;// @suppress("Invalid arguments")
		if (result3 != SQLITE_OK) {
			printf("Error preparing statement (SELECT)\n");
			printf("%s\n", sqlite3_errmsg(db));// @suppress("Invalid arguments")
		}

		int contador=0;

		int result;
		do {

			result = sqlite3_step(stmt) ;// @suppress("Invalid arguments")
			if (result == SQLITE_ROW) {
				contador++;
			}
		} while (result == SQLITE_ROW);

		result = sqlite3_finalize(stmt);// @suppress("Invalid arguments")
		if (result != SQLITE_OK) {
			printf("Error finalizing statement (SELECT)\n");
			printf("%s\n", sqlite3_errmsg(db));// @suppress("Invalid arguments")
		}

		Reserva::numReservas=contador;
		/////////////////////////////////////////////////

		Reserva* array = new Reserva[contador];
	sqlite3_stmt *stmt2;

		char sql2[] = "select * from reserva ";

		int result2 = sqlite3_prepare_v2(db, sql2, -1, &stmt2, NULL) ;// @suppress("Invalid arguments")
		if (result2 != SQLITE_OK) {
			printf("Error preparing statement (SELECT)\n");
			printf("%s\n", sqlite3_errmsg(db));// @suppress("Invalid arguments")
		}

		int id;
		char fecha[11];
		int dniCliente;
		int numeroHabitacion;
		int numeroPlazaParking;
		int posicion =0;

		do {

			result = sqlite3_step(stmt2) ;// @suppress("Invalid arguments")
			if (result == SQLITE_ROW) {
				id = sqlite3_column_int(stmt2, 0);// @suppress("Invalid arguments")
				strcpy(fecha, (char *) sqlite3_column_text(stmt2, 1));// @suppress("Invalid arguments")
				dniCliente = sqlite3_column_int(stmt2, 2);// @suppress("Invalid arguments")
				numeroHabitacion = sqlite3_column_int(stmt2, 3);// @suppress("Invalid arguments")
				numeroPlazaParking = sqlite3_column_int(stmt2, 4);// @suppress("Invalid arguments")
				Reserva r (id,fecha,dniCliente,numeroHabitacion,numeroPlazaParking);

				array[posicion]=r;
				posicion++;
			}
		} while (result == SQLITE_ROW);

		result = sqlite3_finalize(stmt2);// @suppress("Invalid arguments")
		if (result != SQLITE_OK) {
			printf("Error finalizing statement (SELECT)\n");
			printf("%s\n", sqlite3_errmsg(db));// @suppress("Invalid arguments")
		}
		return array;
}


int anadirReserva(Reserva &r, sqlite3* db){

	sqlite3_stmt *stmt1;

		char sql1[] = "insert into reserva (fecha,dniCliente,numeroHabitacion,numeroPlazaParking) values (?,?,?,?) ";

		int result = sqlite3_prepare_v2(db, sql1, -1, &stmt1, NULL) ;// @suppress("Invalid arguments")
		sqlite3_bind_text(stmt1, 1, r.getFecha().c_str(), strlen( r.getFecha().c_str()),SQLITE_STATIC);// @suppress("Invalid arguments")
		sqlite3_bind_int(stmt1, 2, r.getDniCliente());// @suppress("Invalid arguments")
		sqlite3_bind_int(stmt1, 3, r.getNumeroHabitacion());// @suppress("Invalid arguments")
		sqlite3_bind_int(stmt1, 4, r.getNumeroPlazaParking());// @suppress("Invalid arguments")



		if (result != SQLITE_OK) {
			printf("Error preparing statement (Insert)\n");
			printf("%s\n", sqlite3_errmsg(db));// @suppress("Invalid arguments")
			return NOT_OK;
		}


		result = sqlite3_step(stmt1);// @suppress("Invalid arguments")
		if (result != SQLITE_DONE) {
			printf("Error inserting new data into reserva table\n");
			return NOT_OK;
		}

		result = sqlite3_finalize(stmt1);// @suppress("Invalid arguments")
		if (result != SQLITE_OK) {
			printf("Error finalizing statement (INSERT)\n");
			return NOT_OK;
			printf("%s\n", sqlite3_errmsg(db));// @suppress("Invalid arguments")
		}

		Reserva::numReservas++;
		return OK;
}


int borrarReserva(sqlite3*db,int numero){

	sqlite3_stmt *stmt1;

		char sql1[] = "delete from reserva where id = ?";

		int result = sqlite3_prepare_v2(db, sql1, -1, &stmt1, NULL) ;// @suppress("Invalid arguments")
		sqlite3_bind_int(stmt1, 1,numero);// @suppress("Invalid arguments")
		if (result != SQLITE_OK) {
			printf("Error preparing statement (Insert)\n");
			printf("%s\n", sqlite3_errmsg(db));// @suppress("Invalid arguments")
			return NOT_OK;
		}


		result = sqlite3_step(stmt1);// @suppress("Invalid arguments")
		if (result != SQLITE_DONE) {
			printf("Error borrando reserva %i table\n", numero);
			return NOT_OK;
		}

		result = sqlite3_finalize(stmt1);// @suppress("Invalid arguments")
		if (result != SQLITE_OK) {
			printf("Error finalizing statement (INSERT)\n");
			printf("%s\n", sqlite3_errmsg(db));// @suppress("Invalid arguments")
			return NOT_OK;
		}

		Reserva::numReservas--;
		return OK;
}

int modificarReserva(sqlite3* db, Reserva &r){
	sqlite3_stmt *stmt1;

	char sql1[] = "update reserva set fecha=?, numeroHabitacion=?, numeroPlazaParking=? where id = ?";

	int result = sqlite3_prepare_v2(db, sql1, -1, &stmt1, NULL) ;// @suppress("Invalid arguments")
	sqlite3_bind_text(stmt1, 1, r.getFecha().c_str(), strlen( r.getFecha().c_str()),SQLITE_STATIC);// @suppress("Invalid arguments")
	sqlite3_bind_int(stmt1, 2,r.getNumeroHabitacion());// @suppress("Invalid arguments")
	sqlite3_bind_int(stmt1, 3,r.getNumeroPlazaParking());// @suppress("Invalid arguments")
	sqlite3_bind_int(stmt1, 4,r.getId());// @suppress("Invalid arguments")

	if (result != SQLITE_OK) {
		printf("Error preparing statement (Update)\n");
		printf("%s\n", sqlite3_errmsg(db));// @suppress("Invalid arguments")
		return NOT_OK;
	}
	result = sqlite3_step(stmt1);// @suppress("Invalid arguments")
	if (result != SQLITE_DONE) {
		printf("Error actualizando reserva %i table\n", r.getId());
		return NOT_OK;
	}

	result = sqlite3_finalize(stmt1);// @suppress("Invalid arguments")
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (Update)\n");
		printf("%s\n", sqlite3_errmsg(db));// @suppress("Invalid arguments")
		return NOT_OK;
	}


	return OK;
}

/*
 *
 *
 * Funciones para habitaciones
 *
 *
 */

Habitacion* getListaHabitaciones(sqlite3*db){
	sqlite3_stmt *stmt;

		char sql[] = "select * from habitacion ";

		int result3 = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;// @suppress("Invalid arguments")
		if (result3 != SQLITE_OK) {
			printf("Error preparing statement (SELECT)\n");
			printf("%s\n", sqlite3_errmsg(db));// @suppress("Invalid arguments")
		}



		int contador=0;
		int result;
		do {

			result = sqlite3_step(stmt) ;// @suppress("Invalid arguments")
			if (result == SQLITE_ROW) {
				contador++;
			}
		} while (result == SQLITE_ROW);

		result = sqlite3_finalize(stmt);// @suppress("Invalid arguments")
		if (result != SQLITE_OK) {
			printf("Error finalizing statement (SELECT)\n");
			printf("%s\n", sqlite3_errmsg(db));// @suppress("Invalid arguments")
		}

		Habitacion* array= new Habitacion[contador];
		Habitacion::numHabitaciones=contador;

		sqlite3_stmt *stmt2;

		char sql2[] = "select * from habitacion ";

		result3 = sqlite3_prepare_v2(db, sql2, -1, &stmt2, NULL) ;// @suppress("Invalid arguments")
		if (result3 != SQLITE_OK) {
			printf("Error preparing statement (SELECT)\n");
			printf("%s\n", sqlite3_errmsg(db));// @suppress("Invalid arguments")
		}


		int numero;
		int piso;
		char tipoString[10];
		enum tipoHabitacion tipo;
		int capacidad;
		int precio;
		bool ocupado;
		int pos=0;

		int result2;
		do {

			result2 = sqlite3_step(stmt2) ;// @suppress("Invalid arguments")
			if (result2 == SQLITE_ROW) {
				numero = sqlite3_column_int(stmt2, 0);// @suppress("Invalid arguments")
				piso = sqlite3_column_int(stmt2, 1);// @suppress("Invalid arguments")
				strcpy(tipoString, (char *) sqlite3_column_text(stmt2, 2));// @suppress("Invalid arguments")
				if(tipoString[1]=='i'){
					tipo=simple;
				}else if(tipoString[1]=='o'){
					tipo=doble;
				}else{
					tipo=suite;
				}
				capacidad = sqlite3_column_int(stmt2, 3);// @suppress("Invalid arguments")
				precio = sqlite3_column_int(stmt2, 4);// @suppress("Invalid arguments")
				ocupado = sqlite3_column_int(stmt2, 5);// @suppress("Invalid arguments")

				Habitacion h(numero,piso,tipo,capacidad,precio,ocupado);
				array[pos]=h;
				pos++;
			}
		} while (result2 == SQLITE_ROW);

		result2 = sqlite3_finalize(stmt2);// @suppress("Invalid arguments")
		if (result != SQLITE_OK) {
			printf("Error finalizing statement (SELECT)\n");
			printf("%s\n", sqlite3_errmsg(db));// @suppress("Invalid arguments")
		}


		return array;
}

int borrarHabitacion(sqlite3*db,int numero){

	sqlite3_stmt *stmt1;

	char sql1[] = "delete from habitacion where numero = ?";

	int result = sqlite3_prepare_v2(db, sql1, -1, &stmt1, NULL) ;// @suppress("Invalid arguments")
	sqlite3_bind_int(stmt1, 1,numero);// @suppress("Invalid arguments")
	if (result != SQLITE_OK) {
		printf("Error preparing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(db));// @suppress("Invalid arguments")
		return NOT_OK;
	}


	result = sqlite3_step(stmt1);// @suppress("Invalid arguments")
	if (result != SQLITE_DONE) {
		printf("Error borrando habitacion %i table\n", numero);
		return NOT_OK;
	}

	result = sqlite3_finalize(stmt1);// @suppress("Invalid arguments")
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(db));// @suppress("Invalid arguments")
		return NOT_OK;
	}

	Habitacion::numHabitaciones--;
	return OK;
}

int anadirHabitacion(sqlite3*db,Habitacion &h){

	sqlite3_stmt *stmt1;

		char sql1[] = "insert into habitacion (numero,piso,tipo,capacidad,precio,ocupado) values (?,?,?,?,?,?) ";

		int result = sqlite3_prepare_v2(db, sql1, -1, &stmt1, NULL) ;// @suppress("Invalid arguments")
		char tipos[][10]= {"simple","doble","suite"};
		sqlite3_bind_int(stmt1, 1, h.getNumero());// @suppress("Invalid arguments")
		sqlite3_bind_int(stmt1, 2,h.getPiso());// @suppress("Invalid arguments")
		sqlite3_bind_text(stmt1, 3, tipos[h.getTipo()], strlen(tipos[h.getTipo()]),SQLITE_STATIC);// @suppress("Invalid arguments")
		sqlite3_bind_int(stmt1, 4,h.getCapacidad());// @suppress("Invalid arguments")
		sqlite3_bind_int(stmt1, 5,h.getPrecio());// @suppress("Invalid arguments")
		sqlite3_bind_int(stmt1, 6,h.isOcupado());// @suppress("Invalid arguments")


		if (result != SQLITE_OK) {
			printf("Error preparing statement (Insert)\n");
			printf("%s\n", sqlite3_errmsg(db));// @suppress("Invalid arguments")
			return NOT_OK;
		}


		result = sqlite3_step(stmt1);// @suppress("Invalid arguments")
			if (result != SQLITE_DONE) {
				printf("Error inserting new data into habitacion table\n");
				return NOT_OK;

			}

			result = sqlite3_finalize(stmt1);// @suppress("Invalid arguments")
			if (result != SQLITE_OK) {
				printf("Error finalizing statement (INSERT)\n");
				printf("%s\n", sqlite3_errmsg(db));// @suppress("Invalid arguments")
				return NOT_OK;

			}

			Habitacion::numHabitaciones++;
			return OK;

}

int modificarHabitacion(sqlite3*db,Habitacion &h){
	sqlite3_stmt *stmt1;

	char sql1[] = "update habitacion set ocupado=? where numero = ?";

	int result = sqlite3_prepare_v2(db, sql1, -1, &stmt1, NULL) ;// @suppress("Invalid arguments")
	sqlite3_bind_int(stmt1, 1,h.isOcupado());// @suppress("Invalid arguments")

	sqlite3_bind_int(stmt1, 2,h.getNumero());// @suppress("Invalid arguments")

	if (result != SQLITE_OK) {
		printf("Error preparing statement (Update)\n");
		printf("%s\n", sqlite3_errmsg(db));// @suppress("Invalid arguments")
		return NOT_OK;
	}
	result = sqlite3_step(stmt1);// @suppress("Invalid arguments")
	if (result != SQLITE_DONE) {
		printf("Error actualizando habitacion %i table\n", h.getNumero());
		return NOT_OK;
	}

	result = sqlite3_finalize(stmt1);// @suppress("Invalid arguments")
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (Update)\n");
		printf("%s\n", sqlite3_errmsg(db));// @suppress("Invalid arguments")
		return NOT_OK;
	}


	return OK;
}

/*
 *
 *
 * Funciones Plaza Parking
 *
 *
 *
 *
 */



PlazaParking* getListaPlazasParking(sqlite3*db){

		sqlite3_stmt *stmt;

		char sql[] = "select * from plazaparking ";

		int result3 = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;// @suppress("Invalid arguments")
		if (result3 != SQLITE_OK) {
			printf("Error preparing statement (SELECT)\n");
			printf("%s\n", sqlite3_errmsg(db));// @suppress("Invalid arguments")
		}

		int contador=0;

		int result;
		do {

			result = sqlite3_step(stmt);// @suppress("Invalid arguments")
			if (result == SQLITE_ROW) {
				contador++;
			}
		} while (result == SQLITE_ROW);

		result = sqlite3_finalize(stmt);// @suppress("Invalid arguments")
		if (result != SQLITE_OK) {
			printf("Error finalizing statement (SELECT)\n");
			printf("%s\n", sqlite3_errmsg(db));// @suppress("Invalid arguments")
		}

		PlazaParking* array= new PlazaParking[contador];

		PlazaParking::numPlazaParkings=contador;

	sqlite3_stmt *stmt2;

	char sql2[] = "select * from plazaparking ";

	result3 = sqlite3_prepare_v2(db, sql2, -1, &stmt2, NULL) ;// @suppress("Invalid arguments")
	if (result3 != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));// @suppress("Invalid arguments")
	}

	int numero;
	char zona;
	string zonas;
	bool ocupado;
	int pos=0;
	do {

		result = sqlite3_step(stmt2) ;// @suppress("Invalid arguments")
		if (result == SQLITE_ROW) {
			numero = sqlite3_column_int(stmt2, 0);// @suppress("Invalid arguments")
			strcpy(&zona, (char *) sqlite3_column_text(stmt2, 1));// @suppress("Invalid arguments")
			ocupado = sqlite3_column_int(stmt2, 2);// @suppress("Invalid arguments")

			zonas = zona;
			PlazaParking p(numero,zonas,ocupado);
			array[pos]=p;
			pos++;
		}
	} while (result == SQLITE_ROW);

	result = sqlite3_finalize(stmt2);// @suppress("Invalid arguments")
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));// @suppress("Invalid arguments")
	}

	return array;
}


int anadirPlazaParking(sqlite3*db,PlazaParking &p){
	sqlite3_stmt *stmt1;

	char sql1[] = "insert into plazaparking (numero,zona,ocupado) values (?,?,?) ";

	int result = sqlite3_prepare_v2(db, sql1, -1, &stmt1, NULL) ;// @suppress("Invalid arguments")
	sqlite3_bind_int(stmt1, 1, p.getNumero());// @suppress("Invalid arguments")
	sqlite3_bind_text(stmt1, 2, p.getZona().c_str(), strlen(p.getZona().c_str()),SQLITE_STATIC);// @suppress("Invalid arguments")
	sqlite3_bind_int(stmt1, 3, p.isOcupado());// @suppress("Invalid arguments")



	if (result != SQLITE_OK) {
		printf("Error preparing statement (Insert)\n");
		printf("%s\n", sqlite3_errmsg(db));// @suppress("Invalid arguments")
		return NOT_OK;
	}


	result = sqlite3_step(stmt1);// @suppress("Invalid arguments")
		if (result != SQLITE_DONE) {
			printf("Error inserting new data into plazaparking table\n");
			return NOT_OK;
		}

		result = sqlite3_finalize(stmt1);// @suppress("Invalid arguments")
		if (result != SQLITE_OK) {
			printf("Error finalizing statement (INSERT)\n");
			printf("%s\n", sqlite3_errmsg(db));// @suppress("Invalid arguments")
			return NOT_OK;
		}

		PlazaParking::numPlazaParkings++;
		return OK;
}

int borrarPlazaParking(sqlite3*db, int numero){

	sqlite3_stmt *stmt1;

	char sql1[] = "delete from plazaparking where numero = ?";

	int result = sqlite3_prepare_v2(db, sql1, -1, &stmt1, NULL) ;// @suppress("Invalid arguments")
	sqlite3_bind_int(stmt1, 1,numero);// @suppress("Invalid arguments")
	if (result != SQLITE_OK) {
		printf("Error preparing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(db));// @suppress("Invalid arguments")
		return NOT_OK;
	}


	result = sqlite3_step(stmt1);// @suppress("Invalid arguments")
		if (result != SQLITE_DONE) {
			printf("Error borrando plazaparking %i table\n", numero);
			return NOT_OK;
		}

		result = sqlite3_finalize(stmt1);// @suppress("Invalid arguments")
		if (result != SQLITE_OK) {
			printf("Error finalizing statement (DELETE)\n");
			printf("%s\n", sqlite3_errmsg(db));// @suppress("Invalid arguments")
			return NOT_OK;
		}
		PlazaParking::numPlazaParkings--;
		return OK;

}

int modificarPlazaParking(sqlite3*db,PlazaParking &p){
	sqlite3_stmt *stmt1;

	char sql1[] = "update plazaparking set ocupado=? where numero = ?";

	int result = sqlite3_prepare_v2(db, sql1, -1, &stmt1, NULL) ;// @suppress("Invalid arguments")
	sqlite3_bind_int(stmt1, 1,p.isOcupado());// @suppress("Invalid arguments")

	sqlite3_bind_int(stmt1, 2,p.getNumero());// @suppress("Invalid arguments")

	if (result != SQLITE_OK) {
		printf("Error preparing statement (Update)\n");
		printf("%s\n", sqlite3_errmsg(db));// @suppress("Invalid arguments")
		return NOT_OK;
	}
	result = sqlite3_step(stmt1);// @suppress("Invalid arguments")
	if (result != SQLITE_DONE) {
		printf("Error actualizando plazaparking %i table\n", p.getNumero());
		return NOT_OK;
	}

	result = sqlite3_finalize(stmt1);// @suppress("Invalid arguments")
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (Update)\n");
		printf("%s\n", sqlite3_errmsg(db));// @suppress("Invalid arguments")
		return NOT_OK;
	}


	return OK;
}


