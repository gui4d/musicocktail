from Excel_import import *
from DataBase import *
from IA import *
from Music import *
from Cocktail import *
from Gui import *
from Main import *

class Test(Main):

    def __init__(self , Excel_path = "./Database/Database.xlsx" , Sql_path = r"./DataTest/test.db" , IA_path= "./DataTest/testMatrix.npy", IA_ref_path ="./DataTest/testMatrix.npy"):
        self.excel_path = Excel_path
        self.excel = Excel_importer(self.excel_path)
        self.excel_loaded = False
        self.sql_path = Sql_path
        self.data = DataBase(self.sql_path)
        self.IA_path= IA_path
        self.IA_ref_path = IA_ref_path
        self.gui = Gui()

    
    def test_everything(self):
        print("CREATE DATABASE ############################################")
        self.create_database()
        print("EXCEL TO DATABASE ############################################")
        self.excel_to_database()
        print("READ DATABASE ############################################")
        self.read_database(verbose=False)
        print("MODIFY DATABASE ###############")
        self.graphical_Cocktails_Modification()
        #self.distance_recipe_music()
        #self.SurAprentisage_IA()
        #self.graphical_Music_Modification()
        #self.graphical_Cocktail_Modification()

    def create_cocktail(self):
        pina_colada = Cocktail()
        pina_colada.Randomize_Descriptors()
        pina_colada.Name = "pina colada"
        pina_colada.Source_name="none"
        pina_colada.Picture_link="https://assets.afcdn.com/recipe/20180705/80258_w648h344c1cx974cy1535cxt0cyt0cxb2471cyb3164.jpg"
        pina_colada.Glass="punch"
        pina_colada.Instructions = "pas d'instructions"
        Ingredients_names=["rhum blanc", "rhum ambré", "jus d'annanas" , "noix de coco"]
        self.Ingredients_measures=["40", "20" , "120", "40"]
        return pina_colada

    def create_music(self):
        muse_uprise = Music()
        muse_uprise.Title = "Uprise"
        muse_uprise.Album = "Uprising"
        muse_uprise.Author = "Muse"
        muse_uprise.Comentary = " exemple"
        muse_uprise.Year = "2009"
        muse_uprise.Genre = "Rock"
        muse_uprise.Randomize_Extractors()
        return muse_uprise

    def create_IA(self):
        Correlation_test=IA()
        for i in range(163): 
            for j in range(124):
                Correlation_test.Add_Relation(i,j, -i + j + math.sqrt(i*j) )
        Correlation_test.Normalise()
        return Correlation_test
    
    def distance_recipe_music(self):
        pina_colada = self.create_cocktail()
        muse_uprise = self.create_music()
        Correlation_test = self.create_IA()      
        print("Cocktail size ",pina_colada.Descriptors_list_size)
        print("music size ", muse_uprise.Extractor_list_size)
        distance = Correlation_test.Distance(muse_uprise,pina_colada)
        print( "Distance ", distance)

    def SurAprentisage_IA(self):
        Cocktail0  = self.create_cocktail()
        Music0 = self.create_music()
        Ia0 = self.create_IA()  
        Equivalent_Cocktail= Cocktail() 
        Equivalent_Cocktail.Load_Descriptors_From_Array(Ia0.Equivalent_Cocktail_array(Music0));
        # do not pas by array but by MUSIC class 
        Ia0.show_Matrix()
        for i in range (10):
            Ia0.Apprentissage(Music0,Cocktail0)
            Ia0.show_Matrix()


