#include <string>

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

#include"ingredient.h"
#include"recipes.h"
#include "constants.h"
#include "ingredient.h"
#include "demo.h"
#include "music.h"

//need to create a bunch of objects in order to  make better interactions between widgets

INGREDIENT* LIST_INGREDIENTS=NULL;
int NUMBER_INGREDIENTS = 0;
int LIST_INGREDIENTS_CHANGED = 0; 
RECIPE* LIST_RECIPES=NULL; 
int NUMBER_RECIPES=0;
int LIST_RECIPES_CHANGED = 0;


void close_appli(){

    freeRecipeList(Save);
    freeIngredientList(Save);
    Gtk::Main::quit();
}

void refresh_appli(){


}

void saveNewIngredientThroughtInterface(std::string Sname, int salt, int sugar , int strenght, int servoAdress){

    char name[Sname.size()+1];
    std::copy(Sname.begin(),Sname.end(), name);
    addIngredient(name,(float)(salt), (float) (sugar) , (float) (strenght), servoAdress);
    //metre une boite de dialogue si l'enregistrement s'est mal passé
}


void addIngredientThroughtInterface(){

    extern INGREDIENT* LIST_INGREDIENTS;
    extern int NUMBER_INGREDIENTS;
    
    Gtk::Window addIngredientWindow;
    addIngredientWindow.set_default_size(WIDTH, HEIGHT);
    addIngredientWindow.set_border_width(10);
    addIngredientWindow.set_title("Musicocktail: ajouter un ingredient");
    addIngredientWindow.set_icon_from_file("icone.png");
        Gtk::VBox addIngredientBox(false,10);
            Gtk::Label titleLabel("Nouvel ingrédient : création de la fiche");
            titleLabel.set_justify(Gtk::JUSTIFY_CENTER);
            titleLabel.set_line_wrap();
            titleLabel.set_can_focus(false);
        addIngredientBox.pack_start(titleLabel);

            Gtk::HBox nameBox(false,10);
            nameBox.set_can_focus(false);
                Gtk::Label nameLabel("nom :");
                nameLabel.set_can_focus(false);
            nameBox.pack_start(nameLabel);
                Gtk::Entry nameEntry;
                nameEntry.set_text("rentrer le nom");
                nameEntry.set_max_length(100);
            nameBox.pack_start(nameEntry);
        addIngredientBox.pack_start(nameBox);

            Gtk::HBox saltBox(false,10);
            saltBox.set_can_focus(false);
                Gtk::Label saltLabel("taux de sel en g/L :");
                saltLabel.set_can_focus(false);
            saltBox.pack_start(saltLabel);
                Glib::RefPtr<Gtk::Adjustment> ajustementsalt = Gtk::Adjustment::create(0, 0, 100, 1);
                Gtk::SpinButton saltEntry(ajustementsalt);
                saltEntry.set_numeric();
            saltBox.pack_start(saltEntry);
        addIngredientBox.pack_start(saltBox);

            Gtk::HBox sugarBox(false,10);
            sugarBox.set_can_focus(false);
                Gtk::Label sugarLabel("taux de sucre en g/L :");
                sugarLabel.set_can_focus(false);
            sugarBox.pack_start(sugarLabel);
                Glib::RefPtr<Gtk::Adjustment> ajustementSugar = Gtk::Adjustment::create(0, 0, 100, 1);
                Gtk::SpinButton sugarEntry(ajustementSugar);
                sugarEntry.set_numeric();
            sugarBox.pack_start(sugarEntry);
        addIngredientBox.pack_start(sugarBox);

            Gtk::HBox strenghtBox(false,10);
            strenghtBox.set_can_focus(false);
                Gtk::Label strenghtLabel("taux d'alcoolémie en % :");
                strenghtLabel.set_can_focus(false);
            strenghtBox.pack_start(strenghtLabel);
                Glib::RefPtr<Gtk::Adjustment> ajustementStrenght = Gtk::Adjustment::create(0, 0, 100, 1);
                Gtk::SpinButton strenghtEntry(ajustementStrenght);
                strenghtEntry.set_numeric();
            strenghtBox.pack_start(strenghtEntry);
        addIngredientBox.pack_start(strenghtBox);

            Gtk::HBox servoBox(false,10);
            servoBox.set_can_focus(false);
                Gtk::Label servoLabel("numero sur le bar (-1 si il n'est pas sur le bar ):");
                servoLabel.set_can_focus(false);
            servoBox.pack_start(servoLabel);
                Glib::RefPtr<Gtk::Adjustment> ajustementServo = Gtk::Adjustment::create(-1, -1, 15, 1);
                Gtk::SpinButton servoEntry(ajustementServo);
                servoEntry.set_numeric();
            servoBox.pack_start(servoEntry);
        addIngredientBox.pack_start(servoBox);

            Gtk::HBox actionBox(false,10);
            actionBox.set_can_focus(false);
                Gtk::Button saveButton(Gtk::Stock::SAVE);
                saveButton.signal_clicked().connect(sigc::bind<std::string,int,int,int,int>(sigc::ptr_fun(&saveNewIngredientThroughtInterface),nameEntry.get_text(),saltEntry.get_value_as_int(), sugarEntry.get_value_as_int(), strenghtEntry.get_value_as_int(),servoEntry.get_value_as_int() ));
            actionBox.pack_start(saveButton);
                Gtk::Button quitButton(Gtk::Stock::QUIT);
            actionBox.pack_start(quitButton);

        addIngredientBox.pack_end(actionBox);
    
    addIngredientWindow.add(addIngredientBox);
    addIngredientWindow.show_all();
    Gtk::Main::run(addIngredientWindow);
}

void addRecipeThroughtInterface(){
    Gtk::Window addRecipeWindow;
    addRecipeWindow.set_default_size(WIDTH, HEIGHT);
    addRecipeWindow.set_border_width(10);
    addRecipeWindow.set_title("Musicocktail: ajouter une recette");
    addRecipeWindow.set_icon_from_file("icone.png");


}




int main(int argc, char* argv[]){

    extern INGREDIENT* LIST_INGREDIENTS;
    extern int NUMBER_INGREDIENTS;
    extern RECIPE* LIST_RECIPES; 
    extern int NUMBER_RECIPES;

    initIngredientList();
    readAllIngredients(VERBOSE);
    initRecipeList();
    readAllRecipes(NVERBOSE);

    Gtk::Main app(argc, argv);
    Gtk::Window mainWindow;
    mainWindow.set_default_size(WIDTH,HEIGHT);
    mainWindow.set_border_width(10);
    mainWindow.set_title("Musicocktail");
    mainWindow.set_icon_from_file("icone.png");


    Gtk::VBox mainVbox(false,10);

        Gtk::Notebook mainNotebook;
        mainNotebook.set_scrollable();
        
            Gtk::VButtonBox welcomBox(Gtk::BUTTONBOX_START,10);
            welcomBox.set_border_width(10);
        
        mainNotebook.append_page(welcomBox, "accueil");

            Gtk::VButtonBox ingredientsBox(Gtk::BUTTONBOX_START,10);
            ingredientsBox.set_border_width(10);
                Gtk::Button addRecipe("_Ajouter un ingrédient ", true);
                addRecipe.signal_clicked().connect(sigc::ptr_fun(&addIngredientThroughtInterface));
            ingredientsBox.pack_end(addRecipe);
            ingredientsBox.set_child_secondary(addRecipe);

            int i ;
            Gtk::Button* pButton;
            for( i = 0 ; i < NUMBER_INGREDIENTS ; i ++){
                pButton = Gtk::manage(new Gtk::Button(LIST_INGREDIENTS[i]->name));
                ingredientsBox.pack_start(*pButton);
            }
        
        mainNotebook.append_page(ingredientsBox,"ingrédients");

            Gtk::VButtonBox recipesBox(Gtk::BUTTONBOX_START,10);
            recipesBox.set_border_width(10);
                pButton = Gtk::manage(new Gtk::Button("_Ajouter un cocktail ", true));
            recipesBox.pack_end(*pButton);
            recipesBox.set_child_secondary(*pButton);
            for(i = 0 ; i <NUMBER_RECIPES; i ++){
                pButton = Gtk::manage(new Gtk::Button(LIST_RECIPES[i]->name));
                recipesBox.pack_start(*pButton);
            }
        
        mainNotebook.append_page(recipesBox, "recettes");

            Gtk::VButtonBox musicsBox(Gtk::BUTTONBOX_START,10);
            musicsBox.set_border_width(10);
        
        mainNotebook.append_page(musicsBox, "musique");        

    mainVbox.pack_start(mainNotebook);

        Gtk::Alignment quitBox(Gtk::ALIGN_END, Gtk::ALIGN_END,0,0);
        
            Gtk::Button quitButton(Gtk::Stock::QUIT);
            quitButton.signal_clicked().connect(sigc::ptr_fun(&close_appli));
        
        quitBox.add(quitButton);
    
    mainVbox.pack_end(quitBox);

    mainWindow.add(mainVbox);
    mainWindow.show_all();    
    Gtk::Main::run(mainWindow);



    return  1;
}