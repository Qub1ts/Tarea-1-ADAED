#include <stdio.h>
#include <stdlib.h>

// ABRIR UN ARCHIVO EN MODO LECTURA
FILE* abrirArchivo(char *nombreFile) {
    FILE *archivo;
    archivo = fopen(nombreFile,"r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo %s\n", nombreFile);
        return NULL;
    }
    printf("El archivo %s se abre correctamente\n", nombreFile);
    return archivo;
}

int main(int argc, char* argv[]) {

    // ABRIR EL ARCHIVO
    FILE* fp = abrirArchivo(argv[1]);
    int numero_proyectos = atoi(argv[2]);

    if (fp == NULL){
        return 0;
    }
    int proyecto[numero_proyectos], costo[numero_proyectos];
    char costos[numero_proyectos][100];
    int i = 0;
    while (i < numero_proyectos) {
        fscanf(fp, "%i %s", &proyecto[i], costos[i]);
        i++;
    }

    fclose(fp);

    // Imprimir los datos leídos
    for (i = 0; i < numero_proyectos; i++) {
        printf("Proyecto: %d, Costo: %s\n", proyecto[i], costos[i]);
    }

    return 0;
}








