#ifndef PROTOTIPOS_H
#define PROTOTIPOS_H


void muestroRetorno(TipoRet retorno);
TipoRet creoA(Archivo &a);
TipoRet borroA(Archivo &a);
TipoRet inserto(Archivo &a, Cadena parametros[]);
TipoRet borroL(Archivo &a, Cadena parametros[]);
TipoRet muestroT(Archivo a, Cadena parametros[]);

Archivo CrearArchivo(char * nombre);
TipoRet BorrarArchivo(Archivo &a);
TipoRet InsertarLinea(Archivo &a, char * version, char * linea, unsigned int nroLinea);
TipoRet BorrarLinea(Archivo &a, char * version, unsigned int nroLinea);
TipoRet MostrarTexto(Archivo a, char * version);

void help();


#endif