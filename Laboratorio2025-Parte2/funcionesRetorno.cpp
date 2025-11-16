#include<iostream>
using namespace std;
#include "string.h"
#include "estructuras.h"
#include "prototipos.h"


TipoRet creoV(Archivo &a, Cadena parametros[]){
	if (a==NULL)
		return ERROR;
	Cadena version = new char[100];
	strcpy(version, parametros[2]);
	return CrearVersion(a, version);
}

TipoRet muestroV(Archivo &a){
	return MostrarVersiones(a);
}


TipoRet borroV(Archivo &a, Cadena parametros[]){
	if (a==NULL)
		return ERROR;
	Cadena version = new char[100];
	strcpy(version, parametros[2]);
	return BorrarVersion(a, version);
}

TipoRet inserto(Archivo &a, Cadena parametros[]) {
    if (a==NULL)
        return ERROR;

    Cadena version = new char[100];
    strcpy(version, parametros[2]);

    Cadena linea= new char[100];
    strcpy(linea, parametros[3]);

    unsigned int nroLinea = atoi(parametros[4]);

    return InsertarLinea(a,version,linea,nroLinea);
}

TipoRet borroL(Archivo &a, Cadena parametros[]) {
    if (a==NULL)
        return ERROR;
    Cadena version = new char[100];
    strcpy(version, parametros[2]);


    unsigned int nroLinea = atoi(parametros[3]);

    return BorrarLinea(a, version, nroLinea);
}

TipoRet muestroT(Archivo a, Cadena parametros[]) {
	if (parametros[1]==NULL) {
        return ERROR;
    }
    Cadena version = new char[10];
    strcpy(version, parametros[2]);
    return MostrarTexto(a,version);
}

TipoRet muestroC(Archivo a, Cadena parametros[]){
	Cadena version = new char[10];
	strcpy(version, parametros[2]);
	return MostrarCambios(a,version);
}


TipoRet igual(Archivo a, Cadena parametros[]){
	Cadena version1 = new char[10];
	strcpy(version1, parametros[2]);

	Cadena version2 = new char[10];
	strcpy(version2, parametros[3]);

	bool iguales;
	return Iguales(a,version1,version2,iguales);
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
