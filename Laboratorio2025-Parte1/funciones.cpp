#include "estructuras.h"

#include <string>
using namespace std;

Archivo CrearArchivo(char * nombre){
	Archivo nuevoArchivo = new _archivo;
	nuevoArchivo -> titulo = nombre;
	nuevoArchivo -> version = '1';
	nuevoArchivo -> sig = NULL;
	return nuevoArchivo;
}
	
TipoRet BorrarVersion(Archivo &a, char * version){
	
}
	
