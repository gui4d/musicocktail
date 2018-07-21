#ifndef _COCKTAIL

#define _COCKTAIL
#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include "constants.h"
#include"ingredient.h"


struct recipe{
    char* name;
    int iddRecipe; 
    float amount;
    int nbIngredients; 
    int * listIddIngredients; 
    float* listAmount;
    int iddSimilarRecipe;
};
typedef struct recipe  * RECIPE;  



int initNbRecipe(FILE* recipeFile);
int initRecipe(FILE* recipeFile,int iddRecipe );
int initRecipeList();
void freeRecipeList();

void readRecipe(RECIPE Recipe, int verbose);
void readAllRecipes();
int addRecipe(char* name,float amount, int nbIngredients, INGREDIENT* listIngredients, float* listAmount, int iddRecipe, RECIPE similarRecipe, int iddSimilarRecipe );

RECIPE recipe( int iddRecipe);

#endif