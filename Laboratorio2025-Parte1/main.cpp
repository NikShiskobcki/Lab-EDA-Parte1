#include<iostream>

#include "estructuras.h"
#include "prototipos.h"
using namespace std;

int main (int argc, char *argv[]) {
	Archivo a = CrearArchivo("curriculo.txt");
	cout << a->titulo;
	
	
	return 0;
}

