#include <stdio.h>
#include <stdlib.h>
#include "ingredient.h"
#include "recipes.h"


INGREDIENT* LIST_INGREDIENTS=NULL;
int NUMBER_INGREDIENTS = 0;
int LIST_INGREDIENTS_CHANGED = 0; 
RECIPE* LIST_RECIPES=NULL; 
int NUMBER_RECIPES=0;
int LIST_RECIPES_CHANGED = 0; 



int main() 
{
    //extern INGREDIENT* LIST_INGREDIENTS;
    extern int NUMBER_INGREDIENTS;
    //extern RECIPE* LIST_RECIPES; 
    extern int NUMBER_RECIPES;
    
    initIngredientList();
    printf("\n\nnombre d'ingrédient disponibles : %d \n",NUMBER_INGREDIENTS);
    readAllIngredients(VERBOSE);
    initRecipeList();
    printf("\n\nnombre de cocktails disponibles : %d \n",NUMBER_RECIPES);
    readAllRecipes(VERBOSE);
    if (addIngredientThroughtTerminal()){
        readAllIngredients(NVERBOSE);
    }
    else{
        printf("erreur de creation du nouvel ingredient");
    }
    if(addRecipeThroughtTerminal()){
        readAllRecipes(NVERBOSE);
    }
    else{
        printf("erreur de création de la nouvelle recette");
    }
    freeRecipeList(Save);
    freeIngredientList(Save);
    return 1;
    
}