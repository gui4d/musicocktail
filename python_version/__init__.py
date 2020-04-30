from Test import *
from Cocktail import *
from DataBase import *
from Excel_import import *
from Gui import *
from IA import *
from Music_Analysis import *
from Music import *

#config
Excel_path = "./Database/Database.xlsx"
Sql_path = r"./Database/Database.db"
IA_path= "./DataTest/IA.npy"
IA_Ref_path = "./DataTest/matrice_ref.npy"
database= DataBase(Sql_path)



# programm 

def init_Database():
    if (database.open()):
        database.create_tables()
        return True
    else: 
        return False

def fuel_Database():
    if (database.open()):
        excel_file = Excel_importer(Excel_path)
        list_ingredients = excel_file.load_ingredients("Ingredients")
        list_recipes = excel_file.load_recipes("Recettes")
        list_musics  = excel_file.load_musics("Musiques")
        for ingredient in list_ingredients:
            database.save_ingredient(ingredient)
            print(ingredient.Name , end='')
        print('#########')
        for recipe in list_recipes : 
            database.save_recipe_data(recipe)
            database.save_recipe_descriptors(recipe)
            print(recipe.Name , end='')
        print('#########')
        for music in list_musics:
            database.save_music_data(music)
            print(music.Title , end='')
        print('#########')
        database.close()

def change_recipes_descriptors():
    gui = Gui()
    recipe_id= 1
    number_recipe = 0
    if (database.open()): 
        number_recipe=database.number_recipe()
        for i in range(number_recipe):
            Cocktails=database.recipes(recipe_id)
            if len(Cocktails)==0 : 
                continue
            else : 
                Cocktail= Cocktails[0]
                event=gui.Modify_Cocktail(Cocktail)
                database.save_recipe_data(Cocktail)
                database.save_recipe_descriptors(Cocktail)
                if event in (None, 'Stop') :
                    break
    
                
        

    else: 
        return False


def test_everything():
    test = Test()
    print("CREATE DATABASE ############################################")
    test.create_database()
    print("EXCEL TO DATABASE ############################################")
    test.excel_to_database()
    #print("READ DATABASE ############################################")
    #test.read_database()
    #test.distance_recipe_music()
    #test.SurAprentisage_IA()
    #test.graphical_Music_Modification()
    #test.graphical_Cocktail_Modification()




test_everything()
#init_Database()
#fuel_Database()

#print(cocktail_unity_conversion(["16 oz	","1.5 oz "], 200))
#print(cocktail_unity_conversion(["1/2 oz ",	"1/2 oz ",	"1/2 oz Bacardi" ,	"1 oz" ,	"1 oz" ,	"3 oz" ,	"1 oz" ,	"1 cup" ], 200))
#print(cocktail_unity_conversion(["2 1/2 oz" ,	"1 splash" ,	"Fill with" ], 300))
#print(cocktail_unity_conversion(["1 3/4 shot ",	"1 Shot" ,	"1/4 Shot"	,"1/8 Shot"],200))
#print(cocktail_unity_conversion(["1 part", 	"1 part ",	"1 part" ,	"1/2 part", " 1 oz"],200))

