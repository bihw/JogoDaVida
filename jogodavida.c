#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define GEN 200  // numero de geracoes
#define N 12    // dimensão da matriz
#define CELLS N*N   // numero de celulas do tabuleiro
#define ANSI_COLOR_GREEN "\e[0;32m"
#define ANSI_COLOR_RESET "\x1b[0m"

void printTabuleiro(int tabuleiro[CELLS]);
int mod(int a, int b);

int main(int argc, char **argv){
    // INICIANDO TABULEIRO:
    
    /*// Para valores "aleatórios":
    int tabuleiro[CELLS];
    srand(time(NULL)); 
    for (int i = 0; i < N; i++){
        tabuleiro[i] = rand() % 2; // inicializa a matriz com valores "aleatórios" 0 ou 1
    }*/
    
    // Para dois planadores/gliders
    int tabuleiro[CELLS] = {
        0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,1,1,1,0,0,0,0,0,
        0,0,0,0,1,0,0,0,0,0,0,0,
        0,0,0,0,0,1,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,1,1,1,
        0,0,0,0,0,0,0,0,0,1,0,0,
        0,0,0,0,0,0,0,0,0,0,1,0
    };

    int size, rank, j;

    if (argc != 1){
        printf("Erro: numero de argumentos \n");
        exit(1);
    }

    MPI_Status status;

    if (MPI_Init(&argc, &argv) != MPI_SUCCESS){
        printf("Erro: MPI_Init \n");
    }

    MPI_Comm_size(MPI_COMM_WORLD, &size); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0){
       printf("Estado inicial: ");
       printTabuleiro(tabuleiro);
    }

    // Cálculo do número de linhas atribuídas a cada processo
    int rowsPerProcess = N / size;
    int extraRows = N % size;   
    int rows = (rank < extraRows) ? rowsPerProcess + 1 : rowsPerProcess;
    int start = rank * rowsPerProcess + ((rank < extraRows) ? rank : extraRows);

    int *tabLocal = (int *)malloc((rows + 2) * N * sizeof(int));
    
    if (rank == 0){
        for (int dest = 1; dest < size; dest++){
            int startIndex = dest * rowsPerProcess + ((dest < extraRows) ? dest : extraRows);
            MPI_Send(&tabuleiro[startIndex * N], rowsPerProcess * N, MPI_INT, dest, 0, MPI_COMM_WORLD);
        }
        memcpy(&tabLocal[N], &tabuleiro[start * N], rows * N * sizeof(int));
    } else {
        MPI_Recv(&tabLocal[N], rows * N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    MPI_Bcast(tabLocal, (rows + 2) * N, MPI_INT, 0, MPI_COMM_WORLD);

    for (int ger = 0; ger < GEN; ger++){
        j = N;
        for (int i = rank * (CELLS / size); i < (rank + 1) * (CELLS / size); i++){
            tabLocal[j] = tabuleiro[i];
            j++;
        }

        if (size != 1){
            int incoming_1[N];
            int incoming_2[N];
            int send_1[N];
            int send_2[N];
            if (rank % 2 == 0){
                for (int i = 0; i < N; i++)
                    send_1[i] = tabLocal[i + N];
                MPI_Ssend(&send_1, N, MPI_INT, mod(rank - 1, size), 1, MPI_COMM_WORLD);

                for (int i = 0; i < N; i++)
                    send_2[i] = tabLocal[(N * rowsPerProcess) + i];
                MPI_Ssend(&send_2, N, MPI_INT, mod(rank + 1, size), 1, MPI_COMM_WORLD);
            } else {
                MPI_Recv(&incoming_2, N, MPI_INT, mod(rank + 1, size), 1, MPI_COMM_WORLD, &status);
                MPI_Recv(&incoming_1, N, MPI_INT, mod(rank - 1, size), 1, MPI_COMM_WORLD, &status);
            }
            if (rank % 2 == 0){
                MPI_Recv(&incoming_2, N, MPI_INT, mod(rank + 1, size), 1, MPI_COMM_WORLD, &status);
                MPI_Recv(&incoming_1, N, MPI_INT, mod(rank - 1, size), 1, MPI_COMM_WORLD, &status);
            } else {
                for (int i = 0; i < N; i++)
                    send_1[i] = tabLocal[i + N];
                MPI_Ssend(&send_1, N, MPI_INT, mod(rank - 1, size), 1, MPI_COMM_WORLD);

                for (int i = 0; i < N; i++)
                    send_2[i] = tabLocal[(N * rowsPerProcess) + i];
                MPI_Ssend(&send_2, N, MPI_INT, mod(rank + 1, size), 1, MPI_COMM_WORLD);
            }
            for (int i = 0; i < N; i++){
                tabLocal[i] = incoming_1[i];
                tabLocal[(N * (rowsPerProcess + 1)) + i] = incoming_2[i];
            }
        } else {
            for (int i = 0; i < N; i++)
                tabLocal[i + CELLS + N] = tabuleiro[i];
            for (int i = CELLS; i < CELLS + N; i++)
                tabLocal[i - CELLS] = tabuleiro[i - N];
        }

        int *final = (int *)malloc(N * rows * sizeof(int));

        for (int k = N; k < N * (rows + 1); k++){
            int r = k / N;  // linha atual
            int c = k % N;  // coluna atual
            int totalRows = N * rows + 2;  // Total de linhas no tabuleiro local

            int prevR = mod(r - 1, totalRows);
            int prevC = mod(c - 1, N);
            int nextR = mod(r + 1, totalRows);
            int nextC = mod(c + 1, N);

            int livingN = tabLocal[prevR * N + prevC] + tabLocal[prevR * N + c] + tabLocal[prevR * N + nextC] + tabLocal[r * N + prevC] +
                 tabLocal[r * N + nextC] + tabLocal[nextR * N + prevC] + tabLocal[nextR * N + c] + tabLocal[nextR * N + nextC];
            if (tabLocal[k] == 1){
                if (livingN < 2)
                    final[k - N] = 0; // morre de solidao
                else if (livingN > 3)
                    final[k - N] = 0; // morre de superpopulacao
                else
                    final[k - N] = 1; // continua viva
            } else {
                if (livingN == 3)
                    final[k - N] = 1; // morta ressuscita
                else
                    final[k - N] = 0;
            }
        }

        j = 0;
        for (int i = rank * (CELLS / size); i < (rank + 1) * (CELLS / size); i++){
            tabuleiro[i] = final[j];
            j++;
        }
        MPI_Gather(final, N * rowsPerProcess, MPI_INT, &tabuleiro, N * rowsPerProcess, MPI_INT, 0, MPI_COMM_WORLD);

        if (rank == 0){
            printf("\nGeracao %d: ", ger+1);
            printTabuleiro(tabuleiro);
        }
    }

    free(tabLocal);
    MPI_Finalize(); 

    return 0;
}

void printTabuleiro(int tabuleiro[CELLS]){
    for (int i = 0; i < CELLS; i++){
        if (i % N == 0) 
            printf("\n");

        // printf("%d ", tabuleiro[i]);
        
        // para escrever as celulas vivas em verde
        if (tabuleiro[i] == 1)
            printf(ANSI_COLOR_GREEN "1 " ANSI_COLOR_RESET);
        else
            printf("0 ");
    }
    printf("\n");
}

int mod(int a, int b){
    int r = a % b;
    return r < 0 ? r + b : r;
}