#ifndef LABPARTE2_PROTOTIPOS_H
#define LABPARTE2_PROTOTIPOS_H
void muestroRetorno(TipoRet retorno);
TipoRet inserto(Archivo &a, Cadena parametros[]);
TipoRet borroL(Archivo &a, Cadena parametros[]);
TipoRet muestroT(Archivo a, Cadena parametros[]);
TipoRet creoV(Archivo &a, Cadena parametros[]);
TipoRet muestroV(Archivo &a);
TipoRet borroV(Archivo &a, Cadena parametros[]);
TipoRet muestroC(Archivo a, Cadena parametros[]);
TipoRet igual(Archivo a, Cadena parametros[]);

Archivo CrearArchivo(char * nombre);
TipoRet MostrarVersiones(Archivo a);
TipoRet BorrarVersion(Archivo &a, char* version);
TipoRet BorrarArchivo(Archivo &a);
TipoRet CrearVersion(Archivo &a, char * version);
TipoRet InsertarLinea(Archivo &a, char * version, char * linea, unsigned int nroLinea);
TipoRet BorrarLinea(Archivo &a, char * version, unsigned int nroLinea);
TipoRet MostrarTexto(Archivo a, char * version);
TipoRet MostrarCambios(Archivo a, char* version);
TipoRet Iguales(Archivo a, char* version1, char* version2, bool &iguales);
void help();

#endif
