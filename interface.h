#ifndef _INTERFACE
#define _INTERFACE


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
        //int addNEwPAge( int type );
        

};

class MainWindow : public Gtk::Window {

    public: 
        MainWindow();

    private:
        MainNotebook mainNotebook;


};





#endif