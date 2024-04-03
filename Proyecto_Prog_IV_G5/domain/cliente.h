
#ifndef cliente_h
#define cliente_h


typedef struct{

	int dni;
	char* nombre;
	int edad;
	char *correo;


}Cliente;


Cliente crearCliente(int dni, char*nombre,int edad ,char*correo);

void imprimirCliente(Cliente c);

#endif
