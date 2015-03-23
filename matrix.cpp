/* --------------------------------------------------------------------------------------

Obj do Fonte : Algoritimo paralelo de multiplicação matricial em Cilk (Utilizando cilk_for)
Disciplina   : PDP 2013/II UFRGS PPGC (Prf. Cláudio Geyer) 
Data         : 27/11/2013
Autor        : Raffael Bottoli Schemmer

--------------------------------------------------------------------------------------- */

// Bibliotecas utilizadas
#include<stdio.h> // Entrada e saída (printf)
 
#define TAM 1024
// Constante que define o tamanho da matriz.
// Esse valor pode ser parametrizável seguindo as restrições:
// #1 - Apenas valores base 2 são aceitos Ex:(2/4/8/16/32/64) não existindo restrição de tamanho.
// #2 - As matrizes serão sempre quadráticas, no sentido que TAM define tanto o número de linhas como de colunas.

// Declaração das matrizes (Totalmente feita de maneira estática)
unsigned long int A[TAM][TAM];
unsigned long int B[TAM][TAM];
unsigned long int C[TAM][TAM];

// Função de depuração que mostra na saída padrão (usando a função Print declarada no pacote fmt) o conteúdo das matrizes A, B e C. Devido a resolução do monitor, apenas matrizes de ordem de 4 a 8 linhas são fáceis de visualizar o conteúdo na tela.
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

// Diferente das demais casos, cilk obriga que a função main seja chamada de cilk_main
int cilk_main()
{
	// Variáveis temporárias
	unsigned long int lin=0,col=0;
	unsigned long int i=0,j=0;

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
	
	// Bloco responsável por realizar a execução paralela da multiplicação das linhas das matrizes. Cilk permite através da estrutura cilk_for, que todas as chamadas internas a esta estrutura, sejam encapsuladas em threads que irão processar as TAM linhas em N threads (Definidas durante a chamada do programa via passagem de parametros.)
	cilk_for (int il = 0; il < TAM; ++il)
    {
        for (int jl = 0; jl < TAM; ++jl)
        {
            for (int k = 0; k < TAM; ++k)
            {
                C[il][jl] += A[il][k] * B[k][jl];
            }
        }
    }
	
	// Descomentar a chamada desta função para visualizar a saída da multiplicação (Lembrando que o tempo de execução é aumentando expressivamente ao descomentar esta função).
	//show_matrix();
	
    return 0;
}
