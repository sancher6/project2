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
int sudoku[SUDOKU_SIZE][SUDOKU_SIZE]; 

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
    FILE* out;  
    char str[MAXCHAR]; 
    char* filename = "input.txt";
    pthread_t rows,cols,sqrs;
    pthread_t row[SUDOKU_SIZE];
    pthread_t col[SUDOKU_SIZE];
    pthread_t sqr[SUDOKU_SIZE];
    int id[SUDOKU_SIZE];
    int i = 0, totalnums, runs, j = 0;
    size_t count; 
    char *line = malloc(SUDOKU_SIZE); 
    double time = 0.0;
    int option = atoi(argv[1]);
    clock_t start,end;

    fp = fopen(filename, "r"); 
    if(fp == NULL){
        printf("Could not open file %s", filename); 
        return 1; 
    }
    for(i = 0; i < SUDOKU_SIZE; ++i){
        for(j = 0; j < SUDOKU_SIZE; ++j){
            fscanf(fp, "%d", &sudoku[i][j]); 
        }
    }
    fclose(fp); 

    /* start clock */
    start = clock();
    
    /* each thread does all 9 parts, 1 thread per sqr */
    if(option == 1){
        pthread_create(&rows,NULL,rowCheck,NULL);
        pthread_create(&cols,NULL,colCheck,NULL);
        for(int i = 0; i < SUDOKU_SIZE; i++){
            id[i] = i;
            pthread_create(&sqr[i],NULL,checkOneSqr,(void*)(id+i));
        }
    }
    
    /* each thread does only 1 part */
    if(option == 2){
        for(int i = 0; i < SUDOKU_SIZE; i++){
            id[i] = i;
            pthread_create(&row[i],NULL,checkOneRow,(void*)(id+i));
            pthread_create(&col[i],NULL,checkOneCol,(void*)(id+i));
            pthread_create(&sqr[i],NULL,checkOneSqr,(void*)(id+i));
        }
    }
    
    /* close threads w/ all 9 parts */
    if(option == 1){
        pthread_join(rows,NULL);
        pthread_join(cols,NULL);
        pthread_join(sqrs,NULL);
    }
    
    /* close threads w/ only 1 part */
    if(option == 2){
        for(int i = 0; i < SUDOKU_SIZE; i++){
            pthread_join(row[i],NULL);
            pthread_join(col[i],NULL);
            pthread_join(sqr[i],NULL);
        }
    }
    
    /* stop clock */
    end = clock();
    
    time = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("BOARD STATE IN %s:\n",filename);
    for(int i = 0; i < SUDOKU_SIZE; i++){
        for(int j = 0; j < SUDOKU_SIZE; j++){
            printf("%d ",sudoku[i][j]);
        }
        printf("\n");
    }
    if(valid)
        printf("SOLUTION: YES ");
    else
        printf("SOLUTION: NO ");
    printf("(%f seconds)\n",time);
    
    printf("(%f seconds)\n",
        (double)(end - start) / CLOCKS_PER_SEC);

    free(line); 
    out = fopen("output1.txt", "w");
    fprintf(out, "%f ", time); 
    fclose(out);

        
    return 0; 
}