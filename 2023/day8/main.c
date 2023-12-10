#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "prints.h"

#define LINE_SIZE 100

char* readDirections(char* File, int* counterDirections, int* cursor){ //Function witch read directions form input file;
    FILE* f = fopen(File, "r");
    if(!f){
        fprintf(stderr, "The input file couldn't be opened!\n");
        exit(-1);
    }

    char nextDirection;
    char* arrayDirections = NULL;
    while((nextDirection = fgetc(f)) != EOF && nextDirection != '\n'){
        arrayDirections = (char*)realloc(arrayDirections, ((*counterDirections) + 1) * sizeof(char));
        if(!arrayDirections){
            fprintf(stderr, "An error occurred at newDirection reading!\n");
            exit(-1);
        }
        arrayDirections[(*counterDirections)++] = nextDirection;
    }

    *cursor = ftell(f);

    if(fclose(f) != 0){
        fprintf(stderr, "The input file couldn't be closed!\n");
        exit(-1);
    }
    return arrayDirections;
}

Data_t processLine(char* line){
    Data_t data;
    char* p = strtok(line, " ");
    strncpy(data.key, p, 4);
    p = strtok(NULL, "(");
    p = strtok(NULL, ",");
    strncpy(data.left, p, 4);
    p = strtok(NULL, ")");
    strncpy(data.right, p + 1, 4);
    return data;
}

Data_t* readData(char* File, int* counterData, const int cursor){
    FILE* f = fopen(File, "r");
    if(!f){
        fprintf(stderr, "The input file couldn't be opened!\n");
        exit(-1);
    }

    Data_t* arrayData = NULL;
    char line[LINE_SIZE];
    fseek(f, cursor, SEEK_SET);
    fgets(line, LINE_SIZE, f);

    while(fgets(line, LINE_SIZE, f) != NULL){
        arrayData = (Data_t*)realloc(arrayData, ((*counterData) + 1) * sizeof(Data_t));
        if(!arrayData){
            fprintf(stderr, "Out of memory!\n");
            exit(-1);
        }
        arrayData[(*counterData)++] = processLine(line);
    }

    if(fclose(f) != 0){
        fprintf(stderr, "The input file couldn't be closed!\n");
        exit(-1);
    }
    return arrayData;
}

Data_t nextMove(const Data_t arrayData[], const int size, const char* current){
    Data_t data;
    for(int i = 0; ; i++){
        if(strcasecmp(arrayData[i].key, current) == 0){
            data = arrayData[i];
            break;
        }
    }
    return data;
}

int move(const Data_t arrayData[], const char* arrayDirections, const int sizeDirections, const int size, const char* start){
    int numberMoves = 0, indexMoves = 0;
    char currentKey[4];
    strncpy(currentKey, start, 4);
    Data_t current;

    for(int i = 0; i < size; i++){
        if(strcmp(start, arrayData[i].key) == 0){
            current = arrayData[i];
            break;
        }
    }

    char nextDirection;

    while(currentKey[2] != 'Z'){
        nextDirection = arrayDirections[indexMoves];
        current = nextMove(arrayData, size, currentKey);
        printf("%s\n", currentKey);

        if(nextDirection == 'L'){
            strncpy(currentKey, current.left, 4);
        }
        else{
            strncpy(currentKey, current.right, 4);
        }

        if(indexMoves == sizeDirections - 1 && currentKey[2] != 'Z'){
            indexMoves = 0;
        }
        else if(currentKey[2] != 'Z')
        {
            indexMoves++;
        }
        numberMoves++;
    }

    return numberMoves;
}

void simultanlyMoves(const Data_t arrayDate[], const char* arrayDirections, const int sizeDirections, const int size){
    int sumMoves = 0;
    for(int i = 0; i < size; i++){
        if(toupper(arrayDate[i].key[2]) == 'A')
        {
            //printf("%s\n", arrayDate[i].key);
            int currentMoves =  move(arrayDate, arrayDirections, sizeDirections, size, arrayDate[i].key);
            printf("%d\n", currentMoves);
            sumMoves += currentMoves;
        }
    }
    printf("All moves -> %d\n", sumMoves);
}

int main(int argc, char* argv[]){
    if(argc != 2){
        fprintf(stderr, "Invalid arguments!\n");
        exit(-1);
    }

    int counterDirections = 0;
    int cursor = 0;
    char* arrayDirections = readDirections(argv[1], &counterDirections, &cursor);
    //printDirections(arrayDirections, counterDirections);

    int counterData = 0;
    Data_t* arrayData = readData(argv[1], &counterData, cursor);
    //printData(arrayData, counterData);

    //int numberMoves = move(arrayData, arrayDirections, counterDirections, counterData, "AAA");
    //printf("Moves -> %d\n", numberMoves);
    simultanlyMoves(arrayData, arrayDirections, counterDirections, counterData);

    free(arrayData);
    free(arrayDirections);
    return 0;
}