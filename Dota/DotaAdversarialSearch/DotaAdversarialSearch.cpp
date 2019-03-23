// DotaAdversarialSearch.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <iterator>
#include <stdio.h>
#include <algorithm>
/*
int bestID = 0;

int minimax(int depth, std::vector<Hero*> r, std::vector<Hero*> d,  std::vector<Hero*> heroes, bool isMax)
{
	float score = calculateAdvantage(r, d);
	int numLeft = 0;

	for (int i = 0; i < heroes.size(); i++) {
		if (heroes.at(i)->team == 0) {
			numLeft++;
		}
	}
	if (numLeft == 0) {
		//return -1000;

		float radiantPoints = calculateSynergy(r);
		float direPoints = calculateSynergy(d);

		for (int i = 0; i < r.size(); i++) {
			radiantPoints += (r.at(i)->mastery * r.at(i)->power);
		}

		for (int i = 0; i < d.size(); i++) {
			direPoints += (d.at(i)->mastery * d.at(i)->power);
		}
		if (radiantPoints > direPoints) {
			//bestID = r.at(0)->id;
			return (score - depth);
		}
		else if (direPoints > radiantPoints) {
			//bestID = d.at(0)->id;
			return (score + depth);
		}
		else {
			return 0;
		}
	}
	/*
	if (numLeft == 0) {
		if (score < 0) {
			return (score + depth);
		}
		else if (score >0) {
			return (score - depth);
		}
		else {
			return 0;
		}
	}*

	if (isMax)
	{
		int best = -1000;
		for (int i = 0; i < heroes.size(); i++) {
			if (heroes.at(i)->team == 0) {

				// Pick hero
				heroes.at(i)->team = 1;
				r.emplace_back(heroes.at(i));
				int oldBest = best;
				best = std::max(best, minimax(depth + 1, r, d, heroes, !isMax));

				if (oldBest != best) {
					//bestID = r.at(0)->id;
				}
				// Undo move
				heroes.at(i)->team = 0;
				auto iter = std::find(r.begin(), r.end(), heroes.at(i));
				if (iter != r.end()) {
						auto iter2 = r.end() - 1;
						std::iter_swap(iter, iter2);
						r.pop_back();
				}
			}
		}
		//bestID = r.at(0)->id;
		return best;
	}
	// If minimizer's move
	else
	{
		int best = 1000;
		for (int i = 0; i < heroes.size(); i++)
		{
			if (heroes.at(i)->team == 0) {

				// pick hero
				heroes.at(i)->team = 2;
				d.emplace_back(heroes.at(i));
				int oldBest = best;
				best = std::min(best, minimax(depth + 1, r, d, heroes, !isMax));

				if (best != oldBest) {
					//bestID = d.at(0)->id;
				}
				// Undo move
				heroes.at(i)->team = 0;
				auto iter = std::find(d.begin(), d.end(), heroes.at(i));
				if (iter != d.end())
				{
					auto iter2 = d.end() - 1;
					std::iter_swap(iter, iter2);
					d.pop_back();
				}

			}
		}
		return best;
	}
}*/


class Hero {
public:
	int id;
	float power;
	float mastery;
	float opponentMastery;
	int team;

	bool operator < (const Hero& str) const
	{
		return (id < str.id);
	}
};

float calculateSynergy(std::vector<Hero*> h) {
	bool distinct = true;
	/*
	for (int i = 0; i < h.size(); i++) {
		for (int j = 0; j < h.size(); j++) {
			if (i != j) {
				std::string idStr = std::to_string(h.at(i)->id);
				int digits = stoi(idStr.substr(idStr.length() - 1));
				std::string otherIdStr = std::to_string(h.at(j)->id);
				int otherDigits = stoi(otherIdStr.substr(otherIdStr.length() - 1));
				if (digits == otherDigits) {
					distinct = false;
				}
			}
		}
	}*/
	for (int i = 0; i < h.size(); i++) {
		for (int j = 0; j < h.size(); j++) {
			if (i != j) {
				if (((h.at(i)->id) % 10) == ((h.at(j)->id) % 10)){
				distinct = false;
				}
			}
		}
	}
	if (distinct) {
		return 120;
	}
	else {
		return 0;
	}
}
float calculateAdvantage(std::vector<Hero*> radiant, std::vector<Hero*> dire) {
	float radiantPoints = calculateSynergy(radiant);
	float direPoints = calculateSynergy(dire);

	for (int i = 0; i < radiant.size(); i++) {
		radiantPoints += (radiant.at(i)->mastery * radiant.at(i)->power);
	}

	for (int i = 0; i < dire.size(); i++) {
		direPoints += (dire.at(i)->opponentMastery * dire.at(i)->power);
	}

	return (radiantPoints - direPoints);
}

class state {
public:
	std::vector<Hero*> h;
	std::vector<Hero*> getRadiant() {
		std::vector<Hero*> r;
		for (int i = 0; i < h.size(); i++) {
			if (h.at(i)->team == 1) {
				r.push_back(h.at(i));
			}
		}
		return r;
	};
	std::vector<Hero*> getDire() {
		std::vector<Hero*> d;
		for (int i = 0; i < h.size(); i++) {
			if (h.at(i)->team == 2) {
				d.push_back(h.at(i));
			}
		}
		return d;
	};
	std::vector<Hero*> getActions() {
		std::vector<Hero*> a;
		for (int i = 0; i < h.size(); i++) {
			if (h.at(i)->team == 0) {
				a.push_back(h.at(i));
			}
		}
		return a;
	};

	float getScore() {
		return calculateAdvantage(this->getRadiant(), this->getDire());
	};

	int getRemaining() {
		int rem = 0;
		for (int i = 0; i < h.size(); i++) {
			if (h.at(i)->team == 0) {
				rem++;
			}
		}
		return rem;
	}

	void undoMove(Hero* chosen) {
		//auto iter = std::find((this->h).begin(), (this->h).end(), chosen);
		//if (iter != (this->h).end())
		for(int i=0; i<(this->h).size(); i++)
		{
			if ((this->h).at(i) == chosen) {
				((this->h).at(i))->team = 0;
			}
			//auto iter2 = (this->h).end() - 1;
			//std::iter_swap(iter, iter2);
			//(this->h).pop_back();
			//(this->h).at(iter)->team = 0;
		}
	}
};

state result(state cur, Hero* choice, int t) {
	state s;
	s.h = cur.h;

	for (int i = 0; i < (s.h).size(); i++) {
		//(s.h).emplace_back((cur.h).at(i));
		if ((s.h).at(i) == choice) {
			(s.h).at(i)->team = t;
		}
	}
	return s;
}

float utility(state s) {
	if (s.getScore() > 0) {
		return 1.0;
	}
	else if (s.getScore() < 0) {
		return 0.0;
	}
	else {
		return 0.5;
	}
}

bool terminal(state s) {
	if (s.getRemaining() == 0) {
		return true;
	}
	else if (s.getDire().size() >= 5 ){
		//&& s.getRadiant().size() >= 5) {
		return true;
	}
	else {
		return false;
	}
};
float minVal(state s);

float maxVal(state s) {
	if (terminal(s)) {
		//return utility(s);
		return s.getScore();
	}
	float biggest = -100000;
	std::vector<Hero*> taken;
	for (int i = 0; i < (s.h).size(); i++) {
		Hero* h = (s.h).at(i);
		taken.push_back(h);
	}
	for (int i = 0; i < (s.h).size(); i++) {
		if (taken.at(i)->team == 0) {
			(s.h).at(i)->team = 1;
			float oldBiggest = biggest;
			//biggest = minVal(s);
			biggest = std::max(biggest, minVal(s));
			//(s.h).at(i)->team = 0;

			//if (biggest > oldBiggest) {
				//(s.h).at(i)->team = 0;
			//}
			//else {
				//(s.h).at(i)->team = 0;
			//	biggest = oldBiggest;
			//}
		//	(s.h).at(i)->team = 0;
		}
		//(s.h).at(i)->team = 0;
		//(s.h).at(i)->team = 1;
		//int oldBiggest = biggest;
		//if (biggest == oldBiggest) {
			//s.undoMove(actions.at(i));
			//actions.at(i)->team = 0;
		//}
	}
	std::cout << "Biggest " << biggest << std::endl;
	return biggest;
}

float minVal(state s) {
	if (terminal(s)) {
		//return utility(s);
		//return s.getScore();
	}
	float smallest = 100000;
	std::vector<Hero> taken;
	for (int i = 0; i < (s.h).size(); i++) {
		Hero h = *(s.h).at(i);
		taken.push_back(h);
	}
	for (int i = 0; i < (s.h).size(); i++) {
		float oldSmallest = smallest;
		if (taken.at(i).team == 0) {
			(s.h).at(i)->team = 2;
			//smallest = (maxVal(s));
			smallest = std::min(smallest, maxVal(s));
		//	(s.h).at(i)->team = 0;

			//if (smallest >= oldSmallest) {
				//(s.h).at(i)->team = 0;
			//}
			//else {
				//(s.h).at(i)->team = 0;
			//	smallest = oldSmallest;
			//}
			//(s.h).at(i)->team = 0;
		}
		//(s.h).at(i)->team = 0;
			//result(s, actions.at(i), 1)));
		//if (smallest == oldSmallest) {
			//s.undoMove(actions.at(i));
			//actions.at(i)->team = 0;
		//}
	}
	std::cout << "Smallest " << smallest << std::endl;
	return smallest;
}

int minimaxDecision (state s) {
	std::vector<Hero> taken;
	for (int i = 0; i < (s.h).size(); i++) {
		Hero h = *(s.h).at(i);
		taken.push_back(h);
	}

	int decision = 0;
	float score = -100000;
	//std::vector<Hero*> actions = s.getActions();
	for (int i = 0; i < (s.h).size(); i++) {
		if (taken.at(i).team == 0) {
			(s.h).at(i)->team = 1;
			float oldScore = score;
			score = minVal(s);
			//score = std::max(oldScore, score);
			if (score > oldScore) {
				decision = (s.h).at(i)->id;
				//if(contender == 1) {
				//decision = actions.at(i)->id;
			}
			else {
				score = oldScore;
			}
			
			(s.h).at(i)->team = 0;
		}
		for (int j = 0; j < (s.h).size(); j++) {
				(s.h).at(j)->team = 0;
			}
		std::cout << std::endl;
	}

	return decision;
}

struct lessThan
{
	bool operator()(Hero* lx, Hero* rx) const {
		return lx->id < rx->id;
	}
};

int main()
{
	char x;
	std::ifstream inFile;

	std::string filename = "test_case/input8.txt";
	inFile.open(filename);
	if (!inFile) {
		std::cout << "Unable to open file";
		exit(1); // terminate with error
	}
	
	std::vector<Hero*> heroes;

	std::string numHeroes = "";
	inFile >> numHeroes;

	std::string algo = "";
	inFile >> algo;

	std::string line = "";
	while (inFile >> line) {
		if (!line.empty()) {
			std::string attributes[5];
			std::string del = ",";

			Hero* h = new Hero();

			h->id = stoi(line.substr(0, line.find(del)));
			line = line.substr(line.find(del)+1);

			h->power = stof(line.substr(0, line.find(del)));
			line = line.substr(line.find(del)+1);

			h->mastery = stof(line.substr(0, line.find(del)));
			line = line.substr(line.find(del)+1);

			h->opponentMastery = stof(line.substr(0, line.find(del)));
			line = line.substr(line.find(del)+1);

			h->team = stoi(line);

			heroes.emplace_back(h);
		}
	}

	inFile.close();

	int nextHero = 0;
	std::vector<Hero*> radiant;
	std::vector<Hero*> dire;

	for (int i = 0; i < heroes.size(); i++) {
		if (heroes.at(i)->team == 1) {
			radiant.push_back(heroes.at(i));
		}
		else if (heroes.at(i)->team == 2) {
			dire.push_back(heroes.at(i));
		}
	}


	if (algo == "minimax") {
		//nextHero = minimax(0, radiant, dire, heroes, 1);
		//int done = bestID;
		//std::sort(heroes.begin(), heroes.end());
		std::sort(heroes.begin(), heroes.end(), lessThan());
		state startState;
		startState.h = heroes;
		int answer = minimaxDecision(startState);
		int i = 0;
	}

	else if (algo == "ab") {
		
	}
}

