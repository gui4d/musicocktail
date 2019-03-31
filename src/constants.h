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

#define RECIPESFILE "medias/recipes.txt"
#define INGREDIENTSFILE "medias/ingredients.txt"
#define ICONEFILE "medias/icone.png"
#define RECIPEDESCRIPTORFILE "medias/recipeDescriptors.txt"

#define MUSICANALYSISPROFILEFILE "src/musicAnalysis/profiles/all_config.yaml"
#define MUSICANALYSISRESULTSFILE "results_last_music_analysis.yaml"

#define MAXSALT 100 
#define MAXSUGAR 100
#define MAXSTRENGHT 100

#define ARDUINOADRESS "/dev/ttyUSB0"

#define SERVOSLOTNUMBER 16

#define HEIGHT 600
#define WIDTH 400


#ifdef __cplusplus
extern "C" {
#endif

void clean_stdin(void) ;

#ifdef __cplusplus
}
#endif

#endif