#include <stdio.h>
#include <stdlib.h>
#include <string.h>  

int main(){
    char run[] = "make";
    /* run1 is used to identify what option will be passed to main.c s*/ 
    char run1[] = "./main 2";
    system(run); 
    /* runs this option for 50 iterations */
    for(int i = 0; i < 49; ++i){
        system(run1); 
        // wait(1); 
    }
    return 0;
}

