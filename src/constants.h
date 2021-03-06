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
#define FLOWFILE "medias/flows.txt"
#define ICONEFILE "medias/icone.png"
#define RECIPEDESCRIPTORFILE "medias/recipeDescriptors.txt"
#define MAXNUMBERDESCRIPTOR 32

#define MUSICANALYSISPROFILEFILE "src/musicAnalysis/profiles/all_config.yaml"
#define MUSICANALYSISRESULTSFILE "results_last_music_analysis.yaml"


#define MAXSALT 100 
#define MAXSUGAR 100
#define MAXSTRENGHT 100

#define ARDUINOADRESS "/dev/ttyUSB0"

#define SERVOSLOTNUMBER 10

#define HEIGHT 600
#define WIDTH 600


#ifdef __cplusplus
extern "C" {
#endif

void clean_stdin(void) ;


int initFlowList();
int saveFlowList();
void readAllFlows();
int editFlow( int servoAdress, int Flow);

#ifdef __cplusplus
}
#endif

#endif