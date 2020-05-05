import numpy as np
import math
import matplotlib.cm as cm
from datetime import date
import random

cocktail_data = ['name',
        'source_name',
        'picture_link',
        'Glass',
        'Instructions',
        'ingredient1',
        'ingredient2',
        'ingredient3',
        'ingredient4',
        'ingredient5',
        'ingredient6',
        'ingredient7',
        'ingredient8',
        'ingredient9',
        'ingredient10',
        'ingredient11',
        'ingredient12',
        'ingredient13',
        'ingredient14',
        'ingredient15',
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

       'Preparation_On_the_Rocks' ,
       'Preparation_Up_Cocktails',
       'Preparation_Neat_Cocktails' ,
       'Preparation_Shaken' ,
       'Preparation_Built_in_Glass' ,
       'Preparation_Poured' ,
       'Preparation_Stirred' ,
       'Preparation_Heated' ,
       'Preparation_Frozen_Blended' ,

        'Occasion_Soiree',
        'Occasion_Party',
        'Occasion_night',
        'Occasion_moring',
        'Occasion_celebration',
        'Occasion_Romantic',
        'Occasion_Terrace',
        'Occasion_BBQ',
        'Occasion_vacation',
        'Occasion_Picnic',
        'Occasion_Diner',
        'Occasion_Aperetif_Digestifs',
        'Occasion_Intelectual_time',
        'Occasion_Hard_Time',
        'Occasion_Reception',
        'Occasion_Winter',
        'Occasion_Spring',
        'Occasion_Summer',
        'Occasion_Autuumn',
        'Occasion_Everyday',
        'Occasion_Detox',
        'Occasion_Special_event',
        'Occasion_Coffe_Dessert',    

       'Flavors_Bitter' ,
       'Flavors_Sweet' ,
       'Flavors_Savory' ,
       'Flavors_Sour' ,
       'Flavors_Spicy' ,
       'Flavors_Fruity' ,
       'Flavors_Smoky' ,
       'Flavors_Herbaceous' ,
       'Flavors_Light',
        'Flavors_Creamy',
        'Flavors_Refreshing',
        'Flavors_dry',
        'Flavor_tonic',
        'Flavor_acid',
        'Flavor_mild',
        'Flavor_flavored',

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
        'Region_North_Africa',
        'Region_South_Africa',
        'Region_South_America',
        'Region_North_America',
        'Region_East_Asia',
        'Region_Center_Asia',
        'Region_South_East_Asia',
        'Region_Caribbean',
        'Region_Eastern_Europe',
        'Region_North_Europe',
        'Region_India',
        'Region_Orient',
        'Region_Mediterranea',
        'Region_island',
        'Region_City',
        'Region_countryside',

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

cocktail_descriptors_title =['Main_Alcool','Genre','Preparation','Occasion','Flavors','Paul_Clarke','Gary_Regan' , 'IBA' ,'Region','City','age']
ingredient_data= ['name','base_name','type','birth_region','birth_date']
 
class Cocktail:

    def __init__(self): 
        self.Id=0 #int
        self.Name="" #str
        self.Source_name="" #str
        self.Source_id= 0 #int
        self.Picture_link="" #str
        self.Glass="" #str
        self.Instructions ="" #str
        self.Ingredients=[["",0,0.] for i in range(15)] #str name / #int id / #flot  measure
        self.Number_ingredients = 0
        self.Descriptors_Name = cocktail_descriptors #str
        self.Descriptors_list_size = len(self.Descriptors_Name); #int
        self.Descriptors_Value = [0. for i in range(self.Descriptors_list_size)]  #float

    #def create_manual(self):

    def show(self):
        print(self.Id,self.Name,self.Source_name,self.Picture_link,self.Glass, self.Instructions,self.Ingredients)
        self.show_Descriptors()
    
    def summary(self):
        print(self.Id,self.Name,self.Source_name,self.Picture_link,self.Glass, self.Instructions,self.Ingredients)
    
    def show_Descriptors(self):       
            for i in range(self.Descriptors_list_size): 
                print(self.Descriptors_Name[i], " : " , self.Descriptors_Value[i])
       
    def Randomize_Descriptors(self):
        for i in range(self.Descriptors_list_size):
            self.Descriptors_Value[i]= float(random.randint(0,100))/100.

    def Load_Descriptors_From_Array(self,Descriptors_Value):
        if (len(Descriptors_Value)==self.Descriptors_list_size) :
            for i in range(self.Descriptors_list_size):
                self.Descriptors_Value[i]= Descriptors_Value[i]
    

class Ingredient:

    def __init__(self):
        self.Id = 0
        self.Name=""
        self.Base_name=""
        self.type=""
        self.Birth_region=""
        self.Birth_date = ""
    
    def show(self):
        print( self.Id , self.Name , self.Base_name ,self.type, self.Birth_region, self.Birth_date )

