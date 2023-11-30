#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int* makeArrayOfCalories(char* File, int* counter){
    int* array = NULL;

    FILE* f = fopen(File, "r");
    if(!f){
        fprintf(stderr, "Error at file opening!\n");
        exit(-1);
    }

    char line[100];
    int sum = 0;

    while(true){
        if(fgets(line, 100, f) == NULL){
            break;
        }
        else
        {  
            if(line[0] != '\n'){
                //printf("%s", line);
                sum += atoi(line);
            }
            else
            {
                array = realloc(array, ((*counter)+ 1) * sizeof(int));
                if(!array){
                    fprintf(stderr, "Insufficient memory!\n");
                    exit(-1);
                }
                array[(*counter)++] = sum;
                sum = 0;
            }
            
        }
    }

    if(fclose(f) != 0){
        fprintf(stderr, "The file couldn't be closed\n");
        exit(-1);
    }
    return array;
}

int printMaxValue(int array[], const int size){ //First part + second; 
    int max = array[0], imax = 0;
    for(int i = 1; i < size; i++){
        if(array[i] > max){
            max = array[i];
            imax = i;
        }
    }
    array[imax] = 0;
    return max;
}

void printArray(const int array[], const int size){
    for(int i = 0; i < size; i++){
        printf("%d\n", array[i]);
    }
}

int main(void){
    int counter = 0;
    char File[10]= "in.txt";
    int* array = makeArrayOfCalories(File, &counter);
    //printArray(array, counter);
    
    //De fiecare daca cand gasesc cel mai mare numar de calorii, il salvez intr-un numar aditional si il sterg din array pentru a [..]
    //[..] putea cauta mai usor si pe urmatoarele;
    int max1 = printMaxValue(array, counter);
    int max2 = printMaxValue(array, counter);
    int max3 = printMaxValue(array, counter);
    printf("%d\n", max1);
    printf("%d\n", max1 + max2 + max3);

    free(array);
    return 0;
}