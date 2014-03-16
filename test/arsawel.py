#!/usr/bin/env python2.7
# coding: utf-8
from random import randrange
from turtle import *
on_passe_par_la_moria=0
def finder(bx,by):
	return bx + longueur_totale * by
def note(ax,ay):
	matrice[finder(ax,ay)]=1
print "__________________________________________________________"
print "|                                                        |"
print "|                     A R S A W E L                      |"
print "|________________________________________________________|\n\n"
print " Auto-Redirecting Self Avoiding Walk in Euclidian Lattice\n"
print "Longueur totale du parcours ? {100}"
longueur_totale = raw_input("INPUT : ")
print "Prise en compte de l'entrée ..."
if longueur_totale:# par défaut, 100.
	longueur_totale = int(longueur_totale)
else:
	longueur_totale = int(100)
print "Pas ? {6}"
pas = raw_input("INPUT : ")
print "Prise en compte de l'entrée ..."
if pas:# par défaut, 6.
	pas = float(pas)
else:
	pas = int(6)
print "Trace tests ? {0}"
tra = raw_input("INPUT : ")
print "Prise en compte de l'entrée ..."
print "Epaisseur du tracé ?"
epa=raw_input("INPUT : ")
print "Prise en compte de l'entrée ..."
if epa:
	epa=int(epa)
else:
	epa=int(1)
print "High-speed ? {1}"
spe=raw_input("INPUT : ")
if spe:
	spe=2
else:
	speed(0)
if tra:# par défaut, 0.
	tra = int(1)
else:
	tra = int(0)
print "Génération de la matrice ..."
matrice = [0]
PedroDeLaMuerte = 1
while PedroDeLaMuerte != longueur_totale * longueur_totale:
	matrice.append(0)
	PedroDeLaMuerte = PedroDeLaMuerte + 1
print "Initialisation ..."
x, y = longueur_totale / 2 , longueur_totale / 2
card = randrange(4)
note(x,y)
width(epa)
forward(pas)
if card == 0:
	x = x + 1
elif card == 1:
	y = y + 1
elif card == 2:
	x = x - 1
elif card == 3:
	y = y - 1
else:
	print "Bug ! Va dormir !"
note(x,y)
compteur_pas = 1
print "Départ de la tortue ! ( en",x,y,"direction",card,")"
while compteur_pas < longueur_totale:
# d'abord, on note les cases en vue. (ancienne fonction note_cases).
	if card == 0:
		champ = [matrice[finder(x,y+1)],matrice[finder(x+1,y+1)],matrice[finder(x+1,y)],matrice[finder(x+1,y-1)],matrice[finder(x,y-1)]]
	elif card == 1:
		champ = [matrice[finder(x-1,y)],matrice[finder(x-1,y+1)],matrice[finder(x,y+1)],matrice[finder(x+1,y+1)],matrice[finder(x+1,y)]]
	elif card == 2:
		champ = [matrice[finder(x,y-1)],matrice[finder(x-1,y-1)],matrice[finder(x-1,y)],matrice[finder(x-1,y+1)],matrice[finder(x,y+1)]]
	elif card == 3:
		champ = [matrice[finder(x+1,y)],matrice[finder(x+1,y-1)],matrice[finder(x,y-1)],matrice[finder(x-1,y-1)],matrice[finder(x-1,y)]]
# maintenant on élimine les directions occupées.
	dir_pos=[0,1,2]
	if champ[0] == 1:
		dir_pos.remove(0)
	if champ[2] == 1:
		dir_pos.remove(1)
	if champ[4] == 1:
		dir_pos.remove(2)
# maintenant, on évalue pour savoir si il faut différencier impasse et espace.
	if [champ[0],champ[1],champ[2]]==[0,1,0] or [champ[2],champ[3],champ[4]]==[0,1,0] or [champ[0],champ[2],champ[4]]==[0,1,0]:
		on_passe_par_la_moria = on_passe_par_la_moria + 1
		if tra == 1:
			color('red')
			width(1)
		posit = position()
		n0,n1,n2=0,0,0
# parmi les portes non obstruées, on va déterminer là où il y a le plus de place.
		for depart_relatif in dir_pos:
			up()
			if depart_relatif == 0:
				vi_card = (card+1)%4
				vi_dir = (vi_card+1)%4
				if card == 0:
					vi_x = x
					vi_y = y + 1
				elif card == 1:
					vi_x = x - 1
					vi_y = y
				elif card == 2:
					vi_x = x
					vi_y = y - 1
				elif card == 3:
					vi_x = x + 1
					vi_y = y
				else:
					print "Bug ! Va dormir !"
			elif depart_relatif == 2:
				vi_card = (card-1)%4
				vi_dir = (vi_card-1)%4
				if card == 0:
					vi_x = x
					vi_y = y - 1
				elif card == 1:
					vi_x = x + 1
					vi_y = y
				elif card == 2:
					vi_x = x
					vi_y = y + 1
				elif card == 3:
					vi_x = x - 1
					vi_y = y
				else:
					print "Bug ! Va dormir !"
			elif depart_relatif == 1:
				vi_card = card
				vi_dir = (vi_card+1)%4
				if card == 0:
					vi_x = x + 1
					vi_y = y
				elif card == 1:
					vi_x = x
					vi_y = y + 1
				elif card == 2:
					vi_x = x - 1
					vi_y = y
				elif card == 3:
					vi_x = x
					vi_y = y - 1
				else:
					print "Bug ! Va dormir !"
#C'est ici que sa déchire sa race.
			if vi_dir == 0:
				di_vi_x = vi_x + 1
				di_vi_y = vi_y
			elif vi_dir == 1:
				di_vi_x = vi_x
				di_vi_y = vi_y + 1
			elif vi_dir == 2:
				di_vi_x = vi_x - 1
				di_vi_y = vi_y
			elif vi_dir == 3:
				di_vi_x = vi_x
				di_vi_y = vi_y - 1
			if depart_relatif == 1:
				n1 = 0
				aprop = 1
			elif depart_relatif == 0:
				n0 = 0
				aprop = -1
			elif depart_relatif == 2:
				n2 = 0
				aprop = 1
			if tra == 1:
				goto(di_vi_x*pas-((longueur_totale*pas)/2),di_vi_y*pas-((longueur_totale*pas)/2))
			bloqueun=0
			down()
			while matrice[finder(di_vi_x,di_vi_y)] == 1 and bloqueun != 5:
				bloqueun=bloqueun+1
				vi_dir = (vi_dir + aprop)%4 # ! ?
				if vi_dir == 0:
					di_vi_x = vi_x + 1
					di_vi_y = vi_y
				elif vi_dir == 1:
					di_vi_x = vi_x
					di_vi_y = vi_y + 1
				elif vi_dir == 2:
					di_vi_x = vi_x - 1
					di_vi_y = vi_y
				elif vi_dir == 3:
					di_vi_x = vi_x
					di_vi_y = vi_y - 1
			vi_x,vi_y=di_vi_x,di_vi_y
			vi_dir = (vi_dir - aprop)%4
			virinit = [vi_x,vi_y]
			if tra == 1:
				goto(vi_x*pas-((longueur_totale*pas)/2),vi_y*pas-((longueur_totale*pas)/2))
			vir = [1,1]
			if tra == 1:
				goto(di_vi_x*pas-((longueur_totale*pas)/2),di_vi_y*pas-((longueur_totale*pas)/2))
			while vir != virinit and bloqueun != 5:
				if depart_relatif == 0:
					n0 = n0 + 1
				elif depart_relatif == 1:
					n1 = n1 +1
				elif depart_relatif == 2:
					n2 = n2 + 1
				if vi_dir == 0:
					di_vi_x = vi_x + 1
					di_vi_y = vi_y
				elif vi_dir == 1:
					di_vi_x = vi_x
					di_vi_y = vi_y + 1
				elif vi_dir == 2:
					di_vi_x = vi_x - 1
					di_vi_y = vi_y
				elif vi_dir == 3:
					di_vi_x = vi_x
					di_vi_y = vi_y - 1
				while matrice[finder(di_vi_x,di_vi_y)]:
					vi_dir = (vi_dir + aprop)%4
					if vi_dir == 0:
						di_vi_x = vi_x + 1
						di_vi_y = vi_y
					elif vi_dir == 1:
						di_vi_x = vi_x
						di_vi_y = vi_y + 1
					elif vi_dir == 2:
						di_vi_x = vi_x - 1
						di_vi_y = vi_y
					elif vi_dir == 3:
						di_vi_x = vi_x
						di_vi_y = vi_y - 1
				if tra == 1:
					goto(di_vi_x*pas-((longueur_totale*pas)/2),di_vi_y*pas-((longueur_totale*pas)/2))
				vi_x , vi_y = di_vi_x , di_vi_y
				vi_dir = (vi_dir - aprop)%4
				vir=[vi_x,vi_y]
			up()
			if bloqueun==5:
				bloqueun=0
				if depart_relatif == 0:
					n0=1
				if depart_relatif == 1:
					n1=1
				if depart_relatif == 2:
					n2=1
#ici on change le champ des possibles, il ne reste 'que' l'infini d'accessible
		listepatates = [n0,n1,n2]
		dir_pos=[]
		if n0 == max(listepatates):
			dir_pos.append(0)
		if n1 == max(listepatates):
			dir_pos.append(1)
		if n2 == max(listepatates):
			dir_pos.append(2)
		up()
		goto(posit)
		color('black')
		width(epa)
		down()
	if len(dir_pos) != 0:
		direction=dir_pos[randrange(len(dir_pos))]# ici on prend une direction aléatoire dans celles qui restent
	else:
		print "Coincé ! à",compteur_pas,"pas. (Normalement, ca n'arrive pas.)"
		break
# ici l'on tourne
	if direction == 0:
		card = ( card + 1 )%4
		left(90)
	if direction == 2:
		card = ( card - 1 )%4
		right(90)
# ici l'on avance
	forward(pas)
	if card == 0:
		x = x + 1
	elif card == 1:
		y = y + 1
	elif card == 2:
		x = x - 1
	elif card == 3:
		y = y - 1
	else:
		print "Bug ! Va dormir !"
	note(x,y)
	compteur_pas = compteur_pas + 1
print "Nombre de tests :", on_passe_par_la_moria
stop = raw_input("< [Entrée] pour quitter >")
print "Fini !"
