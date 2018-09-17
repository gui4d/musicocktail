#include "interface.h"


AddIngredient::AddIngredient(){

}

MainNotebook::MainNotebook(){
    extern INGREDIENT* LIST_INGREDIENTS;
    extern int NUMBER_INGREDIENTS;
    extern RECIPE* LIST_RECIPES; 
    extern int NUMBER_RECIPES;

    set_scrollable();
        Gtk::VButtonBox* pwelcomBox=Gtk::manage(new Gtk::VButtonBox(Gtk::BUTTONBOX_START,10));
    append_page(*pwelcomBox, "accueil");
        pwelcomBox->set_border_width(10);
        

        Gtk::VButtonBox* pingredientsBox = Gtk::manage( new Gtk::VButtonBox(Gtk::BUTTONBOX_START,10));
    append_page(*pingredientsBox,"ingrédients");
        pingredientsBox->set_border_width(10);
            Gtk::Button* paddIngredient = Gtk::manage(new Gtk::Button("_Ajouter un ingrédient ", true));
            paddIngredient->signal_clicked().connect(sigc::mem_fun(*this,&MainNotebook:: addIngredientThroughtInterface));
        pingredientsBox->pack_end(*paddIngredient);
        pingredientsBox->set_child_secondary(*paddIngredient);
            int i ;
            Gtk::Button* pButton;
            for( i = 0 ; i < NUMBER_INGREDIENTS ; i ++){
                pButton = Gtk::manage(new Gtk::Button(LIST_INGREDIENTS[i]->name));
                pingredientsBox->pack_start(*pButton);
            }
    

        Gtk::VButtonBox* precipesBox = Gtk::manage( new Gtk::VButtonBox(Gtk::BUTTONBOX_START,10));
    append_page(*precipesBox, "recettes");
        precipesBox->set_border_width(10);
            Gtk::Button* paddRecipe = Gtk::manage(new Gtk::Button("_Ajouter un cocktail ", true));
            paddRecipe->signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this,&MainNotebook:: addRecipeThroughtInterface),this->page_num(*precipesBox)));
        precipesBox->pack_end(*paddRecipe);
        precipesBox->set_child_secondary(*paddRecipe);
            for( i = 0 ; i < NUMBER_RECIPES ; i ++){
                pButton = Gtk::manage(new Gtk::Button(LIST_RECIPES[i]->name));
                precipesBox->pack_start(*pButton);
            }
    

        Gtk::VButtonBox* pmusicsBox = Gtk::manage(new Gtk::VButtonBox(Gtk::BUTTONBOX_START,10));
    append_page(*pmusicsBox, "musique");
        pmusicsBox->set_border_width(10);
        
    
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
            //pquitButton->signal_clicked().connect(sigc::ptr_fun(&close_appli)); //à revoir 
        
        pquitBox->add(*pquitButton);
    
    pmainVbox->pack_end(*pquitBox);

    add(*pmainVbox);
    show_all();

}


void MainNotebook::addIngredientThroughtInterface(){
    if( newIngredientPage==0){
        newIngredientPage=1;
        Gtk::VBox* pnewBox=Gtk::manage(new Gtk::VBox(Gtk::BUTTONBOX_START,10));
        pnewBox->set_border_width(10);

            Gtk::Label* ptitleLabel= Gtk::manage(new Gtk::Label("Nouvel ingrédient : création de la fiche"));
            ptitleLabel->set_justify(Gtk::JUSTIFY_CENTER);
            ptitleLabel->set_line_wrap();
            ptitleLabel->set_can_focus(false);
        pnewBox->pack_start(*ptitleLabel);

            Gtk::HBox* pnameBox = Gtk::manage( new Gtk::HBox(false,10));
            pnameBox->set_can_focus(false);
                Gtk::Label* pnameLabel=Gtk::manage( new Gtk::Label("nom :"));
                pnameLabel->set_can_focus(false);
            pnameBox->pack_start(*pnameLabel);
                newIngredientName.set_text("rentrer le nom");
                newIngredientName.set_max_length(100);
            pnameBox->pack_start(newIngredientName);
        pnewBox->pack_start(*pnameBox);

            Gtk::HBox* psaltBox= Gtk::manage(new Gtk::HBox(false,10));
            psaltBox->set_can_focus(false);
                Gtk::Label* psaltLabel= Gtk::manage(new Gtk::Label("taux de sel en g/L :"));
                psaltLabel->set_can_focus(false);
            psaltBox->pack_start(*psaltLabel);
                Glib::RefPtr<Gtk::Adjustment> ajustementsalt = Gtk::Adjustment::create(0, 0, 100, 1);
                saltEntry.set_adjustment(ajustementsalt);
                saltEntry.set_numeric();
            psaltBox->pack_start(saltEntry);
        pnewBox->pack_start(*psaltBox);

            Gtk::HBox* psugarBox= Gtk::manage(new Gtk::HBox(false,10));
            psugarBox->set_can_focus(false);
                Gtk::Label* psugarLabel= Gtk::manage(new Gtk::Label("taux de sucre en g/L :"));
                psugarLabel->set_can_focus(false);
            psugarBox->pack_start(*psugarLabel);
                Glib::RefPtr<Gtk::Adjustment> ajustementSugar = Gtk::Adjustment::create(0, 0, 100, 1);
                sugarEntry.set_adjustment(ajustementSugar);
                sugarEntry.set_numeric();
            psugarBox->pack_start(sugarEntry);
        pnewBox->pack_start(*psugarBox);

            Gtk::HBox* pstrenghtBox= Gtk::manage( new Gtk:: HBox(false,10));
            pstrenghtBox->set_can_focus(false);
                Gtk::Label* pstrenghtLabel= Gtk::manage( new Gtk::Label("taux d'alcoolémie en % :"));
                pstrenghtLabel->set_can_focus(false);
            pstrenghtBox->pack_start(*pstrenghtLabel);
                Glib::RefPtr<Gtk::Adjustment> ajustementStrenght = Gtk::Adjustment::create(0, 0, 100, 1);
                strenghtEntry.set_adjustment(ajustementStrenght);
                strenghtEntry.set_numeric();
            pstrenghtBox->pack_start(strenghtEntry);
        pnewBox->pack_start(*pstrenghtBox);

            Gtk::HBox* pservoBox = Gtk::manage( new Gtk::HBox(false,10));
            pservoBox->set_can_focus(false);
                Gtk::Label* pservoLabel= Gtk::manage( new Gtk::Label("numero sur le bar (-1 si il n'est pas sur le bar ):"));
                pservoLabel->set_can_focus(false);
            pservoBox->pack_start(*pservoLabel);
                Glib::RefPtr<Gtk::Adjustment> ajustementServo = Gtk::Adjustment::create(-1, -1, 15, 1);
                servoEntry.set_adjustment(ajustementServo);
                servoEntry.set_numeric();
            pservoBox->pack_start(servoEntry);
        pnewBox->pack_start(*pservoBox);

            Gtk::HBox* pactionBox = Gtk::manage( new Gtk::HBox(false,10));
            pactionBox->set_can_focus(false);
                Gtk::Button* psaveButton= Gtk::manage( new Gtk::Button(Gtk::Stock::SAVE));
                //saveButton.signal_clicked().connect(sigc::bind<std::string,int,int,int,int>(sigc::ptr_fun(&saveNewIngredientThroughtInterface),nameEntry.get_text(),saltEntry.get_value_as_int(), sugarEntry.get_value_as_int(), strenghtEntry.get_value_as_int(),servoEntry.get_value_as_int() ));
            pactionBox->pack_start(*psaveButton);
                Gtk::Button* pquitButton = Gtk::manage( new Gtk::Button(Gtk::Stock::CANCEL));
            pactionBox->pack_start(*pquitButton);
        
        pnewBox->pack_end(*pactionBox);

        int numPage = this->get_n_pages();
        newIngredientPageNumber=numPage;
        this->insert_page(*pnewBox, "Nouvel ingrédient",  numPage);
        this->show_all();
        this->set_current_page(numPage);
    }
    else{
        this->show_all();
        this->set_current_page(newIngredientPageNumber);

    }
}


void MainNotebook::addRecipeThroughtInterface(int numPage /*changer ça*/ ){
    
        Gtk::VBox* pnewBox = Gtk::manage(new Gtk::VBox(Gtk::BUTTONBOX_START,10));
        pnewBox->set_border_width(10);
    numPage = this->get_n_pages();//
    this->insert_page(*pnewBox, "Nouveau cocktail",  numPage);
    this->show_all();
    this->set_current_page(numPage);
}


/*
extern INGREDIENT* LIST_INGREDIENTS;
    extern int NUMBER_INGREDIENTS;
    
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

    */

/*
   void saveNewIngredientThroughtInterface(std::string Sname, int salt, int sugar , int strenght, int servoAdress){

    char name[Sname.size()+1];
    std::copy(Sname.begin(),Sname.end(), name);
    addIngredient(name,(float)(salt), (float) (sugar) , (float) (strenght), servoAdress);
    //metre une boite de dialogue si l'enregistrement s'est mal passé
}
*/