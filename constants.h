#ifndef _CONSTANTS
#define _CONSTANTS

#define True 1
#define False 0

#define Yes 1
#define No 0

#define Save 1
#define Nsave 0

#define VERBOSE 1
#define NVERBOSE 0

#define RECIPESFILE "recipes.txt"
#define INGREDIENTSFILE "ingredients.txt"

#ifdef __cplusplus
extern "C" {
#endif

void clean_stdin(void) ;

#ifdef __cplusplus
}
#endif

#endif