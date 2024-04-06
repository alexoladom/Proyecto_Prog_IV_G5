

#ifndef dbManager_h
#define dbManager_h




sqlite3 conectarDB();

void imprimirClientes(sqlite3*db); //DONE
void anadirCliente(Cliente c,sqlite3*db);//DONE
void imprimirReservas(sqlite3*db); //DONE
void anadirReserva(Reserva r, sqlite3* db); //DONE
void borrarReserva(sqlite3*db,int numero); //DONE
void imprimirHabitaciones(sqlite3*db); //DONE
void borrarHabitacion(sqlite3*db,int numero); //DONE
void anadirHabitacion(sqlite3*db,Habitacion h);//DONE
void imprimirPlazasParking(sqlite3*db);//DONE


#endif
