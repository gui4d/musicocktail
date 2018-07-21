#include "cocktail.h"


int initNbRecipe(FILE* recipeFile)
{
    char* charNbRecipe=NULL;  
    size_t charSize=0;
    getline( &charNbRecipe, &charSize , recipeFile);
    int nbRecipes=atoi(charNbRecipe);
    return nbRecipes;
}


int initRecipe(FILE* recipeFile,int iddRecipe )
{
    extern RECIPE* LIST_RECIPES; 
    char* line=NULL;
    size_t lineSize=0;
    getline( &line, &lineSize , recipeFile);
    LIST_RECIPES[iddRecipe]->name= strdup(line);
    
    line=NULL;
    lineSize=0;
    getline( &line, &lineSize , recipeFile);
    LIST_RECIPES[iddRecipe]->iddRecipe=atoi(line);
    
    line=NULL;
    lineSize=0;
    getline( &line, &lineSize , recipeFile);
    int nbIngredient = atoi(line);
    LIST_RECIPES[iddRecipe]->nbIngredients=nbIngredient;

    LIST_RECIPES[iddRecipe]->listIddIngredients=calloc(nbIngredient,sizeof(*(LIST_RECIPES[iddRecipe]->listIddIngredients)));
    LIST_RECIPES[iddRecipe]->listAmount=calloc(nbIngredient,sizeof(*(LIST_RECIPES[iddRecipe]->listAmount)));
    float quantitee = 0;
    for( int i =0 ; i < nbIngredient;i++){
        line=NULL;
        lineSize=0;
        getline( &line, &lineSize , recipeFile);
        (LIST_RECIPES[iddRecipe]->listIddIngredients)[i]=atoi(line);
    
        line=NULL;
        lineSize=0;
        getline( &line, &lineSize , recipeFile);
        (LIST_RECIPES[iddRecipe]->listAmount)[i]=atoi(line);
    
        quantitee += (LIST_RECIPES[iddRecipe]->listAmount)[i];
    }

    LIST_RECIPES[iddRecipe]->amount=quantitee;

    line=NULL;
    lineSize=0;
    getline( &line, &lineSize , recipeFile);
    LIST_RECIPES[iddRecipe]->iddSimilarRecipe=atoi(line);
    return 1;
} 

int initRecipeList()
{
    extern RECIPE* LIST_RECIPES; 
    extern int NUMBER_RECIPES;
    FILE* recipeFile=NULL;
    recipeFile = fopen("recipes.txt", "r" );
    if(recipeFile!=NULL)
    {
        NUMBER_RECIPES=initNbIngredient(recipeFile);
        LIST_RECIPES=calloc(NUMBER_RECIPES,sizeof(*LIST_RECIPES));
        for(int i = 0 ; i < NUMBER_RECIPES; i++){
            LIST_RECIPES[i]=calloc(1,sizeof(*LIST_RECIPES[i]));
            initRecipe(recipeFile, i );
        } 
        fclose(recipeFile);
        return 1 ;
    }
    else 
    {
        printf("error when reading database\n");
        return 0;
    }
}

void freeRecipeList(){
    extern RECIPE* LIST_RECIPES; 
    extern int NUMBER_RECIPES;
    for (int i = 0 ; i < NUMBER_RECIPES ; i++){
        free(LIST_RECIPES[i]->listAmount);
        free(LIST_RECIPES[i]->listIddIngredients);
        free(LIST_RECIPES[i]); 
    }
    free(LIST_RECIPES);
}

void readRecipe(RECIPE Recipe, int verbose){
    if( verbose){
        printf("name :%s /identifiant :%d /amount :%f  /nb ingredients : %d /idd similar recipe : %d \n",Recipe->name, Recipe->iddRecipe,Recipe->amount, Recipe->nbIngredients,Recipe->iddSimilarRecipe );
        for( int i = 0; i < Recipe->nbIngredients ; i++ ){
            readIngredient( ingredient((Recipe->listIddIngredients)[i]), verbose ); 
            printf("\n"); 
        }
    }
    else{
        printf("name: %s",Recipe->name);
        for( int i = 0; i < Recipe->nbIngredients ; i++ ){
            readIngredient( ingredient((Recipe->listIddIngredients)[i]), verbose ); 
            printf("%f ml\n",Recipe->listAmount[i]); 
        }

    }
}

void readAllRecipes(){
    extern RECIPE* LIST_RECIPES; 
    extern int NUMBER_RECIPES;
    for( int i = 0; i <NUMBER_RECIPES ; i++){
        readRecipe(LIST_RECIPES[i],0);
    }
}

int addRecipe(char* name,float amount, int nbIngredients, INGREDIENT* listIngredients, float* listAmount, int iddRecipe, RECIPE similarRecipe, int iddSimilarRecipe );


RECIPE recipe( int iddRecipe){
    extern RECIPE* LIST_RECIPES; 
    extern int NUMBER_RECIPES;
    if( iddRecipe>=0 || NUMBER_RECIPES>iddRecipe || LIST_RECIPES!= NULL){
        return LIST_RECIPES[iddRecipe];
    }
    else 
    {
        return NULL;
    }
}