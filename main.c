// Incluye las bibliotecas necesarias para manejar entrada/salida y memoria dinámica
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define una estructura para representar un Proyecto con dos campos: sroi y costos
typedef struct {
    int sroi;
    int costos;
} Proyectos;

// Declara las funciones que serán definidas más adelante
int leer_archivo(const char *nombrearchivo, Proyectos **proyecto, int *n, int *presupuesto_max);
void imprimir_proyectos_seleccionados(int mejor_conjunto, Proyectos *proyecto, int n);
long long Solucion(Proyectos *proyecto, int n, int presupuesto_max);
// int Solucion(Proyectos *proyecto, int n, int presupuesto_max);

int main(int argc, char *argv[]){
    Proyectos *proyecto = 0;             // Puntero para los proyectos que será asignado después de leer el archivo
    int n;                              // Número de proyectos
    int presupuesto_max;                // Presupuesto máximo disponible
    int mejor_conjunto;                 // Representa el conjunto óptimo de proyectos a seleccionar

    // Verifica que el número correcto de argumentos ha sido pasado (nombre del programa + nombre del archivo)
    if (argc != 2) {
        printf("Uso correcto: %s <nombre_del_archivo>\n", argv[0]);
        return 1;
    }

    // Intenta leer el archivo. Si hay un error, libera la memoria y termina
    if (!leer_archivo(argv[1], &proyecto, &n, &presupuesto_max)) {
        printf("Error al abrir el archivo.\n");
        free(proyecto);
        return 1;
    }

    clock_t inicio = clock();      // Obtenemos el inicio del tiempo
    // Encuentra la mejor combinación de proyectos
    mejor_conjunto = Solucion(proyecto, n, presupuesto_max);
    clock_t final = clock();       // Obtenemos el final del tiempo
    double tiempo_ejecucion = (double)(final - inicio) / CLOCKS_PER_SEC;  // Calculamos el tiempo de ejecucion

    // Imprime los proyectos seleccionados en la mejor combinación
    printf("\nSeleccionamos al mejor proyecto:\n");
    imprimir_proyectos_seleccionados(mejor_conjunto, proyecto, n);
    printf("Tiempo de ejecucion: %f segundos\n", tiempo_ejecucion); //Imprimimos el tiempo de ejecucion
    

    // Libera la memoria asignada para los proyectos
    free(proyecto);
    return 0;
}

// Función para leer el archivo y cargar la información de los proyectos
int leer_archivo(const char *nombrearchivo, Proyectos **proyecto, int *n, int *presupuesto_max) {
    FILE *archivo = fopen(nombrearchivo, "r");
    if (!archivo) return 0;  // Si hay un error al abrir el archivo, retorna 0

    // Intenta obtener el número de proyectos y el presupuesto máximo del nombre del archivo
    sscanf(nombrearchivo, "knapPI_%d_%d.txt", n, presupuesto_max);
    
    // Asigna memoria para los proyectos
    *proyecto = (Proyectos*)malloc(sizeof(Proyectos) * (*n));

    // Lee la información de cada proyecto y la almacena
    for (int i = 0; i < *n; i++) {
        fscanf(archivo, "%d %d", &(*proyecto)[i].sroi, &(*proyecto)[i].costos);
    }

    fclose(archivo);  // Cierra el archivo
    return 1;  // Retorna 1 indicando que la lectura fue exitosa
}

// Función para imprimir los proyectos seleccionados
void imprimir_proyectos_seleccionados(int mejor_conjunto, Proyectos *proyecto, int n) {
    int costo_total = 0;
    int sroi_total = 0;

    // Itera sobre todos los proyectos
    for (int j = 0; j < n; j++) {
        // Verifica si el proyecto j está en el conjunto seleccionado
        if (mejor_conjunto & (1 << j)) {
            printf("Proyecto %d con SROI %d y costo %d\n", j + 1, proyecto[j].sroi, proyecto[j].costos);
            sroi_total += proyecto[j].sroi;      // Acumula el sroi
            costo_total += proyecto[j].costos;   // Acumula el costo
        }
    }
    printf("\nTotal SROI: %d\nTotal Costos: %d\n", sroi_total, costo_total);  // Imprime los totales
}

long long Solucion(Proyectos *proyecto, int n, int presupuesto_max) {
    long long subconjuntos = 1LL << n;  // 2^n subconjuntos posibles
    int maximo_sroi = 0;  // Almacena el máximo sroi encontrado
    long long mejor_conjunto = 0;  // Almacena el mejor conjunto de proyectos

    // Itera sobre todos los subconjuntos posibles
    for (long long i = 0; i < subconjuntos; i++) {
        int sroi_actual = 0;
        int costo_actual = 0;

        // Verifica qué proyectos están en el subconjunto i
        for (int j = 0; j < n; j++) {
            if (i & (1LL << j)) {
                sroi_actual += proyecto[j].sroi;      // Acumula el sroi del proyecto j
                costo_actual += proyecto[j].costos;   // Acumula el costo del proyecto j
            }
        }

        // Si el costo total no supera el presupuesto y el sroi es el máximo encontrado, actualiza el mejor conjunto
        if (costo_actual <= presupuesto_max && sroi_actual > maximo_sroi) {
            maximo_sroi = sroi_actual;
            mejor_conjunto = i;
        }
    }
    return mejor_conjunto;  // Retorna el mejor conjunto encontrado
}







// // Función que encuentra la mejor combinación de proyectos
// int Solucion(Proyectos *proyecto, int n, int presupuesto_max) {
//     int subconjuntos = 1 << n;      // 2^n subconjuntos posibles
//     int maximo_sroi = 0;            // Almacena el máximo sroi encontrado
//     int mejor_conjunto = 0;         // Almacena el mejor conjunto de proyectos

//     // Itera sobre todos los subconjuntos posibles
//     for (int i = 0; i < subconjuntos; i++) {
//         int sroi_actual = 0;
//         int costo_actual = 0;

//         // Verifica qué proyectos están en el subconjunto i
//         for (int j = 0; j < n; j++) {
//             if (i & (1 << j)) {
//                 sroi_actual += proyecto[j].sroi;      // Acumula el sroi del proyecto j
//                 costo_actual += proyecto[j].costos;   // Acumula el costo del proyecto j
//             }
//         }

//         // Si el costo total no supera el presupuesto y el sroi es el máximo encontrado, actualiza el mejor conjunto
//         if (costo_actual <= presupuesto_max && sroi_actual > maximo_sroi) {
//             maximo_sroi = sroi_actual;
//             mejor_conjunto = i;
//         }
//     }
//     return mejor_conjunto;  // Retorna el mejor conjunto encontrado
// }
















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









