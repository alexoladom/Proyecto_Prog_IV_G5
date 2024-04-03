#ifndef administrador_h
#define administrador_h


enum funcionAdministrador{recepcion,direccion,contabilidad,seguridad};


typedef struct {


	int dni;
	char * nombre;
	int edad;
	char * correo;
	enum funcionAdministrador funcion;


}Administrador;

Administrador crearAdministrador(int dni, char*nombre,int edad, char*correo, enum funcionAdministrador funcion);



#endif
