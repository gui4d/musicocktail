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
#include <gtkmm/dialog.h>
#include <gtkmm/textview.h>
#include <gtkmm/checkbutton.h>
#include <fstream> 

#include "constants.h"
#include "ingredient.h"
#include "recipes.h"
#include "music.h"
#include "music.h"
#include "serialCommunication.h"
#include "musicAnalysis/streaming_extractor_music.h"


class MainNotebook : public Gtk::Notebook {

    public: 
        MainNotebook();

    private:        

        Gtk::VButtonBox* pwelcomBox;

        void changeIngredientPlace(int emplacement,int iddpreviousingredient);
        std::vector <Gtk::ComboBoxText*> tabPSelectedIngredients;
        void _saveIngredientList();
        void _resetIngredientPlace(int place);

        void  initAddIngredientThroughtInterface();
        void  closeAddIngredientThroughtInterface(int save);
        Gtk::VButtonBox* pingredientsList;
        int newIngredientPage;
        int newIngredientPageNumber;
        Gtk::Entry newIngredientName;
        //Gtk::SpinButton saltEntry;
        //Gtk::SpinButton sugarEntry;
        //Gtk::SpinButton strenghtEntry;
        Gtk::SpinButton servoEntry;


        void openIngredientParameter(int iddIngredient);
        void editIngredientParameter(int iddIngredient , Gtk::SpinButton* pservoEntry);
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
        std::vector <Gtk::CheckButton*> tabpdescriptorCheckNew;
        std::vector <Gtk::CheckButton*> tabpdescriptorCheckEdit;

        void openRecipeParameter(int iddRecipe);
        void runRecipe(int iddRecipe);
        void closeRecipeParameter();
        int paramRecipePage;
        int paramRecipePageNumber;

        Gtk::VButtonBox* pmusicsBox;

        void launchMusicAnalysis();
        void launchMusicFileDialog();
        Gtk::Label musicPath;
        char* MusicFilePath=NULL; 
        Gtk::TextView * pAnalysisResultBox;
        Gtk::TextBuffer * pAnalysisResultText;
    
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