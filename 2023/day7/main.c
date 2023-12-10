#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define CARD_LENGTH 5
#define SIZE_LINE 50
#define SYMBOLS_NUMBER 15

typedef struct{
    char cardValueString[CARD_LENGTH];
    int cardBid, cardValue, cardType, indexSameType;
    int array[CARD_LENGTH]; //Used to codify every simbol with a number for compare function;
}Card_t;

Card_t processingLine(char* line){
    Card_t card;
    char* p = strtok(line, " ");
    strncpy(card.cardValueString, p, CARD_LENGTH);
    p = strtok(NULL, "\n");
    card.cardBid = atoi(p);
    card.cardValue = 0;
    card.cardType = 0;
    card.indexSameType = 1;
    return card;
}

Card_t* readData(char* File, int* counter){
    Card_t* cards = NULL;
    Card_t currentCard;
    
    FILE* f = fopen(File, "r");
    if(!f){
        fprintf(stderr, "The input file couldn't be opened!\n");
        exit(-1);
    }

    char line[SIZE_LINE];
    while(fgets(line, SIZE_LINE, f) != NULL){
        currentCard = processingLine(line);
        cards = realloc(cards, (*counter + 1) * sizeof(Card_t));
        if(!cards){
            fprintf(stderr, "Out of memory! readData\n");
            exit(-1);
        }
        cards[(*counter)++] = currentCard;
    }

    if(fclose(f) != 0){
        fprintf(stderr, "The input file couldn't be closed!\n");
        exit(-1);
    }

    return cards;
}

void printCards(const Card_t* cards, const int size){
    for(int i = 0; i < size; i++){
        printf("valueString %s value %d bid %d type %d\n", cards[i].cardValueString, cards[i].cardValue, cards[i].cardBid, cards[i].cardType);
    }
}

void printSimbolsArray(const int array[], const int size){
    for(int i = 0; i < size; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
}

void resetSimbolsArray(int array[], const int size){
    for(int i = 0; i < size; i++){
        array[i] = 0;
    }
}

Card_t* extractCardType(Card_t cards[], const int size){
    int cardSimbols[SYMBOLS_NUMBER] = {0};
    char simbol;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < CARD_LENGTH; j++){
            simbol = cards[i].cardValueString[j];
            if(isdigit(simbol)){
                cards[i].array[j] = atoi(&simbol);
                cardSimbols[atoi(&simbol)]++;
            }
            else{
                if(toupper(simbol) == 'A'){
                    cardSimbols[14]++;
                    cards[i].array[j] = 14;
                }
                else if(toupper(simbol) == 'K'){
                    cardSimbols[13]++;
                    cards[i].array[j] = 13;
                }
                else if(toupper(simbol) == 'Q'){
                    cardSimbols[12]++;
                    cards[i].array[j] = 12;
                }
                else if(toupper(simbol) == 'J'){
                    cardSimbols[11]++;
                    cards[i].array[j] = 11;
                }
                else if(toupper(simbol) == 'T'){
                    cardSimbols[10]++;
                    cards[i].array[j] = 10;
                }
            }
        }

        //Acum ca stiu ce simboluri am in fiecare carte, vreau sa vad de ce tip e;
        int maxValue = 0;
        int secondValue = 0;
        int indexMax, indexSecond;
        for(int j = 0; j < SYMBOLS_NUMBER; j++){
            if(cardSimbols[j] > maxValue){
                secondValue = maxValue;
                indexSecond = indexMax;
                maxValue = cardSimbols[j];
                indexMax = j;
            }
            if(cardSimbols[j] > secondValue && j != indexMax){
                secondValue = cardSimbols[j];
                indexSecond = j;
            }
        }

        //printf("max %d sec %d\n", maxValue, secondValue);
        if(maxValue == 5){
            cards[i].cardType = 7;
        }
        else if(maxValue == 4){
            cards[i].cardType = 6;
        }
        else if(maxValue == 3){
            if(secondValue == 2 && indexSecond != indexMax){
                cards[i].cardType = 5;
            }
            else{
                cards[i].cardType = 4;
            }
        }
        else if(maxValue == 2){
            if(secondValue == 2){
                cards[i].cardType = 3;
            }
            else{
                cards[i].cardType = 2;
            }
        }
        else{
            cards[i].cardType = 1;
        }
        //printSimbolsArray(cardSimbols, SIMBOLS_NUMBER);
        resetSimbolsArray(cardSimbols, SYMBOLS_NUMBER);
    }
    //printCards(cards, size);
    return cards;
}

int compare2CardStringValues(const Card_t card1, const Card_t card2){
    for(int i = 0; i < CARD_LENGTH; i++){
        if(card1.array[i] < card2.array[i])
        {
            return -1;
        }
        else if(card1.array[i] > card2.array[i]){
            return 1;
        }
    }
    return 0;
}

Card_t bubbleSort(Card_t card){ //Sortez crescator simbolurile de pe carduri;
    int s = 0;
    int aux;
    do{
        s = 0;
        for(int i = 1; i < SYMBOLS_NUMBER; i++){
            if(card.array[i] < card.array[i-1]){
                aux = card.array[i];
                card.array[i] = card.array[i - 1];
                card.array[i-1] = aux;
                s = 1;
            }
        }
    }while(s);

    return card;
}

int compare2(Card_t card1, Card_t card2){
    //Verific daca nu cumva am acelasi tip de carte dar 
    card1 = bubbleSort(card1);
    card2 = bubbleSort(card2);

    for(int i = 0; i < SYMBOLS_NUMBER; i++){
        if(card1.array[i] != card2.array[i]){
            return -1;
        }
    }
    return 0;
}

Card_t* sortType(Card_t cards[],const int size){
    int s = 0;
    Card_t aux;
    do{
        s = 0;
        for(int i = 1; i < size; i++){
            if(compare2CardStringValues(cards[i-1], cards[i]) == 1){
                aux = cards[i-1];
                cards[i - 1] = cards[i];
                cards[i] = aux;
                s = 1;
            }
        }
    }while(s);
    return cards;
}

Card_t* extractCardValue(Card_t cards[], const int size){
    Card_t* type1 = NULL;
    Card_t* type2 = NULL;
    Card_t* type3 = NULL;
    Card_t* type4 = NULL;
    Card_t* type5 = NULL;
    Card_t* type6 = NULL;
    Card_t* type7 = NULL;

    
    int counter1 = 0, counter2 = 0, counter3 = 0, counter4 = 0, counter5 = 0, counter6 = 0, counter7 = 0;
    for(int i = 0; i < size; i++){
        if(cards[i].cardType == 1){
            type1 = realloc(type1, (counter1 + 1) * sizeof(Card_t));
            if(!type1){
                fprintf(stderr, "Out of memory type1!\n");
                exit(-1);
            }
            type1[counter1++] = cards[i];
        }
        else if(cards[i].cardType == 2){
            type2 = realloc(type2, (counter2 + 1) * sizeof(Card_t));
            if(!type2){
                fprintf(stderr, "Out of memory type2!\n");
                exit(-1);
            }
            type2[counter2++] = cards[i];
        }
        else if(cards[i].cardType == 3){
            type3 = realloc(type3, (counter3 + 3) * sizeof(Card_t));
            if(!type3){
                fprintf(stderr, "Out of memory type3!\n");
                exit(-1);
            }
            type3[counter3++] = cards[i];
        }
        else if(cards[i].cardType == 4){
            type4 = realloc(type4, (counter4 + 1) * sizeof(Card_t));
            if(!type4){
                fprintf(stderr, "Out of memory type4!\n");
                exit(-1);
            }
            type4[counter4++] = cards[i];
        }
        else if(cards[i].cardType == 5){
            type5 = realloc(type5, (counter5 + 1) * sizeof(Card_t));
            if(!type5){
                fprintf(stderr, "Out of memory type5!\n");
                exit(-1);
            }
            type5[counter5++] = cards[i];
        }
        else if(cards[i].cardType == 6){
            type6 = realloc(type6, (counter6 + 1) * sizeof(Card_t));
            if(!type6){
                fprintf(stderr, "Out of memory type6!\n");
                exit(-1);
            }
            type6[counter6++] = cards[i];
        }
        else
        {
            type7 = realloc(type7, (counter7 + 1) * sizeof(Card_t));
            if(!type7){
                fprintf(stderr, "Out of memory type7!\n");
                exit(-1);
            }
            type7[counter7++] = cards[i];
        }
    }
    //Acum trebuie sa sortez fiecare tip;
    
    if(counter1 >= 2){
        type1 = sortType(type1, counter1);
    }
    
    if(counter2 >= 2){
        type2 = sortType(type2, counter2);
    }

    if(counter3 >= 2){
        type3 = sortType(type3, counter3);
    }
    if(counter4 >= 2){
        type4 = sortType(type4, counter4);
    }
    if(counter5 >= 2){
        type5 = sortType(type5, counter5);
    }
    if(counter6 >= 2){
        type6 = sortType(type6, counter6);
    }
    if(counter7 >= 2){
        type7 = sortType(type7, counter7);
    }


    int index = 0;
    for(int j = 0; j < counter1; j++){
        cards[j + index] = type1[j];
        cards[j + index].indexSameType = j;
    }
    free(type1);
    index += counter1;

    for(int j= 0; j < counter2; j++){
        cards[j + index] = type2[j];
        cards[j + index].indexSameType = j;
    }
    free(type2);
    index += counter2;

    for(int j = 0; j < counter3; j++){
        cards[j + index] = type3[j];
        cards[j + index].indexSameType = j;
    }
    free(type3);
    index += counter3;

    for(int j = 0; j < counter4; j++){
        cards[j + index] = type4[j];
        cards[j + index].indexSameType = j;
    }
    free(type4);
    index += counter4;

    for(int j = 0; j < counter5; j++){
        cards[j + index] = type5[j];
        cards[j + index].indexSameType = j;
    }
    free(type5);
    index += counter5;

    for(int j = 0; j < counter6; j++){
        cards[j + index] = type6[j];
        cards[j + index].indexSameType = j;
    }
    free(type6);
    index += counter6;

    for(int j = 0; j < counter7; j++){
        cards[j + index] = type7[j];
        cards[j + index].indexSameType = j;
    }
    free(type7);
    
    //printCards(cards, size);
    return cards;
}

void calculatePoints(const Card_t cards[], const int size){
    long int points = 0;
    int currentRank = 1;
    
    for(int i = 0; i < size; i++){
       //printf("%s rank %d type %d indexSame %d  bid %d\n", cards[i].cardValueString, currentRank + same, cards[i].cardType, cards[i].indexSameType, cards[i].cardBid);
        points += currentRank * cards[i].cardBid;

        if(i < size - 1)
        {
            if(compare2(cards[i], cards[i+1]) != 0 || (cards[i].cardType != cards[i + 1].cardType)){
                currentRank++;
            }
        }
    }
    printf("Total points -> %ld\n", points);
}

char selectSymbol(const int position){
    if(position == 2){
        return '2';
    }
    else if(position == 3){
        return '3';
    }
    else if(position == 4){
        return '4';
    }
    else if(position == 5){
        return '5';
    }
    else if(position == 6){
        return '6';
    }
    else if(position == 7){
        return '7';
    }
    else if(position == 8){
        return '8';
    }
    else if(position == 9){
        return '9';
    }
    else if(position == 10){
        return 'T';
    }
    else if(position == 12){
        return 'Q';
    }
    else if(position == 13){
        return 'K';
    }
    else if(position == 14){
        return 'A';
    }
    return '.';
}

int getGraterSymbol(Card_t card){
    int i = SYMBOLS_NUMBER - 1;
    while(i){
        if(card.array[i] != 0){
            return i;
        }
    }
    return 0;
}

int calculateNumberOfJokers(Card_t card);

void convertJoker(Card_t card, const int cardType){
    int numberOfJokers = calculateNumberOfJokers(card);
    char ch;

    if(cardType == 1){
        if(numberOfJokers == 4){
            ch = selectSymbol(getGraterSymbol(card));
        }
    }
}

int calculateNumberOfJokers(Card_t card){
    int numberOfJokers = 0;
    for(int i = 0; i < CARD_LENGTH; i++){
        if(card.cardValueString[i] == 'J'){
            numberOfJokers++;
        }
    }
    return numberOfJokers;
}

int main(int argc, char* argv[]){
    if(argc != 2){
        fprintf(stderr, "Invalid arguments!\n");
        exit(-1);
    }

    int counter = 0;
    Card_t* cards = readData(argv[1], &counter);
    //printCards(cards, counter);
    cards = extractCardType(cards, counter);
    cards = extractCardValue(cards, counter);
    //printCards(cards, counter);

    calculatePoints(cards, counter);


    free(cards);
    return 0;
}