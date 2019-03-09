#ifndef _RECEPIES
#define _RECEPIES

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include "constants.h"
#include"ingredient.h"


struct recipe{
    char* name;
    int iddRecipe;
    int nbIngredients; 
    int * listIddIngredients; 
    float* listAmount;
    int iddSimilarRecipe;
};
typedef struct recipe  * RECIPE;  



int initNbRecipe(FILE* recipeFile);
int initRecipe(FILE* recipeFile,int iddRecipe );
int initRecipeList();

int writeRecipeList(char* recipesFileName);
int saveRecipeList();
void freeRecipeList(int saveNewRecipes);

void readRecipe(RECIPE Recipe, int verbose);
void readAllRecipes(int verbose);
int addRecipe(char* name,  int nbIngredients , int*  listIngredients, float* listAmount,int iddSimilarRecipe );
int addRecipeThroughtTerminal();
RECIPE recipe( int iddRecipe);

#ifdef __cplusplus
}
#endif

#endif