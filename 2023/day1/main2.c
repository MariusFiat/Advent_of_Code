#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE_LINE 500

char* convertireDigiti(char* line){
    char* p = line;
    char line2[SIZE_LINE];
    strncpy(line2, line, SIZE_LINE);
    int nextStep = 0;
    

    while((p = strcasestr(line + nextStep, "one")) != NULL){
        nextStep = p - line;
        *(p + 1) = '1';
    }

    nextStep = 0;
    while((p = strcasestr(line + nextStep, "two")) != NULL){
        nextStep = p - line;
        *(p + 1) = '2';
    }

    nextStep = 0;
    while ((p = strcasestr(line + nextStep, "three")) != NULL)
    {
        nextStep = p - line;
        *(p + 1) = '3';
    }
    
    nextStep = 0;
    while ((p = strcasestr(line + nextStep, "four")) != NULL)
    {
        nextStep = p - line;
        *(p + 1) = '4';
    }

    nextStep = 0;
    while ((p = strcasestr(line + nextStep, "five")) != NULL)
    {
        nextStep = p - line;
        *(p + 1) = '5';
    }

    nextStep = 0;
    while ((p = strcasestr(line + nextStep, "six")) != NULL)
    {
        nextStep = p - line;
        *(p + 1) = '6';
    }

    nextStep = 0;
    while ((p = strcasestr(line + nextStep, "seven")) != NULL)
    {
        nextStep = p - line;
        *(p + 1) = '7';
    }

    nextStep = 0;
    while ((p = strcasestr(line + nextStep, "eight")) != NULL)
    {
        nextStep = p - line;
        *(p + 1) = '8';
    }

    nextStep = 0;
    while ((p = strcasestr(line + nextStep, "nine")) != NULL)
    {
        nextStep = p - line;
        *(p + 1) = '9';
    }
    return line;
}

int cautaNumar(char* line){
    int digit1 = 0;
    int digit2 = 0;

    for(int i = 0; i < strlen(line); i++){
        if(isdigit(line[i])){
            digit1 = line[i] - '0';
            break;
        }
    }

    for(int i = strlen(line) - 1; i >= 0; i--){
        if(isdigit(line[i])){
            digit2 = line[i] - '0';
            break;
        }
    }

    int numar = digit1 * 10 + digit2;
    return numar;
}

void citireDate(char* File){
    FILE* f = fopen(File, "r");
    if(!f){
        fprintf(stderr, "Eroare la deschiderea fisierului de input!\n");
        exit(-1);
    }

    char line[SIZE_LINE];
    char* line2;
    int sum = 0;
    int numar = 0;
    while(fgets(line, SIZE_LINE, f) != NULL){
        line2 = convertireDigiti(line);
        numar = cautaNumar(line2);
        sum += numar;
        printf("Linia -> %s  nuamr -> %d\n", line2, numar);
    }

    printf("Suma totala este -> %d\n", sum);
    if(fclose(f) != 0){
        fprintf(stderr, "Eroare la inchiderea fisierului de input!\n");
        exit(-1);
    }
}
int main(int argc, char* argv[]){
    if(argc != 2){
        fprintf(stderr, "Numar invalid de argumente!\n");
        exit(-1);
    }

    citireDate(argv[1]);

    return 0;
}