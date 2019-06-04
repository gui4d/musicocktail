#ifndef _INGREDIENT
#define _INGREDIENT

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include "constants.h"


 struct ingredient{
    char* name; 
    //float salt;
    //float sugar; 
    //float strenght; 
    int iddIngredient;
    int servoAdress;

};

typedef struct ingredient * INGREDIENT ;

int initNbIngredient(FILE* ingredientFile);
int initIngredient(FILE* ingredientFile,int iddIngredient);
int initIngredientList();

int writeIngredientList(char * IngrdientFileName);
int saveIngredientList();
void freeIngredientList(int saveNewIngredients);


void readIngredient(INGREDIENT Ingredient,int verbose);
void readAllIngredients(int verbose);
int addIngredient(char* name, int servoAdress);
int addIngredientThroughtTerminal();
int editIngredient( int servoAdress, int iddIngredient);
int*  listUnplacedIngredients();
int iddingredientofplace(int placement);

INGREDIENT ingredient(int iddIngredient);


#ifdef __cplusplus
}
#endif

#endif
