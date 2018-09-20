#ifndef _INTERFACE
#define _INTERFACE

#include <string.h>
#include <vector>
#include<gtkmm/main.h>
#include<gtkmm/window.h>
#include<gtkmm/button.h>
#include<gtkmm/stock.h>
#include<gtkmm/alignment.h>
#include<gtkmm/box.h>
#include<gtkmm/notebook.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/label.h>
#include <gtkmm/entry.h>
#include <gtkmm/adjustment.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/comboboxtext.h>

#include "constants.h"
#include "ingredient.h"
#include "recipes.h"
#include "music.h"

/*class RecipeElement : public Gtk::HBox {

    public:
        RecipeElement();
        int getIddIngredient();
        int getAmountIngredient();
    private:
        Gtk::Label ingredient;
        Gtk::Label amount;
        Gtk::ComboBoxText ingredientName;
        Gtk::SpinButton ingredientAmount;


};*/

class MainNotebook : public Gtk::Notebook {

    public: 
        MainNotebook();

    private:
        void  initAddIngredientThroughtInterface();
        void  closeAddIngredientThroughtInterface(int save);
        

        Gtk::VButtonBox* pwelcomBox;

        Gtk::VButtonBox* pingredientsList;

        int newIngredientPage=0;
        int newIngredientPageNumber=1;
        Gtk::Entry newIngredientName;
        Gtk::SpinButton saltEntry;
        Gtk::SpinButton sugarEntry;
        Gtk::SpinButton strenghtEntry;
        Gtk::SpinButton servoEntry;

        Gtk::VButtonBox* precipesList;

        int newRecipePage=0;
        int newRecipePageNumber=2;
        Gtk::Entry newRecipeName;
        Gtk::SpinButton NumberIngredientsEntry;
        Gtk::ComboBoxText* psimilareRecipeEntry;
        Gtk::VBox* pRecipeElementsList;
        std::vector <Gtk::HBox*> tabpRecipeElement;
        std::vector <Gtk::ComboBoxText*> tabpIngredients;
        std::vector <Gtk::SpinButton*> tabpAmount;
        Gtk::ComboBoxText iddSimilarRecipe;

        void initAddRecipeThroughtInterface();
        void closeAddRecipeThroughtInterface(int save);
        void actuateNumberIngredients();

        Gtk::VButtonBox* pmusicsBox;
};

class MainWindow : public Gtk::Window {

    public: 
        MainWindow();

    private:
        MainNotebook mainNotebook;
        void closeMainWindow();


};







#endif