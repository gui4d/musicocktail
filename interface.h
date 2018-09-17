#ifndef _INTERFACE
#define _INTERFACE

#include <string.h>
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

#include "constants.h"
#include "ingredient.h"
#include "recipes.h"
#include "music.h"


class MainNotebook : public Gtk::Notebook {

    public: 
        MainNotebook();

    private:
        void  initAddIngredientThroughtInterface();
        void  closeAddIngredientThroughtInterface(int save);
        void  addRecipeThroughtInterface(int numPage );

        Gtk::VButtonBox* pwelcomBox;

        Gtk::VButtonBox* pingredientsBox;
        int newIngredientPage=0;
        int newIngredientPageNumber=1;
        Gtk::Entry newIngredientName;
        Gtk::SpinButton saltEntry;
        Gtk::SpinButton sugarEntry;
        Gtk::SpinButton strenghtEntry;
        Gtk::SpinButton servoEntry;

        Gtk::VButtonBox* precipesBox;

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