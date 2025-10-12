#include <cstring>
#include<iostream>
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

    cout << "Titulo: "<< nuevoArchivo->titulo << endl;
    cout << "Version: "<< nuevoArchivo -> version << endl;
    return nuevoArchivo;
}


TipoRet BorrarArchivo(Archivo &a){
    if (a==NULL)
        return ERROR;

    Linea aux = a->contenido;
    while(aux!=NULL) {
        Linea borrar = aux;
        aux = aux->sig;

        delete borrar->texto;
        delete borrar;
    }

    delete a;
    a = NULL;
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
    if (a==NULL || a->contenido==NULL)
        return ERROR;

    Linea actual = a->contenido;
    Linea anterior = NULL;

    while (actual != NULL && actual->nroLinea != nroLinea) {
        anterior = actual;
        actual = actual->sig;
    }

    if (actual==NULL)
        return ERROR;

    if (anterior==NULL) {
        a->contenido = actual->sig;
    }else {
        anterior->sig = actual->sig;
    }

    delete actual;

    actualizarLineas(a);
    return OK;
}

TipoRet MostrarTexto(Archivo a, char * version) {
    Linea aux = a->contenido;

    while (aux != NULL) {
        cout << aux->nroLinea << '\t' << aux->texto << endl;
        aux = aux->sig;
    }
    return OK;
}

void help() {
    cout << "Comandos:" << endl;
    cout << "crearA"<< endl;
    cout << "borrarA"<< endl;
    cout << "insertar(version,texto,nroLinea)"<< endl;
    cout << "borrarL(version, nroLinea)"<< endl;
    cout << "mostrarT(version)"<< endl;
    cout << "limpiar" << endl;
    cout << "salir"<< endl;
}