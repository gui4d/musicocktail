from excel_import import *
from DataBase import *
from IA import *
from Music import *
from Cocktail import *


class test():

    def __init__(self):
        self.excel_path = "./test.xlsx"
        self.sql_path = r"./test.db"
        self.Data = DataBase(self.sql_path)
        self.IA_path= "./testMAtrix.npy"

    def read_excel(self):
        excel_file = excel_importer(self.excel_path, self.Data)
        excel_file.load_ingredients("Ingredients")
        excel_file.load_recipes("Recettes")
        excel_file.load_musics("Musiques")
        excel_file.show_data()

    def create_and_read_database(self):
        if (self.Data.open()):
            self.Data.create_tables()
            self.Data.show_all()
            print("ingredients : " + str(self.Data.number_ingredients()))
            print("recipes : " + str(self.Data.number_recipes()))
            print("musics : " + str(self.Data.number_musics()))

    def excel_to_database(self):
        if (self.Data.open()):
            #self.Data.create_tables()
            excel_file = excel_importer(self.excel_path, self.Data)
            list_ingredients = excel_file.load_ingredients("Ingredients")
            list_recipes = excel_file.load_recipes("Recettes")
            list_musics  = excel_file.load_musics("Musiques")
            for ingredient in list_ingredients:
                self.Data.save_ingredient(ingredient)
            for recipe in list_recipes : 
                print(recipe.Ingredients_names)
                print(recipe.Ingredients_measures)
                self.Data.save_recipe_data(recipe)
                self.Data.save_recipe_descriptors(recipe)
            for music in list_musics:
                self.Data.save_music_data(music)
            self.Data.show_all()
            self.Data.close()

    def create_cocktail(self):
        pina_colada = Cocktail()
        for i in range(pina_colada.Descriptors_list_size):
            pina_colada.Descriptors_Value[i]=float(random.randint(0,100))/100.
        print("pina colada :" + str(pina_colada.Descriptors_Value))
        return pina_colada

    def create_music(self):
        muse_uprise = Music()
        for i in range(muse_uprise.Extractor_list_size):
            muse_uprise.Extractors_Value[i]=float(random.randint(0,100))/100.
        print("muse uprise : " + str( muse_uprise.Extractors_Value))
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
        print("pina colada ",pina_colada.Descriptors_Value)
        print("muse uprise ", muse_uprise.Extractors_Value)
        print("alcool size ",pina_colada.Descriptors_list_size)
        print("music size ", muse_uprise.Extractor_list_size)
        print("correlation matrix ",Correlation_test.Matrix)
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
        print("MUSIC :")
        print(Music0.Extractors_Value)
        print("Cocktail :")
        print(Cocktail0.Descriptors_Value)
        print("Equivalent Cocktail :")
        print(Equivalent_Cocktail.Descriptors_Value)
        for i in range (10):
            Ia0.Apprentissage(Music0,Cocktail0)
            Ia0.show_Matrix()

    def Manual_Learning_IA(self):
        Ia = IA()
        Ia.load_matrix_at(self.IA_path)
        Ia.show_Matrix()
        Ia.save_matrix_at(self.IA_path)



test = test()

#test.create_and_read_database()
test.excel_to_database()
#test.distance_recipe_music()
#test.SurAprentisage_IA()
