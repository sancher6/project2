#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <wait.h> 

int main(){
    char run[] = "make";
    char run1[] = ",/main 1";
    system(run); 

    for(int i = 0; i < 49; ++i){
        system(run1); 
        wait(1); 
    }
    return 0;
}

