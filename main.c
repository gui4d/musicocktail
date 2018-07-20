#include <stdio.h>
#include <stdlib.h>
#include "cocktail.h"
#include "ingredient.h"



int main() 
{
    INGREDIENT* ListIngredient = NULL;
    int nbIngredient;
    initIngredientList( &ListIngredient,&nbIngredient);
    //addIngredient("wisky", 3.12, 10.1 , 49.2, 3); ne marche pas 
}