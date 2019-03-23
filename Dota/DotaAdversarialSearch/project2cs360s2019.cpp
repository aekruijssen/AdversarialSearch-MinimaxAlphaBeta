#ifndef PCH_H
#define PCH_H

#endif //PCH_H

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <iterator>
#include <stdio.h>
#include <algorithm>
#include <ostream>

class Hero {
public:
	int id;
	double power;
	double mastery;
	double opponentMastery;
	int team;
};

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

	double calculateSynergy(std::vector<Hero*> h) {
		bool distinct = true;
		if (h.size() >= 5) {
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					if (i != j) {
						if (((h.at(i)->id) % 10) == ((h.at(j)->id) % 10)) {
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
		return 0;
	};

	double calculateAdvantage(std::vector<Hero*> radiant, std::vector<Hero*> dire) {
		//if (dire.size() < 5) {
		//	return -5000000;
		//}
		double radiantPoints = this->calculateSynergy(radiant);
		double direPoints = this->calculateSynergy(dire);

			for (int i = 0; i < radiant.size(); i++) {
				//for (auto i : radiant) {
				radiantPoints += (radiant.at(i)->mastery * radiant.at(i)->power);
					//radiantPoints += (i->mastery * i->power);
			}

		for (int i = 0; i < dire.size(); i++) {
			//for (auto i : dire) {
			direPoints += (dire.at(i)->opponentMastery * dire.at(i)->power);
			//direPoints += (i->opponentMastery * i->power);
		}

		return (radiantPoints - direPoints);
	};

	double getScore() {
		return (this->calculateAdvantage(this->getRadiant(), this->getDire()));
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
};


bool terminal(state s) {
	if (s.getRemaining() == 0) {
		return true;
	}
	else if (s.getDire().size() >= 5) {
		//if (s.getRadiant().size() >= 5) {
			return true;
		//}
	}
	else {
		return false;
	}
};

double minVal(state s, std::string strat, double a, double ft);

double maxVal(state s, std::string strat, double a, double b) {
	if (terminal(s)) {
		//std::cout << "Terminal Biggest " << s.getScore() << std::endl;
		return s.getScore();
	}
	
	//double terminal = s.getScore();
	//if (terminal != -5000000) {
	//	return terminal;
	//}
	

	double biggest = -1000000;

	for (int i = 0; i < (s.h).size(); i++) {
		if ((s.h).at(i)->team == 0) {

			(s.h).at(i)->team = 1;

			if (strat == "minimax") {
				biggest = std::max(biggest, minVal(s, "minimax", a, b));
			}
			else if (strat == "ab") {
				double score = minVal(s, "ab", a, b);
				biggest = std::max(biggest, score);

				if (biggest > a) {
					//std::cout << "Biggest greater than alpha break " << biggest << std::endl;
					a = biggest;
				}
			}

			(s.h).at(i)->team = 0;

			if (strat == "ab") {
				if (b <= a) {
				   //std::cout << "Beta less than alpha break " << b << std::endl;
				   break;
				}
			}

			(s.h).at(i)->team = 0;
		}
	}
	//std::cout << "End of MaxVal Biggest " << biggest << std::endl;
	//std::cout << std::endl;
	
	return biggest;
}

double minVal(state s, std::string strat, double a, double ft) {
	if (terminal(s)) {
		//std::cout << "Terminal Smallest " << s.getScore() << std::endl;
		return s.getScore();
	}

	//double terminal = s.getScore();
	//if (terminal != -5000000) {
	//	return terminal;
	//}


	double smallest = 1000000;

	for (int i = 0; i < (s.h).size(); i++) {
		if ((s.h).at(i)->team == 0) {

			(s.h).at(i)->team = 2;

			if (strat == "minimax") {
				smallest = std::min(smallest, maxVal(s, "minimax", a, ft));
			}
			else if (strat == "ab") {

				double score = maxVal(s, "ab", a, ft);
				smallest = std::min(smallest, score);
				
				if (smallest < ft) {
					ft = smallest;
				}
				
				(s.h).at(i)->team = 0;

				if (ft <= a) {
					//std::cout << "Less than Alpha break " << ft << std::endl;
					break;
				}
			}
			(s.h).at(i)->team = 0;
		}
	}
	//std::cout << "End of MinVal Smallest " << smallest << std::endl;
	//std::cout << std::endl;
	
	return smallest;
}

int minimaxDecision(state s, std::string strategy) {
	int decision = 0;
	double score = -100000;

	for (int i = 0; i < (s.h).size(); i++) {
		if((s.h).at(i)->team == 0) {

			(s.h).at(i)->team = 1;

			double oldScore = score;

			if (strategy == "minimax") {
				score = minVal(s, "minimax", -1000000, 1000000);
			}
			else if (strategy == "ab") {
				score = minVal(s, "ab", -1000000, 1000000);
			}

			if (score > oldScore) {
				decision = (s.h).at(i)->id;
			}
			else {
				score = oldScore;
			}

			(s.h).at(i)->team = 0;
		}
		
		//std::cout << std::endl;
		//std::cout << std::endl;
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
	//std::ifstream inFile("test_case/input6.txt", std::ifstream::in);
	std::ifstream inFile("input.txt", std::ifstream::in);

	std::string line;
	int numHeroes;
	std::string algo;
	
	inFile >> numHeroes;
	inFile >> algo;

	std::vector<Hero*> heroes;

	for (int i = 0; i < numHeroes; i++) {
		Hero* h = new Hero();

		inFile >> line;

		h->id = std::stoi(line.substr(0, line.find_first_of(",")));
		line = line.substr(line.find_first_of(",") + 1);
		h->power = std::stod(line.substr(0, line.find_first_of(",")));
		line = line.substr(line.find_first_of(",") + 1);
		h->mastery = std::stod(line.substr(0, line.find_first_of(",")));
		line = line.substr(line.find_first_of(",") + 1);
		h->opponentMastery = std::stod(line.substr(0, line.find_first_of(",")));
		line = line.substr(line.find_first_of(",") + 1);
		h->team = std::stoi(line);

		heroes.push_back(h);
	}

	inFile.close();

	std::sort(heroes.begin(), heroes.end(), lessThan());
	state startState;
	startState.h = heroes;

	int answer = 0;

	//algo = "minimax";
	//algo = "ab";

	if (algo == "minimax") {
		answer = minimaxDecision(startState, "minimax");
	}

	else if (algo == "ab") {
		answer = minimaxDecision(startState, "ab");
	}

	std::ofstream myfile;
	myfile.open("output.txt");
	myfile << answer << "\n";
	myfile.close();
}