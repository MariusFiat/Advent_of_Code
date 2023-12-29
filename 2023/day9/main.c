#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define SIZE_LINE 500

void printMatrix(int** matrix, const int lines, const int columns){
    for(int i = 0; i < lines; i++){
        for(int j = 0; j < columns; j++){
            printf("%D ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("--\n");
}

void freeMatrix(int** matrix, const int size){
    for(int i= 0; i < size; i++){
        free(matrix[i]);
    }
    free(matrix);
}

int** findNextLines(int** matrix, int size, int* lines){
    bool allZero = true;
    int newLines = 1;
    for(int i = 1; i < size; i++){
        matrix = realloc(matrix, (++newLines) * sizeof(int*));
        if(!matrix){
            fprintf(stderr, "Out of memory at newLines allocation!\n");
            exit(-1);
        }

        matrix[i] = realloc(matrix[i], size * sizeof(int));
        if(!matrix){
            fprintf(stderr, "Out of memory at newLines allocation!\n");
            exit(-1);
        }

        for(int j = 0; j < size - i; j++){
            matrix[i][j] = matrix[i-1][j+1] - matrix[i-1][j];
            //printf("%d %d i,j %d, %d\n", matrix[i-1][j], matrix[i-1][j+1], i, j);
        }

        allZero = true;
        for(int j = 0; j < size - i; j++){
            if(matrix[i][j] != 0){
                allZero = false;
            }
        }
        if(allZero && i != size - 1) break;
    }
    *lines = newLines;
    return matrix;
}

int predictLastValue(int** matrix, const int lines, const int columns){
    int lastEmptyJ = columns - (lines - 1) + 1;
    int lastEmptyI = lines - 1;
    
    int currentI = lastEmptyI - 1, currentJ = lastEmptyJ;
    while(currentI > 0){
        matrix[currentI][currentJ] = matrix[currentI][currentJ-1] + matrix[currentI+1][currentJ - 1];
        currentI--;
        currentJ++;
    }

    //int lastValue = abs(matrix[0][columns-2] + matrix[0][columns-1]);
    int lastValue = matrix[0][columns - 1] + matrix[1][columns-1];
    //printf("%d %D\n", matrix[0][columns - 1], matrix[1][columns - 1]);

    return lastValue;
}

int** setMatrixToZero(int** matrix, const int size){
    for(int i = 1; i < size; i++){
        for(int j = 0; j < size; j++){
            matrix[i][j] = 0;
        }
    }
    return matrix;
}

int dataProcessing(char* line){
    char* p;
    int sizeData = 0;

    int** kindOfMatrix = malloc(1 * sizeof(int*));
    p = strtok(line, " ");

    while(p){
        kindOfMatrix[0] = realloc(kindOfMatrix[0], (sizeData + 1) * sizeof(int));
        if(!kindOfMatrix[0]){
            fprintf(stderr, "Out of memory for kindOfMatrix allocation!\n");
            exit(-1);
        }
        kindOfMatrix[0][sizeData++] = atoi(p);
        p = strtok(NULL, " \n");
    }

    int newLines = 0;

    kindOfMatrix = findNextLines(kindOfMatrix, sizeData, &newLines);
    
    int lastValue = predictLastValue(kindOfMatrix, newLines, sizeData);
    //printf("LAST %d\n", lastValue);

    //printMatrix(kindOfMatrix, newLines, sizeData);
    freeMatrix(kindOfMatrix, newLines); 
    
    return lastValue;
}

void readData(char* File){
    FILE* f = fopen(File, "r");
    if(!f){
        fprintf(stderr, "The input file couldn't be opend!\n");
        exit(-1);
    }

    int result = 0;
    char line[SIZE_LINE];
    while(fgets(line, SIZE_LINE, f) != NULL){
        result += dataProcessing(line);
    }

    if(fclose(f) != 0){
        fprintf(stderr, "The input file couldn't be closed!\n");
        exit(-1);
    }
    printf("Sum -> %d\n", result);
}

int main(int argc, char* argv[]){
    if(argc != 2){
        fprintf(stderr, "Invaid arguments!\n");
        exit(-1);
    }

    readData(argv[1]);  
    return 0;
}