/*
Richard Bustamante & Paul Brodhead
CSC345-01
Project 2
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#define MAXCHAR 18
#define SUDOKU_SIZE 9
#define CORRECT_SUDOKU 45

int valid = 1;
int sudoku[SUDOKU_SIZE][SUDOKU_SIZE] = {/* ; /* DEBUG */
    {1,2,3,4,5,6,7,8,9},
    {7,8,9,1,2,3,4,5,6},
    {4,5,6,7,8,9,1,2,3},
    {3,1,2,8,4,5,9,6,7},
    {6,9,7,3,1,2,8,4,5},
    {8,4,5,6,9,7,3,1,2},
    {2,3,1,5,7,4,6,9,8},
    {9,6,8,2,3,1,5,7,4},
    {5,7,4,9,6,8,2,3,1}
};

void *rowCheck(void *param){
    int check[SUDOKU_SIZE] = {0,0,0,0,0,0,0,0,0};
    int rowSum = 0;
        
    for(int i = 0; i < SUDOKU_SIZE; i++){
        for(int j = 0; j < SUDOKU_SIZE; j++){
            rowSum += sudoku[i][j];
        }
        if(rowSum == CORRECT_SUDOKU)
            check[i] = 1;
        rowSum = 0;
    }
    
    for(int i = 0; i < SUDOKU_SIZE; i++){
        if(check[i] != 1)
            valid = 0;
    }
        
    if(valid)
        printf("rows are valid\n");
    else
        printf("rows are NOT valid\n");
}

void *colCheck(void *param){
    int check[SUDOKU_SIZE] = {0,0,0,0,0,0,0,0,0};
    int colSum = 0;
        
    for(int i = 0; i < SUDOKU_SIZE; i++){
        for(int j = 0; j < SUDOKU_SIZE; j++){
            colSum += sudoku[j][i];
        }
        if(colSum == CORRECT_SUDOKU)
            check[i] = 1;
        colSum = 0;
    }
    
    for(int i = 0; i < SUDOKU_SIZE; i++){
        if(check[i] != 1)
            valid = 0;
    }
        
    if(valid)
        printf("cols are valid\n");
    else
        printf("cols are NOT valid\n");
}

void *sqrCheck(void *param){
    int sum = 0;
    int sqrSum = 0;
    
    for(int n = 0; n < (SUDOKU_SIZE / 3); n++){
        for(int m = 0; m < (SUDOKU_SIZE / 3); m++){
            for(int i = 0; i < (SUDOKU_SIZE / 3); i++){
                for(int j = 0; j < (SUDOKU_SIZE / 3); j++){
                    sqrSum += sudoku[i+(3*n)][j+(3*m)];
                }
            }
            if(sqrSum = CORRECT_SUDOKU)
                sum++;
            sqrSum = 0;
        }
    }
    
    if(sum != SUDOKU_SIZE)
        valid = 0;
        
    if(valid)
        printf("sqrs are valid\n");
    else
        printf("sqrs are NOT valid\n");
}

int main(int argc, char** argv){
    FILE* fp; 
    char str[MAXCHAR]; 
    char* filename = "input.txt";
    pthread_t rows,cols,sqrs;

    fp = fopen(filename, "r"); 
    if(fp == NULL){
        printf("Could not open file %s", filename); 
        return 1; 
    }
    while(fgets(str, MAXCHAR, fp) != NULL){
        printf("%s\n", str); 
    }
    fclose(fp); 
    
    pthread_create(&rows,NULL,rowCheck,NULL);
    pthread_create(&cols,NULL,colCheck,NULL);
    pthread_create(&sqrs,NULL,sqrCheck,NULL);
    
    pthread_join(rows,NULL);
    pthread_join(cols,NULL);
    pthread_join(sqrs,NULL);
    
    return 0; 
}