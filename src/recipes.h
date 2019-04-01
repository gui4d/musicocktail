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
    unsigned long recipeDescription;
};
typedef struct recipe  * RECIPE;  

struct recipeDescriptor{
    char* name;
    int idd;
};
typedef struct recipeDescriptor * DESCRIPTOR;



int initNb(FILE* recipeFile);
int initRecipe(FILE* recipeFile,int iddRecipe );
int initRecipeList();

int writeRecipeList(char* recipesFileName);
int saveRecipeList();
void freeRecipeList(int saveNewRecipes);

void readRecipe(RECIPE Recipe, int verbose);
void readAllRecipes(int verbose);
int addRecipe(char* name,  int nbIngredients , int*  listIngredients, float* listAmount,int iddSimilarRecipe, unsigned long tagDescription );
int addRecipeThroughtTerminal();
RECIPE recipe( int iddRecipe);
int initDescriptor(FILE* descriptorFile,int i );
int initDescriptorsList();
int* descriptorTagtoList(unsigned long tagDescriptor);

#ifdef __cplusplus
}
#endif

#endif