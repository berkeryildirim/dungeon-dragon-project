#include "Classes.h"

void randomize_speed(std::vector<Unit*>& unit) {
	for (int i = 0; i < 8; i++) {
		unit.at(i)->set_speed_turn((unit.at(i)->get_speed() + (rand() & 8) + 1));
	}
}


void GAMELOGIC(std::vector<Hero*>&heroes,std::vector<Monster*>&monsters,std::vector<Unit*>&units) {
	int round=1;
	int attack_selector=0;
	int randomize;
	while (true) {
		randomize_speed(units);
		auto compareSpeeds = [](Unit* u1, Unit* u2) {
			return u1->get_speed_turn() > u2->get_speed_turn();
		};
		std::sort(units.begin(), units.end(),compareSpeeds);
		for (int i = 0; i < 8; i++) {
			if (units.at(i)->get_class() == "crusader") {
				while (true) {
					randomize = rand() % 4;
					if (units.at(i)->get_pos() < 3&& monsters.at(randomize)->get_pos()<3) {
						while (monsters.at(randomize)->is_Alive() == false) {
							randomize = rand() % 4;
							if (monsters.at(0)->are_allDead(monsters) == true)
								break;
						}
						units.at(i)->attack(monsters.at(randomize));
						break;
					}
					else {
						while (monsters.at(randomize)->is_Alive() == false) {
							randomize = rand() % 4;
							if (monsters.at(0)->are_allDead(monsters) == true)
								break;
						}
						units.at(i)->attack(monsters.at(randomize));
						heroes.at(0)->lance(heroes);
						break;
					}
				}
			}
			else if (units.at(i)->get_class() == "vestal") {
				attack_selector = rand() % 3;
				switch (attack_selector) {
				case 0:
					randomize = rand() % 4;
					while (monsters.at(randomize)->is_Alive() == false) {
						randomize = rand() % 4;
						if (monsters.at(0)->are_allDead(monsters) == true)
							break;
					}
					units.at(i)->attack(monsters.at(rand() % 4));
					break;
				case 1:
					randomize = rand() % 4;
					while (heroes.at(randomize)->is_Alive() == false) {
						randomize = rand() % 4;
						if (heroes.at(0)->are_allDead(heroes) == true)
							break;
					}
					units.at(i)->attack(heroes.at(rand() % 4));
					break;
				case 2:
					units.at(i)->divine_Comfort(units);
				}
			}
			else if (units.at(i)->get_class() == "soldier") {
				while (true) {
					randomize = rand() % 4;
					if (units.at(i)->get_pos() < 4 && heroes.at(randomize)->get_pos() < 4) {
						
						while (heroes.at(randomize)->is_Alive() == false && heroes.at(randomize)->get_pos() == 4) {
							randomize = rand() % 4;
							if (heroes.at(0)->are_allDead(heroes) == true)
								break;
						}
						units.at(i)->attack(heroes.at(randomize));
						break;
					}
					else if (units.at(i)->get_pos() == 4 && heroes.at(randomize)->get_pos() <3) {
						
						while (heroes.at(randomize)->is_Alive() == false && heroes.at(randomize)->get_pos() < 4) {
							randomize = rand() % 4;
							if (heroes.at(0)->are_allDead(heroes) == true)
								break;
						}
						units.at(i)->attack(heroes.at(randomize));
						monsters.at(0)->stumble(monsters);
						break;
					}
				}
			}
			else {
				attack_selector = rand() % 2;
				while (true) {
					if (attack_selector == 1) {
						randomize = rand() % 4;
						while (heroes.at(randomize)->is_Alive() == false) {
							randomize = rand() % 4;
							if (heroes.at(0)->are_allDead(heroes) == true)
								break;
						}
						units.at(i)->attack(heroes.at(rand() % 4));
						break;
					}
					else if (units.at(i)->get_pos() >= 3 && attack_selector==0) {
						randomize = rand() % 4;
						while (monsters.at(randomize)->is_Alive() == false) {
							randomize = rand() % 4;
							if (monsters.at(0)->are_allDead(monsters) == true)
								break;
						}
						units.at(i)->attack(monsters.at(rand() % 4));
						break;
					}
					else {
						attack_selector = 1;
					}
				}
			}
			std::cout << "" << std::endl;
		}
		for (int i = 0; i < 4; i++) {
			heroes.at(i)->check_hp();
		}
		std::cout << "" << std::endl;
		for (int i = 0; i < 4; i++) {
			monsters.at(i)->check_hp();
		}
		std::cout << "" << std::endl;
		if (monsters.at(0)->are_allDead(monsters) == true) {
			std::cout << "Game Over Heroes Won" << std::endl;
			break;
		}
		if (heroes.at(0)->are_allDead(heroes) == true) {
			std::cout << "Game Over Monsters Won" << std::endl;
			break;
		}
		std::cout << "///////////////////////////////////" << std::endl;
		std::cout << "Round " << round << " is Over!" << std::endl;
		std::cout << "///////////////////////////////////" << std::endl;
		std::cout << "" << std::endl;
		round++;

	}
}

int main() {
	srand(time(NULL));
	
	Hero* pCrusader1;
	Hero* pCrusader2;
	Hero* pVestal1;
	Hero* pVestal2;

	Monster* pBoneDefender1;
	Monster* pBoneSoldier1;
	Monster* pBoneDefender2;
	Monster* pBoneSoldier2;

	Crusader Crusader1("Crusader1", 4), Crusader2("Crusader2", 1);
	Vestal Vestal1("Vestal1", 3), Vestal2("Vestal2", 2);
	
	Bone_Defender Bone_Defender1("BoneDefender1",1), Bone_Defender2("BoneDefender2", 3);
	Bone_Soldier Bone_Soldier1("BoneSoldier1", 2), Bone_Soldier2("BoneSoldier2", 4);

	pCrusader1 = &Crusader1;
	pCrusader2 = &Crusader2;
	pVestal1 = &Vestal1;
	pVestal2 = &Vestal2;

	pBoneDefender1 = &Bone_Defender1;
	pBoneDefender2 = &Bone_Defender2;
	pBoneSoldier1 = &Bone_Soldier1;
	pBoneSoldier2 = &Bone_Soldier2;


	std::vector<Hero*>heroes;
	heroes.push_back(pCrusader1);
	heroes.push_back(pCrusader2);
	heroes.push_back(pVestal1);
	heroes.push_back(pVestal2);

	std::vector<Monster*>monsters;
	monsters.push_back(pBoneDefender1);
	monsters.push_back(pBoneSoldier1);
	monsters.push_back(pBoneDefender2);
	monsters.push_back(pBoneSoldier2);

	std::vector<Unit*>units;
	units.push_back(pCrusader1);
	units.push_back(pCrusader2);
	units.push_back(pVestal1);
	units.push_back(pVestal2);
	units.push_back(pBoneDefender1);
	units.push_back(pBoneSoldier1);
	units.push_back(pBoneDefender2);
	units.push_back(pBoneSoldier2);

	GAMELOGIC(heroes, monsters,units);


	return 0;
}