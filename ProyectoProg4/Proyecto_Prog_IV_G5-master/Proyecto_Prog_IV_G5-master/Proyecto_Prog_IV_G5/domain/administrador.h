#ifndef administrador_h
#define administrador_h


enum funcionAdministrador{recepcion,direccion,contabilidad,seguridad};


typedef struct {


	int dni;
	char nombre[20];
	int edad;
	char correo[30];
	enum funcionAdministrador funcion;


}Administrador;




#endif
