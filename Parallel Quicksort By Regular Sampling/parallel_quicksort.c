#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int generate_random_number(int);
void init_integer_list(int* integer_list, int list_size);

int main(int argc, char* argv[]){

	int list_size = 0;				// Numero de elementos a serem ordenados
	int proc_num = 0;				// Numero de processos a serem utilizados
	int proc_list_quota = 0;		// Numero de elementos sobre qual cada processo ira trabalhar
	int* integer_list = NULL;		// Lista de elementos a serem ordenados

	// Leitura do tamanho da Lista
	scanf("%d", &list_size);
	integer_list = (int*) malloc(list_size * sizeof(int));

	srand(time(NULL));
	init_integer_list(integer_list, list_size);

	for(int i = 0; i < list_size; i++){
		if(i%10 == 0 && i != 0){
			printf("%d\n", integer_list[i]);
		}
		else{
			printf("%d\t", integer_list[i]);
		}
	}

	printf("\n");

	if(integer_list != NULL){
		free(integer_list);
	}

	return 0;
}

/*
	----- Implementação das Funções utilizadas pelo programa -----
*/

/* 
	return a random number between 0 and limit inclusive.
 */
int generate_random_number(int limit) {
    int divisor = RAND_MAX/(limit+1);
    int retval;

    do { 
        retval = rand() / divisor;
    } while (retval > limit);

    return retval;
}

/*

*/
void init_integer_list(int* integer_list, int list_size){
	for(int i = 0; i < list_size; i++){
		integer_list[i] = generate_random_number(list_size-1);
	}	
}

