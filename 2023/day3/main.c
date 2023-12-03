#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

void printLinii(char** lines, const int lineIndex){
    for(int i = 0; i < lineIndex; i++){
        printf("%s", lines[i]);
    }
}

bool cautaInStanga(char** allLines, const int linieCurenta, const int coloanaCurenta){
    if(coloanaCurenta == 0){
        return false;
    }

    if(isalnum(allLines[linieCurenta][coloanaCurenta - 1]) == 0 && allLines[linieCurenta][coloanaCurenta - 1] != '.'){
        return true;
    }
    return false;
}

bool cautaSimbol(char** allLines, const int numarLinii, const int numarColoane, const int linieCurenta, const int coloanaCurenta, const int numarDigiti){
    bool stanga = false, dreapta = false, sus = false, jos = false;
    //Caut in stanga;
    if(coloanaCurenta != 0){
        if(isalnum(allLines[linieCurenta][coloanaCurenta - 1]) == 0 && allLines[linieCurenta][coloanaCurenta - 1] != '.')
        {
            stanga = true;
        }
    }

    //Caut deasupra cu tot cu colturile diagonale;
    if(linieCurenta != 0){
        if(coloanaCurenta == 0){ //Am grija sa vad daca am element in diagonala stanga sus;
            for(int i = 0; i < numarDigiti + 1; i++){ //Aici parcurg caracterele de deasupra numarului plus unu la stnga sus si dreapta sus mai mult, diagonalele;
                if(isalnum(allLines[linieCurenta - 1][coloanaCurenta + i]) == 0 && allLines[linieCurenta - 1][coloanaCurenta + i] != '.')
                {
                    sus = true;
                }
            }
        }
        else if(coloanaCurenta == numarColoane - numarDigiti - 1){ //Am grija sa vad daca am element in diagonala drepata sus;
            for(int i = 0; i < numarDigiti + 1; i++){ //Aici parcurg caracterele de deasupra numarului plus unu la stnga sus si dreapta sus mai mult, diagonalele;
                if(isalnum(allLines[linieCurenta - 1][coloanaCurenta + i - 1]) == 0 && allLines[linieCurenta - 1][coloanaCurenta + i - 1] != '.')
                {
                    sus = true;
                }
            }
        }
        else
        {
            for(int i = 0; i < numarDigiti + 2; i++){ //Aici parcurg caracterele de deasupra numarului plus unu la stnga sus si dreapta sus mai mult, diagonalele;
                if(isalnum(allLines[linieCurenta - 1][coloanaCurenta + i - 1]) == 0 && allLines[linieCurenta - 1][coloanaCurenta + i - 1] != '.')
                {
                    sus = true;
                }
            }
        }
    }

    //Caut in dreapta;
    if(coloanaCurenta != numarColoane - 1 - numarDigiti){
        if(isalnum(allLines[linieCurenta][coloanaCurenta + numarDigiti]) == 0 && allLines[linieCurenta][coloanaCurenta + numarDigiti] != '.'){
            dreapta = true;
        }
    }
    
    //Caut sub;
    if(linieCurenta != numarLinii - 1){ //Pot cauta doar daca mai am o linie sub linia in functie de care vreau sa caut;
        if(coloanaCurenta == 0){ //Am grija sa vad daca am element in diagonala stanga jos;
            for(int i = 0; i < numarDigiti + 1; i++){
                if(isalnum(allLines[linieCurenta + 1][coloanaCurenta + i]) == 0 && allLines[linieCurenta + 1][coloanaCurenta + i] != '.')
                {
                    jos = true;
                }
            }
        }
        else if(coloanaCurenta == numarColoane - numarDigiti - 1){
            for(int i= 0; i < numarDigiti + 1; i++){
                if(isalnum(allLines[linieCurenta + 1][coloanaCurenta + i - 1]) == 0 && allLines[linieCurenta + 1][coloanaCurenta + i - 1] != '.')
                {
                    jos = true;
                }
            }
        }
        else
        {
            for(int i = 0; i < numarDigiti + 2; i++){
                if(isalnum(allLines[linieCurenta + 1][coloanaCurenta + i - 1]) == 0 && allLines[linieCurenta + 1][coloanaCurenta + i - 1] != '.')
                {
                    jos = true;
                }
            }
        }
    }
    return stanga || dreapta || sus || jos;
}

int numarCifre(int numar){
    int numarCifre = 0;
    while(numar){
        numar = numar/10;
        numarCifre++;
    }
    return numarCifre;
}

void suprascriereDigiti(char** allLines, const int numarLinie, const int numarColoana, const int numarDigiti)
{
    for(int i = 0; i < numarDigiti; i++){
        allLines[numarLinie][numarColoana + i] = '.';
    }
}

int realizareSuma(char** allLines, const int lineIndex, const int columnIndex){
    int suma = 0;
    int valoare = 0;
    int numarDigiti = 0;

    for(int i = 0; i < lineIndex; i++){
        for(int j = 0; j < columnIndex; j++){
            numarDigiti = 0;

            if(isdigit(allLines[i][j]))
            {
                valoare = atoi(allLines[i] + j);
                numarDigiti = numarCifre(valoare);
                if(cautaSimbol(allLines, lineIndex, columnIndex, i, j, numarDigiti))
                {
                    suma += valoare;
                    //printf("L -> %d C -> %d\n", i, j);
                }
                suprascriereDigiti(allLines, i, j, numarDigiti);
            }   
        }
    }
    return suma;
}

void citireDate(char* File){
    FILE* f = fopen(File, "r");
    if(!f){
        fprintf(stderr, "Eroare la deschiderea fisierului de input!\n");
        exit(-1);
    }

    char line[500];
    char** allLines = NULL;
    int lineIndex = 0;

    while(fgets(line, 500, f) != NULL){
        allLines = (char**)realloc(allLines, (lineIndex + 1) * sizeof(char*));
        if(allLines == NULL){
            fprintf(stderr, "Eroare la alocarea memoriei unei noi linii!\n");
            exit(-1);
        }
        allLines[lineIndex] = (char*)realloc(allLines[lineIndex], sizeof(char) * strlen(line));
        strncpy(allLines[lineIndex++], line, strlen(line));
    }

    int suma = realizareSuma(allLines, lineIndex, strlen(allLines[0]));
    printf("Suma este -> %d\n", suma);

    //printLinii(allLines, lineIndex);
    if(fclose(f) != 0){
        fprintf(stderr, "Eroare la inchiderea fisierului de input!\n");
        exit(-1);
    }
}


int main(int argc, char* argv[]){
    if(argc != 2){
        fprintf(stderr, "Numar de argumente invalid!\n");
        exit(-1);
    }

    citireDate(argv[1]);

    return 0;
}