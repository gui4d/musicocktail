#ifndef _INGREDIENT

#define _INGREDIENT
#include <stdlib.h>
#include <stdio.h>
#include<string.h>

 struct ingredient{
    char* name; 
    float salt;
    float sugar; 
    float strenght; 
    int iddIngredient; 

};

typedef struct ingredient * INGREDIENT ;

int initNbIngredient(FILE* ingredientFile);
int initIngredient(FILE* ingredientFile,int iddIngredient);
int initIngredientList();
void freeIngredientList();

void readIngredient(INGREDIENT Ingredient,int verbose);
void readAllIngredients();
int addIngredient(char* name, float salt, float sugar , float alcool, int idd);

INGREDIENT ingredient(int iddIngredient);
#endif
