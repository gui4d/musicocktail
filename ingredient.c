#include "ingredient.h"


int initNbIngredient(FILE* ingredientFile)
{
    if(ingredientFile== NULL)return 0; 
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
    line[strcspn(line, "\n")] = 0;
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
    ingredientFile = fopen(INGREDIENTSFILE, "r" );
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

int writeIngredientList(char * IngrdientFileName)
{
    extern INGREDIENT* LIST_INGREDIENTS;
    extern int NUMBER_INGREDIENTS;
    FILE* ingredientFile;
    ingredientFile = fopen(IngrdientFileName, "w");
    if( ingredientFile == NULL){
        printf("error when trying to open file %s \n ", IngrdientFileName); 
        return 0 ;
    }
    else{
        fprintf(ingredientFile,"%d                           -name - salt - sugar - strenght - iddingredient \n",NUMBER_INGREDIENTS);
        for( int i = 0 ; i < NUMBER_INGREDIENTS ; i++)
        {
          fprintf(ingredientFile,"%s\n", LIST_INGREDIENTS[i]->name); 
          fprintf(ingredientFile,"%f---------------salt\n", LIST_INGREDIENTS[i]->salt);
          fprintf(ingredientFile,"%f---------------sugar\n", LIST_INGREDIENTS[i]->sugar);
          fprintf(ingredientFile,"%f---------------strenght\n", LIST_INGREDIENTS[i]->strenght);
          fprintf(ingredientFile,"%d---------------idd ingredient\n", LIST_INGREDIENTS[i]->iddIngredient);    
        }
        fclose(ingredientFile);
    }
    return 1;
}


void freeIngredientList(int saveNewIngredients)
{
    extern INGREDIENT* LIST_INGREDIENTS;
    extern int NUMBER_INGREDIENTS;
    if(saveNewIngredients){
        FILE* ingredientsFile= NULL;
        ingredientsFile= fopen(INGREDIENTSFILE,"r");
        if(ingredientsFile==NULL){
            printf("error when  opening ingredient file , new ingredients can't be saved \n");
        }
        else{
            int previousNumberIngredient = initNbIngredient(ingredientsFile);
            fclose(ingredientsFile);
            if(previousNumberIngredient< NUMBER_INGREDIENTS){
                char * temporaryName="temporaryIngredients.txt";
                if( writeIngredientList(temporaryName))
                {
                    remove(RECIPESFILE);
                    rename(temporaryName,RECIPESFILE);
                }
                
                else
                {
                   printf("error when writing ingredients list in a new file \n"); 
                   remove(temporaryName);
                }
               
            }
        }
    }

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

int addIngredient(char* name, float salt, float sugar , float strenght)
{
    extern INGREDIENT* LIST_INGREDIENTS;
    extern int NUMBER_INGREDIENTS;
   INGREDIENT* newIngredientList=realloc(LIST_INGREDIENTS,(NUMBER_INGREDIENTS+1)*sizeof(*LIST_INGREDIENTS)); 
   if(newIngredientList==NULL) {
       printf("error when reallocating space to new ingredient list\n");
       return 0;
   }
   else{
       LIST_INGREDIENTS=newIngredientList;
       LIST_INGREDIENTS[NUMBER_INGREDIENTS]=calloc(1, sizeof(**LIST_INGREDIENTS));
       if(LIST_INGREDIENTS[NUMBER_INGREDIENTS]== NULL){
           printf("error when allocating space to new ingredient\n");
           return 0 ;
       }
       else{
           LIST_INGREDIENTS[NUMBER_INGREDIENTS]->name=strdup(name);
           LIST_INGREDIENTS[NUMBER_INGREDIENTS]->salt= salt;
           LIST_INGREDIENTS[NUMBER_INGREDIENTS]->salt= sugar;
           LIST_INGREDIENTS[NUMBER_INGREDIENTS]->sugar=strenght;
           LIST_INGREDIENTS[NUMBER_INGREDIENTS]->iddIngredient= NUMBER_INGREDIENTS;
           NUMBER_INGREDIENTS++;
           return 1 ;
       } 
   }
}

INGREDIENT ingredient(int iddIngredient){
    extern INGREDIENT* LIST_INGREDIENTS;
    extern int NUMBER_INGREDIENTS;

    if(iddIngredient>=0 || NUMBER_INGREDIENTS>iddIngredient || LIST_INGREDIENTS!=NULL){
        return LIST_INGREDIENTS[iddIngredient];
    }
    else return NULL; 

}
