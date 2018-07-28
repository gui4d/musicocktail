#include <stdio.h>
#include "constants.h"
void clean_stdin(void) 
{ 
    int c; 
  
    do { 
        c = getchar(); 
    } while (c != '\n' && c != EOF); 
}