/******************************************************************************
* FILE: psrs.c
* DESCRIPTION: 
*	SCC0143 - Programação Concorrente
*	Trabalho Prático: QuickSort Concorrente em MPI (OpenMP) e OpenMP
*	Aluno: Fábio Alves Martins Pereira
*	NºUSP: 7987435
* AUTHOR: Fábio Alves Martins Pereira  01/11/2016
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
	Assinatura das funções utilizadas pelo programa
*/
void printCommLineArguments(int arraySize, int numOfThreads);
int generateRandomNumber(int limit);
void initIntegerArray(int* integerArray, int arraySize);
void printIntegerArray(int* integerArray, int arraySize);
void quicksort(int* integerArray, int leftmost, int rightmost);

int main(int argc, char* argv[]) {

	srand(time(NULL));

	int arraySize = atoi(argv[1]);
	int numOfThreads = atoi(argv[2]);
	int* integerArray = (int*) malloc(arraySize * sizeof(int));
	initIntegerArray(integerArray, arraySize);
	
	//printCommLineArguments(arraySize, numOfThreads);
	quicksort(integerArray,0,arraySize-1);
	// Impressão do vetor de inteiros ordenados
	printIntegerArray(integerArray, arraySize);

	if(integerArray != NULL){
		free(integerArray);
	}

	return 0;
}

/*
	----- Implementação das Funções utilizadas pelo programa -----
*/

/*

*/
void printCommLineArguments(int arraySize, int numOfThreads){
	printf("Array Size: %d\n", arraySize);
	printf("Number of Threads: %d\n", numOfThreads);
}

/* 
	return a random number between 0 and limit inclusive.
 */
int generateRandomNumber(int limit) {
    int divisor = RAND_MAX/(limit+1);
    int generatedInteger;

    do { 
        generatedInteger = rand() / divisor;
    } while (generatedInteger > limit);

    return generatedInteger;
}

/*
	Initiates an integer array with arraySize unordered integers
*/
void initIntegerArray(int* integerArray, int arraySize) {
	for(int i = 0; i < arraySize; i++){
		integerArray[i] = generateRandomNumber(arraySize-1);
	}	
}

/*
	Print integer array
*/
void printIntegerArray(int* integerArray, int arraySize) {
	for(int i = 0; i < arraySize; i++){
		if(i == arraySize-1){
			printf("%d.", integerArray[i]);
		}
		else {
			printf("%d, ", integerArray[i]);
		}
	}
}

/*
	Quicksort implementation
*/
void quicksort(int* integerArray, int leftmost, int rightmost){
    
    int chosenPivot = leftmost;
    int ch;
    int j;

    for(int i = leftmost+1; i <= rightmost; i++){        
        j = i;                      
		if(integerArray[j] < integerArray[chosenPivot]){
        	ch = integerArray[j];
         	while(j > chosenPivot){
            	integerArray[j] = integerArray[j-1];
            	j--;
         	}
         	integerArray[j] = ch;
         	chosenPivot++; 
        }  
    }

    if(chosenPivot-1 >= leftmost){              
        quicksort(integerArray,leftmost,chosenPivot-1);
    }

    if(chosenPivot+1 <= rightmost){              
        quicksort(integerArray,chosenPivot+1,rightmost);
    }
 }
