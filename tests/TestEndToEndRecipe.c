#include "../ingredient.h"
#include"../recipes.h"
#include "../serialCommunication.h"
#include "../constants.h"

INGREDIENT* LIST_INGREDIENTS=NULL;
int NUMBER_INGREDIENTS = 0;
int LIST_INGREDIENTS_CHANGED = 1;
RECIPE* LIST_RECIPES=NULL; 
int NUMBER_RECIPES=0;
int LIST_RECIPES_CHANGED = 0; 

int main(){
    extern INGREDIENT* LIST_INGREDIENTS;
    extern int NUMBER_INGREDIENTS;
    extern RECIPE* LIST_RECIPES; 
    extern int NUMBER_RECIPES;
    
    initIngredientList();
    printf("\n\nnombre d'ingrédient disponibles : %d \n",NUMBER_INGREDIENTS);
    readAllIngredients(VERBOSE);
    initRecipeList();
    printf("\n\nnombre de cocktails disponibles : %d \n",NUMBER_RECIPES);
    readAllRecipes(NVERBOSE);
    int fd = initSerial();
    executeRecipe(LIST_RECIPES[0],fd);
    int i;
    for (i = 0 ; i<100; i ++){
    readSerial(fd);
    }
    freeIngredientList(Save);
    freeIngredientList(Save);
    return 1;
    
}