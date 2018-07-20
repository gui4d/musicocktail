#include "ingredient.h"

int readNbIngredient(FILE* ingredientFile)
{
    char* charNbIngredient=NULL;  
    size_t charSize=0;
    getline( &charNbIngredient, &charSize , ingredientFile);
    int nbIngredients=atoi(charNbIngredient);
    printf("nb ingredient :%d\n",nbIngredients);
    return nbIngredients;
} 

int readIngredient(FILE* ingredientFile, char** name, float* salt , float* sugar , float* strenght , int* iddIngredient)
{
    char* line=NULL;
    size_t lineSize=0;
    getline( &line, &lineSize , ingredientFile);
    *name= strdup(line);
    
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

void readAllIngredients(INGREDIENT* listIngredient, int nbIngredient)
{
    for( int i = 0; i < nbIngredient ; i ++){
        printf("nom  : %s \nsel :%f \nsucre : %f \nalcool : %f \nidentifiant : %d \n", listIngredient[i].name , listIngredient[i].salt ,  listIngredient[i].sugar , listIngredient[i].strenght, listIngredient[i].iddIngredient); 
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


int addIngredient(char* name, float salt, float sugar , float alcool, int idd)
{
    FILE* ingredientFile=NULL;
    puts("1");
    ingredientFile = fopen("ingredients.txt", "a" );
    if(ingredientFile!=NULL)
    {
        puts("2");
        fputs("\n", ingredientFile);
        puts("2.1");
        fputs(name, ingredientFile);
        puts("2.2");
        char* charsalt=NULL;
        puts("2.22");
        sprintf(charsalt,"%f" ,salt);
        puts("2.3");
        fputs("\n", ingredientFile);
        fputs(charsalt, ingredientFile);
        char* charsugar=NULL;
        sprintf(charsugar,"%.3f",sugar); 
        fputs("\n", ingredientFile);
        fputs(charsugar, ingredientFile);
        char* charalcool=NULL;
        sprintf(charalcool,"%.3f",alcool); 
        fputs("\n", ingredientFile);
        fputs(charalcool, ingredientFile);
        char* charIDD=NULL;
        sprintf(charIDD,"%d",idd); 
        fputs("\n", ingredientFile);
        fputs(charIDD, ingredientFile);
        fclose(ingredientFile);
        puts("3");//
        INGREDIENT* listIngredients=NULL;
        int nbIngredients = 0;
        if ( ! initIngredientList(&listIngredients,&nbIngredients)) return 0; 
        readAllIngredients(listIngredients,nbIngredients);
        //
        return 1 ;
    }
    else 
    {
        printf("erreur\n");
        return 0;
    }



    return 1; 
}
