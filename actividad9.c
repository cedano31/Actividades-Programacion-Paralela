#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

//Gabriel Cedano 24-1242

int main(int argc, char *argv[]) {
    int rank, size;
    int N;
    float *valores_locales;
    float suma_local = 0.0, suma_total = 0.0, promedio = 0.0;

    MPI_Init(&argc, &argv);                        // Inicializa MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);          // Rank de cada proceso
    MPI_Comm_size(MPI_COMM_WORLD, &size);          // Total de procesos

    if (rank == 0) {
        printf("Ingrese la cantidad de valores por proceso (N): ");
        scanf("%d", &N);
    }

    // Broadcast del valor N a todos los procesos
    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Reservar memoria y generar valores aleatorios
    valores_locales = (float*)malloc(N * sizeof(float));
    srand(time(NULL) + rank);  // Semilla diferente por proceso

    for (int i = 0; i < N; i++) {
        valores_locales[i] = (float)(rand() % 100); // valores de 0 a 99
        suma_local += valores_locales[i];
    }

    // Reduce: suma de todas las sumas locales en el proceso raíz
    MPI_Reduce(&suma_local, &suma_total, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        promedio = suma_total / (N * size);
    }

    // Broadcast del promedio a todos los procesos
    MPI_Bcast(&promedio, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);

    // Cada proceso imprime el promedio recibido
    printf("Proceso %d recibió el promedio: %.2f\n", rank, promedio);

    free(valores_locales);
    MPI_Finalize();  // Finaliza MPI
    return 0;
}
