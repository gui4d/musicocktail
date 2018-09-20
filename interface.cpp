#include "interface.h"

MainNotebook::MainNotebook(){
    extern INGREDIENT* LIST_INGREDIENTS;
    extern int NUMBER_INGREDIENTS;
    extern RECIPE* LIST_RECIPES; 
    extern int NUMBER_RECIPES;

    newIngredientPage=0;
    newIngredientPageNumber=1;
    paramIngredientPage= 0;
    paramIngredientPageNumber=1;
    newRecipePage=0;
    newRecipePageNumber=2;
    paramRecipePage= 0;
    paramRecipePageNumber=2;
    ArduinoPort= 0;
    ArduinoFailed= 0;

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
                    pButton->signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this,&MainNotebook::openIngredientParameter),i));
                    pingredientsList->pack_start(*pButton);
                }
            Gtk::Button* paddIngredient = Gtk::manage(new Gtk::Button("_Ajouter un ingrédient ", true));
            pingredientsBox->pack_end(*paddIngredient, Gtk::PACK_SHRINK);

    pingredientsBox->set_border_width(10);
    pscrolledIngredients->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    paddIngredient->signal_clicked().connect(sigc::mem_fun(*this,&MainNotebook:: initAddIngredientThroughtInterface));
    
    Gtk::VBox* precipesBox = Gtk::manage ( new Gtk::VBox(false,10));
        append_page(*precipesBox,"Cocktails");
            Gtk::ScrolledWindow* pscrolledRecipes = Gtk::manage( new Gtk::ScrolledWindow());
            precipesBox->pack_start(*pscrolledRecipes);
                precipesList = Gtk::manage( new Gtk::VButtonBox(Gtk::BUTTONBOX_START,10));
                pscrolledRecipes->add(*precipesList);
                for( i = 0 ; i < NUMBER_RECIPES ; i ++){
                    pButton = Gtk::manage(new Gtk::Button(LIST_RECIPES[i]->name));
                    pButton->signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this,&MainNotebook::openRecipeParameter),i));
                    precipesList->pack_start(*pButton);
                }
            Gtk::Button* paddRecipe = Gtk::manage(new Gtk::Button("_Ajouter un cocktail ", true));
            precipesBox->pack_end(*paddRecipe, Gtk::PACK_SHRINK);

    precipesBox->set_border_width(10);
    pscrolledRecipes->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    paddRecipe->signal_clicked().connect(sigc::mem_fun(*this,&MainNotebook:: initAddRecipeThroughtInterface));
    

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

void MainNotebook::initAddIngredientThroughtInterface(){
    if( newIngredientPage==0){
        newIngredientPage=1;
        Gtk::VBox* pnewBox=Gtk::manage(new Gtk::VBox(false,10));
        

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
        
        pnewBox->pack_end(*pactionBox,Gtk::PACK_SHRINK);

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
            pButton->signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this,&MainNotebook::openIngredientParameter),NUMBER_INGREDIENTS-1));
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
    this->updatePageNumerotation(newIngredientPageNumber);
    newIngredientPageNumber=1;
    newIngredientPage=0;
    this->show_all();
    this->set_current_page(1);
  
}

void MainNotebook::initAddRecipeThroughtInterface(){
    
    extern INGREDIENT* LIST_INGREDIENTS;
    extern int NUMBER_INGREDIENTS;
    
    if( newRecipePage==0){
        newRecipePage=1;
        Gtk::VBox* pnewBox=Gtk::manage(new Gtk::VBox(false,10));

            Gtk::Label* ptitleLabel= Gtk::manage(new Gtk::Label("Nouveau Coktail: création de la fiche"));
            ptitleLabel->set_justify(Gtk::JUSTIFY_CENTER);
            ptitleLabel->set_line_wrap();
            ptitleLabel->set_can_focus(false);
            pnewBox->pack_start(*ptitleLabel);

            Gtk::HBox* pnameBox = Gtk::manage( new Gtk::HBox(false,10));
            pnameBox->set_can_focus(false);
            pnewBox->pack_start(*pnameBox,Gtk::PACK_SHRINK);
                Gtk::Label* pnameLabel=Gtk::manage( new Gtk::Label("nom :"));
                pnameLabel->set_can_focus(false);
                pnameBox->pack_start(*pnameLabel,Gtk::PACK_SHRINK);
                
                newRecipeName.set_text("rentrer le nom");
                newRecipeName.set_max_length(100);
                pnameBox->pack_start(newRecipeName,Gtk::PACK_SHRINK);
                

            Gtk::HBox* pNumberIngredientsBox= Gtk::manage(new Gtk::HBox(false,10));
            pNumberIngredientsBox->set_can_focus(false);
            pnewBox->pack_start(*pNumberIngredientsBox,Gtk::PACK_SHRINK);
                Gtk::Label* pNumberIngredientsLabel= Gtk::manage(new Gtk::Label("Nombre d'ingrédients:"));
                pNumberIngredientsLabel->set_can_focus(false);
                pNumberIngredientsBox->pack_start(*pNumberIngredientsLabel,Gtk::PACK_SHRINK);
                
                Glib::RefPtr<Gtk::Adjustment> ajustementNumberIngredients = Gtk::Adjustment::create(1,1,20, 1);
                NumberIngredientsEntry.set_adjustment(ajustementNumberIngredients);
                NumberIngredientsEntry.set_numeric();
                NumberIngredientsEntry.signal_value_changed().connect(sigc::mem_fun(*this,&MainNotebook::actuateNumberIngredients));
                pNumberIngredientsBox->pack_start(NumberIngredientsEntry,Gtk::PACK_SHRINK);
        
            Gtk::ScrolledWindow* pscrolledIngredients = Gtk::manage( new Gtk::ScrolledWindow());
            pscrolledIngredients->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
            pnewBox->pack_start(*pscrolledIngredients,Gtk::PACK_EXPAND_WIDGET );
                pRecipeElementsList = Gtk::manage ( new Gtk::VBox(false,20));
                pscrolledIngredients->add(*pRecipeElementsList);
                    Gtk::HBox* pnewRecipeElement =Gtk::manage( new Gtk::HBox(false,10));
                    pRecipeElementsList->pack_start(*pnewRecipeElement,Gtk::PACK_SHRINK);
                    tabpRecipeElement.push_back(pnewRecipeElement);
                        Gtk::ComboBoxText* pnewRecipeIngredient = Gtk::manage( new Gtk::ComboBoxText());
                        int i;
                        for (i = 0 ; i < NUMBER_INGREDIENTS ; i ++){
                            pnewRecipeIngredient->append(LIST_INGREDIENTS[i]->name);
                        }
                        pnewRecipeElement->pack_start(*pnewRecipeIngredient,Gtk::PACK_SHRINK);
                        tabpIngredients.push_back(pnewRecipeIngredient);

                        Gtk::Label* pnewRecipeElementLabel = Gtk::manage( new Gtk::Label());
                        pnewRecipeElementLabel->set_text("ml:");
                        pnewRecipeElementLabel->set_can_focus(false);
                        pnewRecipeElement->pack_start(*pnewRecipeElementLabel,Gtk::PACK_SHRINK);

                        Gtk::SpinButton* pnewRecipeAmount =Gtk::manage ( new Gtk::SpinButton);
                        pnewRecipeAmount->set_numeric();
                        Glib::RefPtr<Gtk::Adjustment> ajustementAmount = Gtk::Adjustment::create(0, 0, 100, 1);
                        pnewRecipeAmount->set_adjustment(ajustementAmount);
                        pnewRecipeElement->pack_start(*pnewRecipeAmount,Gtk::PACK_SHRINK);
                        tabpAmount.push_back(pnewRecipeAmount);

            Gtk::HBox* pactionBox = Gtk::manage( new Gtk::HBox(false,10));
            pactionBox->set_can_focus(false);
            pnewBox->pack_end(*pactionBox,Gtk::PACK_SHRINK);
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
        this->set_current_page(newRecipePageNumber);

    }
}

void MainNotebook::actuateNumberIngredients(){


    extern INGREDIENT* LIST_INGREDIENTS;
    extern int NUMBER_INGREDIENTS;

     int newNumberIngredient = NumberIngredientsEntry.get_value_as_int();
     int oldNumberIngredient = tabpRecipeElement.size();
     int j;
     if( oldNumberIngredient < newNumberIngredient){
         Gtk::HBox* pnewRecipeElement;
         Gtk::ComboBoxText* pnewRecipeIngredient;
         Gtk::Label* pnewRecipeElementLabel;
         Gtk::SpinButton* pnewRecipeAmount;
         Glib::RefPtr<Gtk::Adjustment> ajustementAmount;
         for( j = oldNumberIngredient; j < newNumberIngredient; j++){
            pnewRecipeElement =Gtk::manage( new Gtk::HBox(false,10));
            pRecipeElementsList->pack_start(*pnewRecipeElement,Gtk::PACK_SHRINK);
            tabpRecipeElement.push_back(pnewRecipeElement);
                pnewRecipeIngredient = Gtk::manage( new Gtk::ComboBoxText());
                int i;
                for (i = 0 ; i < NUMBER_INGREDIENTS ; i ++){
                    pnewRecipeIngredient->append(LIST_INGREDIENTS[i]->name);
                }
                pnewRecipeElement->pack_start(*pnewRecipeIngredient,Gtk::PACK_SHRINK);
                tabpIngredients.push_back(pnewRecipeIngredient);

                pnewRecipeElementLabel = Gtk::manage( new Gtk::Label());
                pnewRecipeElementLabel->set_text("ml:");
                pnewRecipeElementLabel->set_can_focus(false);
                pnewRecipeElement->pack_start(*pnewRecipeElementLabel,Gtk::PACK_SHRINK);

                pnewRecipeAmount =Gtk::manage ( new Gtk::SpinButton);
                pnewRecipeAmount->set_numeric();
                ajustementAmount = Gtk::Adjustment::create(0, 0, 100, 1);
                pnewRecipeAmount->set_adjustment(ajustementAmount);
                pnewRecipeElement->pack_start(*pnewRecipeAmount,Gtk::PACK_SHRINK);
                tabpAmount.push_back(pnewRecipeAmount);

         }
         pRecipeElementsList->show_all();


     }
     if( oldNumberIngredient > newNumberIngredient){
        for( j = oldNumberIngredient-1 ; j > newNumberIngredient-1 ; j-- ){
            pRecipeElementsList->remove(*tabpRecipeElement[j]);
            tabpRecipeElement.pop_back();
            tabpIngredients.pop_back();
            tabpAmount.pop_back();

        }
        pRecipeElementsList->show_all();
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
        int nbIngredients = NumberIngredientsEntry.get_value_as_int();
        int  listIngredients[20];
        float listAmount[20];
        int i ;
        for (i = 0 ; i < nbIngredients ; i ++){
            listIngredients[i]= tabpIngredients[i]->get_active_row_number();
            listAmount[i] = (float)(tabpAmount[i]->get_value_as_int()); 
        }
        int iddSimilarRecipe = -1;

        if( addRecipe( name,  nbIngredients ,   listIngredients,  listAmount, iddSimilarRecipe ))
        {
            Gtk::Button* pButton = Gtk::manage(new Gtk::Button(LIST_RECIPES[NUMBER_RECIPES-1]->name));
            pButton->signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this,&MainNotebook::openRecipeParameter),NUMBER_RECIPES-1));
            this->precipesList->pack_start(*pButton);
            if( ! saveRecipeList() ){
                //metre une boite de dialogue si l'enregistrement s'est mal passé
            }
        }
        else
        {
            //metre une boite de dialogue si l'enregistrement s'est mal passé
        }
    }
    int NumberIngredient=tabpRecipeElement.size();
    int j;
    for( j = NumberIngredient-1 ; j >-1 ; j-- ){
        pRecipeElementsList->remove(*tabpRecipeElement[j]);
        tabpRecipeElement.pop_back();
        tabpIngredients.pop_back();
        tabpAmount.pop_back();
    }
    this->remove_page(newRecipePageNumber);
    this->updatePageNumerotation(newRecipePageNumber);
    newRecipePageNumber=2;
    newRecipePage=0;
    this->show_all();
    this->set_current_page(2);
  
}

void MainNotebook::openIngredientParameter(int iddIngredient){
    extern INGREDIENT* LIST_INGREDIENTS;

    if( paramIngredientPage==0){
        paramIngredientPage=1;
        Gtk::VBox* pnewBox=Gtk::manage(new Gtk::VBox(false,10));

            Gtk::Label* ptitleLabel= Gtk::manage(new Gtk::Label(LIST_INGREDIENTS[iddIngredient]->name));
            ptitleLabel->set_justify(Gtk::JUSTIFY_CENTER);
            ptitleLabel->set_line_wrap();
            ptitleLabel->set_can_focus(false);
            pnewBox->pack_start(*ptitleLabel);

            Gtk::HBox* psaltBox = Gtk::manage( new Gtk::HBox(false,10));
            psaltBox->set_can_focus(false);
            pnewBox->pack_start(*psaltBox);
                Gtk::Label* psaltLabel=Gtk::manage( new Gtk::Label("taux de sel (g/l):"));
                psaltLabel->set_can_focus(false);
                psaltBox->pack_start(*psaltLabel);

                char saltValue[10];
                sprintf(saltValue, "%f", LIST_INGREDIENTS[iddIngredient]->salt);
                psaltLabel=Gtk::manage( new Gtk::Label());
                psaltLabel->set_text(saltValue);
                psaltLabel->set_can_focus(false);
                psaltBox->pack_start(*psaltLabel);
            
            Gtk::HBox* psugarBox = Gtk::manage( new Gtk::HBox(false,10));
            psugarBox->set_can_focus(false);
            pnewBox->pack_start(*psugarBox);
                Gtk::Label* psugarLabel=Gtk::manage( new Gtk::Label("taux de sucre (g/l):"));
                psugarLabel->set_can_focus(false);
                psugarBox->pack_start(*psugarLabel);

                char sugarValue[10];
                sprintf(sugarValue, "%f", LIST_INGREDIENTS[iddIngredient]->sugar);
                psugarLabel=Gtk::manage( new Gtk::Label(sugarValue));
                psugarLabel->set_can_focus(false);
                psugarBox->pack_start(*psugarLabel);
            
            Gtk::HBox* pstrenghtBox = Gtk::manage( new Gtk::HBox(false,10));
            pstrenghtBox->set_can_focus(false);
            pnewBox->pack_start(*pstrenghtBox);
                Gtk::Label* pstrenghtLabel=Gtk::manage( new Gtk::Label("taux alcoolémique (%):"));
                pstrenghtLabel->set_can_focus(false);
                pstrenghtBox->pack_start(*pstrenghtLabel);

                char strenghtValue[10];
                sprintf(strenghtValue, "%f", LIST_INGREDIENTS[iddIngredient]->strenght);
                pstrenghtLabel=Gtk::manage( new Gtk::Label(strenghtValue));
                pstrenghtLabel->set_can_focus(false);
                pstrenghtBox->pack_start(*pstrenghtLabel);

            Gtk::HBox* pservoBox = Gtk::manage( new Gtk::HBox(false,10));
            pservoBox->set_can_focus(false);
            pnewBox->pack_start(*pservoBox);
                if ( LIST_INGREDIENTS[iddIngredient]->servoAdress==-1){
                    Gtk::Label* pservoLabel=Gtk::manage( new Gtk::Label("n'est pas placé sur le bar"));
                    pservoLabel->set_can_focus(false);
                    pservoBox->pack_start(*pservoLabel);

                }
                else{
                    Gtk::Label* pservoLabel=Gtk::manage( new Gtk::Label("emplacement sur l'armoire :"));
                    pservoLabel->set_can_focus(false);
                    pservoBox->pack_start(*pservoLabel);

                    char servoValue[3];
                    sprintf(servoValue, "%d", LIST_INGREDIENTS[iddIngredient]->servoAdress);
                    pservoLabel=Gtk::manage( new Gtk::Label(servoValue));
                    pservoLabel->set_can_focus(false);
                    pservoBox->pack_start(*pservoLabel);

                }

        
            Gtk::HBox* pactionBox = Gtk::manage( new Gtk::HBox(false,10));
            pactionBox->set_can_focus(false);
            pnewBox->pack_end(*pactionBox,Gtk::PACK_SHRINK);
                Gtk::Button* psaveButton= Gtk::manage( new Gtk::Button(Gtk::Stock::EDIT));
                //psaveButton->signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this,&MainNotebook::closeAddIngredientThroughtInterface),1));
                pactionBox->pack_start(*psaveButton);
                
                Gtk::Button* pcancelButton = Gtk::manage( new Gtk::Button(Gtk::Stock::CLOSE));
                pcancelButton->signal_clicked().connect(sigc::mem_fun(*this,&MainNotebook::closeIngredientParameter));
                pactionBox->pack_start(*pcancelButton);
        
        

        int numPage = this->get_n_pages();
        paramIngredientPageNumber=numPage;
        this->insert_page(*pnewBox, LIST_INGREDIENTS[iddIngredient]->name,  numPage);
        this->show_all();
        this->set_current_page(numPage);
    }
    else{

        this->show_all();
        this->set_current_page(paramIngredientPageNumber);
        closeIngredientParameter();
        openIngredientParameter(iddIngredient);

    }
}


void MainNotebook::closeIngredientParameter(){

    this->remove_page(paramIngredientPageNumber);
    this->updatePageNumerotation(paramIngredientPageNumber);
    paramIngredientPageNumber=1;
    paramIngredientPage=0;
    this->show_all();
    this->set_current_page(1);  
}

void MainNotebook::openRecipeParameter(int RecipeNumber){
    extern RECIPE* LIST_RECIPES;

    if( paramRecipePage==0){
        paramRecipePage=1;
        Gtk::VBox* pnewBox=Gtk::manage(new Gtk::VBox(false,10));

            Gtk::Label* ptitleLabel= Gtk::manage(new Gtk::Label(LIST_RECIPES[RecipeNumber]->name));
            ptitleLabel->set_justify(Gtk::JUSTIFY_CENTER);
            ptitleLabel->set_line_wrap();
            ptitleLabel->set_can_focus(false);
            pnewBox->pack_start(*ptitleLabel);
            
            int i;
            Gtk::HBox* pelementBox;
            Gtk::Label* pelementLabel;
            char elementValue[10];
            for( i= 0 ; i < LIST_RECIPES[RecipeNumber]->nbIngredients; i ++){
                pelementBox= Gtk::manage( new Gtk::HBox(false,10));
                pelementBox->set_can_focus(false);
                pnewBox->pack_start(*pelementBox);
                    pelementLabel=Gtk::manage( new Gtk::Label(ingredient(((LIST_RECIPES[RecipeNumber])->listIddIngredients)[i])->name));
                    pelementLabel->set_can_focus(false);
                    pelementBox->pack_start(*pelementLabel);

                    sprintf(elementValue, "%f", ((LIST_RECIPES[RecipeNumber])->listAmount)[i]);
                    pelementLabel=Gtk::manage( new Gtk::Label());
                    pelementLabel->set_text(elementValue);
                    pelementLabel->set_can_focus(false);
                    pelementBox->pack_start(*pelementLabel);
                    
                    pelementLabel=Gtk::manage( new Gtk::Label("ml"));
                    pelementLabel->set_can_focus(false);
                    pelementBox->pack_start(*pelementLabel);
            }

            Gtk::HBox* pactionBox = Gtk::manage( new Gtk::HBox(false,10));
            pactionBox->set_can_focus(false);
            pnewBox->pack_end(*pactionBox,Gtk::PACK_SHRINK);
                Gtk::Button* psaveButton= Gtk::manage( new Gtk::Button(Gtk::Stock::EDIT));
                //psaveButton->signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this,&MainNotebook::closeAddRecipeThroughtInterface),1));
                pactionBox->pack_start(*psaveButton);

                Gtk::Button* prunButton= Gtk::manage( new Gtk::Button(Gtk::Stock::EXECUTE));
                prunButton->signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this,&MainNotebook::runRecipe),RecipeNumber));
                pactionBox->pack_start(*prunButton);
                
                Gtk::Button* pcancelButton = Gtk::manage( new Gtk::Button(Gtk::Stock::CLOSE));
                pcancelButton->signal_clicked().connect(sigc::mem_fun(*this,&MainNotebook::closeRecipeParameter));
                pactionBox->pack_start(*pcancelButton);
        
        
        int numPage = this->get_n_pages();
        paramRecipePageNumber=numPage;
        this->insert_page(*pnewBox, LIST_RECIPES[RecipeNumber]->name,  numPage);
        this->show_all();
        this->set_current_page(numPage);
    }
    else{

        this->show_all();
        this->set_current_page(paramRecipePageNumber);
        closeRecipeParameter();
        openRecipeParameter(RecipeNumber);
    }
}

void MainNotebook::runRecipe(int recipeNumber){
    if( ArduinoFailed) {
        return;
    }
    if((!ArduinoPort) || (! (ArduinoPort = initSerial())) )
    {
        ArduinoFailed = 1;
        return;
    }
    RECIPE newrecipe= recipe(recipeNumber);
    executeRecipe(newrecipe,ArduinoPort);
}


void MainNotebook::closeRecipeParameter(){

    this->remove_page(paramRecipePageNumber);
    this->updatePageNumerotation(paramRecipePageNumber);
    paramRecipePageNumber=2;
    paramRecipePage=0;
    this->show_all();
    this->set_current_page(2);  
}




void MainNotebook::updatePageNumerotation( int numberPageRemoved){

    if( paramRecipePageNumber>numberPageRemoved) paramRecipePageNumber--;
    if( newRecipePageNumber>numberPageRemoved) newRecipePageNumber--;
    if( paramIngredientPageNumber>numberPageRemoved) paramIngredientPageNumber--;
    if( newIngredientPageNumber>numberPageRemoved) newIngredientPageNumber--;
}