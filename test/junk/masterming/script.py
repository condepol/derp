#!/usr/bin/env python3
# coding: utf-8

import sys
import random 

def pion_couleur(couleur):
  return "\x1b[3"+str(["rouge","vert","jaune","bleu","violet","cyan"].index(couleur)+1)+"mX\x1b[0m"

def verifie(solution,reponse):
  return sum(1 for i in range(len(solution)) if solution[i] == reponse[i])
  
def partie(nombre_de_cases,nombre_de_couleurs):
  # Définition des couleurs
  couleurs = ["rouge","vert","jaune","bleu","violet","cyan"]
  solution = [random.randint(0, nombre_de_couleurs -1) for i in range(nombre_de_cases)]
  print(" ".join([pion_couleur(couleurs[solution[i]]) for i in range(nombre_de_cases)]))
  
  # Association des chiffres aux couleurs 
  print(" / ".join(["{0} pour {1}".format(i,pion_couleur(couleurs[i])) for i in range(nombre_de_couleurs)]))
  
  # Vérification par rapport au code
  win = False
  print()
  while (not win):
    # Récupération du code
    reponse = [min(int(i),nombre_de_couleurs) for i in input("Entrez votre code ({} cases) : ".format(nombre_de_cases))]
    # Tant qu'on a pas le bon nombre de chiffres, on recommence
    while (len(reponse) != nombre_de_cases):
      reponse = [min(int(i),nombre_de_couleurs) for i in input("Entrez votre code (\x1b[31m{} cases\x1b[0m) : ".format(nombre_de_cases))]

    # Affichage correspondant
    print(" ".join([pion_couleur(couleurs[reponse[i]]) for i in range(nombre_de_cases)]))
  
    bien_placees = verifie(solution,reponse)
    print("Vous avez {} bonne(s) couleur(s) bien placée(s)".format(bien_placees))
    if (reponse == solution) :
      print ("\nGagné \:D/")
      win = True
      
  #Mal placées

def main():
   # Introduction
  print ("!---------------------------------!")
  print ("!        Mastermind - v3.0        !")
  print ("!---------------------------------!")
 
  # Lecture des arguments
  if (len(sys.argv) != 3):
    print("Usage : {0} <nombre-de-cases> <nombre-de-couleurs> (max 6)".format(sys.argv[0]))
    sys.exit(1)
  
  play = True
  while(play):
    partie(int(sys.argv[1]),min(6,int(sys.argv[2])))
    if (input("Rejouer ? (rien = non)")==""):
      play = False

if __name__ == "__main__":
  main()
