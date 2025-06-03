#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;
    int valor;

    // Inicializar entorno MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // ID del proceso
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Número total de procesos

    if (rank == 0) {
        valor = 100;
        MPI_Send(&valor, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Proceso %d envió el valor %d al proceso 1\n", rank, valor);
    } else if (rank == 1) {
        MPI_Recv(&valor, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Proceso %d recibió el valor %d del proceso 0\n", rank, valor);
    }

    // Finalizar entorno MPI
    MPI_Finalize();
    return 0;
}
