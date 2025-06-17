#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 100000000

int main()
{
    int *array = malloc(N * sizeof(int));
    for (int i = 0; i < N; i++)
    {
        array[i] = 1;
    }

    long long suma_parcial[16] = {0}; // Suponiendo máximo 16 hilos
    int hilos[] = {1, 2, 4, 8, 16};

    printf("Hilos\tTiempo (s)\tSuma\n");

    for (int h = 0; h < 5; h++)
    {
        int num_hilos = hilos[h];
        for (int i = 0; i < num_hilos; i++)
        {
            suma_parcial[i] = 0;
        }

        double start = omp_get_wtime();

#pragma omp parallel num_threads(num_hilos)
        {
            int id = omp_get_thread_num();
            int chunk_size = N / num_hilos;
            int start_idx = id * chunk_size;
            int end_idx = (id == num_hilos - 1) ? N : start_idx + chunk_size;

            long long local_sum = 0;
            for (int i = start_idx; i < end_idx; i++)
            {
                local_sum += array[i];
            }
            suma_parcial[id] = local_sum;
        }

        long long suma_total = 0;
        for (int i = 0; i < num_hilos; i++)
        {
            suma_total += suma_parcial[i];
        }

        double end = omp_get_wtime();

        printf("%d\t%.6f\t%lld\n", num_hilos, end - start, suma_total);
    }

    free(array);
    return 0;
}
