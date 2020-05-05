import numpy  as np
import pandas 
import math
from Music import *
from IA import *
from Cocktail import * 

class Excel_importer():

    def __init__(self,excel_path):
        
        self.excel_path = excel_path
        self.excel_ingredient= None
        self.loaded_ingredients = []
        self.excel_recipe = None
        self.loaded_recipes =[]
        self.excel_music= None
        self.loaded_musics =[]

    def load_musics(self, tab_name):
        self.excel_music = pandas.read_excel(self.excel_path, tab_name) 
        new_musics= self.excel_music[music_data].dropna(how = 'all')
        table_size = new_musics.shape[0]
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
            self.loaded_musics.append(new_music)
        return self.loaded_musics

    def load_ingredients(self, tab_name):
        self.excel_ingredient = pandas.read_excel(self.excel_path, tab_name)
        new_ingredients = self.excel_ingredient[ingredient_data].dropna(how = 'all')
        table_size = new_ingredients.shape[0]
        for i in range(table_size):
            ingredient_array= new_ingredients.iloc[i,:]
            ingredient = Ingredient()      
            ingredient.Name= str(ingredient_array["name"])
            ingredient.Base_name = str(ingredient_array["base_name"])
            ingredient.Type = str(ingredient_array["type"])
            ingredient.Birth_region = str(ingredient_array["birth_region"])
            ingredient.Birth_date = str(ingredient_array["birth_date"])
            self.loaded_ingredients.append(ingredient)
        return self.loaded_ingredients
    
    def load_recipes(self, tab_name):
        self.excel_recipe = pandas.read_excel(self.excel_path, tab_name)
        new_recipes = self.excel_recipe[cocktail_data + cocktail_descriptors_title].dropna(how = 'all')
        table_size = new_recipes.shape[0]
        for i in range(table_size):
            recipe= new_recipes.iloc[i,:]
            new_recipe = Cocktail()
            new_recipe.Name = recipe[0]
            new_recipe.Source_recipe = recipe[1]
            new_recipe.Picture_link = recipe[2]
            new_recipe.Glass =  recipe[3]
            new_recipe.Instructions = recipe[4]
            ####find an other way to clean the entrant data 
            ingredient_names = recipe[5:19].replace(' ', np.nan).replace('\r\n', np.nan).replace('\n', np.nan).dropna().tolist()
            ingredient_measures = recipe[20:34].replace(' ', np.nan).dropna().replace('\r\n', np.nan).replace('\n', np.nan).dropna().tolist()
            ingredient_measures = self.cocktail_unity_conversion(ingredient_measures)
            new_recipe.Number_ingredients = len(ingredient_names)
            for i in range(new_recipe.Number_ingredients): 
                        new_recipe.Ingredients[i][0]= ingredient_names[i]
                        if new_recipe.Ingredients[i][0]=="":
                            print( "WARNING : in load_recipe , empty ingredient")
                        try:
                            new_recipe.Ingredients[i][2] = ingredient_measures[i]
                        except IndexError :
                            new_recipe.Ingredients[i][2] = 0.
                            print("WARNING : in load_recipe, missing measure in ", new_recipe.Name)
            self.loaded_recipes.append(new_recipe)
        return self.loaded_recipes


    def show(self):
        if self.excel_ingredient is not None :
            print("ingredients #################")
            print(self.excel_ingredient.head())
        if self.excel_recipe is not None :
            print("Cocktails #################")
            print(self.excel_recipe.head())
        if self.excel_music is not None :
            print("musics #################")
            print(self.excel_music.head())

    def summary(self):
        if self.excel_ingredient is not None :
            print("ingredients:",  len(self.loaded_ingredients))
        if self.excel_recipe is not None :
            print("Cocktails :", len(self.loaded_recipes))
        if self.excel_music is not None :
            print("musics :", len(self.loaded_musics))

    def cocktail_unity_conversion(self,measure_array, total_amount=200):
        already_poured = 0
        clean_measure= [ 0. for i in measure_array]
        complete= -1
        part = []
        total_part = 0
        multiplier = 1
        value = 0  
        for i in range(len(measure_array)): 
            multiplier = self.unity_finder(measure_array[i])
            value= self.regex_convert(measure_array[i])
            if measure_array[i].find("Fill")!=-1 or measure_array[i].find("Top")!=-1:
                complete = i
            elif measure_array[i].find("part")!=-1:
                clean_measure[i]=value
                total_part += value
                part.append(i)
            else: 
                clean_measure[i] = multiplier*value
                already_poured += clean_measure[i]            
        if total_part!=0 and already_poured < total_amount: 
            for i in part:
                clean_measure[i] *= (total_amount - already_poured)/total_part
        elif complete!=-1 and already_poured < total_amount: 
            clean_measure[complete] = total_amount- already_poured
        return(clean_measure)

    def unity_finder(self,measure): #find the unity and give the conversition to the mililiter
        if measure.find("oz") !=-1:
            multplier= 29.5735
        elif measure.find("cl") !=-1:
            multplier = 10.
        elif measure.find("Shot")!=-1 or measure.find("shot")!=-1  :
            multplier= 44.3603
        elif measure.find("dash")!=-1 or measure.find("Dash")!=-1:
            multplier= 0.62
        elif measure.find("wedge")!=-1:
            multplier = 0.5
        elif measure.find("twist")!=-1:
            multplier = 0.1
        elif measure.find("cup")!=-1:
            multplier = 236.588
        elif measure.find("splash")!=-1 or measure.find("Splash")!=-1:
            multplier= 5.91
        elif measure.find("tsp")!=-1:
            multplier= 4.92892
        elif measure.find("tbsp")!=-1:
            multplier = 14.7868
        elif measure.find("jigger")!=-1:
            multplier= 44.3603
        elif measure.find("juice")!=-1:
            multplier= 30. 
        else : 
            multplier = 1.
        return multplier

    def regex_convert(self,element):# convert in float expression of type 2/3-4/5 other type gives 0
        if element=="":
            return 0
        if element.isalpha():
            return 0
        size = len(element)
        for i in range(size ):
            if element[i] == " ":
                return self.regex_convert(element[:i]) + self.regex_convert(element[i+1:])    
        for i in range(size ):
            if element[i] == "-":
                return (self.regex_convert(element[:i]) + self.regex_convert(element[i+1:]))/2 
        for i in range(size ):
            if element[i] =="/":
                divis = self.regex_convert(element[i+1:])
                if divis != 0:
                    divid = self.regex_convert(element[:i])
                    return divid/divis
                else : 
                    return 0
        try:
            element=float(element)
            return element
        except ValueError: 
            return 0





