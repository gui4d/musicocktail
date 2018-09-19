#include "interface.h"

RecipeElement::RecipeElement(){
    extern INGREDIENT* LIST_INGREDIENTS;
    extern int NUMBER_INGREDIENTS;

    pack_start(ingredient);
    pack_start(ingredientName);
    pack_start(amount);
    pack_start(ingredientAmount);
    ingredient.set_text("choisissez un ingredient");
    amount.set_text("quantité en ml :");
    set_border_width(10);
    set_can_focus(false);
     
    int i;
    for (i = 0 ; i < NUMBER_INGREDIENTS ; i ++){
        ingredientName.append(LIST_INGREDIENTS[i]->name);
    }


}

int RecipeElement::getIddIngredient(){
    return ingredientName.get_active_row_number();
}

int RecipeElement::getAmountIngredient(){
    return ingredientAmount.get_value_as_int(); 
}


MainNotebook::MainNotebook(){
    extern INGREDIENT* LIST_INGREDIENTS;
    extern int NUMBER_INGREDIENTS;
    extern RECIPE* LIST_RECIPES; 
    extern int NUMBER_RECIPES;

    set_scrollable();
        pwelcomBox=Gtk::manage(new Gtk::VButtonBox(Gtk::BUTTONBOX_START,10));
        append_page(*pwelcomBox, "accueil");
            Gtk::Label* ppresentationLabel= Gtk::manage ( new Gtk::Label());
            pwelcomBox->pack_start(*ppresentationLabel);
            Gtk::Button* plaunchMusicocktail =Gtk:: manage( new Gtk::Button("lancez vous !"));
            pwelcomBox->pack_start(*plaunchMusicocktail);
            Gtk::HBox* pparameterBox = Gtk::manage( new Gtk::HBox(false,10));
            pwelcomBox->pack_end(*pparameterBox);
                Gtk::Button* plaunchIngredients =Gtk:: manage( new Gtk::Button("parametrer les ingrédients"));
                pparameterBox->pack_start(*plaunchIngredients);
                Gtk::Button* plaunchRecipe =Gtk:: manage( new Gtk::Button("parametrer les recettes"));
                pparameterBox->pack_start(*plaunchRecipe);
    
    pwelcomBox->set_border_width(10);
    ppresentationLabel -> set_justify(Gtk::JUSTIFY_CENTER);
    ppresentationLabel -> set_markup("<b><big>          Musicocktail        </big></b> \n\n Le musicocktail est un bar expérimental automatique.\n  Vous jouez d'un instrument ? alors exprimez vous !\n Le musicocktail saura composer un cocktail en fonction de l'humeurs du morceau  et de vos inspiration \n\n Pour parametrer le musicocktail, cliquer sur les icones ingrédient et  cocktail , sinon vous pouvez simplement cliquer sur 'lancez-vous!'.");
    ppresentationLabel -> set_line_wrap();
    ppresentationLabel -> set_width_chars(WIDTH/10);
    plaunchIngredients->signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this,&MainNotebook::set_current_page),1));
    plaunchRecipe->signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this,&MainNotebook::set_current_page),2));

        Gtk::VBox* pingredientsBox = Gtk::manage ( new Gtk::VBox(false,10));
        append_page(*pingredientsBox,"ingrédients");
            Gtk::ScrolledWindow* pscrolledIngredients = Gtk::manage( new Gtk::ScrolledWindow());
            pingredientsBox->pack_start(*pscrolledIngredients);
                pingredientsList = Gtk::manage( new Gtk::VButtonBox(Gtk::BUTTONBOX_START,10));
                pscrolledIngredients->add(*pingredientsList);
                int i ;
                Gtk::Button* pButton;
                for( i = 0 ; i < NUMBER_INGREDIENTS ; i ++){
                    pButton = Gtk::manage(new Gtk::Button(LIST_INGREDIENTS[i]->name));
                    pingredientsList->pack_start(*pButton);
                }
            Gtk::Button* paddIngredient = Gtk::manage(new Gtk::Button("_Ajouter un ingrédient ", true));
            pingredientsBox->pack_end(*paddIngredient, Gtk::PACK_SHRINK);

    pingredientsBox->set_border_width(10);
    pscrolledIngredients->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    paddIngredient->signal_clicked().connect(sigc::mem_fun(*this,&MainNotebook:: initAddIngredientThroughtInterface));
    
    

        precipesBox = Gtk::manage( new Gtk::VButtonBox(Gtk::BUTTONBOX_START,10));
        append_page(*precipesBox, "recettes");
            Gtk::Button* paddRecipe = Gtk::manage(new Gtk::Button("_Ajouter un cocktail ", true));
            precipesBox->pack_end(*paddRecipe);
            for( i = 0 ; i < NUMBER_RECIPES ; i ++){
                pButton = Gtk::manage(new Gtk::Button(LIST_RECIPES[i]->name));
                precipesBox->pack_start(*pButton);
            }

    precipesBox->set_border_width(10);
    paddRecipe->signal_clicked().connect(sigc::mem_fun(*this,&MainNotebook:: initAddRecipeThroughtInterface));
    precipesBox->set_child_secondary(*paddRecipe);

        pmusicsBox = Gtk::manage(new Gtk::VButtonBox(Gtk::BUTTONBOX_START,10));
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
            pquitButton->signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::closeMainWindow));
        
        pquitBox->add(*pquitButton);
    
    pmainVbox->pack_end(*pquitBox);

    add(*pmainVbox);
    show_all();

}

void MainWindow::closeMainWindow(){

    freeRecipeList(Save);
    freeIngredientList(Save);
    Gtk::Main::quit();
}

void MainNotebook::closeAddIngredientThroughtInterface(int save){
    
    extern INGREDIENT* LIST_INGREDIENTS;
    extern int NUMBER_INGREDIENTS;
    
    if(save)
    {
        //créer une sécuritée dans les entrées
        std::string Sname = newIngredientName.get_text();
        float salt = (float)(saltEntry.get_value_as_int());
        float sugar = (float)(sugarEntry.get_value_as_int());
        float strenght = (float)(strenghtEntry.get_value_as_int());
        int servoAdress = servoEntry.get_value_as_int();
        char name[Sname.size()+1];
        std::copy(Sname.begin(),Sname.end(), name);
        name[Sname.size()]='\0';
        if(addIngredient(name,salt, sugar, strenght, servoAdress))
        {
            Gtk::Button* pButton = Gtk::manage(new Gtk::Button(LIST_INGREDIENTS[NUMBER_INGREDIENTS-1]->name));
            this->pingredientsList->pack_start(*pButton);
            if( ! saveIngredientList() ){
                //metre une boite de dialogue si l'enregistrement s'est mal passé
            }
        }
        else
        {
            //metre une boite de dialogue si l'enregistrement s'est mal passé
        }
    }
    this->remove_page(newIngredientPageNumber);
    newIngredientPageNumber=1;
    newIngredientPage=0;
    this->show_all();
    this->set_current_page(1);
  
}


void MainNotebook::initAddIngredientThroughtInterface(){
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
                psaveButton->signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this,&MainNotebook::closeAddIngredientThroughtInterface),1));
            pactionBox->pack_start(*psaveButton);
                Gtk::Button* pcancelButton = Gtk::manage( new Gtk::Button(Gtk::Stock::CANCEL));
                pcancelButton->signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this,&MainNotebook::closeAddIngredientThroughtInterface),0));
            pactionBox->pack_start(*pcancelButton);
        
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

void MainNotebook::closeAddRecipeThroughtInterface(int save){
    
    extern RECIPE* LIST_RECIPES; 
    extern int NUMBER_RECIPES;
    
    if(save)
    {
        //créer une sécuritée dans les entrées
        std::string Sname = newRecipeName.get_text();
        char name[Sname.size()+1];
        std::copy(Sname.begin(),Sname.end(), name);
        name[Sname.size()]='\0';
        int ingredientNumber = NumberIngredientsEntry.get_value_as_int();

        ////adapter!!!
        /*if(addIngredient(name,salt, sugar, strenght, servoAdress))
        {
            Gtk::Button* pButton = Gtk::manage(new Gtk::Button(LIST_INGREDIENTS[NUMBER_INGREDIENTS-1]->name));
            this->pingredientsList->pack_start(*pButton);
            if( ! saveIngredientList() ){
                //metre une boite de dialogue si l'enregistrement s'est mal passé
            }
        }
        else
        {
            //metre une boite de dialogue si l'enregistrement s'est mal passé
        }*/
    }
    this->remove_page(newRecipePageNumber);
    newRecipePageNumber=2;
    newRecipePage=0;
    this->show_all();
    this->set_current_page(2);
  
}

void MainNotebook::initAddRecipeThroughtInterface(){
    if( newRecipePage==0){
        newRecipePage=1;
        Gtk::VBox* pnewBox=Gtk::manage(new Gtk::VBox(Gtk::BUTTONBOX_START,10));
        pnewBox->set_border_width(10);

            Gtk::Label* ptitleLabel= Gtk::manage(new Gtk::Label("Nouveau Coktail: création de la fiche"));
            ptitleLabel->set_justify(Gtk::JUSTIFY_CENTER);
            ptitleLabel->set_line_wrap();
            ptitleLabel->set_can_focus(false);
            pnewBox->pack_start(*ptitleLabel);

            Gtk::HBox* pnameBox = Gtk::manage( new Gtk::HBox(false,10));
            pnameBox->set_can_focus(false);
            pnewBox->pack_start(*pnameBox);
                Gtk::Label* pnameLabel=Gtk::manage( new Gtk::Label("nom :"));
                pnameLabel->set_can_focus(false);
                pnameBox->pack_start(*pnameLabel);
                
                newRecipeName.set_text("rentrer le nom");
                newRecipeName.set_max_length(100);
                pnameBox->pack_start(newRecipeName);
                

            Gtk::HBox* pNumberIngredientsBox= Gtk::manage(new Gtk::HBox(false,10));
            pNumberIngredientsBox->set_can_focus(false);
            pnewBox->pack_start(*pNumberIngredientsBox);
                Gtk::Label* pNumberIngredientsLabel= Gtk::manage(new Gtk::Label("Nombre d'ingrédients:"));
                pNumberIngredientsLabel->set_can_focus(false);
                pNumberIngredientsBox->pack_start(*pNumberIngredientsLabel);
                
                Glib::RefPtr<Gtk::Adjustment> ajustementNumberIngredients = Gtk::Adjustment::create(1,1,20, 1);
                NumberIngredientsEntry.set_adjustment(ajustementNumberIngredients);
                NumberIngredientsEntry.set_numeric();
                pNumberIngredientsBox->pack_start(NumberIngredientsEntry);
        
            Gtk::ScrolledWindow* pscrolledIngredients = Gtk::manage( new Gtk::ScrolledWindow());
            pscrolledIngredients->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
            pnewBox->pack_start(*pscrolledIngredients);
                RecipeElement* pnewRecipeElement;
                tabpRecipeElement.push_back(pnewRecipeElement);

                extern INGREDIENT* LIST_INGREDIENTS;
                extern int NUMBER_INGREDIENTS;
                
                pingredientsList = Gtk::manage( new Gtk::VButtonBox(Gtk::BUTTONBOX_START,10));
                pscrolledIngredients->add(*pingredientsList);
                int i ;
                Gtk::Button* pButton;
                for( i = 0 ; i < NUMBER_INGREDIENTS ; i ++){
                    pButton = Gtk::manage(new Gtk::Button(LIST_INGREDIENTS[i]->name));
                    pingredientsList->pack_start(*pButton);
                }
                //pscrolledIngredients->add(*pnewRecipeElement);

            /*Gtk::HBox* psugarBox= Gtk::manage(new Gtk::HBox(false,10));
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
        pnewBox->pack_start(*pservoBox);*/

            Gtk::HBox* pactionBox = Gtk::manage( new Gtk::HBox(false,10));
            pactionBox->set_can_focus(false);
            pnewBox->pack_end(*pactionBox);
                Gtk::Button* psaveButton= Gtk::manage( new Gtk::Button(Gtk::Stock::SAVE));
                psaveButton->signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this,&MainNotebook::closeAddRecipeThroughtInterface),1));
                pactionBox->pack_start(*psaveButton);
                
                Gtk::Button* pcancelButton = Gtk::manage( new Gtk::Button(Gtk::Stock::CANCEL));
                pcancelButton->signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this,&MainNotebook::closeAddRecipeThroughtInterface),0));
                pactionBox->pack_start(*pcancelButton);
        
        

        int numPage = this->get_n_pages();
        newRecipePageNumber=numPage;
        this->insert_page(*pnewBox, "Nouveau cocktail",  numPage);
        this->show_all();
        this->set_current_page(numPage);
    }
    else{
        this->show_all();
        this->set_current_page(newIngredientPageNumber);

    }
}
/*
   void saveNewIngredientThroughtInterface(std::string Sname, int salt, int sugar , int strenght, int servoAdress){

    sigc::bind<std::string,int,int,int,int>(sigc::ptr_fun(&saveNewIngredientThroughtInterface),nameEntry.get_text(),saltEntry.get_value_as_int(), sugarEntry.get_value_as_int(), strenghtEntry.get_value_as_int(),servoEntry.get_value_as_int() ));
    char name[Sname.size()+1];
    std::copy(Sname.begin(),Sname.end(), name);
    addIngredient(name,(float)(salt), (float) (sugar) , (float) (strenght), servoAdress);
    //metre une boite de dialogue si l'enregistrement s'est mal passé
}
*/