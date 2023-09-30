#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int sroi;
    int costos;
} Proyectos;

int leer_archivo(const char *nombrearchivo, Proyectos **proyecto, int *n, int *presupuesto_max);
void imprimir_proyectos_seleccionados(int mejor_conjunto, Proyectos *proyecto, int n);
int Solucion(Proyectos *proyecto, int n, int presupuesto_max);

int main() {
    char nombrearchivo[50];
    Proyectos *proyecto = 0;
    int n; 
    int presupuesto_max;
    int mejor_conjunto;

    printf("Ingresa el archivo (ejemplo: knapPI_6_500.txt): ");
    scanf("%s", nombrearchivo);

     if (!leer_archivo(nombrearchivo, &proyecto, &n, &presupuesto_max)) {
         printf("Error al abrir el archivo.\n");
         free(proyecto);
         return 1;
     }

    mejor_conjunto = Solucion(proyecto, n, presupuesto_max);

    printf("\nSeleccionamos al mejor proyecto:\n");
    imprimir_proyectos_seleccionados(mejor_conjunto, proyecto, n);

    free(proyecto);
    return 0;
}

int leer_archivo(const char *nombrearchivo, Proyectos **proyecto, int *n, int *presupuesto_max) {
    FILE *archivo = fopen(nombrearchivo, "r");
    if (!archivo) return 0;

    sscanf(nombrearchivo, "knapPI_%d_%d.txt", n, presupuesto_max);
    
    *proyecto = (Proyectos*)malloc(sizeof(Proyectos) * (*n));
    for (int i = 0; i < *n; i++) {
        fscanf(archivo, "%d %d", &(*proyecto)[i].sroi, &(*proyecto)[i].costos);
    }

    fclose(archivo);
    return 1;
}

void imprimir_proyectos_seleccionados(int mejor_conjunto, Proyectos *proyecto, int n) {
    int costo_total = 0;
    int sroi_total = 0;
    for (int j = 0; j < n; j++) {
        if (mejor_conjunto & (1 << j)) {
            printf("Proyecto %d con SROI %d y costo %d\n", j + 1, proyecto[j].sroi, proyecto[j].costos);
            sroi_total += proyecto[j].sroi;
            costo_total += proyecto[j].costos;
        }
    }
    printf("\nTotal SROI: %d\nTotal Cost: %d\n", sroi_total, costo_total);
}

int Solucion(Proyectos *proyecto, int n, int presupuesto_max) {
    int subconjuntos = 1 << n;
    int maximo_sroi = 0;
    int mejor_conjunto = 0;

    for (int i = 0; i < subconjuntos; i++) {
        int sroi_actual = 0;
        int costo_actual = 0;

        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                sroi_actual += proyecto[j].sroi;
                costo_actual += proyecto[j].costos;
            }
        }

        if (costo_actual <= presupuesto_max && sroi_actual > maximo_sroi) {
            maximo_sroi = sroi_actual;
            mejor_conjunto = i;
        }
    }
    return mejor_conjunto;
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









