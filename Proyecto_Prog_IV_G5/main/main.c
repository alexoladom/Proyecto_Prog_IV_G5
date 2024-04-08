#include "../domain/menuPrincipal.h"


int main(){

	sqlite3* db = conectarDB();
	mostrarMenuPrincipal(db);

	return 0;
}
