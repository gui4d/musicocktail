#ifndef _COCKTAIL

#define _COCKTAIL
#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include"ingredient.h"

typedef struct {
    char* name;
    float amount;
    int nbIngredients; 
    INGREDIENT * listIngredients; 
    float* listAmount;
    int iddRecette;
}RECETTE; 

#endif