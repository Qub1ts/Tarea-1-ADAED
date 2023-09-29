#include <stdio.h>
#include <stdlib.h>

// ABRIR UN ARCHIVO EN MODO LECTURA
FILE* abrirArchivo(char *nombreFile) {
    FILE *archivo;
    archivo = fopen(nombreFile,"r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo %s\n",nombreFile);
        return NULL;
    }
    printf("El archivo %s se abre correctamente\n",nombreFile);
    return archivo;
}


int main(int argc, char* argv[]) {

    // ABRIR EL ARCHIVO
    FILE* fp = abrirArchivo(argv[1]);
    int numero_proyectos = atoi(argv[2]);

    fp = fopen(argv[1], "r");
    if(fp == NULL){
        printf("Error al abrir el archivo %s\n", argv[1]);
        return 0;
    }
        



