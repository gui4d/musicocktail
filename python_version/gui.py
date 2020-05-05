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
        [sg.Text('Title', size=(25, 1)), sg.InputText(default_text=Music.Title)],
        [sg.Text('Album', size=(25, 1)), sg.InputText(default_text=Music.Album)],
        [sg.Text('Comentary', size=(25, 1)), sg.InputText(default_text=Music.Comentary)],
        [sg.Text('Author', size=(25, 1)), sg.InputText(default_text=Music.Author)],
        [sg.Text('Year', size=(25, 1)), sg.InputText(default_text=Music.Year)],
        [sg.Text('File_path', size=(25, 1)), sg.InputText(default_text=Music.File_path)],
        [sg.Text('Genre', size=(25, 1)), sg.InputText(default_text=Music.Genre)],
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
        [sg.Text('Name', size=(25, 1)), sg.InputText(default_text=Cocktail.Name)],
        [sg.Text('Source_name', size=(25, 1)), sg.InputText(default_text=Cocktail.Source_name)],
        [sg.Text('Picture_link', size=(25, 1)), sg.InputText(default_text=Cocktail.Picture_link)],
        [sg.Text('Glass', size=(25, 1)), sg.InputText(default_text=Cocktail.Glass)],
        [sg.Text('Instructions', size=(25, 1)), sg.InputText(default_text=Cocktail.Instructions)],
        ]
        for i in range(Cocktail.Number_ingredients):
            layout.append([sg.Text(Cocktail.Ingredients[i][0], size=(25, 1)), sg.InputText(default_text=Cocktail.Ingredients[i][2])])
        for i in range(Cocktail.Descriptors_list_size):
            layout.append([sg.Text(Cocktail.Descriptors_Name[i], size=(25, 1)), sg.InputText(default_text=Cocktail.Descriptors_Value[i])])
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
            for i in range(Cocktail.Number_ingredients):
                Cocktail.Ingredients[i][2] = values[i + 5]
            for i in range(Cocktail.Descriptors_list_size): 
                Cocktail.Descriptors_Value[i] = float(values[Cocktail.Number_ingredients + 5 + i])
        return event
    

