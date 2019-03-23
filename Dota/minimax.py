# -*- coding: utf-8 -*-
"""
Created on Wed Mar 13 23:14:06 2019

@author: adina
"""

import random

class Hero():
    def __init__(self, id, power, mastery, opponentMastery, team):
        self.id = id
        self.power = power
        self.mastery = mastery
        self.opponentMastery = opponentMastery
        self.team = team
        

class TicTacToe:

    def __init__(self, h):
        self.heroes = h


    def clearBoard(self):
        self.heroes = []

    def whoWon(self):
        if self.checkWin() == "Radiant":
            return "Radiant"
        elif self.checkWin() == "Dire":
            return "Dire"
        elif self.gameOver() == True:
            return "Tie"

    def availableMoves(self):
        """Return empty spaces on the board"""
        moves = []
        for i in self.heroes:
            if i.team == 0:
                moves.append(i)
        return moves

    def getMoves(self, t):
        """Get all moves made by a given player"""
        moves = []
        for i in range(0, len(self.heroes)):
            if self.heroes[i] == t:
                moves.append(i)
        return moves

    def makeMove(self, position, player):
        if player == "Radiant":
            for i in self.heroes:
                if i == position:
                    if i.team == 0:
                        i.team = player
        elif player == "Dire":
            # if len(self.getDire()) <= 5:
            for i in self.heroes:
                if i == position:
                    if i.team == 0:
                        i.team = player

    def getRadiant(self):
        r = []
        for i in self.heroes:
            if i.team == 1:
                r.append(i)
        return r
                
    def getDire(self):
        d = []
        for i in self.heroes:
            if i.team == 2:
                d.append(i)
        return d
    
    def calculateSynergy(self, type):
        if type == "Radiant":
            distinct = True
            for i in self.getRadiant():
                for j in self.getRadiant():
                    if i != j:
                        if i.id%10 == j.id%10:
                            distinct = False
            if distinct:
                return 120
            else:
                return 0
            
        elif type == "Dire":
            distinct = True
            for i in self.getDire():
                for j in self.getDire():
                    if i != j:
                        if i.id%10 == j.id%10:
                            distinct = False
            if distinct:
                return 120
            else:
                return 0
        
    def calculateAdvantage(self):
        radiantPoints = self.calculateSynergy("Radiant")
        direPoints = self.calculateSynergy("Dire")
        for i in self.getRadiant():
            radiantPoints += (i.mastery * i.power)
        for i in self.getDire():
            direPoints += (i.opponentMastery * i.power) 
        return (radiantPoints - direPoints)
                
    def getScore(self):
        return self.calculateAdvantage()
    
    def checkWin(self):
        """Return the player that wins the game"""
        if len(self.availableMoves()) <= 0:
            if self.getScore() > 0:
                return 1
            elif self.getScore() < 0:
                return 2
        return 0

    def gameOver(self):
        """Return True if X wins, O wins, or draw, else return False"""
        if len(self.availableMoves()) <= 0:
            return True
        elif len(self.getDire()) >= 5:
           return True
        return False

    def minimax(self, node, depth, player):
        """
        Recursively analyze every possible game state and choose
        the best move location.
        node - the board
        depth - how far down the tree to look
        player - what player to analyze best move for (currently setup up ONLY for "O")
        """
        if depth == 0 or node.gameOver():
            return self.calculateAdvantage()
           # if node.checkWin() == "Dire":
            #    return 0
            #elif node.checkWin() == "Radiant":
             #   return 100
            #else:
            #    return 50

        if player == "Radiant":
            bestValue = 0
            for move in node.availableMoves():
                node.makeMove(move, player)
                moveValue = self.minimax(node, depth-1, changePlayer(player))
                node.makeMove(move, " ")
                bestValue = max(bestValue, moveValue)
            print("Radiant Move: " + str(bestValue))
            return bestValue
        
        if player == "Dire":
            bestValue = 100
            for move in node.availableMoves():
                node.makeMove(move, player)
                moveValue = self.minimax(node, depth-1, changePlayer(player))
                node.makeMove(move, " ")
                bestValue = min(bestValue, moveValue)
            print("Dire Move: " + str(bestValue))
            return bestValue

def changePlayer(player):
    """Returns the opposite player given any player"""
    if player == "Dire":
        return "Radiant"
    else:
        return "Dire"

def make_best_move(board, depth, player):
    """
    Controllor function to initialize minimax and keep track of optimal move choices
    board - what board to calculate best move for
    depth - how far down the tree to go
    player - who to calculate best move for (Works ONLY for "O" right now)
    """
   # print("in")
    neutralValue = 50
    choices = []
    for move in board.availableMoves():
        board.makeMove(move, player)
        moveValue = board.minimax(board, depth-1, changePlayer(player))
        board.makeMove(move, 0)

        if moveValue > neutralValue:
            choices = [move]
            break
        elif moveValue == neutralValue:
            choices.append(move)
    print("choices: ", choices)

    if len(choices) > 0:
        return random.choice(choices)
    else:
        return random.choice(board.availableMoves())


def makeFirst(game):
     while game.gameOver() == False:
        #person_move = int(input("You are X: Choose number from 1-9: "))
        print("Dire: ")
        
        dAI = make_best_move(game,-1,"Dire")
        game.makeMove(dAI, "Dire")
        #game.show()

        #if game.gameOver() == True:
         #   break

        print("Radiant: ")
        ai_move = make_best_move(game, -1, "Radiant")
        game.makeMove(ai_move, "Radiant")


#Actual game
if __name__ == '__main__':
    
    heroes = []
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
    
    game = TicTacToe(heroes)
    
    #game.show()

    answer = makeFirst(game)
    print(str(answer))
       # game.show()

    print("Game Over. " + game.whoWon() + " Wins")
