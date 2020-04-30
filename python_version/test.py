from Excel_import import *
from DataBase import *
from IA import *
from Music import *
from Cocktail import *
from Gui import *


class Test():

    def __init__(self):
        self.excel_path = "./Database/Database.xlsx"
        self.sql_path = r"./DataTest/test.db"
        self.Data = DataBase(self.sql_path)
        self.IA_path= "./DataTest/testMatrix.npy"

    def read_excel(self):
        excel_file = Excel_importer(self.excel_path)
        excel_file.load_ingredients("Ingredients")
        excel_file.load_recipes("Recettes")
        excel_file.load_musics("Musiques")
        excel_file.summary()

    def create_database(self):
        if (self.Data.open()):
            self.Data.create_tables()
            self.Data.summary()
            self.Data.close()
        
    def read_database(self):
        if (self.Data.open()):
            ingredients = self.Data.ingredients()
            for ingredient in ingredients:
                ingredient.show()
            recipes = self.Data.recipes()
            for recipe in recipes : 
                recipe.show()
            musics = self.Data.musics()
            for music in musics :
                music.show()
            self.Data.close()

    def excel_to_database(self):
        if (self.Data.open()):
            #self.Data.create_tables()
            excel_file = Excel_importer(self.excel_path)
            list_ingredients = excel_file.load_ingredients("Ingredients")
            list_recipes = excel_file.load_recipes("Recettes")
            list_musics  = excel_file.load_musics("Musiques")
            for ingredient in list_ingredients:
                self.Data.save_ingredient(ingredient)
            for recipe in list_recipes : 
                self.Data.save_recipe_data(recipe)
                self.Data.save_recipe_descriptors(recipe)
            for music in list_musics:
                self.Data.save_music_data(music)
            self.Data.close()

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

    def Manual_Learning_IA(self):
        Ia = IA()
        Ia.load_matrix_at(self.IA_path)
        Ia.show_Matrix()
        Ia.save_matrix_at(self.IA_path)

    def graphical_Music_Modification(self): 
        graph = Gui()
        music = self.create_music()
        music.show()
        graph.Modify_Music(music)
        music.show()
    
    def graphical_Cocktail_Modification(self):
        graph = Gui()
        cocktail = self.create_cocktail()
        cocktail.show()
        cocktail.show_Descriptors_Values_by_groups()
        graph.Modify_Cocktail(cocktail)
        cocktail.show()
        cocktail.show_Descriptors_Values_by_groups()


