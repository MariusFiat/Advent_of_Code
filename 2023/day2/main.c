#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED 12
#define GREEN 13
#define BLUE 14

//Deci in fisierul de date, elfu baga mana si scoate niste cuburi, fiecare runda e separata de ;, intr-un joc poate baga [..]
//[..] mana de mai multe ori;
int prelucrareDate(char* line, int* respecta){ //? Parametrul respecta va fi setat 1 daca respecta valorile cerute cuburile si pe 0 daca nu;
    char *p = NULL, line2[100],*p2 = NULL;
    int sumRed = 0, sumGreen = 0, sumBlue = 0, gameIndex = 0, valoare = 0;
    char *l1 = line, *l2 = NULL;

    p = strtok_r(line, " ", &l1); //Aici elimin cuvantul Game;
    p = strtok_r(NULL, ":", &l1); //Aici scot indexul jocului;
    gameIndex = atoi(p);

    //? Acum trebuie sa stai cat timp am capuri, inca nu stiu exact cate am;
    p = strtok_r(NULL, ";", &l1); //? p taie fiecare secventa in care elful baga mana;
    while(p){
        sumRed = 0; sumGreen = 0; sumBlue = 0; //La fiecare secventa, le setez la 0;

        strncpy(line2, p, 99);
        line2[strlen(line2)] = ','; //? Adaug virgula la finalul fiecarei secvente in care baga mana pentru a facilita taierea;
        l2 = line2;

        p2 = strtok_r(line2, ",", &l2); //? p2 taie fiecare pereche de cuburi din secventa;
        while(p2 != NULL){
            valoare = atoi(p2);

            if(strcasestr(p2, "red") != NULL)  //! strcasestr cauta un sir in sirul sursa fara sa tina cont de marimea literelor;
            {
                sumRed += valoare;
            }
            else if(strcasestr(p2, "green") != NULL)
            {
                sumGreen += valoare;
            }
            else if(strcasestr(p2, "blue") != NULL)
            {
                sumBlue += valoare;
            }
            p2 = strtok_r(NULL, ",", &l2);
        }

        if(sumRed > RED || sumGreen > GREEN || sumBlue > BLUE){
            *respecta = 0;
            return -1;
        }
        p = strtok_r(NULL, ";", &l1);
    }

    *respecta = 1;
    return gameIndex;
}

void citireDate(char* File){
    int sumIndex = 0, currentIndex = 0;

    FILE* f = fopen(File, "r");
    if(!f){
        fprintf(stderr, "Eroare la deschiderea fisierului sursa!\n");
        exit(-1);
    }

    char line[500];
    int respecta = 0;
    while(fgets(line, 500, f)){
        respecta = 0;
        line[strlen(line) - 1] = ';';

        currentIndex = prelucrareDate(line, &respecta);

        if(respecta == 1){
            sumIndex += currentIndex;
        }
    }

    if(fclose(f) != 0){
        fprintf(stderr, "Eroare la inchiderea fisierului sursa!\n");
        exit(-1);
    }
    printf("Sum of games index is -> %d\n", sumIndex);
}

int main(int argc, char* argv[]){
    if(argc != 2){
        fprintf(stderr, "Numar invalid de argumente!\n");
        exit(-1);
    }

    citireDate(argv[1]);

    return 0;
}


//! Ce am invatat din problema asta;
/*
    NU pot folosi strtok pe doua stringuri concomitent chiar daca tai cu pointeri diferiti, folosesc strtok_t la care se adauga[..]
    [..] un camp ce salveaza adresa stringului initial din care taie pointerul respectiv;

*/