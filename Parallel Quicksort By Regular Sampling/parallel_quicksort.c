#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int generate_random_number(int);

int main(int argc, char* argv[]){

	int list_size = 0;
	int* integer_list = NULL;

	scanf("%d", &list_size);

	integer_list = (int*) malloc(list_size * sizeof(int));

	srand(time(NULL));
	for(int i = 0; i < list_size; i++){
		integer_list[i] = generate_random_number(list_size-1);
	}

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