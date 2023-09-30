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
    int mejor_conjunto = 1 << n; // sabemos cuantas combinaciones de subconjuntos de proyectos

    // recorremos el que suponemos es el mejor conjunto
    for(int i = 0; i < mejor_conjunto; i++){
        int actual_sroi;
        int actual_costos;
        for(int j = 0; j < n; j++){
            // verificamos si el proyecto j esta incluido en el subconjunto i
            if(i & (1<<j)){
                actual_sroi = actual_sroi + proyecto[j].sroi;
                actual_costos = actual_costos = proyecto[j].costos;
            }               

        }

        //preguntamos si los costos actuales son menores o iguales a los presupuestos y 
        //si el actual sroi es mayor al maximo
        if(actual_costos <= presupuesto_max && actual_sroi > *maximo_sroi){
            *maximo_sroi = actual_sroi; // actualizamos el maximo sroi
            mejor_conjunto = i;   //lo agregamos al mejor conjunto
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









