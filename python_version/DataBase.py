import sqlite3 as sq
from sqlite3 import Error
from Music import *
from Cocktail import *
from IA import *

### faire les link entre tables 
###update les recurences d'ingredients et de recettes 
### update les fundaments ou suprimmer. => creer d'autres arborescences

default_data_path = r"./Musicocktail.db"

class DataBase():

    ####class management

    def __init__(self, DataPath= default_data_path , music_table="musics", recipe_table="recipes", ingredient_table="ingredients", IA_table="ia", tower_table="tower" , training_table = "training") :
        self.DataPath = DataPath
        self.connection = None
        self.current_music_table = music_table
        self.current_recipe_table = recipe_table
        self.current_ingredient_table = ingredient_table
        self.current_IA_table = IA_table
        self.current_tower_table = tower_table
        self.current_training_table = training_table

    def open(self):
        try:
            self.connection = sq.connect(self.DataPath)
        except Error as e:
            print("in Database.open :")
            print(e)
            return False
        return True

    def close(self, commit=True):
        if self.connection is not None:
            if commit:
                self.commit()
            self.connection.close()

    def show_all(self):
        #make a preatier print : remove nan , add \n 
        print("musics##########")
        print(self.__all_musics_rows())
        print("recipes##########")
        print(self.__all_recipes_rows())
        print("ingredients##########")
        print(self.__all_ingredients_rows())

    #### tables creation
    def create_tables(self):
        self.__create_music_table()
        self.__create_recipe_table()
        self.__create_ingredient_table()
        self.__create_training_table()
        self.__create_tower_table()

    def __create_music_table(self):
        command = """CREATE TABLE IF NOT EXISTS """ + self.current_music_table + """(
                                        id INTEGER PRIMARY KEY,
                                        title TEXT NOT NULL,
                                        album TEXT,
                                        commentary TEXT,
                                        author TEXT NOT NULL,
                                        year TEXT NOT NULL,
                                        file_path TEXT,
                                        genre TEXT,"""
        for extractor in music_extractors:
            command += extractor + " REAL, "
        command += " UNIQUE(title,author,year));"
        self.__execute(command)

    def __create_recipe_table(self):
        command = """CREATE TABLE IF NOT EXISTS """ + self.current_recipe_table + """(
                    id INTEGER PRIMARY KEY,
                    name TEXT NOT NULL,
                    source_id INTEGER,
                    picture_link TEXT,
                    Glass TEXT NOT NULL,
                    ingredient1_id INTEGER,
                    ingredient2_id INTEGER,
                    ingredient3_id INTEGER,
                    ingredient4_id INTEGER,
                    ingredient5_id INTEGER,
                    ingredient6_id INTEGER,
                    ingredient7_id INTEGER,
                    ingredient8_id INTEGER,
                    ingredient9_id INTEGER,
                    ingredient10_id INTEGER,
                    ingredient11_id INTEGER,
                    ingredient12_id INTEGER,
                    ingredient13_id INTEGER,
                    ingredient14_id INTEGER,
                    ingredient15_id INTEGER,
                    measure1 REAL,
                    measure2 REAL,
                    measure3 REAL,
                    measure4 REAL,
                    measure5 REAL,
                    measure6 REAL,
                    measure7 REAL,
                    measure8 REAL,
                    measure9 REAL,
                    measure10 REAL,
                    measure11 REAL,
                    measure12 REAL,
                    measure13 REAL,
                    measure14 REAL,
                    measure15 REAL,"""
        for extractor in cocktail_descriptors:
            command += extractor + " REAL, "
        command += " UNIQUE(name, Glass ));"
        self.__execute(command)

    def __create_ingredient_table(self):
        command = """CREATE TABLE IF NOT EXISTS """ + self.current_ingredient_table + """(
                    id INTEGER PRIMARY KEY,
                    name TEXT NOT NULL,
                    source_id INTEGER,
                    type TEXT ,
                    birth_region TEXT,
                    birth_date INTEGER, 
                    UNIQUE(name)
                    ); """
        self.__execute(command)

    def __create_training_table(self):
        command = """CREATE TABLE IF NOT EXISTS """ + self.current_training_table + """(
                                        id INTEGER PRIMARY KEY,
                                        Cocktail_id INTEGER ,
                                        music_id INTEGER,
                                        weight REAL,
                                        Commentary TEXT,
                                        author TEXT, 
                                        UNIQUE(Cocktail_id, Music_id, Weight)
                                        ); """

        self.__execute(command)

    def __create_tower_table(self):
        command = """CREATE TABLE IF NOT EXISTS """ + self.current_tower_table + """(
                    id INTEGER PRIMARY KEY,
                    motor_id INTEGER,
                    ingredient_id INTEGER,
                    flow_rate REAL,
                    UNIQUE(motor_id)); """
        self.__execute(command)

    ### insctructions management
    def commit(self):
        number_change = self.connection.total_changes
        self.connection.commit()
        print("INFO :you have commited " + str(number_change) + " change(s)")

    def rollback(self):
        number_change = self.connection.total_changes()
        self.connection.rollback()
        print("INFO: you have canceled " + str(number_change) + " change(s)")

    def __execute(self, command):
        print("SQL: " + command.strip())
        if self.connection is None:
            return None
        else:
            try:
                cursor = self.connection.cursor()
                cursor.execute(command)
                return cursor
            except Error as e:
                print(e)
                return None

    def __execute_with_values( self, command, values ):
        print("SQL :" + command.strip() + str(values) )
        if self.connection is None:
            return None
        else:
            try:
                cursor = self.connection.cursor() 
                cursor.execute(command, tuple(values))
                return cursor
            except Error as e:
                print(e)
                return None

    ###  music management
    def save_music_data(self, music):
        if music.Id != 0 :# update the music 
            command = """ UPDATE """ + self.current_music_table + """ SET title = ? , album = ? , commentary = ? ,author = ? ,year = ? ,file_path = ?, genre = ?  WHERE id = ?"""
            values = (music.Title, music.Album, music.Commentary , music.Author, music.Year, music.File_path, music.Genre , music.Id)      
        else : # create new music 
            command = """INSERT INTO """ + self.current_music_table +  """(title , album ,commentary ,author ,year ,file_path ,genre) VALUES(?,?,?,?,?,?,?)"""
            values = (music.Title, music.Album, music.Commentary , music.Author, music.Year, music.File_path, music.Genre) 
        cur = self.__execute_with_values(command, values)
        if cur is None :
            return 0
        else:
            music.Id = cur.lastrowid
            return cur.lastrowid

    def save_music_extractors(self,music):
        if music.Id == 0 : 
            print( "save music before saving extractors")
            return False
        values = tuple(list(music.Extractors_Value).append(music.Id))
        command = """ UPDATE """ + self.current_music_table + """ SET """
        for extractor in music_extractors:
            command += extractor + "  = ? , "
        command.pop(len(command)-2)
        command += """ WHERE id = ? """
        cur = self.__execute_with_values(command,values)
        if cur is None : 
            return False
        else:
            return True

    def number_musics(self):
        command = " SELECT COUNT(*) FROM " + self.current_music_table
        cur = self.__execute(command)
        if cur is not None: 
            return int(cur.fetchall()[0][0])
        return 0 
    
    def music(self, *args):
        command = ""
        if len(args) != 0:
            for arg in args:
                if type(arg) == int:
                    command += " SELECT * FROM " + \
                        self.current_music_table + " WHERE id = " + str(arg)
                elif type(arg) == str:
                    command += " SELECT * FROM " + self.current_music_table + " WHERE title = " + arg
                else:
                    print("variable error :" + str(arg))
                command += " UNION ALL"
            command = command[:-9]
        else:
            command = " SELECT * FROM " + self.current_music_table
        cur = self.__execute(command)
        if cur is None :
            return None
        else :
            Musics=[]
            rows = cur.fetchall()
            for row in rows : 
                Musics.append(__row_to_music(row))
            return Musics
    
    def __row_to_music(self,row):
            music = Music()
            music.Id = int(row["id"])
            music.Title = str(row["title"])
            music.Album= str(row["album"])
            music.Comentary = str(row["commentary"])
            music.Author = str(row["author"])
            music.Year = int (row["year"])
            music.File_path = str (row["file_path"])
            music.Genre = str(row["genre"])
            for i in range(len(music_extractors)):
                music.Extractors_Value[i] = float( row[music_extractors[i]])
            return music

    def __all_musics_rows(self):
        command = "SELECT * FROM " + self.current_music_table
        cur = self.__execute(command)
        if cur is None :
            return []
        else :
            return  cur.fetchall()

    ## recipe management
    def save_recipe_data(self,recipe):
        if recipe.Source_name !="":
            source_recipe_id = self.id_of_recipe(recipe.Source_name)
        else : 
            source_recipe_id = 0
        ingredient_ids = [ self.id_of_ingredient(ingredient) for ingredient in recipe.Ingredients_names]
        number_ingredient = len(ingredient_ids)
        if  0 in ingredient_ids: 
            print( "WARNING : Missing ingredient in DataBase :" + recipe.Ingredients_names[ingredient_ids.index(0)])
            return 0

        if recipe.Id != 0 :
            values = tuple([recipe.Name, source_recipe_id , recipe.Picture_link, recipe.Glass] + ingredient_ids + recipe.Ingredients_measure+ [recipe.Id])
            command = """ UPDATE """ + self.current_recipe_table + """ SET name = ? , source_id = ? ,picture_link = ? ,glass = ? """
            for i in range(number_ingredient):
                command += ", ingredient" + str(i+1) + "_id  = ? "
            for i in range(number_ingredient):
                command += ", measure" + str(i+1) + " = ?"
            command +=""" WHERE id = ?"""      
        else :         
            values = tuple([recipe.Name, source_recipe_id , recipe.Picture_link, recipe.Glass] + ingredient_ids + recipe.Ingredients_measures )
            command = """INSERT INTO """ + self.current_recipe_table +   """(name , source_id ,picture_link ,glass """
            for i in range(number_ingredient):
                command += ", ingredient" + str(i+1) + "_id  "
            for i in range(number_ingredient):
                command += ", measure" + str(i+1)
            command += ")  VALUES(?,?,?,?"
            for i in range(number_ingredient*2):
                command += ",?"
            command += " )"
        
        cur = self.__execute_with_values(command, values)
        if cur is None : 
            return 0 
        else: 
            return cur.lastrowid

    def save_recipe_descriptors(self, recipe):
        if recipe.Id == 0 : 
            print( "save recipe before saving descriptors")
            return False
        values =  tuple(list(recipe.Descriptors_Value).append(reipe.Id)) 
        command = """ UPDATE """ + self.current_recipe_table + """" SET """
        for descriptors in cocktail_descriptors:
            command += descriptors + "  = ? , "
        command = command[:-2]
        command += """ WHERE id = """ + str(recipe.Id)
        cur  = self.__execute_with_values(command, values)
        if cur is None : 
            return False
        else: 
            return True

    def number_recipes(self):
        command = " SELECT COUNT(*) FROM " + self.current_recipe_table
        cur = self.__execute(command)
        if cur is not None: 
            return int(cur.fetchall()[0][0])
        return 0  
        
    def recipe(self, *args):
        command = ""
        if len(args) != 0:
            for arg in args:
                if type(arg) == int:
                    command += " SELECT * FROM " + \
                        self.current_recipe_table + " WHERE id = " + str(arg)
                elif type(arg) == str:
                    command += " SELECT * FROM " + self.current_recipe_table + " WHERE name = " + arg
                else:
                    print("variable error :" + str(arg))
                command += " UNION ALL"
            command = command[:-9]
        else:
            command = " SELECT * FROM " + self.current_recipe_table
        cur = self.__execute(command)
        if cur is None :
            return []
        else :
            return  cur.fetchall()
        #make it return recipe

    def id_of_recipe(self, name):
        cur = self.recipe(name)
        if cur is None or cur==[]: 
             return 0 
        else: 
            return cur[0][0]

    def __all_recipes_rows(self):
        command = "SELECT *  FROM " + self.current_recipe_table
        cur = self.__execute(command)
        if cur is None :
            return []
        else :
            return  cur.fetchall()

    ## ingredient management
    def number_ingredients(self):
        command = " SELECT COUNT(*) FROM " + self.current_ingredient_table
        cur = self.__execute(command)
        if cur is not None: 
            return int(cur.fetchall()[0][0])
        return 0    

    def save_ingredient(self, ingredient):
        #if ingredient.Base_name !="":
        #    Source_id = self.id_of_ingredient(ingredient.Base_name)
        Source_id = 0
        if ingredient.Id != 0 : 
            values = (ingredient.Name, Source_id, ingredient.Type, ingredient.Birth_region, ingredient.Birth_date, ingredient.Id)
            command = """ UPDATE """ + self.current_ingredient_table + """ SET name = ? , source_id = ?,type = ? , birth_region = ?, birth_date = ? WHERE id = ?"""
        else : 
            values = (ingredient.Name, Source_id, ingredient.Type, ingredient.Birth_region, ingredient.Birth_date)
            command = """INSERT INTO """ + self.current_ingredient_table +  """(name , source_id ,type , birth_region , birth_date)  VALUES(?,?,?,?,?)"""

        cur = self.__execute_with_values(command,values)
        if cur is None : 
            return 0
        else : 
            return cur.lastrowid

    # make return  ingredient
    def ingredient(self, *args):
        command = ""
        if len(args) != 0:
            for arg in args:
                if type(arg) == int:
                    command += " SELECT * FROM " + \
                        self.current_ingredient_table + \
                        " WHERE id = " + str(arg) 
                elif type(arg) == str:
                    command += " SELECT * FROM " + self.current_ingredient_table + \
                        " WHERE name = '" + arg + "'"
                else:
                    print("variable error :" + str(arg))
                command += " UNION ALL"
            command = command[:-9]
        else:
            command = " SELECT * FROM " + self.current_ingredient_table
        cur = self.__execute(command)
        if cur is None :
            return []
        else :
            return  cur.fetchall()
    
    def id_of_ingredient(self,name):
        cur = self.ingredient(name)
        if cur is None or cur==[]: 
             return 0 
        else: 
            return cur[0][0]

    def __all_ingredients_rows(self):
        command = "SELECT * FROM " + self.current_ingredient_table
        cur = self.__execute(command)
        if cur is None :
            return []
        else :
            return  cur.fetchall()

    ## IA management    
    def create_new_relation(self, music_id, cocktail_id, commentary="", author=""):
        values = (cocktail_id, music_id, commentary, author)
        command = """INSERT INTO """ + self.current_training_table + \
            """(cocktail_id, music_id ,commentary ,author)  VALUES(?,?,?,?)"""
        cur = self.__execute_with_values(command, values)
        if cur is None : 
            return 0 
        else : 
            return cur.lastrowid
   


       # def create_new_tower_emplacement(self):

    # def load_IA(self):

