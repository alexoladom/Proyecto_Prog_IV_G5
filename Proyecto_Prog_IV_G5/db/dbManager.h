

#ifndef dbManager_h
#define dbManager_h




sqlite3 conectarDB();

void imprimirClientes(sqlite3*db);
void imprimirReservas(sqlite3*db);
void borrarReserva(sqlite3*db,int numero);
void imprimirHabitaciones(sqlite3*db);
void borrarHabitacion(sqlite3*db,int numero);
void añadirHabitacion(sqlite3*db,Habitacion h);
void imprimirPlazasParking(sqlite3*db);


#endif
