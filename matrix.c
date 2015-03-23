/* --------------------------------------------------------------------------------------

Obj do Fonte : Algoritimo paralelo de multiplicação matricial em C (Utilizando Pthreads)
Disciplina   : PDP 2013/II UFRGS PPGC (Prf. Cláudio Geyer) 
Data         : 27/11/2013
Autor        : Raffael Bottoli Schemmer

--------------------------------------------------------------------------------------- */

// Bibliotecas utilizadas
#include<stdio.h> // Entrada e saída (printf)
#include<stdlib.h> // Alocação de memória (Malloc)
#include <pthread.h> // Criação e sincronização das threads (pthread_create / pthread/join)

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

// Função que cálcula a multiplicação de um conjunto de linhas da matriz (No caso sequencial, uma thread irá processar todas as linhas da matriz).
void* matrix(void* arg)
{
	unsigned long int lin = 0,col = 0,cont;
	unsigned long int numElements;
	int *index = (int *) &arg;  // Conversão do parametro da função, que indica o número da thread.
			
	numElements = TAM/numCores; // Número de linhas a serem computadas, calculado pela divisão do número de linhas pelo número de threads.
	
	// Estruturas de repetição (for) que calculam a multiplicação das linhas da matriz A pelas colunas da matriz B, armazenando os resultados na matriz C.	
	for (lin = *index * numElements; lin < (*index * numElements)+numElements; lin++)
	{
		for (col = 0; col < TAM; col++)
		{
			for (cont = 0; cont < TAM; cont++)
			{
				C[lin][col] = C[lin][col] +  (A[lin][cont] *  B[cont][col]);
			}
		}
	}
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
			printf("%d ",A[lin][col]);
		}
		printf("]");
		
		printf("  X  [ ");
		for(col=0;col < TAM;col++)
		{
			printf("%d ",B[lin][col]);
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
	unsigned long int i=0,j=0;
	unsigned long int lin=0,col=0;
	unsigned long int cont;
	
	pthread_t *thWork;
	int **index;
	
	// Alocação dinâmica das matrizes.
	A = malloc((sizeof *A) * TAM);
	B = malloc((sizeof *B) * TAM);
	C = malloc((sizeof *C) * TAM);
	
	// Inicialização de valores para as matrizes A, B e C. A irá receber valores incrementados de um em um a partir de zero, B valores decrementados da multiplicação (TAM*TAM), referente ao maior indice da matriz de um em um, e C, o valor zero.
	for(i=0,j=(TAM*TAM)-1; i < TAM*TAM; i++,j--)
	{
		A[lin][col] = i;
		B[lin][col] = j;
		C[lin][col] = 0;
	
		if(col == TAM-1)
		{
			col = 0;
			lin++;
		}
		else col++;		
	}
	
	// Alocação de memória e criação das threads conforme o número de threads definidos na variável numCores. A função pthread_join é chamada após o for, no objetivo de segurar a execução da função main, até que a última thread (i--) seja executada (O que indica o término da execução da multiplicação matricial).
	thWork = (pthread_t*)  malloc (sizeof(pthread_t) * numCores);
	for(i=0,cont=0; i < numCores; i++)
	{
		int **index = i;
		cont = pthread_create(&thWork[i], NULL, matrix,(void*)index);			
	}
	i--;
	pthread_join(thWork[i],(void **)&cont);
	
	// Descomentar a chamada desta função para visualizar a saída da multiplicação (Lembrando que o tempo de execução é aumentando expressivamente ao descomentar esta função).
	//show_matrix();
	
	return(0);
}


