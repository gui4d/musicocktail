#ifndef _INGREDIENT

#define _INGREDIENT
#include <stdlib.h>
#include <stdio.h>
#include<string.h>

typedef struct {
    char* name; 
    float salt;
    float sugar; 
    float strenght; 
    int iddIngredient; 

}INGREDIENT;



int readNbIngredient(FILE* ingredientFile);
int readIngredient(FILE* ingredientFile, char** name, float* salt , float* sugar , float* strenght , int* iddIngredient);
void readAllIngredients(INGREDIENT* listIngredient, int nbIngredient);
int initIngredientList(INGREDIENT** ADDListIngredient,int* ADDnbIngredient);
int addIngredient(char* name, float salt, float sugar , float alcool, int idd);

#endif
