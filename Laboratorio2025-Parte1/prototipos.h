#ifndef PROTOTIPOS_H
#define PROTOTIPOS_H

Archivo CrearArchivo(char * nombre);
TipoRet BorrarVersion(Archivo &a, char * version);
TipoRet InsertarLinea(Archivo &a, char * version, char * linea, unsigned int nroLinea);
TipoRet BorrarLinea(Archivo &a, char * version, unsigned int nroLinea);
//mostrarTexto

#endif
