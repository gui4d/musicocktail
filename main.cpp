#include <string>

#include <gtkmm/main.h>
#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/stock.h>
#include <gtkmm/alignment.h>
#include <gtkmm/box.h>
#include <gtkmm/notebook.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/label.h>
#include <gtkmm/entry.h>
#include <gtkmm/adjustment.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/comboboxtext.h>

#include "src/constants.h"
#include "src/ingredient.h"
#include "src/recipes.h"
#include "src/music.h"
#include "src/interface.h"
#include "src/music.h"
#include "src/serialCommunication.h"

INGREDIENT *LIST_INGREDIENTS = NULL;
int NUMBER_INGREDIENTS = 0;
int LIST_INGREDIENTS_CHANGED = 0;
RECIPE *LIST_RECIPES = NULL;
int NUMBER_RECIPES = 0;
int LIST_RECIPES_CHANGED = 0;
DESCRIPTOR *LIST_DESCRIPTORS = NULL;
int NUMBER_DESCRIPTORS = 0;
int FLOWS[16] ;
int FLOWSCHANGED = 0;

int main(int argc, char *argv[])
{

    initIngredientList();
    initRecipeList();
    initDescriptorsList();
    initFlowList();
    Gtk::Main app(argc, argv);
    MainWindow mainWindow;
    Gtk::Main::run(mainWindow);

    return 1;
}