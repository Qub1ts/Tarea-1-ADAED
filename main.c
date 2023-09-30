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

typedef struct {
        int sroi;
        int costos;
    }proyectos;

void solucion(proyectos proyecto[], int n, int presupuesto_max, int *mejor_conjunto, int *maximo_sroi){
    int total_conjuntos = 1 << n; // Sabemos cuantas combinaciones de subconjuntos de proyectos

    *maximo_sroi = 0; // inicializamos el valor maximo de sroi a 0

    // Recorremos todos los conjuntos posibles
    for(int i = 0; i < total_conjuntos; i++){
        int actual_sroi = 0;
        int actual_costos = 0;
        for(int j = 0; j < n; j++){
            // Verificamos si el proyecto j esta incluido en el subconjunto i
            if(i & (1 << j)){
                actual_sroi += proyecto[j].sroi;
                actual_costos += proyecto[j].costos;
            }               
        }

        // Preguntamos si los costos actuales son menores o iguales al presupuesto y 
        // si el actual sroi es mayor al maximo
        if(actual_costos <= presupuesto_max && actual_sroi > *maximo_sroi){
            *maximo_sroi = actual_sroi; // actualizamos el maximo sroi
            *mejor_conjunto = i;   // lo asignamos como el mejor conjunto
        }
    }
}










    // int i, numero_proyecto = atoi(argv[2]);

    // int proyectos[numero_proyecto];
    // int costos[numero_proyecto];

    // i = 0;
    // while(i < numero_proyecto){
    //     fscanf(fp, "%i %i", &proyectos[i], &costos[i]);
    //     i++;
    // }
    // fclose(fp);


    // //Mostrar en consola lo que contiene el archivo txt
    // i = 0;
    // while(i < numero_proyecto){
    //     printf("%i %i\n", proyectos[i], costos[i]);
    //     i++;
    // }
    // return 0;









