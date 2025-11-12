#ifndef LABPARTE2_ESTRUCTURAS_H
#define LABPARTE2_ESTRUCTURAS_H
#include <stdlib.h>

enum _retorno{
    OK, ERROR, NO_IMPLEMENTADA
};
typedef enum _retorno TipoRet;

/********************************************/
typedef char* Cadena;

struct _linea {
    unsigned int nroLinea;
	unsigned int nroInsercion;
    Cadena texto = new char[100];
    _linea* sig;
	Cadena estado= new char[2];
};
typedef _linea* Linea;

struct  _version {
    Cadena nroVersion;
    _linea* contenido = NULL;
	_version* versionPadre;
    _version* subVersion = NULL;
    _version* sigVersion = NULL;
};
typedef struct _version* Version;


struct _archivo{
    Cadena titulo = new char[50];
    _version* versiones;
    _archivo* sig;
};

typedef enum _opciones{
    crearV, mostrarV, borrarV, insertar, borrarL, mostrarT,mostrarC,sonIguales, ayuda, error, limpiar, salir
}opciones;


/******************************************/

typedef _archivo* Archivo;

#endif
