import PySimpleGUI as sg
from Music import *
from Cocktail import *
from IA import *



class  Gui():

    def review_Music(self,Musics):
        return

    def Modify_Music(self,Music): 
        layout = [
        [sg.Button('Submit'), sg.Button('Next'), sg.Button('Previous'), sg.Button('Stop')],
        [sg.Text('Title', size=(15, 1)), sg.InputText(default_text=Music.Title)],
        [sg.Text('Album', size=(15, 1)), sg.InputText(default_text=Music.Album)],
        [sg.Text('Comentary', size=(15, 1)), sg.InputText(default_text=Music.Comentary)],
        [sg.Text('Author', size=(15, 1)), sg.InputText(default_text=Music.Author)],
        [sg.Text('Year', size=(15, 1)), sg.InputText(default_text=Music.Year)],
        [sg.Text('File_path', size=(15, 1)), sg.InputText(default_text=Music.File_path)],
        [sg.Text('Genre', size=(15, 1)), sg.InputText(default_text=Music.Genre)],
        ]
                 
        # Very basic window.  Return values using auto numbered key
        window = sg.Window('Modify Music', layout)
        event, values = window.read()
        window.close()
        if event == 'Submit':
            Music.Title = values[0]
            Music.Album= values[1]
            Music.Comentary= values[2]
            Music.Author= values[3]
            Music.Year= values[4]
            Music.File_path= values[5]
            Music.Genre= values[6]
            # the input data looks like a simple list when auto numbered
        return event

    def Modify_Cocktail(self,Cocktail):
        background = '#F0F0F0'
        layout = [
        [sg.Text('Name', size=(15, 1)), sg.InputText(default_text=Cocktail.Name)],
        [sg.Text('Source_name', size=(15, 1)), sg.InputText(default_text=Cocktail.Source_name)],
        [sg.Text('Picture_link', size=(15, 1)), sg.InputText(default_text=Cocktail.Picture_link)],
        [sg.Text('Glass', size=(15, 1)), sg.InputText(default_text=Cocktail.Glass)],
        [sg.Text('Instructions', size=(15, 1)), sg.InputText(default_text=Cocktail.Instructions)],
        ]
        number_ingredient = len(Cocktail.Ingredients_names) 

        for i in range(number_ingredient):
            layout.append([sg.InputText(default_text=Cocktail.Ingredients_names[i]), sg.InputText(default_text=Cocktail.Ingredients_measures[i])])
        for i in range(Cocktail.Descriptors_list_size):
            layout.append([sg.Text(Cocktail.Descriptors_Name[i], size=(15, 1)), sg.InputText(default_text=Cocktail.Descriptors_Value[i])])
        container =[[sg.Button('Submit'), sg.Button('Next'), sg.Button('Previous'), sg.Button('Stop')],
                    [sg.Column(layout, scrollable=True)],
                ]
        window = sg.Window('Modify Cocktail', container)
        event, values = window.read()
        window.close()
        if event == 'Submit':
            Cocktail.Name=values[0]
            Cocktail.Source_name=values[1]
            Cocktail.Picture_link=values[2]
            Cocktail.Glass=values[3]
            Cocktail.Instructions = values[4]
            for i in range(number_ingredient):
                Cocktail.Ingredients_names[i] = values[i + 5][0]
                Cocktail.Ingredients_measures=[i] = values[i + 5][1]
            for i in range(Cocktail.Descriptors_list_size): 
                Cocktail.Descriptors_Value[i] = float(values[number_ingredient + 5 + i])
        return event
    

