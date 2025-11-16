#include <cstring>
#include<iostream>
#include "estructuras.h"
#include "prototipos.h"
#include <string>
#include <iomanip>
using namespace std;

//busca la version, si la encuentra devuelve un puntero si no , NULL
Version encontrarVersion(Archivo a, char* version) {
	if (a==NULL) {
		return NULL;
	}
	if (a->versiones == NULL){
		return NULL;
	}

	char copia[100];
	strcpy(copia,version);

	//vTok es un arreglo que guarda tokenizada la version
	char* vTok[5];
	int x = 0;

	char* tok = strtok(copia,".");
	//cargamos el arreglo
	while (tok != NULL && x<5){
		vTok[x++] = tok;
		tok = strtok(NULL, ".");
	}

	Version v = a->versiones;
	//en vAcumulada actualizamos hasta que punto de la version llegamos para comparar
	char vAcumulada[100]="";
	for (int i = 0; i<x ;i++){
		//diferenciamos caso 0 para no poner un punto al principio
		if (i==0){
			strcpy(vAcumulada, vTok[0]);
		}else{
			strcat(vAcumulada,".");
			strcat(vAcumulada,vTok[i]);
		}

		Version aux = v;
		//busca por nivel
		while (aux != NULL && strcmp(aux->nroVersion, vAcumulada)!=0){
			aux = aux->sigVersion;
		}

		if (aux == NULL){
			return NULL;
		}

		if (i<x-1){
			v=aux->subVersion;
		}else{
			return aux;
		}
	}
	return NULL;
}


unsigned int cantLineas(Archivo a, char* version) {
	unsigned int contador = 0;
	Version v = encontrarVersion(a,version);
	if (v==NULL)
		return -1;

	Linea aux = v->contenido;
	while(aux != NULL) {
		if (strcmp(aux->estado, "BL")!=0)
			contador++;
		aux = aux->sig;
	}
	return contador;
}


//procedimiento auxiliar para pasar int a char
void numAChar(int num, char* resultado){
	int temp = num;
	int len = 0;
	while (temp > 0) {
		len++;
		temp /= 10;
	}

	for (int i = len - 1; i >= 0; i--) {
		resultado[i] = num % 10 + '0';
		num /= 10;
	}

	resultado[len] = '\0';
}

//procedimiento para actualizar el numero de subvesiones cuando se elimina una version
void actualizarSubarbolResta(Version v, char* prefijo){
		if (v==NULL)
			return;

		Version actual = v;
		while (actual!=NULL){
			int largo = strlen(actual->nroVersion);
			int posUltimoPunto = -1;

			for (int i = 0; i<largo;i++){
				if (actual->nroVersion[i]=='.'){
					posUltimoPunto=i;
				}
			}

			int numero;
			if (posUltimoPunto==-1)
				numero = atoi(actual->nroVersion);
			else
				numero = atoi(actual->nroVersion + posUltimoPunto+1);

			numero = numero - 1;

			if (numero < 1)
				numero = 1;

			char sufijo[10];
			numAChar(numero, sufijo);

			char nuevaVersion[50];
			nuevaVersion[0]='\0';
			strcpy(nuevaVersion,prefijo);
			strcat(nuevaVersion, sufijo);

			strcpy(actual->nroVersion, nuevaVersion);

			if (actual->subVersion != NULL){
				char nuevoPrefijo[50];
				strcpy(nuevoPrefijo,nuevaVersion);
				strcat(nuevoPrefijo, ".");
				actualizarSubarbolResta(actual->subVersion, nuevoPrefijo);
			}
			actual = actual->sigVersion;
		}
}


//procedimiento que actualiza las versiones del subarbol cuando se inserta una version en el medio
void actualizarSubarbolSuma(Version v, char* prefijo) {
	if (v == NULL) return;

	strcpy(v->nroVersion, prefijo);

	Version hijo = v->subVersion;
	int contador = 1;

	while (hijo != NULL) {
		char nuevoPrefijo[50];
		char sufijo[10];
		numAChar(contador, sufijo);

		strcpy(nuevoPrefijo, prefijo);
		strcat(nuevoPrefijo, ".");
		strcat(nuevoPrefijo, sufijo);

		actualizarSubarbolSuma(hijo, nuevoPrefijo);

		hijo = hijo->sigVersion;
		contador++;
	}
}


//procedimiento que actualiza el tronco principal de versiones +1
void actualizarNivelesSuma(Version v) {
	int contador = 1;
	Version actual = v;

	while (actual != NULL) {
		char nro[10];
		numAChar(contador, nro);

		strcpy(actual->nroVersion, nro);

		Version hijo = actual->subVersion;
		int subContador = 1;

		while (hijo != NULL) {
			char nuevoPrefijo[50];
			char sufijo[10];
			numAChar(subContador, sufijo);

			strcpy(nuevoPrefijo, nro);
			strcat(nuevoPrefijo, ".");
			strcat(nuevoPrefijo, sufijo);

			actualizarSubarbolSuma(hijo, nuevoPrefijo);

			hijo = hijo->sigVersion;
			subContador++;
		}

		actual = actual->sigVersion;
		contador++;
	}
}

//procedimiento para actualizar el tronco principal si se elimina una version
void actualizarNivelesResta(Version v){
	if (v == NULL)
		return;

	Version actual = v;
	char nuevaVersion[50];
	char sufijo[10];

	while (actual != NULL){
		int numero = atoi(actual->nroVersion);
		numero = numero - 1;

		if (numero < 1)
			numero = 1;

		numAChar(numero, sufijo);
		strcpy(nuevaVersion, sufijo);
		strcpy(actual->nroVersion, nuevaVersion);

		if (actual->subVersion != NULL) {
			char nuevoPrefijo[50];
			strcpy(nuevoPrefijo, nuevaVersion);
			strcat(nuevoPrefijo, ".");
			actualizarSubarbolResta(actual->subVersion, nuevoPrefijo);
		}

		actual = actual->sigVersion;
	}
}

//muestra true  si el contenido de dos versiones son exactamente iguales (ignora las de estado borrado)
TipoRet Iguales(Archivo a, char* version1, char* version2, bool &iguales){
	Version v1 = encontrarVersion(a,version1);
	Version v2 = encontrarVersion(a,version2);

	if (v1==NULL || v2==NULL){
		return ERROR;
	}

	Linea l1 =v1->contenido;
	Linea l2 = v2->contenido;
	iguales = true;

	while (l1 != NULL || l2 != NULL){
		while (l1 != NULL && strcmp(l1->estado,"BL")==0)
			l1 = l1->sig;
		while (l2 != NULL && strcmp(l2->estado, "BL") == 0)
			l2 = l2->sig;

		if ((l1 == NULL && l2 != NULL) || (l1 != NULL && l2 == NULL)) {
			iguales = false;
			cout << "iguales tiene valor false"<<endl;
			return OK;
		}

		//si las dos terminaron al mismo tiempo, son iguales de tamanio
		if (l1 == NULL && l2 == NULL)
			break;

		//comparo texto si ambas tienen estado IL o H
		if (strcmp(l1->texto, l2->texto) != 0) {
			iguales = false;
			cout << "iguales tiene valor false"<<endl;
			return OK;
		}

		l1 = l1->sig;
		l2 = l2->sig;
	}
	cout<<"iguales tiene el valor true"<<endl;
	return OK;
}

//muestra el estado del contenido  y si cambio o no
TipoRet MostrarCambios(Archivo a, char* version){
	Version v = encontrarVersion(a, version);
	if (v==NULL){
		return ERROR;
	}
	cout << "Curriculum.txt - "<< version<<endl;
	if (v->contenido == NULL){
		cout << "No se realizaron modificaciones"<<endl;
		return OK;
	}

	Historial h = v->cambios;

	while (h!=NULL) {
		if (strcmp(h->estado, "IL") == 0) {
			cout << "IL\t" << h->nroInsercion << "\t" << h->texto << endl;
		}
		else if (strcmp(h->estado, "BL") == 0) {
			cout << "BL\t" << h->nroEliminacion << endl;
		}

		h = h->sig;
	}

	return OK;
}



void eliminarSubarbol(Version v) {
		if (v == NULL) return;

		Version sig = v->sigVersion;
		Version sub = v->subVersion;

		// Romper conexiones para evitar bucles
		v->sigVersion = NULL;
		v->subVersion = NULL;

		eliminarSubarbol(sub);
		eliminarSubarbol(sig);

		Linea actual = v->contenido;
		while (actual != NULL) {
			Linea siguiente = actual->sig;
			delete[] actual->texto;
			delete[] actual->estado;
			delete actual;
			actual = siguiente;
		}

		if (v->nroVersion !=NULL)
			delete[] v->nroVersion;
		delete v;
	}


TipoRet BorrarVersion(Archivo &a, char* version){
	if (a==NULL || a->versiones == NULL)
		return ERROR;

	Version v = encontrarVersion(a,version);

	if (v == NULL){
		return ERROR;
	}

	Version padre = v->versionPadre;

	//si es parte del tronco principal
	if (padre == NULL){
		//si es el primero
		if (a->versiones == v){
			a->versiones = v->sigVersion;
		}else{
			Version anterior = a->versiones;
			while (anterior->sigVersion!=NULL && anterior->sigVersion != v){
				anterior = anterior->sigVersion;
			}
			if (anterior->sigVersion == v){
				anterior->sigVersion = v->sigVersion;
			}
		}

		if (v->sigVersion!=NULL)
			actualizarNivelesResta(v->sigVersion);
		v->versionPadre = NULL;
		v->sigVersion = NULL;
		v->subVersion = NULL;
		eliminarSubarbol(v);
		return OK;
	}

	Version primerHijo = padre->subVersion;
	if (primerHijo == v){
		padre->subVersion = v->sigVersion;
	}else{
		Version anterior = primerHijo;
		while (anterior->sigVersion!=NULL && anterior->sigVersion != v){
			anterior = anterior->sigVersion;
		}
		if (anterior->sigVersion == v){
			anterior->sigVersion = v->sigVersion;
		}
	}
	if (v->sigVersion != NULL) {
		char prefijo[50];
		strcpy(prefijo, padre->nroVersion);
		strcat(prefijo, ".");
		actualizarSubarbolResta(v->sigVersion, prefijo);
	}

	if (v->versionPadre != NULL)
		v->versionPadre = NULL;
	if (v->sigVersion != NULL)
		v->sigVersion = NULL;
	if (v->subVersion != NULL)
		v->subVersion = NULL;

	eliminarSubarbol(v);
	return OK;
}

void actualizarLineas(Archivo &a, char* version) {
	Version v = encontrarVersion(a,version);
	if (v == NULL)
		return;

	Linea aux = v->contenido;
	unsigned int nL = 1;
	while (aux != NULL) {
		if (strcmp(aux->estado,"BL")!=0 ){
			aux->nroLinea = nL++;
		}
		aux = aux->sig;
	}
}

TipoRet InsertarLinea(Archivo &a, char * version, char * linea, unsigned int nroLinea) {
	if (nroLinea == 0) {
		return ERROR;
	}

	Version v = encontrarVersion(a,version);
	if (v == NULL || v->subVersion != NULL|| nroLinea > cantLineas(a,version)+1)
		return ERROR;

	Historial h = new _historial;
	h->nroInsercion = nroLinea;
	h->nroEliminacion = 0;
	strcpy(h->texto, linea);
	strcpy(h->estado, "IL");
	h->sig = NULL;

	if (v->cambios == NULL)
		v->cambios = h;
	else {
		Historial aux = v->cambios;
		while (aux->sig != NULL) aux = aux->sig;
		aux->sig = h;
	}

	//creo la linea
	Linea l = new _linea;
	strcpy(l->texto, linea);
	strcpy(l->estado, "IL");
	l->sig = NULL;

	//inserta al principio
	if (nroLinea == 1) {
		l->sig = v->contenido;
		v->contenido = l;
		actualizarLineas(a,version);
		return  OK;
	}

	//el for recorre la lista hasta encontrar la posicion de nroLinea
	// linea anterior es para no perder la lista al insertar en el medio
	Linea anterior = v->contenido;

	for (unsigned int i = 1; i < nroLinea - 1; i++) {
		if (anterior->sig != NULL)
			anterior = anterior->sig;
		else
			break;
	}

	// Insertar la línea
	l->sig = anterior->sig;
	anterior->sig = l;

	actualizarLineas(a, version);
	return OK;
}

void copiarContenido(Archivo a, Version nuevaVersion) {
	Version padre = nuevaVersion->versionPadre;

	Linea lPadre = padre->contenido;
	Linea lHijo = NULL;
	Linea ultimo = NULL;

	while (lPadre != NULL) {

		Linea nueva = new _linea;

		strcpy(nueva->texto, lPadre->texto);
		nueva->nroLinea = lPadre->nroLinea;

		// estado pasa a decir que son heredadas
		strcpy(nueva->estado, "H");

		nueva->sig = NULL;

		if (lHijo == NULL) {
			lHijo = nueva;
		} else {
			ultimo->sig = nueva;
		}

		ultimo = nueva;
		lPadre = lPadre->sig;
	}

	nuevaVersion->contenido = lHijo;
}

TipoRet CrearVersion(Archivo &a, char* version){
	Version nuevaVersion = new _version;
	nuevaVersion->nroVersion = new char[50];
	strcpy(nuevaVersion->nroVersion, version);
	nuevaVersion->versionPadre = NULL;
	nuevaVersion->subVersion = NULL;
	nuevaVersion->sigVersion = NULL;
	nuevaVersion->contenido = NULL;
	nuevaVersion->cambios = NULL;

	//si es la primera version a insertar
	if (a->versiones == NULL){
		a->versiones = nuevaVersion;
		return OK;
	}

	int largo = strlen(version);
	int posUltimoPunto = -1;

	//encuentro ultimo punto
	for (int i = 0;i<largo;i++){
		if (version[i] == '.'){
			posUltimoPunto = i;
		}
	}

	Cadena prefijo = new char[50];
	Cadena sufijo = new char[50];

	int i;

	for (i=0;i<posUltimoPunto;i++){
		prefijo[i]=version[i];
	}
	prefijo[i] = '\0';
	int p = 0;
	for (i=posUltimoPunto+1; i<largo;i++){
		sufijo[p++]=version[i];
	}
	sufijo[p]= '\0';

	Version aux = encontrarVersion(a,version);

	//si no esta
	if (aux == NULL){
		//si el numero esta solito ej 1 o 2
		if (posUltimoPunto == -1) {
			nuevaVersion->versionPadre = NULL;
			nuevaVersion->subVersion = NULL;
			nuevaVersion->sigVersion = NULL;

			Version aux = a->versiones;
			int cantHermanos = 1;
			while (aux->sigVersion != NULL) {
				cantHermanos++;
				aux = aux->sigVersion;
			}

			if (atoi(version) > cantHermanos + 1) {
				delete[] nuevaVersion->nroVersion;
				delete nuevaVersion;
				return ERROR;
			}

			aux->sigVersion = nuevaVersion;
			return OK;
		}

		//si el numero no esta solito ej 1.1.3
		//busco al padre ej 1.1
		aux = encontrarVersion(a, prefijo);

		//si no tiene padre error
		if (aux == NULL){
			return ERROR;
		}

		//si es el primer hijo
		if (aux->subVersion == NULL){
			if (strcmp(sufijo,"1")!=0)
				return ERROR;
			nuevaVersion->versionPadre = aux;
			if (aux->contenido !=NULL)
				copiarContenido(a, nuevaVersion);
			aux->subVersion = nuevaVersion;
			return OK;
		}

		//si no es el primer hijo
		int cantHermanos = 1;
		Version hermano = aux->subVersion;


		while (hermano->sigVersion != NULL) {
			cantHermanos++;
			hermano = hermano->sigVersion;
		}

		if (atoi(sufijo) > cantHermanos + 1) {
			delete nuevaVersion;
			return ERROR;
		}

		hermano->sigVersion = nuevaVersion;
		nuevaVersion->versionPadre = aux;
		if (aux->contenido !=NULL)
			copiarContenido(a, nuevaVersion);
		return OK;
	}

	//si ya esta
	if (aux != NULL){
		Version padre = aux->versionPadre;
		//si no tiene padre es que es el numero solito
		if (padre == NULL){
			Version raiz = a->versiones;

			//si es el hijo mayor
			if (strcmp(raiz->nroVersion, version)==0){
				if (strcmp(sufijo,"1")!=0)
					return ERROR;
				nuevaVersion->sigVersion = raiz;
				a->versiones = nuevaVersion;
			}else{
				Version anterior = raiz;
				while(anterior->sigVersion != NULL && strcmp(anterior->sigVersion->nroVersion,version)!=0){
					anterior=anterior->sigVersion;
				}
				nuevaVersion->sigVersion = anterior->sigVersion;
				anterior->sigVersion = nuevaVersion;
			}
			actualizarNivelesSuma(a->versiones);
			return OK;
		}

		// si tiene padre es subversion duplicada
		Version primerHijo = padre->subVersion;
		//si es hijo mayor:
		if (strcmp(primerHijo->nroVersion, version)==0){
			if (strcmp(sufijo,"1")!=0)
				return ERROR;
			nuevaVersion->sigVersion=primerHijo;
			padre->subVersion = nuevaVersion;
		}else{
			Version anterior = primerHijo;
			while(anterior->sigVersion != NULL && strcmp(anterior->sigVersion->nroVersion,version)!=0){
				anterior = anterior->sigVersion;
			}
			nuevaVersion->sigVersion = anterior->sigVersion;
			anterior->sigVersion = nuevaVersion;
		}
		actualizarSubarbolSuma(padre, padre->nroVersion);
		nuevaVersion->versionPadre = padre;
		if (nuevaVersion->versionPadre->contenido !=NULL)
			copiarContenido(a,nuevaVersion);
		return OK;
	}
	return OK;
}


void muestroVersiones(Version v, int espacio = 0) {
	if (v == NULL)
		return;

	if (v->nroVersion==NULL)
		return;
	cout << setfill(' ') << setw(espacio * 4 + strlen(v->nroVersion)) << v->nroVersion << endl;
	muestroVersiones(v->subVersion, espacio + 1);
	muestroVersiones(v->sigVersion, espacio);
}


TipoRet MostrarVersiones(Archivo a){
	Version v = a->versiones;
	cout << "curriculum.txt"<<endl;
	if (v==NULL){
		cout << "No hay versiones creadas"<<endl;
		return OK;
	}

	muestroVersiones(v);
	return OK;
}


Archivo CrearArchivo(char * nombre){
	Archivo nuevoArchivo = new _archivo;
	strcpy(nuevoArchivo->titulo, nombre);
	nuevoArchivo -> versiones = NULL;
	nuevoArchivo -> sig = NULL;

	cout << "Titulo: "<< nuevoArchivo->titulo << endl;
	cout<<"Atencion: no poner espacios entre los argumentos"<<endl;
	cout<<"Para ver la lista de argumentos escriba ayuda"<<endl;
	return nuevoArchivo;
}
TipoRet BorrarArchivo(Archivo &a){
	if (a==NULL)
		return ERROR;
	eliminarSubarbol(a->versiones);
	delete a;
	a = NULL;
	return OK;
}

TipoRet BorrarLinea(Archivo &a, char * version, unsigned int nroLinea) {

	Version v = encontrarVersion(a, version);
	if (v == NULL || v->subVersion != NULL)
		return ERROR;

	// recorro las líneas visibles para encontrar la posición real
	Linea aux = v->contenido;
	unsigned int visible = 1;

	while (aux != NULL) {
		if (strcmp(aux->estado, "BL") != 0) {
			if (visible == nroLinea) {
				Historial h = new _historial;
				h->nroInsercion = 0;
				h->nroEliminacion = nroLinea;
				strcpy(h->estado, "BL");
				h->texto[0] = '\0';
				h->sig = NULL;

				if (v->cambios == NULL)
					v->cambios = h;
				else {
					Historial hAux = v->cambios;
					while (hAux->sig != NULL)
						hAux = hAux->sig;
					hAux->sig = h;
				}


				strcpy(aux->estado, "BL");
				actualizarLineas(a, version);
				return OK;
			}
			visible++;
		}
		aux = aux->sig;
	}

	return ERROR;
}

TipoRet MostrarTexto(Archivo a, char * version) {
	Version v = encontrarVersion(a, version);

	if (v==NULL)
		return ERROR;

	cout<<"curriculum.txt - "<<v->nroVersion<<endl;

	Linea aux = v->contenido;

	if (aux==NULL) {
		cout << "No contiene lineas"<<endl;
		return OK;
	}

	while (aux != NULL) {
		if (strcmp(aux->estado, "BL")!=0)
			cout << aux->nroLinea << '\t' << aux->texto << endl;
		aux = aux->sig;
	}
	return OK;
}


void help() {
	cout << "Comandos:" << endl;
	cout << "CrearVersion(a,\"version\")"<< endl;
	cout << "MostrarVersiones(a)"<< endl;
	cout << "BorrarVersion(a,\"version\")"<< endl;
	cout << "InsertarLinea(a,\"version\",\"texto\",nroLinea)"<< endl;
	cout << "BorrarLinea(a,\"version\", nroLinea)"<< endl;
	cout << "MostrarTexto(a,\"version\")"<< endl;
	cout << "MostrarCambios(a,\"version\")"<< endl;
	cout << "Iguales(a,\"version1\",\"version2\",iguales)"<< endl;

	cout << "limpiar" << endl;
	cout << "salir"<< endl;
}
