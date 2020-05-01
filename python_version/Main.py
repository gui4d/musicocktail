from Excel_import import *
from DataBase import *
from IA import *
from Music import *
from Cocktail import *
from Gui import *


class Main():

    def __init__(self , Excel_path = "./Database/Database.xlsx" , Sql_path = r"./Database/Database.db" , IA_path= "./Database/IA.npy", IA_ref_path ="./Database/matrice_ref.npy"):
        self.excel_path = Excel_path
        self.excel = Excel_importer(self.excel_path)
        self.excel_loaded = False
        self.sql_path = Sql_path
        self.data = DataBase(self.sql_path)
        self.IA_path= IA_path
        self.IA_ref_path = IA_ref_path
        self.gui = Gui()

    def load_excel(self):
        if not self.excel_loaded :
            self.excel.load_ingredients("Ingredients")
            self.excel.load_recipes("Recettes")
            self.excel.load_musics("Musiques")
            self.excel_loaded = True
        self.excel.summary()

    def create_database(self):
        if (self.data.open()):
            self.data.create_tables()
            self.data.summary()
            self.data.close()
        
    def read_database(self, verbose ):
        if (self.data.open()):
            if verbose : 
                self.data.show()
            else : 
                self.data.summary()
            self.data.close()

    def excel_to_database(self):
        if (self.data.open()):
            #self.data.create_tables()
            self.load_excel()
            for ingredient in self.excel.loaded_ingredients:
                self.data.save_ingredient(ingredient)
            for recipe in self.excel.loaded_recipes : 
                self.data.save_recipe(recipe)
            for music in self.excel.loaded_musics:
                self.data.save_music_data(music)
            self.data.summary()
            self.data.close()

    def Manual_Learning_IA(self):
        Ia = IA()
        Ia.load_matrix_at(self.IA_path)
        Ia.show_Matrix()
        Ia.save_matrix_at(self.IA_path)

    def graphical_Music_Modification(self, music): 
        music.show()
        self.gui.Modify_Music(music)
        music.show()
    
    def graphical_Cocktail_Modification(self, cocktail):
        cocktail.show()
        cocktail.show_Descriptors_Values_by_groups()
        self.gui.Modify_Cocktail(cocktail)
        cocktail.show()
        cocktail.show_Descriptors_Values_by_groups()

    def graphical_Cocktails_Modification(self):
        if (self.data.open()): 
            for i in range(self.data.number_recipes()):
                Cocktails=self.data.recipes(i+1)
                if len(Cocktails)==0 :
                    print("no cocktail of id " , i+1) 
                else : 
                    Cocktail= Cocktails[0]
                    event=self.gui.Modify_Cocktail(Cocktail)
                    if self.data.update_recipe_data(Cocktail) != 0:
                        self.data.update_recipe_descriptors(Cocktail)
                    else: 
                        print(" error saving cocktail " , end="")
                        Cocktail.summary()
                    if event in (None, 'Stop') :
                        break
            self.data.close()  
            return True
        else: 
            return False
