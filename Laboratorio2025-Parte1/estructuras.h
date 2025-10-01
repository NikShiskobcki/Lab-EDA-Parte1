#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <string>
using namespace std;

enum _retorno{
	OK, ERROR, NO_IMPLEMENTADA
};
typedef enum _retorno TipoRet;

struct _archivo{
	string titulo;
	string version;
	string contenido;
	_archivo* sig;
};
typedef _archivo* Archivo;
#endif
