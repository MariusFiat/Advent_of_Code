#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

FILE* openFile(char* File){
    FILE* f = fopen(File, "r");
    if(!f){
        fprintf(stderr, "The file couldn't be opened!\n");
        exit(-1);
    }
    return f;
}

void colseFile(FILE* f){
    if(fclose(f) != 0){
        fprintf(stderr, "Error at file closing!\n");
        exit(-1);
    }
}

void search_floor(char* fileName){
    FILE* file = openFile(fileName);
    int ch;
    int floor = 0;
    int position = 0;
    bool found = false;

    while((ch = fgetc(file)) != EOF){
        if(ch == '('){
            floor++;
        }
        else floor--;
        
        if(!found){
            position++;
            if(floor == -1){
                found = true;
            }
        }
    }

    printf("Final floor number: %d\n", floor);
    printf("First basement character: %d\n", position);
    colseFile(file);
}

int main(void){
    search_floor("input_test.txt");
    return 0;
}
