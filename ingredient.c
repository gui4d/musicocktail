#include "ingredient.h"


int initNbIngredient(FILE* ingredientFile)
{
    char* charNbIngredient=NULL;  
    size_t charSize=0;
    getline( &charNbIngredient, &charSize , ingredientFile);
    int nbIngredients=atoi(charNbIngredient);
    return nbIngredients;
} 

int initIngredient(FILE* ingredientFile,int iddIngredient)
{
    extern INGREDIENT* LIST_INGREDIENTS;
    char* line=NULL;
    size_t lineSize=0;
    getline( &line, &lineSize , ingredientFile);
    LIST_INGREDIENTS[iddIngredient]->name= strdup(line);  
    line=NULL;
    lineSize=0;
    getline( &line, &lineSize , ingredientFile);
    LIST_INGREDIENTS[iddIngredient]->salt=atof(line); 
    line=NULL;
    lineSize=0;
    getline( &line, &lineSize , ingredientFile);
    LIST_INGREDIENTS[iddIngredient]->sugar=atof(line);

    line=NULL;
    lineSize=0;
    getline( &line, &lineSize , ingredientFile);
    LIST_INGREDIENTS[iddIngredient]->strenght=atof(line);

    line=NULL;
    lineSize=0;
    getline( &line, &lineSize , ingredientFile);
    LIST_INGREDIENTS[iddIngredient]->iddIngredient=atoi(line);

    return 1;
}

int initIngredientList()
{
    extern INGREDIENT* LIST_INGREDIENTS;
    extern int NUMBER_INGREDIENTS;
    FILE* ingredientFile=NULL;
    ingredientFile = fopen("ingredients.txt", "r" );
    if(ingredientFile!=NULL)
    {
        NUMBER_INGREDIENTS=initNbIngredient(ingredientFile);
        LIST_INGREDIENTS=calloc(NUMBER_INGREDIENTS,sizeof(*LIST_INGREDIENTS));
        for(int i = 0 ; i < NUMBER_INGREDIENTS; i++){
            LIST_INGREDIENTS[i]=calloc(1,sizeof(*LIST_INGREDIENTS[i]));
            initIngredient(ingredientFile, i );
        } 
        fclose(ingredientFile);
        return 1 ;
    }
    else 
    {
        printf("error when reading database\n");
        return 0;
    }
}

void freeIngredientList()
{
    extern INGREDIENT* LIST_INGREDIENTS;
    extern int NUMBER_INGREDIENTS;
    for(int i = 0; i< NUMBER_INGREDIENTS ; i ++){
       free(LIST_INGREDIENTS[i]);
    }
    free(LIST_INGREDIENTS);
    LIST_INGREDIENTS=NULL;
    NUMBER_INGREDIENTS=0;
}

void readIngredient(INGREDIENT Ingredient,int verbose){
    if(verbose ){
        printf("/nom :%s /sel :%f /sucre :%f /alcool :%f /identifiant :%d", Ingredient->name , Ingredient->salt ,  Ingredient->sugar , Ingredient->strenght, Ingredient->iddIngredient); 
    }
    else{
        printf("%s", Ingredient->name); 
    }
}

void readAllIngredients()
{
    extern INGREDIENT* LIST_INGREDIENTS;
    extern int NUMBER_INGREDIENTS;
    for( int i = 0; i < NUMBER_INGREDIENTS ; i ++){
        readIngredient(LIST_INGREDIENTS[i], 1 ); 
        printf("\n"); 
    }
}

int addIngredient(char name[100], float salt, float sugar , float alcool, int idd)
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
        if ( ! initIngredientList()) return 0; 
        readAllIngredients();
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

INGREDIENT ingredient(int iddIngredient){
    extern INGREDIENT* LIST_INGREDIENTS;
    extern int NUMBER_INGREDIENTS;

    if(iddIngredient>=0 || NUMBER_INGREDIENTS>iddIngredient || LIST_INGREDIENTS!=NULL){
        return LIST_INGREDIENTS[iddIngredient];
    }
    else return NULL; 

}
