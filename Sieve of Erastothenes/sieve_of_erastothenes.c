/******************************************************************************
* FILE: sieve_of_erastothenes.c
* DESCRIPTION: 
*	SCC0143 - Programação Concorrente
*	Trabalho Prático: Crivo de Erastotenes utilizando OpenMP
*	Aluno: Fábio Alves Martins Pereira
*	NºUSP: 7987435
* AUTHOR: Fábio Alves Martins Pereira  01/11/2016
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <omp.h>

// Protótipos das funções utilizadas pelo programa
void init_prime_numbers_array(bool*, int);
void print_algorithm_result(bool* , int);
void strike_prime_numbers_array_multiples(bool* ,int ,int ,int);
void find_next_prime(bool* , int* , int);

/*
	--------------------------- Main ---------------------------
*/
int main(int argc, char* argv[]) {

	// Variáveis utilizadas pelo algoritmo
	int highestNatural = 0;				// Número natural que será lido como entrada do algoritmo
	bool* primeNumbersArray = NULL;		// Lista que marca quais números menores ou iguais a 'highestNatural' são primos
	int latestPrime = -1;				// Último número primo verificado pelo algoritmo
	int numThreads = 0;					// Quantidade de threads que serão usadas

	printf("\t\t\tSSC0143 - Programacao Concorrente\n");
	printf("\t\t\tTrabalho: Crivo de Erastotenes em C utilizando OpenMP.\n");
	printf("\t\t\tAluno: Fabio Alves Martins Pereira\n");
	printf("\t\t\tNºUSP: 7987435\n");
	printf("\t\tPara utilizar o programa siga as intrucoes abaixo:\n");
	
	// Aqui o usuario pode escolher quantas threads quer utilizar para resolver o problema
	printf("Digite o numero de threads que deseja utilizar: ");
	scanf("%d", &numThreads);
	omp_set_num_threads(numThreads);

	printf("Digite o maior numero inteiro nao negativo para ser usado pelo algoritmo.\n");
	printf("O Algoritmo vai procurar todos os numeros primos menores ou igual esse numero: ");
	scanf("%d", &highestNatural);

	// Alocacao do espaco de memoria para o array que diz quais sao os numeros primos
	primeNumbersArray = (bool*) calloc (highestNatural+1, sizeof(bool));
	init_prime_numbers_array(primeNumbersArray, highestNatural);

	// Execução do algoritmo do Crivo de Erastotenes	
	while(latestPrime <= sqrt(highestNatural)) {
		/* 
			Paralelização do Algortimo seguindo a descrição do Livro: 
			Cada Thread tanto encontra o proximo primo quanto elimina os multiplos do
			'latestPrime' elevado ao quadrado 
		*/
		#pragma omp parallel num_threads(numThreads) shared(primeNumbersArray, latestPrime, highestNatural)
		{
			find_next_prime(primeNumbersArray, &latestPrime, highestNatural);
			strike_prime_numbers_array_multiples(primeNumbersArray, pow(latestPrime,2), latestPrime, highestNatural);
		}
		
	}

	// Impressao do resultado do algoritmo
	print_algorithm_result(primeNumbersArray, highestNatural);

	// Liberação do espaço de memória alocado
	if(primeNumbersArray != NULL) {
		free(primeNumbersArray);
	}

	return 0;
}

/*
	--------------------------- Funções utilizadas pelo programa ---------------------------
*/

/*
	Função: Init Prime Numbers Array (Inicializa Lista de numeros primos)
	Faz: Inicializa todos os elementos da lista de números primos como 'true'
	Parâmetros:	
		1 - primeNumbersArray: Array que armazena em cada posição [i] 'true' se [i] é primo, ou 'false' caso contrário 
		2 - arraySize: Tamanho da lista
	Saída: 
		void
*/
void init_prime_numbers_array(bool* primeNumbersArray, int arraySize) {
	for(int i = 2; i <= arraySize; i++) {
		primeNumbersArray[i] = true;
	}
}

/*
	Função: Print Algoritm Result (Imprimir o resultado do algoritmo)
	Faz: Mostra na tela quantos números primos existem menores que 'highestNatural' e também quem são eles
	Parâmetros:	
		1 - primeNumbersArray: Array que armazena em cada posição [i] 'true' se [i] é primo, ou 'false' caso contrário 
		2 - highestNatural: Número passado como entrada para o algortimo
	Saída: 
		void
*/
void print_algorithm_result(bool* primeNumbersArray, int highestNatural) {

	int primeCounter = 0;

	for(int i = 2; i <= highestNatural; i++){
		if(primeNumbersArray[i] == true)
			primeCounter++;
	}

	printf("\n\t\t\tExistem %d numeros primos menores ou iguais a %d.\n\n", primeCounter, highestNatural);
	printf("Os numeros sao:\n");

	for(int i = 2; i <= highestNatural; i++){
		if(primeNumbersArray[i] == true)
			printf("Primo: %d\n", i);
	}
}

/*
	Função: Strike Prime Numbers Array Multiples
	Faz: Marca os elementos na lista de números primos que nao sao primos como 'false'
	Parâmetros:	
		1 - primeNumbersArray: Array que armazena em cada posição [i] 'true' se [i] é primo, ou 'false' caso contrário 
		2 - startPosition: Posição da lista a partir da qual será iniciada a verificação
		3 - latestPrime: Último número primo verificado
		4 - highestNatural: Número passado como entrada para o algortimo
	Saída: 
		void
*/
void strike_prime_numbers_array_multiples(bool* primeNumbersArray, int startPosition, int latestPrime, int highestNatural) {
	for(int i = startPosition; i <= highestNatural; i++){
		if((i % latestPrime) == 0 && primeNumbersArray[i] == true) {
			primeNumbersArray[i] = false;
		}
	}
}

/*
	Função: Find Next Prime (Encontrar o proximo numero primo)
	Faz: Encontra o próximo número primo 
	Parâmetros:	
		1 - primeNumbersArray: Array que armazena em cada posição [i] 'true' se [i] é primo, ou 'false' caso contrário 
		2 - latestPrime: Último número primo verificado
		3 - highestNatural: Número passado como entrada para o algortimo
	Saída: 
		void
*/
void find_next_prime(bool* primeNumbersArray, int* latestPrime, int highestNatural) {
	if(*latestPrime == -1){
		*latestPrime = 2;
	}
	else {
		for(int i = *latestPrime; i <= highestNatural; i++){
			if(primeNumbersArray[i] == true && i != *latestPrime){
				*latestPrime = i;
				break;
			}
		}
	}
}