# coding: utf-8
import cgi 
import cgitb
from Web_template import *
import csv   

corelation_path= r'./Database/Correlations.csv'

cgitb.enable()
print("Content-type: text/html; charset=utf-8\n")

form = cgi.FieldStorage()

if form.getvalue('Cocktail')!=None:
    infos = form.getvalue('Cocktail').split(',')
    print(infos)
    print(saved_page(infos))
    with open(corelation_path, 'a') as f:
        writer = csv.writer(f)
        writer.writerow(infos)

elif form.getvalue('url')!=None :
    url = str(form.getvalue('url'))
    print(Cocktails_page(url))
else : 
    print(Welcome_page())
    
    #verifier url type youtube
    

