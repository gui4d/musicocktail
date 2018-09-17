#include "interface.h"


MainNotebook::MainNotebook(){
    extern INGREDIENT* LIST_INGREDIENTS;
    extern int NUMBER_INGREDIENTS;
    extern RECIPE* LIST_RECIPES; 
    extern int NUMBER_RECIPES;

    set_scrollable();
        Gtk::VButtonBox* pwelcomBox=Gtk::manage(new Gtk::VButtonBox(Gtk::BUTTONBOX_START,10));
        pwelcomBox->set_border_width(10);
        
    append_page(*pwelcomBox, "accueil");

        Gtk::VButtonBox* pingredientsBox = Gtk::manage( new Gtk::VButtonBox(Gtk::BUTTONBOX_START,10));
        pingredientsBox->set_border_width(10);
            Gtk::Button* paddIngredient = Gtk::manage(new Gtk::Button("_Ajouter un ingrédient ", true));
                //addIngredient.signal_clicked().connect(sigc::ptr_fun(&addIngredientThroughtInterface)); à voir;
        pingredientsBox->pack_end(*paddIngredient);
        pingredientsBox->set_child_secondary(*paddIngredient);
            int i ;
            Gtk::Button* pButton;
            for( i = 0 ; i < NUMBER_INGREDIENTS ; i ++){
                pButton = Gtk::manage(new Gtk::Button(LIST_INGREDIENTS[i]->name));
                pingredientsBox->pack_start(*pButton);
            }
        
    append_page(*pingredientsBox,"ingrédients");

        Gtk::VButtonBox* precipesBox = Gtk::manage( new Gtk::VButtonBox(Gtk::BUTTONBOX_START,10));
        precipesBox->set_border_width(10);
            Gtk::Button* paddRecipe = Gtk::manage(new Gtk::Button("_Ajouter un cocktail ", true));
                //addRecipe.signal_clicked().connect(sigc::ptr_fun(&addIngredientThroughtInterface)); à voir;
        precipesBox->pack_end(*paddRecipe);
        precipesBox->set_child_secondary(*paddRecipe);
            for( i = 0 ; i < NUMBER_RECIPES ; i ++){
                pButton = Gtk::manage(new Gtk::Button(LIST_RECIPES[i]->name));
                precipesBox->pack_start(*pButton);
            }
    append_page(*precipesBox, "recettes");

        Gtk::VButtonBox* pmusicsBox = Gtk::manage(new Gtk::VButtonBox(Gtk::BUTTONBOX_START,10));
        pmusicsBox->set_border_width(10);
        
    append_page(*pmusicsBox, "musique");


}

MainWindow::MainWindow(){

    set_default_size(WIDTH,HEIGHT);
    set_border_width(10);
    set_title("Musicocktail");
    set_icon_from_file("icone.png");

    Gtk::VBox* pmainVbox = Gtk::manage(new Gtk::VBox(false,10));

    pmainVbox->pack_start(mainNotebook);
        
        Gtk::Alignment* pquitBox= Gtk::manage(new Gtk::Alignment(Gtk::ALIGN_END, Gtk::ALIGN_END,0,0));
        
            Gtk::Button*  pquitButton = Gtk::manage(new Gtk::Button(Gtk::Stock::QUIT));
            //pquitButton->signal_clicked().connect(sigc::ptr_fun(&close_appli)); à revoir
        
        pquitBox->add(*pquitButton);
    
    pmainVbox->pack_end(*pquitBox);

    add(*pmainVbox);
    show_all();

}