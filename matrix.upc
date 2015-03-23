/* --------------------------------------------------------------------------------------

Obj do Fonte : Algoritimo paralelo de multiplicação matricial em UPC.
Disciplina   : PDP 2013/II UFRGS PPGC (Prf. Cláudio Geyer) 
Data         : 27/11/2013
Autor        : Raffael Bottoli Schemmer

--------------------------------------------------------------------------------------- */

// Bibliotecas utilizadas
#include <upc_relaxed.h> // upc_barrier (Barreira para sincronizar o término de execução das threads).
#include <stdio.h> // Entrada e saída (printf)

#define TAM 1024
// Constante que define o tamanho da matriz.
// Esse valor pode ser parametrizável seguindo as restrições:
// #1 - Apenas valores base 2 são aceitos Ex:(2/4/8/16/32/64) não existindo restrição de tamanho.
// #2 - As matrizes serão sempre quadráticas, no sentido que TAM define tanto o número de linhas como de colunas.

// Declaração das matrizes (Parte estática (TAM), Parte dinâmica (Dentro da função main)). A condição shared define que as matrizes são totalmente compartilhadas pelas threads.
shared unsigned long int A[TAM][TAM];
shared unsigned long int B[TAM][TAM];
shared unsigned long int C[TAM][TAM];

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

int main()
{
    // Variáveis temporárias
    unsigned long int lin=0,col=0;
	unsigned long int i=0,j=0,cont=0;
	int numElements=0;
	
	numElements = TAM/THREADS; // Número de linhas a serem computadas, calculado pela divisão do número de linhas pelo número de threads(THREADS).
	
	// Inicialização de valores para as matrizes A, B e C. A irá receber valores incrementados de um em um a partir de zero, B valores decrementados da multiplicação (TAM*TAM), referente ao maior indice da matriz de um em um, e C, o valor zero. MYTHREAD define o ID da thread que irá inicializar parte das matrizes (Usado como indice para calcular quais linhas deverão ser inicializadas).	
	for(i = MYTHREAD * numElements,cont=0; i < (MYTHREAD * numElements)+numElements;i++)
	{
		for(j = 0; j < TAM;j++,cont++)
		{
			A[i][j] = cont;
			B[i][j] = cont;
			C[i][j] = 0;
		}	
		
		if(col == TAM-1)
		{
			col = 0;
			lin++;
		}
		else col++;		
	}
    
	// Estruturas de repetição (for) que calculam a multiplicação das linhas da matriz A pelas colunas da matriz B, armazenando os resultados na matriz C. MYTHREAD define o ID da thread que irá executar a multiplicação (Usado como indice para calcular quais linhas a matriz deverá multiplicar).	
    for (lin = MYTHREAD * numElements; lin < (MYTHREAD * numElements)+numElements; lin++)
	{
		for (col = 0; col < TAM; col++)
		{
			for (cont = 0; cont < TAM; cont++)
			{
				C[lin][col] = C[lin][col] +  (A[lin][cont] *  B[cont][col]);
			}
		}
	}
	
	// Barreira utilizada para sincronizar a execução de todas as threads (Deve ser usada em todos os programas feitos em linguagem UPC).
    upc_barrier;
    
	// Descomentar a chamada desta função para visualizar a saída da multiplicação (Lembrando que o tempo de execução é aumentando expressivamente ao descomentar esta função). Apenas a primeira thread irá mostrar os dados da tela (Sem esta condição cada thread iria realizar a chamada desta função).
    //if(MYTHREAD == 0) show_matrix();
    
    return 0;
}
