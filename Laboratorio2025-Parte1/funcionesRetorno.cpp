#include<iostream>
using namespace std;
#include "string.h"
#include "estructuras.h"
#include "prototipos.h"



TipoRet creoA(Archivo &a) {
    a = CrearArchivo("curriculo.txt");
    return OK;
}

TipoRet borroA(Archivo &a) {
    if (a==NULL)
        return ERROR;
    return BorrarArchivo(a);
}

TipoRet inserto(Archivo &a, Cadena parametros[]) {
    if (a==NULL)
        return ERROR;

    Cadena version = new char[100];
    strcpy(version, parametros[1]);

    Cadena linea= new char[100];
    strcpy(linea, parametros[2]);

    unsigned int nroLinea = atoi(parametros[3]);

    return InsertarLinea(a,version,linea,nroLinea);
}

TipoRet borroL(Archivo &a, Cadena parametros[]) {
    if (a==NULL)
        return ERROR;
    Cadena version = new char[100];
    strcpy(version, parametros[1]);


    unsigned int nroLinea = atoi(parametros[2]);

    return BorrarLinea(a, version, nroLinea);
}

TipoRet muestroT(Archivo a, Cadena parametros[]) {
    if (a==NULL) {
        cout << "No contiene lineas" << endl;
        return OK;
    }
    if (parametros[1]==NULL) {
        return ERROR;
    }
    Cadena version = new char[10];
    strcpy(version, parametros[1]);
    return MostrarTexto(a,version);
}

void muestroRetorno(_retorno ret){
    switch (ret){
        case OK:
            cout << "OK"<< endl;
            break;
        case ERROR:
            cout << "ERROR" << endl;
            break;
        case NO_IMPLEMENTADA:
            cout << "NO IMPLEMENTADA"<<endl;
    }
}