#include "recipes.h"

int initNb(FILE* recipeFile)
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
    
    int i;
    for(i =0 ; i < nbIngredient;i++)
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

    line=NULL;
    lineSize=0;
    getline( &line, &lineSize , recipeFile);
    int description = atoi(line);
    LIST_RECIPES[iddRecipe]->recipeDescription=description;
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
        NUMBER_RECIPES=initNb(recipeFile);
        LIST_RECIPES=calloc(NUMBER_RECIPES,sizeof(*LIST_RECIPES));
        int i;
        for(i = 0 ; i < NUMBER_RECIPES; i++){
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
        int i;
        for( i = 0 ; i < NUMBER_RECIPES ; i ++)
        {
            printf("%s \n", LIST_RECIPES[i]->name);
            fprintf(recipesFile,"%s\n", LIST_RECIPES[i]->name);
            fprintf(recipesFile,"%d---------------idd recipe\n", LIST_RECIPES[i]->iddRecipe);
            fprintf(recipesFile,"%d---------------nb ingredients\n", LIST_RECIPES[i]->nbIngredients);
            int j ;
            for( j = 0 ; j < LIST_RECIPES[i]->nbIngredients; j++)
            {
                fprintf(recipesFile, "%d---------------%s\n" , (LIST_RECIPES[i]->listIddIngredients)[j], ingredient((LIST_RECIPES[i]->listIddIngredients)[j])->name ); 
                fprintf(recipesFile, "%f---------------ml\n" , (LIST_RECIPES[i]->listAmount)[j]); 
            }
            if(LIST_RECIPES[i]->iddSimilarRecipe!=-1){
                 fprintf(recipesFile,"%d---------------similar recipe :%s\n", LIST_RECIPES[i]->iddSimilarRecipe,recipe(LIST_RECIPES[i]->iddSimilarRecipe)->name);
            }
            else{
                fprintf(recipesFile,"%d--------------- original recipe \n", LIST_RECIPES[i]->iddSimilarRecipe);

            }
            fprintf(recipesFile,"%ld---------------Description tag \n", LIST_RECIPES[i]->recipeDescription);
           
            
        }
        fclose(recipesFile);
        return 1;
    }
    return 0;    
}

int saveRecipeList(){
    extern int LIST_RECIPES_CHANGED;
    if(LIST_RECIPES_CHANGED){
        char * temporaryName="temporaryRecipes.txt";
        if( writeRecipeList(temporaryName))
        {
            remove(RECIPESFILE);
            rename( temporaryName,RECIPESFILE);
            LIST_RECIPES_CHANGED = 0;
            return 1;

        }
        else
        {
            printf("error when writing recipes list in a new file \n"); 
            remove(temporaryName);
            return 0;
        }
    } 
    else return 1; 
}

void freeRecipeList(int saveNewRecipes ){
    
    extern RECIPE* LIST_RECIPES; 
    extern int NUMBER_RECIPES;
    
    if( saveNewRecipes )
    {
        saveRecipeList();
    }
    int i;
    for (i = 0 ; i < NUMBER_RECIPES ; i++){
        free(LIST_RECIPES[i]->listAmount);
        free(LIST_RECIPES[i]->listIddIngredients);
        free(LIST_RECIPES[i]); 
    }
    free(LIST_RECIPES);
    NUMBER_RECIPES = 0;
    LIST_RECIPES = NULL;
}

void readRecipe(RECIPE Recipe, int verbose){
    if( verbose){
        printf("name :%s /identifiant :%d  /nb ingredients : %d /idd similar recipe : %d/ tag descrition : %ld\n",Recipe->name, Recipe->iddRecipe, Recipe->nbIngredients,Recipe->iddSimilarRecipe,Recipe->recipeDescription );
         int i;
        for(i = 0; i < Recipe->nbIngredients ; i++ ){
            printf("    -");
            readIngredient( ingredient((Recipe->listIddIngredients)[i]), VERBOSE); 
            printf("\n"); 
        }
    }
    else{
        printf("%s\n",Recipe->name);
    }
}

void readAllRecipes(int verbose){
    extern RECIPE* LIST_RECIPES; 
    extern int NUMBER_RECIPES;
    int i;
    for( i = 0; i <NUMBER_RECIPES ; i++){
        if(verbose) printf("%d :",i);
        readRecipe(LIST_RECIPES[i],verbose);
    }
}

int addRecipe(char* name,  int nbIngredients , int*  listIngredients, float* listAmount,int iddSimilarRecipe, unsigned long tagDescription )
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
            printf("error when allocating space to new recipe");
            return 0;
        }
        
        else
        {
            LIST_RECIPES[NUMBER_RECIPES]->name= strdup(name);
            LIST_RECIPES[NUMBER_RECIPES]->iddRecipe=NUMBER_RECIPES;
            LIST_RECIPES[NUMBER_RECIPES]->nbIngredients= nbIngredients;
            LIST_RECIPES[NUMBER_RECIPES]->listAmount= listAmount;
            LIST_RECIPES[NUMBER_RECIPES]->listIddIngredients= listIngredients;
            LIST_RECIPES[NUMBER_RECIPES]->iddSimilarRecipe= iddSimilarRecipe;
            LIST_RECIPES[NUMBER_RECIPES]->recipeDescription= tagDescription;
            NUMBER_RECIPES++;
            LIST_RECIPES_CHANGED++;
            return 1; 
        }
        
    }
}

int addRecipeThroughtTerminal(){
    char name[100];
    int nbIngredients;
    int* listIngredients = NULL;
    float* listAmount = NULL;
    int iddSimilarRecipe;
    int tagDescription;
    printf("nouveau cocktail :");
    clean_stdin();
    printf("donnez le nom de votre cocktail :\n ");
    fgets(name,99,stdin);
    name[strcspn(name, "\n")] = 0;
    printf("votre cocktail : %s donner le nombre d'ingredient :",name);
    scanf("%d",&nbIngredients);
    listAmount =calloc(nbIngredients, sizeof(*listAmount));
    listIngredients = calloc(nbIngredients, sizeof(*listIngredients)); 
    int i;
    for( i = 0 ; i<nbIngredients ; i++){
        printf("---------------------------\n--liste des ingredients--\n");
        readAllIngredients(VERBOSE);
        printf(" %d° ingredient , donner son numero : ", i+1);
        scanf("%d",&listIngredients[i]);
        printf("%s , quelle quantité (ml) :",ingredient(listIngredients[i])->name);
        scanf("%f",&listAmount[i]);
    }
    printf("----------------------------------\nce cocktail est il inspiré d'un autre ?\n ");
    readAllRecipes(VERBOSE);
    printf("donner son numero (-1 s'il n'y en a pas ) :");
    scanf("%d",&iddSimilarRecipe);
    printf("----------------------------------\nce cocktail a t'il un tag de description ?\n ");
    printf("donner son numero (0 s'il n'y en a pas ) :");
    scanf("%d",&tagDescription);
    return addRecipe(name,nbIngredients ,listIngredients,  listAmount, iddSimilarRecipe,tagDescription );
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

int initDescriptor(FILE* descriptorFile, int i ){
    
    extern DESCRIPTOR * LIST_DESCRIPTORS; 
    char* line;
    size_t lineSize=0;
    getline( &line, &lineSize , descriptorFile);
    line[strcspn(line, "\n")] = 0;
    LIST_DESCRIPTORS[i]->name = strdup(line);//here a segmentation fault
    return 1;
} 

int initDescriptorsList()
{
    extern DESCRIPTOR* LIST_DESCRIPTORS; 
    extern int NUMBER_DESCRIPTORS;
    FILE* descriptorFile=NULL;
    descriptorFile = fopen(RECIPEDESCRIPTORFILE, "r" );
    if(descriptorFile!=NULL)
    {
        NUMBER_DESCRIPTORS=initNb(descriptorFile);
        LIST_DESCRIPTORS=calloc(NUMBER_DESCRIPTORS,sizeof(*LIST_DESCRIPTORS));
        
        int i;
        for (i = 0 ; i < NUMBER_DESCRIPTORS; i++){
            LIST_DESCRIPTORS[i]=calloc(1,sizeof(*LIST_DESCRIPTORS[i]));
            initDescriptor(descriptorFile,i);
        } 
        fclose(descriptorFile);
        return 1 ;
    }
    else 
    {
        printf("error when reading descriptor database\n");
        return 0;
    }
}

int* descriptorTagtoList(unsigned long tagDescriptor){
    extern int NUMBER_DESCRIPTORS;
    int* descriptorList = calloc( NUMBER_DESCRIPTORS,sizeof(*descriptorList));
    unsigned long currentTag=tagDescriptor;
    int i; 
    for(i =0; i< NUMBER_DESCRIPTORS; i++){
        descriptorList[i]=currentTag%2;
        currentTag=currentTag/2;   
    }
    return descriptorList;
}

unsigned long descriptorListtoTag(int* descriptorList){
    extern int NUMBER_DESCRIPTORS;
    unsigned long descriptorTag= 0;
    int i ;
    unsigned long power2=1;
    for(i=0;i<NUMBER_DESCRIPTORS;i++){
        if(descriptorList[i]) descriptorTag+=power2;
        power2*=2;
    }
    return descriptorTag;


}

