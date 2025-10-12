#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

enum _retorno{
    OK, ERROR, NO_IMPLEMENTADA
};
typedef enum _retorno TipoRet;

/********************************************/
typedef char* Cadena;

struct _linea {
    unsigned int nroLinea;
    Cadena texto = new char[100];
    _linea* sig;
};

typedef _linea* Linea;


struct _archivo{
    Cadena titulo;
    Cadena version;
    _linea* contenido;
    _archivo* sig;
};

typedef enum _opciones{
    crearA, borrarA, insertar, borrarL, mostrarT, ayuda, error, limpiar, salir
}opciones;


/******************************************/

typedef _archivo* Archivo;

#endif