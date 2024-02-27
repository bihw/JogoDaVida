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
    int size, rank, j;

    MPI_Status status;

    if (MPI_Init(&argc, &argv) != MPI_SUCCESS){
        printf("Erro: MPI_Init \n");
        exit(1);
    }

    MPI_Comm_size(MPI_COMM_WORLD, &size); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0){
        if (argc != 1){
            printf("Erro: numero de argumentos.\n");
            exit(1);
        }

        if (N % size != 0){  // 
            printf("Erro: dimensao da matriz nao divisivel pelo numero de processos.\n");
            exit(1);
        }
    }

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

    if (rank == 0){
       printf("Estado inicial: ");
       printTabuleiro(tabuleiro);
    }

    int rowsPerProcess = N / size;

    int *tabLocal = (int *)malloc((rowsPerProcess + 2) * N * sizeof(int));

    for (int ger = 0; ger < GEN; ger++){
        if (size != 1){
            int entrada_1[N], entrada_2[N];
            int enviar_1[N], enviar_2[N];

            MPI_Scatter(tabuleiro, CELLS / size, MPI_INT, tabLocal + N, CELLS / size, MPI_INT, 0, MPI_COMM_WORLD);

            if (rank % 2 == 0){
                for (int i = 0; i < N; i++)
                    enviar_1[i] = tabLocal[i + N];
                MPI_Ssend(&enviar_1, N, MPI_INT, mod(rank - 1, size), 1, MPI_COMM_WORLD);

                for (int i = 0; i < N; i++)
                    enviar_2[i] = tabLocal[(N * rowsPerProcess) + i];
                MPI_Ssend(&enviar_2, N, MPI_INT, mod(rank + 1, size), 1, MPI_COMM_WORLD);
            } else {
                MPI_Recv(&entrada_2, N, MPI_INT, mod(rank + 1, size), 1, MPI_COMM_WORLD, &status);
                MPI_Recv(&entrada_1, N, MPI_INT, mod(rank - 1, size), 1, MPI_COMM_WORLD, &status);
            }
            if (rank % 2 == 0){
                MPI_Recv(&entrada_2, N, MPI_INT, mod(rank + 1, size), 1, MPI_COMM_WORLD, &status);
                MPI_Recv(&entrada_1, N, MPI_INT, mod(rank - 1, size), 1, MPI_COMM_WORLD, &status);
            } else {
                for (int i = 0; i < N; i++)
                    enviar_1[i] = tabLocal[i + N];
                MPI_Ssend(&enviar_1, N, MPI_INT, mod(rank - 1, size), 1, MPI_COMM_WORLD);

                for (int i = 0; i < N; i++)
                    enviar_2[i] = tabLocal[(N * rowsPerProcess) + i];
                MPI_Ssend(&enviar_2, N, MPI_INT, mod(rank + 1, size), 1, MPI_COMM_WORLD);
            }
            for (int i = 0; i < N; i++){
                tabLocal[i] = entrada_1[i];
                tabLocal[(N * (rowsPerProcess + 1)) + i] = entrada_2[i];
            }
        } else {
            for (int i = 0; i < N; i++)
                tabLocal[i + CELLS + N] = tabuleiro[i];
            for (int i = CELLS; i < CELLS + N; i++)
                tabLocal[i - CELLS] = tabuleiro[i - N];
        }

        int * nextGen = (int *)malloc(N * rowsPerProcess * sizeof(int));

        for (int k = N; k < N * (rowsPerProcess + 1); k++){
            int r = k / N;  // linha atual
            int c = k % N;  // coluna atual
            int totalRows = N * rowsPerProcess + 2;  // total de linhas no tabuleiro local
            int prevR = mod(r - 1, totalRows);
            int prevC = mod(c - 1, N);
            int nextR = mod(r + 1, totalRows);
            int nextC = mod(c + 1, N);

            // Conta os vizinhos vivos
            int livingN = tabLocal[prevR * N + prevC] + tabLocal[prevR * N + c] + tabLocal[prevR * N + nextC] + tabLocal[r * N + prevC] +
                 tabLocal[r * N + nextC] + tabLocal[nextR * N + prevC] + tabLocal[nextR * N + c] + tabLocal[nextR * N + nextC]; 
            if (tabLocal[k] == 1){
                if (livingN < 2)
                    nextGen[k - N] = 0; // morre de solidao
                else if (livingN > 3)
                    nextGen[k - N] = 0; // morre de superpopulacao
                else
                    nextGen[k - N] = 1; 
            } else {
                if (livingN == 3)
                    nextGen[k - N] = 1; // morta ressuscita
                else
                    nextGen[k - N] = 0; 
            }
        }

        j = 0;
        for (int i = rank * (CELLS / size); i < (rank + 1) * (CELLS / size); i++){
            tabuleiro[i] = nextGen[j];
            j++;
        }
        MPI_Gather(nextGen, N * rowsPerProcess, MPI_INT, &tabuleiro, N * rowsPerProcess, MPI_INT, 0, MPI_COMM_WORLD);

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