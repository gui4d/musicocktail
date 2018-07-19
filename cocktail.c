#include "cocktail.h"

int readNbIngredient(FILE* ingredientFile){
    char* charNbIngredient=NULL;  
    size_t charSize=0;
    getline( &charNbIngredient, &charSize , ingredientFile);
    int nbIngredients=atoi(charNbIngredient);
    printf("nb ingredient :%d\n",nbIngredients);
    return nbIngredients;
} 
int readIngredient(FILE* ingredientFile, char** name, float* salt , float* sugar , float* strenght , int* iddIngredient){
    char* line=NULL;
    size_t lineSize=0;
    getline( &line, &lineSize , ingredientFile);
    *name=strdup(line);
    
    line=NULL;
    lineSize=0;
    getline( &line, &lineSize , ingredientFile);
    *salt=atof(line);
    
    line=NULL;
    lineSize=0;
    getline( &line, &lineSize , ingredientFile);
    *sugar=atof(line);

    line=NULL;
    lineSize=0;
    getline( &line, &lineSize , ingredientFile);
    *strenght=atof(line);

    line=NULL;
    lineSize=0;
    getline( &line, &lineSize , ingredientFile);
    *iddIngredient=atoi(line);

    return 1;
}

void readAllIngredients(INGREDIENT* listIngredient, int nbIngredient){
    for( int i = 0; i < nbIngredient ; i ++){
        printf("nom  %s \nsel :%f \nsucre : %f \nalcool : %f \nidentifiant : %d \n", listIngredient[i].name , listIngredient[i].salt ,  listIngredient[i].sugar , listIngredient[i].strenght, listIngredient[i].iddIngredient); 
    }
}


int initIngredientList(INGREDIENT** ADDListIngredient,int* ADDnbIngredient)
{
   
    FILE* ingredientFile=NULL;
    ingredientFile = fopen("ingredients.txt", "r" );
    if(ingredientFile!=NULL)
    {
        *ADDnbIngredient=readNbIngredient(ingredientFile);
        *ADDListIngredient=calloc(*ADDnbIngredient,sizeof(**ADDListIngredient));
        for(int i = 0 ; i < *ADDnbIngredient; i++){
            readIngredient(ingredientFile,&((*ADDListIngredient)[i].name),&((*ADDListIngredient)[i].salt),&((*ADDListIngredient)[i].sugar), &((*ADDListIngredient)[i].strenght),&((*ADDListIngredient)[i].iddIngredient));
        } 
        fclose(ingredientFile);
        readAllIngredients(*ADDListIngredient, *ADDnbIngredient);
        return 1 ;
    }
    else 
    {
        printf("erreur\n");
        return 0;
    }
}



