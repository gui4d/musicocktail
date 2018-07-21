#include <stdio.h>
#include <stdlib.h>
#include "ingredient.h"
#include "cocktail.h"


INGREDIENT* LIST_INGREDIENTS=NULL;
int NUMBER_INGREDIENTS=0;
RECIPE* LIST_RECIPES=NULL; 
int NUMBER_RECIPES=0;


int main() 
{
    //extern INGREDIENT* LIST_INGREDIENTS;
    extern int NUMBER_INGREDIENTS;
    //extern RECIPE* LIST_RECIPES; 
    extern int NUMBER_RECIPES;
    
    initIngredientList();
    printf("\n\nnombre d'ingrédient disponibles : %d \n",NUMBER_INGREDIENTS);
    readAllIngredients();
    initRecipeList();
    printf("\n\nnombre de cocktails disponibles : %d \n",NUMBER_RECIPES);
    readAllRecipes();
    addIngredient("wisky", 3.12, 10.1 , 49.2);
    freeIngredientList(Save);
}