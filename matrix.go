/* --------------------------------------------------------------------------------------

Obj do Fonte : Algoritimo paralelo de multiplicação matricial em Go (Utilizando goroutines)
Disciplina   : PDP 2013/II UFRGS PPGC (Prf. Cláudio Geyer) 
Data         : 27/11/2013
Autor        : Raffael Bottoli Schemmer

--------------------------------------------------------------------------------------- */

// Nome do pacote (Dado pela função principal)
package main

// Bibliotecas utilizadas
// fmt para realizar as chamadas de print a tela.
// runtime para definir o número máximo de threads que as chamadas (Go - Goroutines) devem executar
// sync para utilizar a estrutura mutex.lock e mutex.unlock.
import (
"fmt"
"runtime"
"sync"
)

const TAM = 1024
// Constante que define o tamanho da matriz.
// Esse valor pode ser parametrizável seguindo as restrições:
// #1 - Apenas valores base 2 são aceitos Ex:(2/4/8/16/32/64) não existindo restrição de tamanho.
// #2 - As matrizes serão sempre quadráticas, no sentido que TAM define tanto o número de linhas como de colunas.

const numCores = 4
// Constante que define o número de threads que irão multiplicar a matriz.
// Esse valor pode ser parametrizável seguindo as restrições:
// #1 - Apenas valores base 2 são aceitos Ex:(1/2/4/8/16/32/64) não existindo restrição de tamanho.
// #2 - O valor 1, refere-se a uma execução sequencial, em que uma thread independente é criada, bloqueando a função main.
// #3 - Obrigatóriamente para este caso, é necessário que o tamanho da matriz (TAM) seja pelo menos igual ao número de threads (numCores) definido (Para que cada thread tenha pelo menos uma linha da matriz para cálcular).

// Declaração das matrizes (Totalmente feita de maneira estática)
var A [TAM][TAM]uint64
var B [TAM][TAM]uint64
var C [TAM][TAM]uint64

// Declaração da variável mutex e da variável inteira finish usada como região de memória compartilhada.
var mutex = &sync.Mutex{}
var finish int;

// Função que cálcula a multiplicação de um conjunto de linhas da matriz (No caso sequencial, uma thread irá processar todas as linhas da matriz).
func matrix(index uint64) {

	// Variáveis temporárias usadas para o cálculo da multiplicação.
	var lin uint64;
	var col uint64;
	var cont uint64;
	var numElements uint64;
	
	// Inicialização das variáveis temporárias.
	lin = 0
	col = 0
	cont = 0
	numElements = 0
	
	// Número de linhas a serem computadas, calculado pela divisão do número de linhas pelo número de threads.
	numElements = TAM/numCores;
	
	// Estruturas de repetição (for) que calculam a multiplicação das linhas da matriz A pelas colunas da matriz B, armazenando os resultados na matriz C.	
	lin = index * numElements
	for lin < (index * numElements)+numElements {
		col = 0;
		for col < TAM {
			cont = 0;
			for cont < TAM {
				C[lin][col] = C[lin][col] +  (A[lin][cont] *  B[cont][col]);
				cont++;
			}
			col++;
		}
		lin++;
	}
	
	// Condição que se a thread for a última a ser chamada (numCores-1), deverá bloquear o mutex e mudar o estado da variável finish para 1 (indicando a função main o término da multiplicação matricial).
	if(index == numCores-1){
		mutex.Lock();
		finish = 1;
		mutex.Unlock();
	}
}

// Função de depuração que mostra na saída padrão (usando a função Print declarada no pacote fmt) o conteúdo das matrizes A, B e C. Devido a resolução do monitor, apenas matrizes de ordem de 4 a 8 linhas são fáceis de visualizar o conteúdo na tela.
func show_matrix() {

	var lin uint64;
	lin=0;
	var col uint64;
	col=0;
	for (lin < TAM) {
		fmt.Print("[ ")
	
		col=0;
		for(col < TAM) {
			fmt.Print(A[lin][col]);
			fmt.Print(" ");
			col++
		}
		fmt.Print("] ")
	
		fmt.Print("  X  [ ");
	
		col=0;
		for(col < TAM) {
			fmt.Print(B[lin][col]);
			fmt.Print(" ");
			col++
		}
		fmt.Print("] ")
	
	
		fmt.Print("  =  [ ");
		col=0;
		for(col < TAM) {
			fmt.Print(C[lin][col]);
			fmt.Print(" ");
			col++
		}
		fmt.Print("]");
		fmt.Println();
		lin++;
	}
}

func main() {

	// Define a GOMAXPROCS que as estruturas goroutines (go) deverão executar até no máximo numCores threads (Número de threads definidas).
    runtime.GOMAXPROCS(numCores)
	
	// Variáveis temporárias
	var i uint64;
	var j uint64;
	var lin uint64;
	var col uint64;
	
	//  Inicialização das variáveis temporárias
	i = 0;
    j = (TAM*TAM)-1
    lin = 0
    col = 0
    
    // Inicialização de valores para as matrizes A, B e C. A irá receber valores incrementados de um em um a partir de zero, B valores decrementados da multiplicação (TAM*TAM), referente ao maior indice da matriz de um em um, e C, o valor zero.
	for i < (TAM*TAM) {
		A[lin][col] = i;
		B[lin][col] = j;
		C[lin][col] = 0;
	
		if col == TAM-1 {
			col = 0;
			lin++;
		} else {
			col++;
		}
		
		i++;
		j--;
	}
	
	// Chamada das estruturas goroutines (go) em que a cada chamada, uma nova thread será criada. Cada thread irá executar um número de linhas da matriz, de maneira paralela.
	i=0;
	for(i < numCores) {
		go matrix(i);
		i++
	}
	
	// Condição que mantem a função main bloqueada a condição de finish, até que a última thread modifique o valor, permitindo que a função saia do for e termine sua execução. A variável mutex é utilizada para garantir a exclusão mutua de finish, uma vez que duas threads podem acessar essa variável ao mesmo tempo.
	mutex.Lock();
	for(finish == 0){
		mutex.Unlock();
		mutex.Lock();
	}
	
	// Descomentar a chamada desta função para visualizar a saída da multiplicação (Lembrando que o tempo de execução é aumentando expressivamente ao descomentar esta função).
	//show_matrix();
}
