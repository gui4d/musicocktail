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
#include"ingredient.h"
#include"recipes.h"
#include "music.h"
#include "music.h"
#include "serialCommunication.h"

class MainNotebook : public Gtk::Notebook {

    public: 
        MainNotebook();

    private:        

        Gtk::VButtonBox* pwelcomBox;

        Gtk::VButtonBox* pingredientsList;
        void  initAddIngredientThroughtInterface();
        void  closeAddIngredientThroughtInterface(int save);
        int newIngredientPage;
        int newIngredientPageNumber;
        Gtk::Entry newIngredientName;
        Gtk::SpinButton saltEntry;
        Gtk::SpinButton sugarEntry;
        Gtk::SpinButton strenghtEntry;
        Gtk::SpinButton servoEntry;

        void openIngredientParameter(int iddIngredient);
        void editIngredientParameter(int iddIngredient, Gtk::SpinButton* psaltEntry, Gtk::SpinButton* psugarEntry, Gtk::SpinButton* pstrenghtEntry , Gtk::SpinButton* pservoEntry);
        void closeIngredientParameter();
        int paramIngredientPage;
        int paramIngredientPageNumber;

        Gtk::VButtonBox* precipesList;

        void initAddRecipeThroughtInterface();
        void closeAddRecipeThroughtInterface(int save);
        void actuateNumberIngredients();
        int newRecipePage;
        int newRecipePageNumber;
        Gtk::Entry newRecipeName;
        Gtk::SpinButton NumberIngredientsEntry;
        Gtk::ComboBoxText* psimilareRecipeEntry;
        Gtk::VBox* pRecipeElementsList;
        std::vector <Gtk::HBox*> tabpRecipeElement;
        std::vector <Gtk::ComboBoxText*> tabpIngredients;
        std::vector <Gtk::SpinButton*> tabpAmount;
        Gtk::ComboBoxText iddSimilarRecipe;

        void openRecipeParameter(int iddRecipe);
        void runRecipe(int iddRecipe);
        void closeRecipeParameter();
        int paramRecipePage;
        int paramRecipePageNumber;

        Gtk::VButtonBox* pmusicsBox;

        int ArduinoPort;
        int ArduinoFailed;

        void updatePageNumerotation( int numberPageRemoved);
};

class MainWindow : public Gtk::Window {

    public: 
        MainWindow();

    private:
        MainNotebook mainNotebook;
        void closeMainWindow();


};







#endif