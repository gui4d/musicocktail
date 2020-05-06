#!/usr/bin/python3
from DataBase import *
from Music import *
from Cocktail import *
import random  as rd

#basic templates

template_form_begin=""" <form action="/" target="_self">"""
template_form_end="""</form>"""
template_info= """<input type="hidden" name="{Name}" value="{Value}" />"""

template_site_begin= """
<!-- init -->
<!DOCTYPE html>
<html>
<title>Musicockatail</title>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="stylesheet" href="http://www.w3schools.com/w3css/4/w3.css">
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
  <a href="/#" class="w3-bar-item w3-button w3-padding-large w3-black">
    <i class="fa fa-home w3-xxlarge"></i>
    <p>HOME</p>
  </a>
  <a href="/#search" class="w3-bar-item w3-button w3-padding-large w3-hover-black">
    <i class="fa fa-search w3-xxlarge"></i>
    <p>COCKTAILS</p>
  </a>
</nav>

<!-- Navbar on small screens (Hidden on medium and large screens) -->
<div class="w3-top w3-hide-large w3-hide-medium" id="myNavbar">
  <div class="w3-bar w3-black w3-opacity w3-hover-opacity-off w3-center w3-small">
    <a href="/#" class="w3-bar-item w3-button" style="width:25% !important">HOME</a>
    <a href="/#search" class="w3-bar-item w3-button" style="width:25% !important">COCKTAILS</a>
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
    <p> Un barman automate, capable de choisir la boisson qui te ferait plaisir. Donne lui ta musique du moment et il te trouvera ce dont tu as besoin... <br\>
	 Mais pour l'instant il est un peu rouill&eacute, il a besoin de ton aide. Indique lui quel est le meilleur choix parmis la selection qu'il te propose. Avec de l'entrainement, il devrait s'am&eacuteliorer. 
	</p>
  </div>
"""

template_Introduction_Reverse_Search= template_form_begin +""" <div class="w3-padding-64 w3-content w3-text-grey" id="search">
    <h2 class="w3-text-light-grey">La Surprise du barman</h2>
    <p>Le barman te propose de te r&eacutealiser un Cocktail surprise, en &eacutechange tu lui trouve une musique apropri&eacute </p>
    <button class="w3-button w3-white w3-padding-large w3-hover-black"  value="1" id="GET_Reverse_Search" name="GET_Reverse_Search" type="submit">  <i class="fa fa-glass"></i> Cocktail Surprise</button>
    </div>
""" + template_form_end

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

template_cocktail_list_begin="""
      <h3 class="w3-padding-16 w3-text-light-grey" > La Carte</h3>
      <div class="w3-row-padding" style="margin:0 -16px">
"""
template_cocktail_list_end= """
      </div> 
      <h3 class=" w3-content w3-margin-bottom ">Riens ne te satisfait ? Relance la page !</h3> 
"""

template_cocktail_begin=""" 
    <div class="w3-half w3-margin-bottom " >
		<div style =" background-image: url('{Picture_link}'); background-size: cover; background-repeat: no-repeat;">
            <ul class="w3-ul w3-white w3-center w3-opacity w3-hover-opacity-off" >
            <li class="w3-dark-grey w3-xlarge w3-padding-32">{Name}</li>"""
        
template_cocktail_ingredients = """
            <li class="w3-padding-16">{ingredient}</li>"""

template_cocktail_Select = """
            <li class="w3-light-grey w3-padding-24">
                <button class="w3-button w3-white w3-padding-large w3-hover-black"  value="{Value}" id="GET_Results" name="GET_Results" type="submit">Choisir</button>
            </li>
            """

template_cocktail_end="""</ul>
		                    </div>
                      </div> """

template_cocktail_result = """
    <div class="w3-content w3-margin-bottom  w3-opacity w3-hover-opacity-off " >
      <h3 class="w3-padding-16 w3-text-light-grey" > Merci pour ton aide ! </h3>
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

template_Reverse_Search_begin=""" 
    <div class="w3-content w3-margin-bottom   id="search" " >
    <h2 class="w3-text-light-grey">La Surprise du Barman</h2>"""
template_Reverse_Search_end="""
    </div>
    <div>
    <p class="  w3-padding-64 w3-content w3-margin-bottom w3-text-light-grey">Tu n'aimes pas la surprise ? Relance la page !</p> </div> """

template_Music_Select_begin= """ 
    <div class="w3-padding-64 w3-content w3-text-grey" id="search">
    <h2 class="w3-text-light-grey">Le comptoir</h2>
    <p>Choisis ta musique du moment</p>
"""
template_Music_Search = """
       <p><input class="w3-input w3-padding-16" type="url" placeholder="lien youtube" id="Music_url" required name="Music_url"></p>
      <p>
        <button class="w3-button w3-light-grey w3-padding-large" type="submit" value="1" id="GET_Cocktail_list" name="GET_Cocktail_list">
          <i class="fa fa-music"></i> Choisir cette musique
        </button>
      </p>
"""
template_Music_Reverse_Search = """
       <p><input class="w3-input w3-padding-16" type="url" placeholder="lien youtube" id="Music_url" required name="Music_url"></p>
      <p>
        <button class="w3-button w3-light-grey w3-padding-large" type="submit" value="0" id="GET_Results" name="GET_Results">
          <i class="fa fa-music"></i> Choisir cette musique
        </button>
      </p>
 """
template_Music_Select_end = """ </div>
"""
template_Music_Result = """
<div class="w3-content w3-margin-bottom " >
  <iframe width="560" height="315" src="{url}" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>
</div>
"""

template_Introduce_New_Choice =  """
    <div class="w3-container w3-padding-32 w3-center w3-black " >
      <h2 class="w3-text-light-grey">Nouvel essai  ?</h2>
    </div> 
"""


### constructed template

def template_music_Selection():
  html = ""
  html += template_Music_Select_begin
  html += template_form_begin
  html += template_Music_Search
  html += template_form_end
  html += template_Music_Select_end
  return html
      
def template_cocktails_Selection(url):
  Cocktails = Select_Cocktail_randomly(6) #_blank
  html =""
  html +=template_form_begin
  html += template_cocktail_list_begin
  for  i in range(len(Cocktails)):
    html += template_cocktail_begin.format(Picture_link=Cocktails[i].Picture_link,Name= Cocktails[i].Name)
    for j in range(Cocktails[i].Number_ingredients):
      html += template_cocktail_ingredients.format(ingredient=Cocktails[i].Ingredients[j][0])
    html += template_cocktail_Select.format(Value=str(i))
    html += template_info.format(Value=Cocktails[i].Id, Name="Cocktail_id")
    html += template_cocktail_end
  html += template_cocktail_list_end
  html += template_info.format(Value=url, Name="Music_url")
  html += template_form_end
  return html 

def  template_Reverse_Searh():
      Cocktail = Select_Cocktail_randomly(1)[0]
      html = ""
      html += template_Reverse_Search_begin
      html +=template_form_begin
      html += template_cocktail_begin.format(Picture_link=Cocktail.Picture_link,Name= Cocktail.Name)
      for j in range(Cocktail.Number_ingredients):
        html += template_cocktail_ingredients.format(ingredient=Cocktail.Ingredients[j][0])
      for j in range(Cocktail.Number_ingredients , 8, 1):
        html += template_cocktail_ingredients.format(ingredient="")
      html += template_info.format(Value=Cocktail.Id, Name="Cocktail_id")
      html += template_cocktail_end
      html += template_Music_Reverse_Search
      html += template_form_end
      html += template_Reverse_Search_end
      return html 
  

def template_Result(Cocktail_id, Music_url):
  data = DataBase( DataPath= r"./Database/Database.db")
  html = ""
  if (data.open()):
    Cocktails= data.recipes(int(Cocktail_id))
    if len(Cocktails)== 0: 
      print("error cocktail",Cocktail_id )
      return html
    else:
      html += template_cocktail_result.format(Picture_link=Cocktails[0].Picture_link,Name= Cocktails[0].Name)
      #html += template_choosen_Music.format(url= Music_url)
      return html
  else : 
    print("dataopen error ")
    return html

def Select_Cocktail_randomly( Number): 
  data = DataBase( DataPath= r"./Database/Database.db")
  if (data.open()):
    Cocktails= []
    ids = []
    Number_Cocktails =data.number_recipes() 
    if Number_Cocktails == 0: 
      return[]
    for i in range(Number):
      ids.append(rd.randint(1,Number_Cocktails))
      Cocktails.append(data.recipes(ids[-1])[0])
    data.close()
    return Cocktails
  else : 
    return []

#pages

def Welcome_page():
  html = template_site_begin + template_site_about + template_music_Selection() + template_site_end
  return html 

def Reverse_page():
  html = template_site_begin + template_Reverse_Searh() + template_site_end
  return html 
      
def Cocktails_list_page(Music_url):
  print([Music_url])
  html = template_site_begin + template_cocktails_Selection(Music_url) + template_site_end
  return html

def Result_page(Music_url, Cocktail_id):
  print([Cocktail_id,Music_url])
  html = template_site_begin  + template_Result(Cocktail_id, Music_url)+ template_Introduce_New_Choice +  template_music_Selection() + template_Introduction_Reverse_Search + template_site_end
  return html

