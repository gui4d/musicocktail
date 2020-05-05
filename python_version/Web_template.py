#!/usr/bin/python3
from DataBase import *
from Music import *
from Cocktail import *
import random  as rd

template_site_begin="""
<!DOCTYPE html>
<html>
<title>Musicockatail</title>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="stylesheet" href="https://www.w3schools.com/w3css/4/w3.css">
<link rel="stylesheet" href="https://fonts.googleapis.com/css?family=Montserrat">
<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">
<style>
body, h1,h2,h3,h4,h5,h6 {
	font-family: "Montserrat", sans-serif
	}
.w3-row-padding img {
	margin-bottom: 12px
	}
/* Set the width of the sidebar to 120px */
.w3-sidebar {
	width: 120px;background: #222;
	}
/* Add a left margin to the "page content" that matches the width of the sidebar (120px) */
#main {
	margin-left: 120px
	}
/* Remove margins from "page content" on small screens */
@media only screen and (max-width: 600px) {#main {margin-left: 0}}
</style>
<body class="w3-black">

<!-- Icon Bar (Sidebar - hidden on small screens) -->
<nav class="w3-sidebar w3-bar-block w3-small w3-hide-small w3-center">
  <a href="#" class="w3-bar-item w3-button w3-padding-large w3-black">
    <i class="fa fa-home w3-xxlarge"></i>
    <p>HOME</p>
  </a>
  <a href="#search" class="w3-bar-item w3-button w3-padding-large w3-hover-black">
    <i class="fa fa-search w3-xxlarge"></i>
    <p>COCKTAILS</p>
  </a>
</nav>

<!-- Navbar on small screens (Hidden on medium and large screens) -->
<div class="w3-top w3-hide-large w3-hide-medium" id="myNavbar">
  <div class="w3-bar w3-black w3-opacity w3-hover-opacity-off w3-center w3-small">
    <a href="#" class="w3-bar-item w3-button" style="width:25% !important">HOME</a>
    <a href="#search" class="w3-bar-item w3-button" style="width:25% !important">COCKTAILS</a>
  </div>
</div>
<!-- Page Content -->
<div class="w3-padding-large" id="main">
  <!-- Header/Home -->
  <header class="w3-container w3-padding-32 w3-center w3-black" id="home">
    <h1 class="w3-jumbo">HELP THE MUSICOCKTAIL</h1>
  </header>

"""
template_site_about= """
  <!-- About Section -->
  <div class="w3-content w3-justify w3-text-grey w3-padding-64" id="about">
    <h2 class="w3-text-light-grey">le Musicockatail c'est </h2>
    <hr style="width:200px" class="w3-opacity">
    <p> un barman automate, capable de choisir la boisson qui te ferais plaisir. Donne lui ta musique du moment et il te trouvera ce que tu as besoin... <br\>
	 Mais pour l'instant il est un peu rouill&eacute , il a besoin de ton aide. Indique lui quel est le meilleur choix parmis la selection qu'il te propose. Avec de l'entrainement, il devrait s'am&eacuteliorer. 
	</p>
    <h3 class="w3-padding-16 w3-text-light-grey">Quelques chiffres</h3>
 
    <p class="w3-wide">Musiques &eacutecout&eacutees</p>
    <div class="w3-white">
      <div class="w3-dark-grey" style="height:28px;width:85%">0</div>
    </div>
    <p class="w3-wide">Cocktails en reserve</p>
    <div class="w3-white">
      <div class="w3-dark-grey" style="height:28px;width:85%">400</div>
    </div><br>
	<!-- End About Section -->
  </div>
"""

template_site_end= """
<!-- Footer -->
  <footer class="w3-content w3-padding-64 w3-text-grey w3-xlarge">
    <p class="w3-medium">Powered by <a href="https://www.w3schools.com/w3css/default.asp" target="_blank" class="w3-hover-text-green">w3.css</a></p>
  <!-- End footer -->
  </footer>

<!-- END PAGE CONTENT -->
</div>
</body>
</html>

"""
#change action page 
template_Music_selection= """
  <!-- Music Selection-->
  <div class="w3-padding-64 w3-content w3-text-grey" id="search">
    <h2 class="w3-text-light-grey">Le comptoir</h2>
    <hr style="width:200px" class="w3-opacity">

    <p>Choisis ta musique du moment</p>

    <form action="/Web_index.py" target="formDestination">
      <p><input class="w3-input w3-padding-16" type="url" placeholder="lien url" required name="url"></p>
      <p>
        <button class="w3-button w3-light-grey w3-padding-large" type="submit">
          <i class="fa fa-music"></i> ASK FOR COCKTAIL
        </button>
      </p>
    </form>
  <!-- End Music Selection -->
  </div>
"""

template_cocktail_begin=""" 
    <div class="w3-half w3-margin-bottom " >
		<div style =" background-image: url('{Picture_link}'); background-size: cover; background-repeat: no-repeat;">
            <ul class="w3-ul w3-white w3-center w3-opacity w3-hover-opacity-off" >
            <li class="w3-dark-grey w3-xlarge w3-padding-32">{Name}</li>"""
        
template_cocktail_ingredients = """
            <li class="w3-padding-16">{ingredient}</li>"""

template_cocktail_end = """
            <li class="w3-light-grey w3-padding-24">
                <button class="w3-button w3-white w3-padding-large w3-hover-black"  value="{id}" name="Cocktail" type="Cocktail">Choisir</button>
            </li>
            </ul>
		</div>
    </div> """

template_choosen_cocktail = """
    <div class="w3-content w3-margin-bottom  w3-opacity w3-hover-opacity-off " >
      <h3 class="w3-padding-16 w3-text-light-grey" > Merci pour votre choix </h3>
		  <div style =" background-image: url('{Picture_link}');  background-color: black ; background-size: cover; background-repeat: no-repeat; >
        <p class="w3-xlarge w3-padding-32"></p>
        <p class="w3-dark-grey  w3-xlarge w3-padding-16 w3-center">{Name}</p>
        <p class="w3-xlarge w3-padding-32"></p>
        <p class="w3-xlarge w3-padding-32"></p>
        <p class="w3-xlarge w3-padding-32"></p>
        <p class="w3-xlarge w3-padding-32"></p>
		  </div>
    </div> 
"""
template_choosen_Music = """
<div class="w3-content w3-margin-bottom " >
  <iframe width="560" height="315" src="{url}" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>
</div>
"""
template_new_choice = """
    <div class="w3-container w3-padding-32 w3-center w3-black " >
       <h1 class="w3-jumbo">New choice </h1>
    </div> 
"""
def template_cocktails_board(url):
  Cocktails = Select_Cocktail_randomly() #_blank
  html ="""
    <form action="/Web_index.py" target="formDestination">
      <h3 class="w3-padding-16 w3-text-light-grey" > La Carte</h3>
      <div class="w3-row-padding" style="margin:0 -16px"> """
  for  i in range(len(Cocktails)):
    html += template_cocktail_begin.format(Picture_link=Cocktails[i].Picture_link,Name= Cocktails[i].Name)
    for j in range(Cocktails[i].Number_ingredients):
      html += template_cocktail_ingredients.format(ingredient=Cocktails[i].Ingredients[j][0])
    infos=','.join([str(Cocktails[i].Id),url])
    html += template_cocktail_end.format(id=infos)
  html += """</div> </form>"""
  return html 

def Select_Cocktail_randomly(): 
  data = DataBase( DataPath= r"./Database/Database.db")
  if (data.open()):
    Cocktails= []
    ids = []
    Number_Cocktails =data.number_recipes() 
    if Number_Cocktails == 0: 
      return[]
    for i in range(6):
      ids.append(rd.randint(1,Number_Cocktails))
      Cocktails.append(data.recipes(ids[-1])[0])
    data.close()
    return Cocktails
  else : 
    return []

def  template_result(infos):
  data = DataBase( DataPath= r"./Database/Database.db")
  html = ""
  if (data.open()):
    Cocktails= data.recipes(int(infos[0]))
    if len(Cocktails)== 0: 
      print("error cocktail",infos[0] )
      return html
    else:
      html += template_choosen_cocktail.format(Picture_link=Cocktails[0].Picture_link,Name= Cocktails[0].Name)
      #html += template_choosen_Music.format(url= infos[1])
      return html
  else : 
    print("dataopen error ")
    return html


def Welcome_page():
  html = template_site_begin + template_site_about + template_Music_selection + template_site_end
  return html 

def Cocktails_page(url):
  html = template_site_begin + template_cocktails_board(url) + template_site_end
  print(url)
  return html

def saved_page(infos):
  html = template_site_begin  + template_result(infos)+ template_new_choice +  template_Music_selection + template_site_end
  return html

