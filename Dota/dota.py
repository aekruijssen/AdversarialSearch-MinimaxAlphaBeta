# -*- coding: utf-8 -*-
"""
Created on Wed Mar 13 10:27:51 2019

@author: adina
"""
import io
import copy

class Hero():
    def __init__(self, id, power, mastery, opponentMastery, team):
        self.id = id
        self.power = power
        self.mastery = mastery
        self.opponentMastery = opponentMastery
        self.team = team
        
''' blank class... we will use this and edit it to be what we want it to be '''
class Blank():
	pass

''' your Roster class... or whatever you want to call it '''
class State():
	# blah blah all your Roster stuff
    def __init__(self, heroes):
        self.h = heroes
    
    def getRadiant(self):
        r = []
        for i in self.h:
            if i.team == 1:
                r.append(i)
        return r
                
    def getDire(self):
        d = []
        for i in self.h:
            if i.team == 2:
                d.append(i)
        return d
    
    def calculateSynergy(self, type):
        if type == "radiant":
            distinct = True
            for i in self.getRadiant():
                for j in self.getRadiant():
                    if i != j:
                        if (i.id)%10 == (j.id)%10:
                            distinct = False
            if distinct:
                return 120
            else:
                return 0
            
        elif type == "dire":
            distinct = True
            for i in self.getDire():
                for j in self.getDire():
                    if i != j:
                        if (i.id)%10 == (j.id)%10:
                            distinct = False
            if distinct:
                return 120
            else:
                return 0
        
    def calculateAdvantage(self):
        radiantPoints = self.calculateSynergy("radiant")
        direPoints = self.calculateSynergy("dire")
        for i in self.getRadiant():
          radiantPoints += i.mastery * i.power 
        for i in self.getDire():
            direPoints += i.opponentMastery * i.power 
        return (radiantPoints - direPoints)
                
    def getScore(self):
        return self.calculateAdvantage()
    
    def getRemaining(self):
        rem = 0
        for i in self.h:
            if i.team == 0:
                rem = rem + 1
        return rem

    def undoMove(self, chosen):
        for i in self.h:
            if i == chosen:
                i.team = 0
    
    def terminal(self):
        if self.getRemaining() == 0:
            return True
        elif len(self.getDire()) >= 5:
            return True
        else:
            return False
    
    def makeMove(self, choice, turn):
        for i in self.h:
            if i == choice:
                i.team = turn

	#custom copy to replace your deepcopy
    def custom_copy(self):
        copy = Blank() # create Blank object to begin with		
        copy.__class__ = self.__class__ # turn the blank object into a Roster object
        copy.Heroes = self.Heroes # copy the stuff that is essential..
        copy.PackedData = self.Pack() # or perhaps pack the minimal data you need to reconstruct the object through computation.. you will need to write self.Pack(), and you will need a self.Unpack()
        return copy
    
def minimax(s, turn, hero):
   # s = copy.deepcopy(st)
    #s = st
    if s.terminal():
        score = s.getScore()
        #s.undoMove(hero)
        return score
    elif turn == "max":
        made = False
        if hero.team == 0:
            made = True
            #s.makeMove(hero, 1)
        biggest = -10000000000
        for i in s.h:
            if i.team == 0:
               # i.team = 1
                s.makeMove(i, 1)
                oldBiggest = biggest
                #print(oldBiggest)
                biggest = minimax(copy.deepcopy(s),"min", i)
                if(oldBiggest > biggest):
                    biggest = oldBiggest
               # s.undoMove(i)
               # biggest = max(biggest, minimax(s, "min",i))
                #st.undoMove(i)
               # i.team = 0
               # s = st
       # s=st
        #if made == True:
            #s.undoMove(hero)
           #hero.team = 0
        print("   Biggest: " + str(biggest))
       # s = st
        return biggest
    
    elif turn == "min":
        made = False
        if hero.team == 0:
            #s.makeMove(hero,2)
            made = True
        smallest = 10000000000
        for i in s.h:
            if i.team == 0:
                #i.team = 2
                s.makeMove(i,2)
                oldSmallest = smallest
                smallest = minimax(copy.deepcopy(s),"max",i)
                if oldSmallest < smallest:
                    smallest = oldSmallest
                #s.undoMove(i)
                #smallest = min(smallest, minimax(s, "max",i))
                #st.undoMove(i)
                #i.team = 0
                #s = st
        #s=st
        #if made == True:
            #s.undoMove(hero)
            #hero.team = 0
        print("   Smallest: " + str(smallest))
        return smallest
    else:
        return 0
    
    
def minimaxDecision(s):
    decision = 0
    score = -1000000000
    for i in s.h:
        if i.team == 0:
            oldScore = score
            i.team = 1
            score = minimax(s, "min", i)
            #score = max(score, oldScore)
            print(score)
            if oldScore > score:
                score = oldScore
            else:
                decision = i.id
            
            for j in s.h:
                j.team = 0 
                
            print(str(i.id) + " Score: " + str(score) + ", Dec: " + str(decision))
            print(" ")
            #i.team = 0
    return decision


#file = "input1.txt"
#try: infile = io.open(file, 'r', newline='\n')
#except: print ("\nFile not found"), quit()

heroes = []
'''
heroes.append(Hero(88703,94.096762,1.000000,0.589972,0))
heroes.append(Hero(86002,94.409059,0.569037,1.000000,0))
heroes.append(Hero(45302,120.307764,1.000000,0.446540,0))
heroes.append(Hero(16203,104.402585,0.976748,1.000000,0))
heroes.append(Hero(46803,94.409059,1.000000,0.996692,0))
heroes.append(Hero(58502,147.666518,1.000000,0.439176,0))
heroes.append(Hero(13202,120.307764,0.600135,1.000000,0))
heroes.append(Hero(95603,147.666518,0.375945,1.000000,0))
heroes.append(Hero(76105,104.402585,1.000000,0.691562,0))
heroes.append(Hero(93005,101.974982,0.635956,1.000000,0))
       
'''
heroes.append(Hero(37401,91.524474,1.000000,0.737905,0))
heroes.append(Hero(30905,99.157370,1.000000,1.000000,0))
heroes.append(Hero(28604,67.536325,1.000000,0.872330,0))
heroes.append(Hero(22001,137.908859,1.000000,0.686673,0))
heroes.append(Hero(26604,137.908859,0.494194,1.000000,0))
heroes.append(Hero(64301,91.524474,0.776373,1.000000,0))
heroes.append(Hero(63901,109.754273,0.983562,1.000000,0))
heroes.append(Hero(14902,96.591484,1.000000,1.000000,0))
heroes.append(Hero(54603,109.754273,1.000000,0.620966,0))
heroes.append(Hero(54205,117.111363,0.888710,1.000000,0))
heroes.append(Hero(78201,104.077997,0.909878,1.000000,0))
heroes.append(Hero(66705,107.950134,0.545751,1.000000,0))
heroes.append(Hero(42903,117.111363,1.000000,0.606749,0))


startState = State(heroes)
answer = minimaxDecision(startState)

print("Final Answer " + str(answer))

        