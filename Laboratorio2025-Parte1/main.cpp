#include <cstring>
#include<iostream>
#include <stdio_ext.h>
#include "estructuras.h"
#include "prototipos.h"
using namespace std;

int main (int argc, char *argv[]) {
	Archivo a = CrearArchivo("curriculum.txt");
	
	Cadena comando = new char[100];
	Cadena parametros[5];
	
	
	while (strlen(comando)==0) {
		cout << ">";
		cin.getline(comando,100);
	}
	
	char delim[] = "(\",\")";
	
	int contador = 0;
	parametros[contador] = strtok(comando,delim);
	
	while (parametros[contador]!=NULL && contador<5) {
		contador++;
		parametros[contador] = strtok(NULL,delim);
	}
	
	opciones opcion;
	
	while (strcmp(parametros[0],"salir")!=0) {
		opcion = error;
		if (strcmp(parametros[0],"InsertarLinea")==0) {opcion=insertar;}
		if (strcmp(parametros[0],"BorrarLinea")==0) {opcion=borrarL;}
		if (strcmp(parametros[0],"MostrarTexto")==0) {opcion=mostrarT;}
		if (strcmp(parametros[0],"ayuda")==0) {opcion=ayuda;}
		if (strcmp(parametros[0],"limpiar")==0) {opcion=limpiar;}
		
		switch (opcion) {
		case insertar:
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
			system("clear");
			break;
			
		default:
			muestroRetorno(ERROR);
		}
		__fpurge(stdin);
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
	BorrarArchivo(a);
	return 0;
}
