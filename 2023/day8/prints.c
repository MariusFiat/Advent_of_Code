#include <stdio.h>
#include <stdlib.h>

#include "prints.h"

void printDirections(const char* arrayDirections, const int size){
    for(int i = 0; i < size; i++){
        printf("%c", arrayDirections[i]);
    }
    printf("\n");
}

void printData(const Data_t arrayData[], const int size){
    for(int i = 0; i < size; i++){
        printf("%s = (%s, %s)\n", arrayData[i].key, arrayData[i].left, arrayData[i].right);
    }
}