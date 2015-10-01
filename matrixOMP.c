#include<stdio.h> // Entrada e saída (printf)
#include<stdlib.h> // Alocação de memória (Malloc)
#include <omp.h> // Criação e sincronização das threads

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <sched.h>
#include <time.h>

#define TAM 1024
// Constante que define o tamanho da matriz.
// Esse valor pode ser parametrizável seguindo as restrições:
// #1 - Apenas valores base 2 são aceitos Ex:(2/4/8/16/32/64) não existindo restrição de tamanho.
// #2 - As matrizes serão sempre quadráticas, no sentido que TAM define tanto o número de linhas como de colunas.

int numCores=4;
// Constante que define o número de threads que irão multiplicar a matriz.
// Esse valor pode ser parametrizável seguindo as restrições:
// #1 - Apenas valores base 2 são aceitos Ex:(1/2/4/8/16/32/64) não existindo restrição de tamanho.
// #2 - O valor 1, refere-se a uma execução sequencial, em que uma thread independente é criada, bloqueando a função main.
// #3 - Obrigatóriamente para este caso, é necessário que o tamanho da matriz (TAM) seja pelo menos igual ao número de threads (numCores) definido (Para que cada thread tenha pelo menos uma linha da matriz para cálcular).

// Declaração das matrizes (Parte estática (TAM), Parte dinâmica (Dentro da função main))
unsigned long int(*A)[TAM];
unsigned long int(*B)[TAM];
unsigned long int(*C)[TAM];

static inline uint64_t RDTSC()
{
  unsigned int hi, lo;
  __asm__ volatile("rdtsc" : "=a" (lo), "=d" (hi));
  return ((uint64_t)hi << 32) | lo;
}

// Função de depuração que mostra na saída padrão (stdout via printf) o conteúdo das matrizes A, B e C. Devido a resolução do monitor, apenas matrizes de ordem de 4 a 8 linhas são fáceis de visualizar o conteúdo na tela.
void show_matrix()
{
	unsigned long int lin,col;
	for(lin=0;lin < TAM;lin++)
	{
		printf("[ ");
		for(col=0;col < TAM;col++)
		{
			printf("%lu ",A[lin][col]);
		}
		printf("]");
		
		printf("  X  [ ");
		for(col=0;col < TAM;col++)
		{
			printf("%lu ",B[lin][col]);
		}
		printf("]");
		
		printf("  =  [ ");
		for(col=0;col < TAM;col++)
		{
			printf("%lu ",C[lin][col]);
		}
		printf("]\n\n\n");
	}
}

int main(int argc, char **argv)
{
	unsigned long int time =0;
	unsigned long int l=0,m=0;
	unsigned long int lin=0,col=0;
	unsigned long int cont;
	
	omp_set_num_threads(numCores);
	
	unsigned long int i=0;
	// Alocação dinâmica das matrizes.
	A = malloc((sizeof *A) * TAM);
	B = malloc((sizeof *B) * TAM);
	C = malloc((sizeof *C) * TAM);

	for(l=0,m=(TAM*TAM)-1; l < TAM*TAM; l++,m--)
	{
		A[lin][col] = l;
		B[lin][col] = m;
		C[lin][col] = 0;
	
		if(col == TAM-1)
		{
			col = 0;
			lin++;
		}
		else col++;		
	}
	
	time = RDTSC();
    #pragma omp parallel for default(none) shared(A,B,C)
    for (i = 0; i < TAM; ++i)
    {
        unsigned long int j=0;
        for (j = 0; j < TAM; ++j)
	{
            unsigned long int k=0;
            for (k = 0; k < TAM; ++k)
	    {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    time = RDTSC() - time ;
    
    //show_matrix();
    printf("Exec: %lu ",time);
    
    return(0);
}
