import numpy as np
import matplotlib.pyplot as plt
import math
import matplotlib.pyplot as plt
import matplotlib.cm as cm
from datetime import date
import random

cocktail_data = ['name',
        'source_name',
        'picture_link',
        'Glass',
        'ingredient1_id',
        'ingredient2_id',
        'ingredient3_id',
        'ingredient4_id',
        'ingredient5_id',
        'ingredient6_id',
        'ingredient7_id',
        'ingredient8_id',
        'ingredient9_id',
        'ingredient10_id',
        'ingredient11_id',
        'ingredient12_id',
        'ingredient13_id',
        'ingredient14_id',
        'ingredient15_id',
        'measure1',
        'measure2',
        'measure3',
        'measure4',
        'measure5',
        'measure6',
        'measure7',
        'measure8',
        'measure9',
        'measure10',
        'measure11',
        'measure12',
        'measure13',
        'measure14',
        'measure15',]
cocktail_descriptors =[ 'Main_Alcool_Vodka',
       'Main_Alcool_Gin',
       'Main_Alcool_Rum' ,
       'Main_Alcool_Bourbon' ,
       'Main_Alcool_Scotch' ,
       'Main_Alcool_Whisky' ,
       'Main_Alcool_Liqueur',
       'Main_Alcool_Schnapps' ,
       'Main_Alcool_Wine',
       'Main_Alcool_Sparkling' ,
       'Main_Alcool_Other' ,
       'Main_Alcool_nonAlcolic' ,
       'Main_Alcool_Whiskey' ,
       'Main_Alcool_Tequila_and_Mezcal' , 

       'Genre_Classic' , 
       'Genre_Modern_Classics' ,
       'Genre_Tiki_and_Tropical' ,
       'Genre_Coffee_and_Dessert' ,
       'Genre_Shots_and_Shooters',
       'Genre_Punches' ,
       'Genre_Nonalcoholic' ,

       'Preparation_On_the_Rocks' ,
       'Preparation_Up_Cocktails',
       'Preparation_Neat_Cocktails' ,
       'Preparation_Shaken' ,
       'Preparation_Built_in_Glass' ,
       'Preparation_Poured' ,
       'Preparation_Stirred' ,
       'Preparation_Heated' ,
       'Preparation_Frozen_Blended' ,

       'Occasion_New_Year_Eve' ,
       'Occasion_Valentine_Day' ,
       'Occasion_St_Patrick_Day' ,
       'Occasion_National_day' ,
       'Occasion_Halloween' ,
       'Occasion_Thanksgiving' ,
       'Occasion_Christmas' ,
       'Occasion_Spring' ,
       'Occasion_Summer' ,
       'Occasion_Winter' ,
       'Occasion_Autumn' ,
       'Occasion_Brunch' ,
       'Occasion_Aperitifs_and_Digestifs' ,
       'Occasion_Nightcaps' ,
       'Occasion_Other' ,

       'Flavors_Bitter' ,
       'Flavors_Sweet' ,
       'Flavors_Savory' ,
       'Flavors_Sour' ,
       'Flavors_Spicy' ,
       'Flavors_Fruity' ,
       'Flavors_Smoky' ,
       'Flavors_Herbaceous' ,

       'Paul_Clarke_Ancestrals' ,
       'Paul_Clarke_Sours' ,
       'Paul_Clarke_Spirit_Forward' ,
       'Paul_Clarke_Duos_and_Trios' ,
       'Paul_Clarke_Champagne' ,
       'Paul_Clarke_Highballs_Collinses_and_Fizzes' ,
       'Paul_Clarke_Juleps_and_Smashes' ,
       'Paul_Clarke_Hot_Drinks' ,
       'Paul_Clarke_Flips_and_Nogs' ,
       'Paul_Clarke_Pousse_Family' ,
       'Paul_Clarke_Tropical_Style' ,
       'Paul_Clarke_Punches' ,

       'Gary_Regan_Beer_Cider_Champagne' ,
       'Gary_Regan_Bottled' ,
       'Gary_Regan_Duos_and_Trios' ,
       'Gary_Regan_French_Italian' ,
       'Gary_Regan_Frozen' ,
       'Gary_Regan_Highballs' ,
       'Gary_Regan_Hot_Drinks' ,
       'Gary_Regan_Infusions' ,
       'Gary_Regan_Jelly_Shots' ,
       'Gary_Regan_Juleps' ,
       'Gary_Regan_Milanese' ,
       'Gary_Regan_Muddled' ,
       'Gary_Regan_Orphans' ,
       'Gary_Regan_Pouss_Cafés' ,
       'Gary_Regan_Punches' ,
       'Gary_Regan_Snappers' ,
       'Gary_Regan_Sours' ,
       'Gary_Regan_Tropical' ,

       'IBA_unforgettables' ,
       'IBA_Contemporary_classics' ,
       'IBA_New_era' ,

       'Region_Musulman' ,
       'Region_Latino_American' ,
       'Region_Slav' ,
       'Region_extreme_orient' ,
       'Region_Africa' ,
       'Region_South_America' ,
       'Region_Caribbean' ,
       'Region_Europe' ,
       'Region_Mediterranea' ,
       'Region_India' ,
       'Region_extreme_asia' ,

       'City_Londres' ,
       'City_Paris' ,
       'City_Singapour' ,
       'City_Venise' ,
       'City_Massachusetts' ,
       'City_Mexique' ,
       'City_San_Francisco' ,
       'City_Cuba' ,
       'City_Brésil' ,
       'City_Porto_Rico' ,
       'City_California' ,
       'City_New_York' ,
       'City_Other' ,

       'age_0' ,
       'age_1000' ,
       'age_1500' ,
       'age_1750' ,
       'age_1800' ,
       'age_1850' ,
       'age_1900' ,
       'age_1925' ,
       'age_1950' ,
       'age_1985' ,
       'age_2000' ,
       'age_2010' ,
       'age_2015' ,
       'age_2020' ,]
cocktail_descriptors_group = [[0,1,2,3,4,5,6,7,8,9,10,11,12,13],
        [14,15,16,17,18,19,20],
        [21,22,23,24,25,26,27,28,29],
        [30,31,32,33,34,35,36,37,38,39,40,41,42,43,44],
        [45,46,47,48,49,50,51,52],
        [53,54,55,56,57,58,59,60,61,62,63,64],
        [65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82],
        [83,84,85],
        [86,87,88,89,90,91,92,93,94,95,96],
        [97,98,99,100,101,102,103,104,105,106,107,108,109],
        [110,111,112,113,114,115,116,117,118,119,120,121,122,123]]
cocktail_descriptors_title =['Main_Alcool','Genre','Preparation','Occasion','Flavors','Paul_Clarke','Gary_Regan' , 'IBA' ,'Region','City','age']
ingredient_data= ['name','base_name','type','birth_region','birth_date']
 
class Cocktail:

    def __init__(self): 
        self.Id=0
        self.Name=""
        self.Source_name=""
        self.Variation_number=0
        self.Picture_link=""
        self.Glass=""
        self.Ingredients_names=[]
        self.Ingredients_measures=[]
        self.Descriptors_Name = cocktail_descriptors
        self.Descriptors_list_size = len(self.Descriptors_Name);
        self.Descriptors_Value = [0. for i in range(self.Descriptors_list_size)] 
        self.Groups = cocktail_descriptors_group

    #def create_manual(self):

    def show_Descriptors_Names_by_groups(self):       
        for group in self.Groups:
            for element in group: 
                print(self.Descriptors_Name[element])
            print("###############")
    
    def show_Descriptors_Values_by_groups(self):       
        for group in self.Groups:
            for element in group: 
                print(self.Descriptors_Value[element])
            print("###############")
    
    def Randomize_Descriptors(self):
        for i in range(self.Descriptors_list_size):
            self.Descriptors_Value[i]= float(random.randint(0,100))/100.

    def Load_Descriptors_From_Array(self,Descriptors_Value):
        if (len(Descriptors_Value)==self.Descriptors_list_size) :
            for i in range(self.Descriptors_list_size):
                self.Descriptors_Value[i]= Descriptors_Value[i]
    

    ###function to migrate in dataBase 

    def Load_From_database(self,row):
        self.Id= int(row[0])
        self.Name= str(row[1])
        self.Source_id= int(row[2])
        self.Variation_number= int(row[3])
        self.Picture_link= str(row[4])
        self.Glass= str(row[5])
        self.Ingredients_names.clear()
        self.Ingredients_measures.clear()
        for i in range(15):
            if(str(row[i+6])!= 0):
                self.Ingredients_id.append(int(row[i+6]))
                self.Ingredients_measures.append(float(row[i+ 21 ]))
            else: 
                break
        for i in range(self.Descriptors_list_size):
            self.Descriptors_Value[i] = float(row[i+36])
        
        #function to migrate in database
    def Save_into_database(self,database):
        if self.Id == 0 :
            self.Id= database.create_new_recipe(self.Name ,self.Ingredients_id ,self.Ingredients_measures, self.Source_id , self.Variation_number,self.Picture_link,self.Glass)
        if(self.Id != 0):
            database.save_recipe_descriptors(self.Id, self.Descriptors_Value)
        else: 
            print("errror in music.save_into_database")

    def Commit_Descriptors_to_database(self, database):
        if(self.Id != None):
            database.save_recipe_descriptors(self.Id, self.Descriptors_Value)
        else: 
            print("errror in music.save_into_database")


class Ingredient:

    def __init__(self):
        self.Id = 0
        self.Name=""
        self.Base_name=""
        self.type=""
        self.Birth_region=""
        self.Birth_date = 0 
    

