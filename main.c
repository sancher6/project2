/*
Richard Bustamante
CSC345-01
Project 2
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#define MAXCHAR 18

int main(int argc, char** argv){
    FILE* fp; 
    char str[MAXCHAR]; 
    char* filename = "input.txt";

    fp = fopen(filename, "r"); 
    if(fp == NULL){
        printf("Could not open file %s", filename); 
        return 1; 
    }
    while(fgets(str, MAXCHAR, fp) != NULL){
        printf("%s\n", str); 
    }
    fclose(fp); 
    
    return 0; 
}