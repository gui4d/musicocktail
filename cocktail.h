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
 

typedef struct {
    char* name;
    float amount;
    int nbIngredients; 
    INGREDIENT * listIngredients; 
    float* listAmount;
    int iddRecette;
}RECETTE; 
