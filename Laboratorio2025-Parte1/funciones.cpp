#include "estructuras.h"
#include "prototipos.h"
#include <string>
using namespace std;

Archivo CrearArchivo(char * nombre){
    Archivo nuevoArchivo = new _archivo;
    nuevoArchivo -> titulo = nombre;
    //cuando se haga la funcion CrearVersion, nuevoArchivo->version se inicializa en NULL
    nuevoArchivo -> version = "1";
    nuevoArchivo -> contenido = NULL;
    nuevoArchivo -> sig = NULL;
    return nuevoArchivo;
}

//modificar para eliminar las lineas que haya adentro
TipoRet BorrarVersion(Archivo &a, char * version){
    delete a;
    return OK;
}


int cantLineas(Archivo a) {
    int contador = 0;
    Linea aux = a->contenido;
    while(aux != NULL) {
        contador++;
        aux = aux->sig;
    }
    return contador;
}

void actualizarLineas(Archivo &a) {
    Linea aux = a->contenido;
    unsigned int nL = 1;
    while (aux != NULL) {
        aux->nroLinea = nL++;
        aux = aux->sig;
    }
}

TipoRet InsertarLinea(Archivo &a, char * version, char * linea, unsigned int nroLinea) {
    if (nroLinea == 0 || nroLinea > cantLineas(a)+1) {
        return ERROR;
    }

    //creo la linea
    Linea l = new _linea;
    strcpy(l->texto, linea);
    l->sig = NULL;

    //inserta al principio
    if (nroLinea == 1) {
        l->sig = a->contenido;
        a->contenido = l;
        actualizarLineas(a);
        return  OK;
    }

    //el for recorre la lista hasta encontrar la posicion de nroLinea
    // linea anterior es para no perder la lista al insertar en el medio
    Linea anterior = a->contenido;
    for (unsigned int i = 1; i < nroLinea-1; i++) {
        anterior = anterior->sig;
    }

    l->sig = anterior->sig;
    anterior->sig = l;
    actualizarLineas(a);
    return OK;
}

TipoRet BorrarLinea(Archivo &a, char * version, unsigned int nroLinea) {
    return NO_IMPLEMENTADA;
}
