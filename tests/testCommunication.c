#include "../ingredient.h"
#include "../serialCommunication.h"
#include "../constants.h"

INGREDIENT* LIST_INGREDIENTS=NULL;
int NUMBER_INGREDIENTS = 0;
int LIST_INGREDIENTS_CHANGED = 1;

int main(){
    extern INGREDIENT * LIST_INGREDIENTS;
    extern int NUMBER_INGREDIENTS;
    
    initIngredientList();
    printf("\n\nnombre d'ingrédient disponibles : %d \n",NUMBER_INGREDIENTS);
    readAllIngredients(VERBOSE);
    int fd = initSerial();
    int i;
    for( i = 0 ; i < NUMBER_INGREDIENTS ; i ++){
        sendNewOrder(LIST_INGREDIENTS[i],110*(i+1),fd);
    }    
    for (i = 0 ; i<100; i ++){
    readSerial(fd);
    }
    freeIngredientList(Save);
    return 1;
    
}