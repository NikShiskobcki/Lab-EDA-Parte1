#include<iostream>

#include "estructuras.h"
#include "prototipos.h"
using namespace std;

int main (int argc, char *argv[]) {
    Archivo a;
    a = CrearArchivo("curriculo.txt");
    cout << a->titulo << endl;
    cout << "Version: "<< a->version << endl;

    InsertarLinea(a, "1", "Direccion: Rivera 1234", 1);
    InsertarLinea(a, "1", "Telefono: 6111111", 2);
    InsertarLinea(a, "1", "Nombre: Juan Perez", 1);

	//mostrarTexto
    Linea aux = a->contenido;
    while (aux != NULL) {
        cout << aux->nroLinea << '\t' << aux->texto << endl;
        aux = aux->sig;
    }

    return 0;
}
