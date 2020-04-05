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

        Gtk::HBox* pingredientsBox = Gtk::manage ( new Gtk::HBox(false,10));
        append_page(*pingredientsBox,"ingrédients");

        Gtk::VBox* psubingredientsBox1 = Gtk::manage ( new Gtk::VBox(false,10));
        pingredientsBox->pack_start(*psubingredientsBox1);
                int i ;
                int iddIngredient;
                Gtk::Label* pLabel;
                Gtk::HBox* pHBox;
                Gtk::ComboBoxText* pnewIngredientSelected;
                for (i=0 ; i< SERVOSLOTNUMBER;i++)
                {              
                    pHBox = Gtk::manage ( new Gtk::HBox(false,10));
                    psubingredientsBox1->pack_start(*pHBox);
                    iddIngredient=iddingredientofplace(i);
                    pLabel = Gtk::manage(new Gtk::Label(to_string(i)));
                    pHBox->pack_start(*pLabel);
                    Gtk::ComboBoxText* pnewIngredientSelected = Gtk::manage( new Gtk::ComboBoxText());
                    pHBox->pack_start(*pnewIngredientSelected);
                    tabPSelectedIngredients.push_back(pnewIngredientSelected);
                    int j;
                    for (j = 0 ; j < NUMBER_INGREDIENTS ; j ++)
                    {
                        pnewIngredientSelected->append(LIST_INGREDIENTS[j]->name);
                    }
                    if(iddIngredient!=-1)
                    {
                        pnewIngredientSelected->set_active(iddIngredient);
                    }
                    pnewIngredientSelected->signal_changed().connect(sigc::bind<int,int>(sigc::mem_fun(*this,&MainNotebook::changeIngredientPlace),i,iddIngredient));
                   

                }
                Gtk::HButtonBox* psetResetBox =  Gtk::manage( new Gtk::HButtonBox(Gtk::BUTTONBOX_START,10)); 
                psubingredientsBox1->pack_end(*psetResetBox);
                    Gtk::Button* pButton = Gtk::manage(new Gtk::Button(Gtk::Stock::SAVE));
                    pButton->signal_clicked().connect(sigc::mem_fun(*this,&MainNotebook::_saveIngredientList));
                    psetResetBox->pack_start(*pButton);
                    pButton = Gtk::manage(new Gtk::Button(Gtk::Stock::DISCARD));
                    pButton->signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this,&MainNotebook::_resetIngredientPlace),-1));
                   
                    psetResetBox->pack_end(*pButton);
                    
                    


        Gtk::VBox* psubingredientsBox2 = Gtk::manage ( new Gtk::VBox(false,10));
        pingredientsBox->pack_start(*psubingredientsBox2);
            Gtk::ScrolledWindow* pscrolledIngredients = Gtk::manage( new Gtk::ScrolledWindow());
            psubingredientsBox2->pack_start(*pscrolledIngredients);
            pingredientsList = Gtk::manage( new Gtk::VButtonBox(Gtk::BUTTONBOX_START,10));
            pscrolledIngredients->add(*pingredientsList);
                for( i = 0 ; i < NUMBER_INGREDIENTS ; i ++){
                    pButton = Gtk::manage(new Gtk::Button(LIST_INGREDIENTS[i]->name));
                    //pButton->signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this,&MainNotebook::openIngredientParameter),i));
                    //there is no need to edit ingredients parameters, will be put back when the ingredient classwill be fournished with more elements
                    pingredientsList->pack_start(*pButton);
                }
            Gtk::Button* paddIngredient = Gtk::manage(new Gtk::Button("_Ajouter un ingrédient ", true));
            psubingredientsBox2->pack_end(*paddIngredient, Gtk::PACK_SHRINK);

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
    

        Gtk::VBox* pmusicsBox = Gtk::manage(new Gtk::VBox(false,10));
        append_page(*pmusicsBox, "musique");
            
            Gtk::Label* pinstructionsLabel= Gtk::manage ( new Gtk::Label());
            pmusicsBox->pack_start(*pinstructionsLabel,Gtk::PACK_EXPAND_WIDGET);

            Gtk::ScrolledWindow* pscrolledResultMusic = Gtk::manage( new Gtk::ScrolledWindow());
            pmusicsBox->pack_start(*pscrolledResultMusic,Gtk::PACK_EXPAND_WIDGET);
                pAnalysisResultBox = Gtk:: manage( new Gtk::TextView());
                pscrolledResultMusic->add(*pAnalysisResultBox);
                pAnalysisResultBox->set_editable(False);

                musicPath.set_markup("choisir un fichier");
                musicPath.set_justify(Gtk::JUSTIFY_CENTER);
                musicPath.set_line_wrap();
            pmusicsBox->pack_start(musicPath);
            


            Gtk::HButtonBox* pmusicButtonList = Gtk::manage( new Gtk::HButtonBox(Gtk::BUTTONBOX_START,10));
            pmusicsBox->pack_end(*pmusicButtonList,Gtk::PACK_EXPAND_WIDGET);
                Gtk::Button* popenMusicFile =Gtk:: manage( new Gtk::Button("Choisir musique"));
                pmusicButtonList->pack_start(*popenMusicFile);
                popenMusicFile->signal_clicked().connect(sigc::mem_fun(*this,&MainNotebook::launchMusicFileDialog));

                Gtk::Button* plaunchMusicAnalysis =Gtk:: manage( new Gtk::Button("Analyser"));
                pmusicButtonList->pack_start(*plaunchMusicAnalysis);
                plaunchMusicAnalysis->signal_clicked().connect(sigc::mem_fun(*this,&MainNotebook::launchMusicAnalysis));

            
            pmusicsBox->set_border_width(10);
            pscrolledResultMusic->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
            //pAnalysisResultText = Gtk:: manage( new Gtk::gtk_text_view_get_buffer (GTK_TEXT_VIEW (pAnalysisResultText)));
        
        pinstructionsLabel -> set_justify(Gtk::JUSTIFY_CENTER);
        pinstructionsLabel -> set_markup("<b><big>          Musicocktail        </big></b> \n\n  choisissez une musique à analyser et cliquer sur Analyser");
        pinstructionsLabel -> set_line_wrap();
        pinstructionsLabel -> set_width_chars(WIDTH/10);

    
    pmusicsBox->set_border_width(10);
        
    
}

MainWindow::MainWindow(){

    set_default_size(WIDTH,HEIGHT);
    set_border_width(10);
    set_title("Musicocktail");
    set_icon_from_file(ICONEFILE);

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

void MainNotebook::changeIngredientPlace(int setemplacement, int iddingredientprec){
    extern INGREDIENT* LIST_INGREDIENTS;
    extern int LIST_INGREDIENTS_CHANGED;
    int iddnewingredient = tabPSelectedIngredients[setemplacement]->get_active_row_number();
    int resetemplacement=-1;
    if(iddnewingredient!=-1) resetemplacement = LIST_INGREDIENTS[iddnewingredient]->servoAdress;
    if (resetemplacement!=-1)
    {
        tabPSelectedIngredients[resetemplacement]->set_active(-1);
    }
    if(iddnewingredient!=-1)
    {
    LIST_INGREDIENTS[iddnewingredient]->servoAdress=setemplacement;
    LIST_INGREDIENTS_CHANGED ++;
    }
    if (iddingredientprec!=-1)
    { 
        LIST_INGREDIENTS[iddingredientprec]->servoAdress=-1;
        LIST_INGREDIENTS_CHANGED ++;

    }

}

void MainNotebook::_saveIngredientList(){
    saveIngredientList();
}
void MainNotebook::_resetIngredientPlace(int place){
    resetIngredientPlace(place);
    int i; 
    for ( i = 0; i <SERVOSLOTNUMBER ; i++){
        tabPSelectedIngredients[i]->set_active(-1);
    }

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

            /*Gtk::HBox* psaltBox= Gtk::manage(new Gtk::HBox(false,10));
            psaltBox->set_can_focus(false);
                Gtk::Label* psaltLabel= Gtk::manage(new Gtk::Label("taux de sel en g/L :"));
                psaltLabel->set_can_focus(false);
            psaltBox->pack_start(*psaltLabel);
                Glib::RefPtr<Gtk::Adjustment> ajustementsalt = Gtk::Adjustment::create(0, 0, MAXSALT, 1);
                saltEntry.set_adjustment(ajustementsalt);
                saltEntry.set_numeric();
            psaltBox->pack_start(saltEntry);
        pnewBox->pack_start(*psaltBox);

            Gtk::HBox* psugarBox= Gtk::manage(new Gtk::HBox(false,10));
            psugarBox->set_can_focus(false);

                Gtk::Label* psugarLabel= Gtk::manage(new Gtk::Label("taux de sucre en g/L :"));
                psugarLabel->set_can_focus(false);
            psugarBox->pack_start(*psugarLabel);

                Glib::RefPtr<Gtk::Adjustment> ajustementSugar = Gtk::Adjustment::create(0, 0, MAXSUGAR, 1);
                sugarEntry.set_adjustment(ajustementSugar);
                sugarEntry.set_numeric();
            psugarBox->pack_start(sugarEntry);
        pnewBox->pack_start(*psugarBox);

            Gtk::HBox* pstrenghtBox= Gtk::manage( new Gtk:: HBox(false,10));
            pstrenghtBox->set_can_focus(false);
                Gtk::Label* pstrenghtLabel= Gtk::manage( new Gtk::Label("taux d'alcoolémie en % :"));
                pstrenghtLabel->set_can_focus(false);
            pstrenghtBox->pack_start(*pstrenghtLabel);
                Glib::RefPtr<Gtk::Adjustment> ajustementStrenght = Gtk::Adjustment::create(0, 0, MAXSTRENGHT, 1);
                strenghtEntry.set_adjustment(ajustementStrenght);
                strenghtEntry.set_numeric();
            pstrenghtBox->pack_start(strenghtEntry);
        pnewBox->pack_start(*pstrenghtBox);
            */
            Gtk::HBox* pservoBox = Gtk::manage( new Gtk::HBox(false,10));
            pservoBox->set_can_focus(false);
                Gtk::Label* pservoLabel= Gtk::manage( new Gtk::Label("numero sur le bar (-1 si il n'est pas sur le bar ):"));
                pservoLabel->set_can_focus(false);
            pservoBox->pack_start(*pservoLabel);
                Glib::RefPtr<Gtk::Adjustment> ajustementServo = Gtk::Adjustment::create(-1, -1,SERVOSLOTNUMBER-1, 1);
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
        //float salt = (float)(saltEntry.get_value_as_int());
        //float sugar = (float)(sugarEntry.get_value_as_int());
        //float strenght = (float)(strenghtEntry.get_value_as_int());
        int servoAdress = servoEntry.get_value_as_int();
        char name[Sname.size()+1];
        std::copy(Sname.begin(),Sname.end(), name);
        name[Sname.size()]='\0';
        if(addIngredient(name,servoAdress))
        {
            Gtk::Button* pButton = Gtk::manage(new Gtk::Button(LIST_INGREDIENTS[NUMBER_INGREDIENTS-1]->name));
            pButton->signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this,&MainNotebook::openIngredientParameter),NUMBER_INGREDIENTS-1));
            this->pingredientsList->pack_start(*pButton);
            int i ;
            for( i=0; i<SERVOSLOTNUMBER; i++){
                tabPSelectedIngredients[i]->append(LIST_INGREDIENTS[NUMBER_INGREDIENTS-1]->name);
            }
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

void MainNotebook::initAddRecipeThroughtInterface(){//can't add recipe two time or open the recipe created!!!
    puts("-1");
    extern INGREDIENT* LIST_INGREDIENTS;
    extern int NUMBER_INGREDIENTS;
    extern DESCRIPTOR* LIST_DESCRIPTORS;
    extern int NUMBER_DESCRIPTORS;
    puts("0");
    if( newRecipePage==0){
        puts("1");
        newRecipePage=2;
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
               puts("1.5"); 

            Gtk::HBox* pNumberIngredientsBox= Gtk::manage(new Gtk::HBox(false,10));
            pNumberIngredientsBox->set_can_focus(false);
            pnewBox->pack_start(*pNumberIngredientsBox,Gtk::PACK_SHRINK);
                Gtk::Label* pNumberIngredientsLabel= Gtk::manage(new Gtk::Label("Nombre d'ingrédients:"));
                pNumberIngredientsLabel->set_can_focus(false);
                pNumberIngredientsBox->pack_start(*pNumberIngredientsLabel,Gtk::PACK_SHRINK);
                puts("1.6");
                Glib::RefPtr<Gtk::Adjustment> ajustementNumberIngredients = Gtk::Adjustment::create(1,1,20, 1);
                puts("1.65");
                NumberIngredientsEntry.set_adjustment(ajustementNumberIngredients);
                puts("1.67");
                NumberIngredientsEntry.set_numeric();
                puts("1.68");
                NumberIngredientsEntry.signal_value_changed().connect(sigc::mem_fun(*this,&MainNotebook::actuateNumberIngredients));
                puts("1.7");
                pNumberIngredientsBox->pack_start(NumberIngredientsEntry,Gtk::PACK_SHRINK);
        puts("2");
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

            puts("3");
            Gtk::HBox* pdescriptorBox=Gtk::manage( new Gtk::HBox(false,10));;
            pdescriptorBox->set_can_focus(false);
            pnewBox->pack_start(*pdescriptorBox,Gtk::PACK_SHRINK);

                Gtk::CheckButton* pdescriptorCheck;
                int j;
                for( j= 0 ; j <NUMBER_DESCRIPTORS; j ++){
                        pdescriptorCheck=Gtk::manage( new Gtk::CheckButton(LIST_DESCRIPTORS[j]->name));
                        pdescriptorCheck->set_can_focus(false);
                        pdescriptorBox->pack_start(*pdescriptorCheck);
                        tabpdescriptorCheckNew.push_back(pdescriptorCheck);
                }
                //free(descriptorList);

            Gtk::HBox* pactionBox = Gtk::manage( new Gtk::HBox(false,10));
            pactionBox->set_can_focus(false);
            pnewBox->pack_end(*pactionBox,Gtk::PACK_SHRINK);
                Gtk::Button* psaveButton= Gtk::manage( new Gtk::Button(Gtk::Stock::SAVE));
                psaveButton->signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this,&MainNotebook::closeAddRecipeThroughtInterface),1));
                pactionBox->pack_start(*psaveButton);
                
                Gtk::Button* pcancelButton = Gtk::manage( new Gtk::Button(Gtk::Stock::CANCEL));
                pcancelButton->signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this,&MainNotebook::closeAddRecipeThroughtInterface),0));
                pactionBox->pack_start(*pcancelButton);
        
        
        puts("4");
        int numPage = this->get_n_pages();
        newRecipePageNumber=numPage;
        puts("5");
        this->insert_page(*pnewBox, "Nouveau cocktail",  numPage);
        this->show_all();
        puts("6");
        this->set_current_page(numPage);
        puts("7");
    }
    else{
        puts("8");
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
    extern int NUMBER_DESCRIPTORS;
    
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
        int j;
        int* descriptorList=(int*)calloc(NUMBER_DESCRIPTORS,sizeof(*descriptorList));
        for(j=0; j<NUMBER_DESCRIPTORS;j++){
            if(tabpdescriptorCheckNew[j]->get_active()) descriptorList[j]=1;
            else descriptorList[j]=0;
        }
        int descriptorTag = descriptorListtoTag(descriptorList);

        if( addRecipe( name,  nbIngredients ,   listIngredients,  listAmount, iddSimilarRecipe, descriptorTag))
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
    int k;
    for( k = NumberIngredient-1 ; k >-1 ; k-- ){
        //pRecipeElementsList->remove(*tabpRecipeElement[k]);
        tabpRecipeElement.pop_back();
        tabpIngredients.pop_back();
        tabpAmount.pop_back();
    }
    int l; 
    for(l = NUMBER_DESCRIPTORS-1;l>-1;l--){
        tabpdescriptorCheckNew.pop_back();
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

            Gtk::HBox* pservoBox = Gtk::manage( new Gtk::HBox(false,10));
            pservoBox->set_can_focus(false);
            pnewBox->pack_start(*pservoBox);
                if ( LIST_INGREDIENTS[iddIngredient]->servoAdress==-1){
                    Gtk::Label* pservoLabel=Gtk::manage( new Gtk::Label("emplacement (aucun pour l'instant) "));
                    pservoLabel->set_can_focus(false);
                    pservoBox->pack_start(*pservoLabel);
                }

                else{
                    Gtk::Label* pservoLabel=Gtk::manage( new Gtk::Label("emplacement sur l'armoire :"));
                    pservoLabel->set_can_focus(false);
                    pservoBox->pack_start(*pservoLabel);
                }
                    
                    Glib::RefPtr<Gtk::Adjustment> ajustementservo = Gtk::Adjustment::create(LIST_INGREDIENTS[iddIngredient]->servoAdress, -1, SERVOSLOTNUMBER-1, 1);
                    Gtk::SpinButton* pservoEntry=Gtk::manage( new Gtk::SpinButton());
                    pservoEntry->set_adjustment(ajustementservo);
                    pservoEntry->set_numeric();
                    pservoBox->pack_start(*pservoEntry);

            /*Gtk::HBox* psaltBox = Gtk::manage( new Gtk::HBox(false,10));
            psaltBox->set_can_focus(false);
            pnewBox->pack_start(*psaltBox);

                Gtk::Label* psaltLabel=Gtk::manage( new Gtk::Label("taux de sel (g/l):"));
                psaltLabel->set_can_focus(false);
                psaltBox->pack_start(*psaltLabel);

                Glib::RefPtr<Gtk::Adjustment> ajustementsalt = Gtk::Adjustment::create(LIST_INGREDIENTS[iddIngredient]->salt, 0, MAXSALT, 1);
                Gtk::SpinButton* psaltEntry=Gtk::manage( new Gtk::SpinButton());
                psaltEntry->set_adjustment(ajustementsalt);
                psaltEntry->set_numeric();
                psaltBox->pack_start(*psaltEntry);
            
            Gtk::HBox* psugarBox = Gtk::manage( new Gtk::HBox(false,10));
            psugarBox->set_can_focus(false);
            pnewBox->pack_start(*psugarBox);
                Gtk::Label* psugarLabel=Gtk::manage( new Gtk::Label("taux de sucre (g/l):"));
                psugarLabel->set_can_focus(false);
                psugarBox->pack_start(*psugarLabel);

                Glib::RefPtr<Gtk::Adjustment> ajustementsugar = Gtk::Adjustment::create(LIST_INGREDIENTS[iddIngredient]->sugar, 0,MAXSUGAR, 1);
                Gtk::SpinButton* psugarEntry=Gtk::manage( new Gtk::SpinButton());
                psugarEntry->set_adjustment(ajustementsugar);
                psugarEntry->set_numeric();
                psugarBox->pack_start(*psugarEntry);
            
            Gtk::HBox* pstrenghtBox = Gtk::manage( new Gtk::HBox(false,10));
            pstrenghtBox->set_can_focus(false);
            pnewBox->pack_start(*pstrenghtBox);
                Gtk::Label* pstrenghtLabel=Gtk::manage( new Gtk::Label("taux alcoolémique (%):"));
                pstrenghtLabel->set_can_focus(false);
                pstrenghtBox->pack_start(*pstrenghtLabel);

                Glib::RefPtr<Gtk::Adjustment> ajustementstrenght = Gtk::Adjustment::create(LIST_INGREDIENTS[iddIngredient]->strenght, 0, MAXSTRENGHT, 1);
                Gtk::SpinButton* pstrenghtEntry=Gtk::manage( new Gtk::SpinButton());
                pstrenghtEntry->set_adjustment(ajustementstrenght);
                pstrenghtEntry->set_numeric();
                pstrenghtBox->pack_start(*pstrenghtEntry);
                */
            Gtk::HBox* pactionBox = Gtk::manage( new Gtk::HBox(false,10));
            pactionBox->set_can_focus(false);
            pnewBox->pack_end(*pactionBox,Gtk::PACK_SHRINK);
                Gtk::Button* peditButton= Gtk::manage( new Gtk::Button(Gtk::Stock::EDIT));
                peditButton->signal_clicked().connect(sigc::bind<int,Gtk::SpinButton*>(sigc::mem_fun(*this,&MainNotebook::editIngredientParameter),iddIngredient,pservoEntry));
                pactionBox->pack_start(*peditButton);
                
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

void MainNotebook::editIngredientParameter(int iddIngredient, Gtk::SpinButton* pservoEntry){
    //float salt = (float)(psaltEntry->get_value_as_int());
    //float sugar = (float)(psugarEntry->get_value_as_int());
    //float strenght = (float)(pstrenghtEntry->get_value_as_int());
    int servoAdress = pservoEntry->get_value_as_int();

    if(editIngredient(servoAdress, iddIngredient)){
        this->closeIngredientParameter();        
    }
    else{
        //psaltEntry->set_sensitive(false);
        //psugarEntry->set_sensitive(false);
        //pstrenghtEntry->set_sensitive(false);
        pservoEntry->set_sensitive(false);
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
    extern DESCRIPTOR* LIST_DESCRIPTORS;
    extern int NUMBER_DESCRIPTORS;

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
            int executable=1;
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
                
                if (ingredient(((LIST_RECIPES[RecipeNumber])->listIddIngredients)[i])->servoAdress==-1){
                    printf("%s non place \n ",ingredient(((LIST_RECIPES[RecipeNumber])->listIddIngredients)[i])->name);
                    executable=0;
                }
            
            }     
            Gtk::HBox* pdescriptorBox=Gtk::manage( new Gtk::HBox(false,10));;
            pdescriptorBox->set_can_focus(false);
            pnewBox->pack_start(*pdescriptorBox,Gtk::PACK_SHRINK);

            //std::vector <Gtk::CheckButton*> tabpdescriptorCheckEdit;//ici!!!!
                Gtk::CheckButton* pdescriptorCheck;
                int j;
                int* descriptorList=descriptorTagtoList(LIST_RECIPES[RecipeNumber]->recipeDescription);

                for( j= 0 ; j <NUMBER_DESCRIPTORS; j ++){
                        pdescriptorCheck=Gtk::manage( new Gtk::CheckButton(LIST_DESCRIPTORS[j]->name));
                        pdescriptorCheck->set_can_focus(false);
                        pdescriptorBox->pack_start(*pdescriptorCheck);
                        if(descriptorList[j]) pdescriptorCheck->set_active();
                }
                //free(descriptorList);

            Gtk::HBox* pactionBox = Gtk::manage( new Gtk::HBox(false,10));
            pactionBox->set_can_focus(false);
            pnewBox->pack_end(*pactionBox,Gtk::PACK_SHRINK);
                Gtk::Button* psaveButton= Gtk::manage( new Gtk::Button(Gtk::Stock::EDIT));
                //psaveButton->signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this,&MainNotebook::closeAddRecipeThroughtInterface),1));
                pactionBox->pack_start(*psaveButton);

                Gtk::Button* prunButton= Gtk::manage( new Gtk::Button(Gtk::Stock::EXECUTE));
                prunButton->signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this,&MainNotebook::runRecipe),RecipeNumber));
                pactionBox->pack_start(*prunButton);
                if(!executable){
                    
                    prunButton->set_sensitive(false);
                }
                else{
                    prunButton->set_sensitive(true);
                }

                
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
        printf("cant connect arduino\n");

        return;
    }
    if( !ArduinoPort && !(ArduinoPort = initSerial()) )
    {
        ArduinoFailed = 1;
        printf("did not connect arduino\n");
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

void MainNotebook::launchMusicFileDialog(){
    GtkWidget *dialog;
    GtkFileFilter* filter = gtk_file_filter_new();
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;

    gtk_file_filter_add_pattern(GTK_FILE_FILTER(filter), "*.mp3");
    gtk_file_filter_add_pattern(GTK_FILE_FILTER(filter), "*.wav");

    dialog = gtk_file_chooser_dialog_new ("Open File",NULL,action, "_Cancel",GTK_RESPONSE_CANCEL,"_Open", GTK_RESPONSE_ACCEPT, NULL);
    gtk_file_chooser_set_filter(GTK_FILE_CHOOSER(dialog), GTK_FILE_FILTER(filter));
    res = gtk_dialog_run (GTK_DIALOG (dialog));

    if (res == GTK_RESPONSE_ACCEPT)
    {
        GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
        MusicFilePath = gtk_file_chooser_get_filename (chooser);
        musicPath.set_text(MusicFilePath);
    }
    gtk_widget_destroy (dialog);
}

void MainNotebook::launchMusicAnalysis(){
    musicPath.set_markup("analysis.....");
    if(MusicFilePath)
    { 
    std::string sMusicFilePath;
    sMusicFilePath += MusicFilePath;
    audioAnalysisFromFile(sMusicFilePath, MUSICANALYSISRESULTSFILE, MUSICANALYSISPROFILEFILE );
    musicPath.set_markup("analysis Done");
    puts("musical analysis done") ;

    /*std::fstream musicResultFile;
    gchar* musicResultText;
    musicResultFile.open (MUSICANALYSISPROFILEFILE, std::fstream::in | std::fstream::out | std::fstream::app);
    musicResultFile.read(musicResultText,musicResultFile.gcount());
    musicResultFile.close();
    pAnalysisResultBox->get_buffer()->set_text(musicResultText);
    */
    }
    else 
    puts("no music to analyse");
    
}

void MainNotebook::updatePageNumerotation( int numberPageRemoved){

    if( paramRecipePageNumber>numberPageRemoved) paramRecipePageNumber--;
    if( newRecipePageNumber>numberPageRemoved) newRecipePageNumber--;
    if( paramIngredientPageNumber>numberPageRemoved) paramIngredientPageNumber--;
    if( newIngredientPageNumber>numberPageRemoved) newIngredientPageNumber--;
}