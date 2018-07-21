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
    line[strcspn(line, "\n")] = 0;
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
    
    for( int i =0 ; i < nbIngredient;i++)
    {
        line=NULL;
        lineSize=0;
        getline( &line, &lineSize , recipeFile);
        (LIST_RECIPES[iddRecipe]->listIddIngredients)[i]=atoi(line);
    
        line=NULL;
        lineSize=0;
        getline( &line, &lineSize , recipeFile);
        (LIST_RECIPES[iddRecipe]->listAmount)[i]=atoi(line); 
    }
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
    recipeFile = fopen(RECIPESFILE, "r" );
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

int writeRecipeList(char* recipesFileName){
    extern RECIPE* LIST_RECIPES; 
    extern int NUMBER_RECIPES; 
    FILE* recipesFile = fopen(recipesFileName, "w");
    if( recipesFile==NULL)
    {
        printf("error when trying to open file %s\n", recipesFileName);
        return 0 ; 

    }
    else 
    {
        fprintf(recipesFile, "%d                     - name - iddRecipe -nbingredients - list ingredient - liste amount - idd similar recipe\n", NUMBER_RECIPES);
        for( int i = 0 ; i < NUMBER_RECIPES ; i ++)
        {
            printf("coucou : %s  cououc", LIST_RECIPES[i]->name);
            fprintf(recipesFile,"%s\n", LIST_RECIPES[i]->name);
            fprintf(recipesFile,"%d---------------idd recipe\n", LIST_RECIPES[i]->iddRecipe);
            fprintf(recipesFile,"%d---------------nb ingredients\n", LIST_RECIPES[i]->nbIngredients);
            for( int j = 0 ; j < LIST_RECIPES[i]->nbIngredients; j++)
            {
                fprintf(recipesFile, "%d---------------%s\n" , (LIST_RECIPES[i]->listIddIngredients)[j], ingredient((LIST_RECIPES[i]->listIddIngredients)[j])->name ); 
                fprintf(recipesFile, "%f---------------ml\n" , (LIST_RECIPES[i]->listAmount)[j]); 
            }
            fprintf(recipesFile,"%d---------------idd similar recipe\n", LIST_RECIPES[i]->iddSimilarRecipe);
        }
        fclose(recipesFile);
        return 1;
    }
    return 0;    
}

void freeRecipeList(int saveNewRecipes){
    extern RECIPE* LIST_RECIPES; 
    extern int NUMBER_RECIPES;
    extern int LIST_RECIPES_CHANGED;
    if( saveNewRecipes || LIST_RECIPES_CHANGED )
    {
        char * temporaryName="temporaryRecipes.txt";
        if( writeIngredientList(temporaryName))
        {
            remove(RECIPESFILE);
            rename( temporaryName,RECIPESFILE);
        }
        else
        {
            printf("error when writing recipes list in a new file \n"); 
            remove(temporaryName);
        }
    }
    for (int i = 0 ; i < NUMBER_RECIPES ; i++){
        free(LIST_RECIPES[i]->listAmount);
        free(LIST_RECIPES[i]->listIddIngredients);
        free(LIST_RECIPES[i]); 
    }
    free(LIST_RECIPES);
}

void readRecipe(RECIPE Recipe, int verbose){
    if( verbose){
        printf("name :%s /identifiant :%d  /nb ingredients : %d /idd similar recipe : %d \n",Recipe->name, Recipe->iddRecipe, Recipe->nbIngredients,Recipe->iddSimilarRecipe );
        for( int i = 0; i < Recipe->nbIngredients ; i++ ){
            readIngredient( ingredient((Recipe->listIddIngredients)[i]), verbose ); 
            printf("\n"); 
        }
    }
    else{
        printf("%s",Recipe->name);
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
        readRecipe(LIST_RECIPES[i],Nverbose );
    }
}

int addRecipe(char* name,  int nbIngredients , int*  listIngredients, float* listAmount,int iddSimilarRecipe )
{
    extern RECIPE* LIST_RECIPES; 
    extern int NUMBER_RECIPES;
    extern int LIST_RECIPES_CHANGED;
    RECIPE* newRecipesList=realloc(LIST_RECIPES,(NUMBER_RECIPES+1)*sizeof(*LIST_RECIPES));
    if( newRecipesList==NULL)
    {
        printf("error when reallocating space to new recipe list\n");
        return 0;
    }
    else
    {
        LIST_RECIPES=newRecipesList;
        LIST_RECIPES[NUMBER_RECIPES]=calloc(1,sizeof(**LIST_RECIPES));
        if( LIST_RECIPES[NUMBER_RECIPES]==NULL)
        {
            printf("error when allocating dpace to new recipe");
            return 0;
        }
        
        else
        {
            LIST_RECIPES[NUMBER_RECIPES]->name= name;
            LIST_RECIPES[NUMBER_RECIPES]->iddRecipe=NUMBER_RECIPES;
            LIST_RECIPES[NUMBER_RECIPES]->nbIngredients= nbIngredients;
            LIST_RECIPES[NUMBER_RECIPES]->listAmount= listAmount;
            LIST_RECIPES[NUMBER_RECIPES]->listIddIngredients= listIngredients;
            LIST_RECIPES[NUMBER_RECIPES]->iddSimilarRecipe= iddSimilarRecipe;
            NUMBER_RECIPES++;
            LIST_RECIPES_CHANGED++;
            return 1; 
        }
        
    }
}

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