#!/usr/bin/python3
# coding: utf-8
import cgi 
import cgitb
from Web_template import *
import csv 
from datetime import datetime

corelation_path= r'./Database/Correlations.csv'

cgitb.enable()
print("Content-type: text/html; charset=utf-8\n")

form = cgi.FieldStorage()


if form.getvalue('GET_Results')!=None:
    index= int(form.getvalue('GET_Results'))
    if form.getvalue('Music_url')!=None:
        Music_url= str(form.getvalue('Music_url'))
        if form.getvalue('Cocktail_id')!=None:
            cocktail_id_t = form.getvalue('Cocktail_id')
            if type(cocktail_id_t)==type([]):
                Cocktail_id = str(cocktail_id_t[index])
            else : 
                Cocktail_id = str(cocktail_id_t)
            print([Cocktail_id,Music_url])
            print(Result_page(Music_url,Cocktail_id))
            with open(corelation_path, 'a') as f:
                now = datetime.now()
                dt_string = now.strftime("%d/%m/%Y-%H:%M:%S")
                writer = csv.writer(f)
                writer.writerow([Cocktail_id,Music_url,dt_string])
        else: 
            print('error finding cocktail id ')
    else: 
        print("error finding music url")

elif form.getvalue('GET_Cocktail_list')!=None :
    if form.getvalue('Music_url')!=None:
        Music_url= str(form.getvalue('Music_url'))
        print(Cocktails_list_page(Music_url))
    else : 
        print("error finding music url")

elif form.getvalue('GET_Reverse_Search'): 
    print(Reverse_page())

else : 
    print(Welcome_page())
    
    #verifier url type youtube
    

