#include <cstring>
#include<iostream>
#include "estructuras.h"
#include "prototipos.h"
using namespace std;

int main (int argc, char *argv[]) {
    Archivo a = NULL;

    Cadena comando = new char[100];
    Cadena parametros[5];


    while (strlen(comando)==0) {
        cout << ">";
        cin.getline(comando,100);
    }

    char delim[] = "(,)";

    int contador = 0;
    parametros[contador] = strtok(comando,delim);

    while (parametros[contador]!=NULL && contador<5) {
        contador++;
        parametros[contador] = strtok(NULL,delim);
    }

    opciones opcion;
    while (strcmp(parametros[0],"salir")!=0) {
        opcion = error;
        if (strcmp(parametros[0],"crearA")==0) {opcion = crearA;}
        if (strcmp(parametros[0],"borrarA")==0) {opcion = borrarA;}
        if (strcmp(parametros[0],"insertar")==0) {opcion=insertar;}
        if (strcmp(parametros[0],"borrarL")==0) {opcion=borrarL;}
        if (strcmp(parametros[0],"mostrarT")==0) {opcion=mostrarT;}
        if (strcmp(parametros[0],"ayuda")==0) {opcion=ayuda;}
        if (strcmp(parametros[0],"limpiar")==0) {opcion=limpiar;}

        switch (opcion) {
            case crearA:
                muestroRetorno(creoA(a));
            break;

            case borrarA:
                muestroRetorno(borroA(a));
            break;

            case insertar:
                cout << contador << endl;
                muestroRetorno(inserto(a, parametros));
            break;

            case borrarL:
                muestroRetorno(borroL(a,parametros));
            break;

            case mostrarT:
                muestroRetorno(muestroT(a,parametros));
            break;

            case ayuda:
                help();
            break;

            case limpiar:
                system("cls");
            break;

            default:
                muestroRetorno(ERROR);
        }
        fflush(stdin);
        strcpy(comando,"");

        while (strlen(comando)==0) {
            cout << ">";
            cin.getline(comando,100);
        }

        int contador = 0;
        parametros[contador] = strtok(comando,delim);

        while (parametros[contador]!=NULL && contador<5) {
            contador++;
            parametros[contador] = strtok(NULL,delim);
        }
    }
    return 0;
}
