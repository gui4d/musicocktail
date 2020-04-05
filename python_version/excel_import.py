import numpy  as np
import pandas 
import math
from Music import *
from IA import *
from Cocktail import * 

##transform into music , cocktail , recipe before going to DB  ( also Clean )

class excel_importer():

    def __init__(self,excel_path, DataBase):
        
        self.excel_path = excel_path
        self.excel_ingredient= None
        self.excel_recipe = None
        self.excel_music= None

    def load_musics(self, tab_name):
        self.excel_music = pandas.read_excel(self.excel_path, tab_name) 
        new_musics= self.excel_music[music_data].dropna(how = 'all')
        table_size = new_musics.shape[0]
        music_array = []
        for i in range(table_size):
            new_music = Music()
            music= new_musics.iloc[i,:]
            new_music.Title= music[0]
            new_music.Album= music[1]
            new_music.Commentary = music[2]
            new_music.Author = music[3]
            new_music.Year = music[4]
            new_music.File_path = music[5]
            new_music.Genre = music[6]
            music_array.append(new_music)
        return music_array

    def load_ingredients(self, tab_name):
        self.excel_ingredient = pandas.read_excel(self.excel_path, tab_name)
        new_ingredients = self.excel_ingredient[ingredient_data].dropna(how = 'all')
        table_size = new_ingredients.shape[0]
        print("ingredients :" + str(table_size))
        ingredient_list = []
        for i in range(table_size):
            ingredient_array= new_ingredients.iloc[i,:]
            ingredient = Ingredient()      
            ingredient.Name= str(ingredient_array["name"])
            ingredient.Base_name = str(ingredient_array["base_name"])
            ingredient.Type = str(ingredient_array["type"])
            ingredient.Birth_region = str(ingredient_array["birth_region"])
            ingredient.Birth_date = int(ingredient_array["birth_date"])
            ingredient_list.append(ingredient)
        return ingredient_list
    
    def load_recipes(self, tab_name):
        self.excel_recipe = pandas.read_excel(self.excel_path, tab_name)
        new_recipes = self.excel_recipe[cocktail_data + cocktail_descriptors_title].dropna(how = 'all')
        table_size = new_recipes.shape[0]
        print("Recipes :" + str(table_size))
        recipe_array=[]
        for i in range(table_size):
            recipe= new_recipes.iloc[i,:]
            new_recipe = Cocktail()
            new_recipe.Name = recipe[0]
            new_recipe.source_recipe= recipe[1]
            new_recipe.picture_link= recipe[2]
            new_recipe.glass =  recipe[3]
            ####find an other way to clean the entrant data 
            ingredient_names = recipe[4:18].replace(' ', np.nan).replace('\r\n', np.nan).replace('\n', np.nan).dropna().tolist()
            ingredient_measures = recipe[19:33].replace(' ', np.nan).dropna().replace('\r\n', np.nan).replace('\n', np.nan).dropna().tolist()
            new_recipe.Ingredients_names = list(ingredient_names)
            new_recipe.Ingredients_measures = list(ingredient_measures)
            ################################################""
            for i in range( len(cocktail_descriptors_group)):
                if recipe[i+34] in cocktail_descriptors :
                    descriptor_index = cocktail_descriptors.index(recipe[i+34])
                    new_recipe.Descriptors_Value[descriptor_index]= 1.
            recipe_array.append(new_recipe)
        return recipe_array

    def show_data(self):
        if self.excel_ingredient is not None :
            print("ingredients #################")
            print(self.excel_ingredient.head())
        if self.excel_recipe is not None :
            print("Cocktails #################")
            print(self.excel_recipe.head())
        if self.excel_music is not None :
            print("musics #################")
            print(self.excel_music.head())



