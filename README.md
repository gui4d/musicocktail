# musicocktail
an electrical version of the so called pianocktail created by Boris Vian  in L'ecume des jours 


#to be started 

to do some basics things  you can write a main() function  like that:

int main() 
{
    first you have to declare the global variables  depending if you will use them : 
    //extern INGREDIENT* LIST_INGREDIENTS;
    extern int NUMBER_INGREDIENTS;
    //extern RECIPE* LIST_RECIPES; 
    extern int NUMBER_RECIPES;
    

    initIngredientList(); // alocate and complet de the global variables extern int NUMBER_INGREDIENTS and  extern INGREDIENT* LIST_INGREDIENTS
    printf("\n\nnombre d'ingrédient disponibles : %d \n",NUMBER_INGREDIENTS);
    readAllIngredients(); // print in the terminal LIST_INGREDIENTS
    initRecipeList();
    printf("\n\nnombre de cocktails disponibles : %d \n",NUMBER_RECIPES);
    readAllRecipes();
    addIngredient("wisky", 3.12, 10.1 , 49.2);// complete extern INGREDIENT* LIST_INGREDIENTS with the one declared. 
    freeIngredientList(Save); // should always be used at the end of the main fonction , it free  allocation and writ the changes in the database. you can alternativelly use freeIngredientList(Nsave) if you don't want to register wisky in your database 
}


to compile : you just have to write "make install" in your teminal and then run the programe. 


next modifications :
add servomoteur idd parameter for ingredients
add presence parameter for ingredients