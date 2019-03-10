/*
Richard Bustamante & Paul Brodhead
CSC345-01
Project 2
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <time.h>

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
}

void *checkOneRow(void *param){
    int *row = (int*) param;
    int rowSum = 0;
    
    for(int i = 0; i < SUDOKU_SIZE; i++){
        rowSum += sudoku[*row][i];
    }
    if(rowSum != CORRECT_SUDOKU)
        valid = 0;
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
}

void *checkOneCol(void *param){
    int *col = (int*) param;
    int colSum = 0;
    
    for(int i = 0; i < SUDOKU_SIZE; i++){
        colSum += sudoku[i][*col];
    }
    if(colSum != CORRECT_SUDOKU)
        valid = 0;
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
}

void *checkOneSqr(void *param){
    int *sqr = (int*) param;
    int sqrSum = 0;
    int iOffset = 3 * (*sqr % (SUDOKU_SIZE / 3));
    int jOffset = 3 * (*sqr / (SUDOKU_SIZE / 3));
    
    for(int i = 0; i < (SUDOKU_SIZE / 3); i++){
        for(int j = 0; j < (SUDOKU_SIZE / 3); j++){
            sqrSum += sudoku[i+iOffset][j+jOffset];
        }
    }
    if(sqrSum != CORRECT_SUDOKU)
        valid = 0;
}

int main(int argc, char** argv){
    FILE* fp; 
    char str[MAXCHAR]; 
    char* filename = "input.txt";
    pthread_t rows,cols,sqrs;
    pthread_t row[SUDOKU_SIZE];
    pthread_t col[SUDOKU_SIZE];
    pthread_t sqr[SUDOKU_SIZE];
    int id[SUDOKU_SIZE];
    double time = 0.0;

    fp = fopen(filename, "r"); 
    if(fp == NULL){
        printf("Could not open file %s", filename); 
        return 1; 
    }
    while(fgets(str, MAXCHAR, fp) != NULL){
        printf("%s\n", str); 
    }
    fclose(fp); 
    
    /* each thread does all 9 parts */
    clock_t startA = clock();
    pthread_create(&rows,NULL,rowCheck,NULL);
    pthread_create(&cols,NULL,colCheck,NULL);
    pthread_create(&sqrs,NULL,sqrCheck,NULL);
    clock_t endA = clock();
    
    /* each thread does only 1 part */
    clock_t startB = clock();
    for(int i = 0; i < SUDOKU_SIZE; i++){
        id[i] = i;
        pthread_create(&row[i],NULL,checkOneRow,(void*)(id+i));
        pthread_create(&col[i],NULL,checkOneCol,(void*)(id+i));
        pthread_create(&sqr[i],NULL,checkOneSqr,(void*)(id+i));
    }
    clock_t endB = clock();
    
    /* close threads w/ all 9 parts */
    pthread_join(rows,NULL);
    pthread_join(cols,NULL);
    pthread_join(sqrs,NULL);
    
    /* close threads w/ only 1 part */
    for(int i = 0; i < SUDOKU_SIZE; i++){
        pthread_join(row[i],NULL);
        pthread_join(col[i],NULL);
        pthread_join(sqr[i],NULL);
    }
    
    printf("BOARD STATE IN %s:\n",filename);
    for(int i = 0; i < SUDOKU_SIZE; i++){
        for(int j = 0; j < SUDOKU_SIZE; j++){
            printf("%d ",sudoku[i][j]);
        }
        printf("\n");
    }
    if(valid)
        printf("SOLUTION: YES\n");
    else
        printf("SOLUTION: NO\n");
    printf("Option 1 time: %f seconds\n",
        (double)(endA - startA) / CLOCKS_PER_SEC);
    printf("Option 2 time: %f seconds\n",
        (double)(endB - startB) / CLOCKS_PER_SEC);
    
    return 0; 
}