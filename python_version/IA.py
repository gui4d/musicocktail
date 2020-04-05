import numpy as np
import matplotlib.pyplot as plt
import math
import matplotlib.pyplot as plt
import matplotlib.cm as cm
from datetime import date
from Music import *
from Cocktail import *
import random

# create function equivalent_cocktail , return a cocktail 
class IA(): 

    def __init__(self):

        __music__=Music()
        __cocktail__ = Cocktail()
        #Descriptors
        self.Music_Extractors_name=__music__.Extractors_Name
        self.Music_Extractors_list_size= __music__.Extractor_list_size

        self.Cocktail_Descriptors_name= __cocktail__.Descriptors_Name
        self.Cocktail_Descriptor_list_size = __cocktail__.Descriptors_list_size

        #Correlation matrix
        self.Matrix=np.zeros( (self.Cocktail_Descriptor_list_size,self.Music_Extractors_list_size) );
        self.Learning_factor=0.01

        #Graphic interface
        self.current_music = 0
        self.current_cocktail = 0 

    #Matrix Graphic management
    def Print_position(self):
        print(self.Music_Extractors_name[self.current_music],";",self.Cocktail_Descriptors_name[self.current_cocktail],";",self.Matrix[self.current_cocktail][self.current_music] )

    def Event_click(self,event):
        if event.inaxes==None: return
        self.current_music = int(event.xdata)
        self.current_cocktail = int(event.ydata)
        self.Print_position()
        
    def Event_key(self,event):
        #enter new value
        if(str.isdigit(event.key)):
            self.Matrix[self.current_cocktail][self.current_music]=float(event.key) - 4
            self.Print_position()
        #displace from postion
        elif(event.key == "up"):
            if(self.current_cocktail>0):
                self.current_cocktail-=1
            self.Print_position()
        elif(event.key == "down"):
            if(self.current_cocktail<self.Cocktail_Descriptor_list_size-1):
                self.current_cocktail+=1
            self.Print_position()
        elif(event.key == "right"):
            if(self.current_music < self.Music_Extractors_list_size-1):
                self.current_music+=1
            self.Print_position()
        elif(event.key == "left"):
            if(self.current_music>0):
                self.current_music-=1
            self.Print_position()
        #special comand
        elif(event.key=="P"):
                plt.close()
                self.show_Matrix()
        elif(event.key=="N"):
                self.Normalise()
        elif(event.key=="R"):
                self.Randomize()

    def show_Matrix(self):
        fig, ax = plt.subplots()
        im = ax.imshow(self.Matrix)
        # We want to show all ticks...
        ax.set_xticks(np.arange(self.Music_Extractors_list_size))
        ax.set_yticks(np.arange(self.Cocktail_Descriptor_list_size))
        # ... and label them with the respective list entries
        ax.set_xticklabels(["" for item in self.Music_Extractors_name])
        ax.set_yticklabels(["" for item in self.Cocktail_Descriptors_name])
        #event gestion
        fig.canvas.mpl_connect('button_press_event', self.Event_click)
        fig.canvas.mpl_connect('key_press_event', self.Event_key)
        plt.text(0,0,"4 : no correlation ,\n 0 : negative corelation ,\n 9 : positive corelation ,\n")
        
        plt.show()


    #matrix core management

    def Add_Relation(self,music_descriptor_index,Cocktail_descriptor_index, weight):
        self.Matrix[Cocktail_descriptor_index][music_descriptor_index] += weight
    
    def Remove_Relation(self,music_descriptor_index,Cocktail_descriptor_index):
        self.Matrix[Cocktail_descriptor_index][music_descriptor_index] = 0
        
    def Normalise(self):
        for j in range(self.Cocktail_Descriptor_list_size) :
            norm = 0
            for i in self.Matrix[j] :
                norm += i*i
            norm = math.sqrt(norm)
            if norm != 0 :
                for i in range(self.Music_Extractors_list_size):
                    self.Matrix[j][i]/=norm
            else :
                print("WARN: descriptor '",Cocktail.Descriptors[j][0], "' is not taken into consideration")

    def Randomize(self):
        for i in range(self.Music_Extractors_list_size):
            for j in range(self.Cocktail_Descriptor_list_size):
                self.Matrix[j][i]= float(random.randint(0,100))/100.


    #Data management

    def save_matrix_at(self, output_location):
        np.save(output_location,self.Matrix)

    def load_matrix_at(self,output_location):
        #to be secured
        self.Matrix= np.load(output_location)

    # IA Core functions

    def Equivalent_Cocktail_array(self, Music):
        Music_Values_array= np.array(Music.Extractors_Value).transpose()
        equivalent_Cocktail_Values = np.dot(self.Matrix,Music_Values_array);
        return equivalent_Cocktail_Values

    # should return cocktail 

    def Distance(self, Music, Cocktail):
        Cocktail_Values = Cocktail.Descriptors_Value
        equivalent_Cocktail_Values = self.Equivalent_Cocktail_array(Music)
        distance= 0 
        for i in range(self.Cocktail_Descriptor_list_size):
            distance += (equivalent_Cocktail_Values[i]-Cocktail_Values[i])**2
        return math.sqrt(distance)

    def Apprentissage( self, Music_, Cocktail_): 
        #initialisation
        Equivalent_Cocktail_array = self.Equivalent_Cocktail_array(Music_)
        Error_array = [ ( Equivalent_Cocktail_array[j] - Cocktail_.Descriptors_Value[j]) for j in range(self.Cocktail_Descriptor_list_size) ]
        Error_norm2 = 0
        #error calculus
        for j in range( self.Cocktail_Descriptor_list_size): 
            Error_norm2 += Error_array[j]**2
        Error_norm2 = math.sqrt(Error_norm2)
        #learning 
        for i in range(self.Music_Extractors_list_size):
            for j in range(self.Cocktail_Descriptor_list_size):
                self.Matrix[j][i] -= self.Learning_factor*Error_array[j]*Music_.Extractors_Value[i]
        #prints
        print("Error :")
        print(Error_norm2)
        

   