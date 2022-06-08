#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <time.h>



//BASE SKILLS
class Skill {
protected:
	
};

class MoveSkill {
protected:
	int move;
	MoveSkill() :move(0) {}

};

//////////////////////////////////////////////////////////////////////

//ATTACK SKILLS
class AttackSkill : public Skill, public MoveSkill {
protected:
	int dmgMod, baseAcc, critMod, stunBase;
	AttackSkill() :dmgMod(0), baseAcc(0), critMod(0), stunBase(0) {}
	int get_dmgMod() { return dmgMod; };
	int get_baseAcc() { return baseAcc; };
	int get_critMod() { return critMod; };
	int get_stunBase() { return stunBase; };

	

};

//CRUSADER ATTACK
class Smite : public AttackSkill {
protected:
	Smite() {
		dmgMod = 0;
		baseAcc = 85;
		critMod = 0;
		stunBase = 0;
	}
};

class Stunning_Blow : public AttackSkill {
protected:
	Stunning_Blow() {
		dmgMod = -50;
		baseAcc = 90;
		critMod = 0;
		stunBase = 100;
	}

};

class Holy_Lance : public AttackSkill {
protected:
	Holy_Lance() {
		dmgMod = 0;
		baseAcc = 85;
		critMod = 6;
		stunBase = 0;
	}
};

//VESTAL ATTACK
class Mace_Bash : public AttackSkill {
protected:
	Mace_Bash() {
		dmgMod = 0;
		baseAcc = 85;
		critMod = 0;
		stunBase = 0;
	}
};

class Dazzling_Light : public AttackSkill {
protected:
	Dazzling_Light() {
		dmgMod = -75;
		baseAcc = 90;
		critMod = 5;
		stunBase = 100;
	}
};

//BONE SOLDIER ATTACK
class Graveyard_Slash : public AttackSkill {
protected:
	Graveyard_Slash() {
		dmgMod = 0;
		baseAcc = 85;
		critMod = 6;
		stunBase = 0;
	}
};

class Graveyard_Stumble : public AttackSkill {
protected:
	Graveyard_Stumble() {
		dmgMod = -50;
		baseAcc = 45;
		critMod = 0;
		stunBase = 0;
		move = 1;
	}
};

//BONE DEFENDER ATTACK
class Axeblade : public AttackSkill {
protected:
	Axeblade() {
		dmgMod = 0;
		baseAcc = 72;
		critMod = 6;
		stunBase = 0;
	}
};

class Dead_Weight : public AttackSkill {
protected:
	Dead_Weight() {
		dmgMod = -25;
		baseAcc = 82;
		critMod = 6;
		stunBase = 100;
	}
};

//////////////////////////////////////////////////////////////////////

//UTILITY SKILLS
class UtilitySkill : public Skill {
protected:
	int heal, protection;
	UtilitySkill() :heal(0), protection(0) {}
};

//CRUSADER UTILITY
class Bulwark_of_Faith : public UtilitySkill {
protected:
	Bulwark_of_Faith() {
		protection = 20;
	}
	void Bulwark(int prot) {
		prot += protection;
	}
};

//VESTAL UTILITY
class Divine_Grace : public UtilitySkill {
protected:
	Divine_Grace() {
		heal = rand()%1 +4;
	}
	int graced() {
		return heal;
	}
};

class Divine_Comfort : public UtilitySkill {
protected:
	Divine_Comfort() {
		heal = rand()%3+1;
	}
	int comforted() {
		return heal;
	}
};

//BONE DEFENDER UTILITY
class Knitting_Bones : public UtilitySkill {
protected:
	Knitting_Bones() {
		heal = rand()%2+2;
	}
	int knitting() {
		return heal;
	}
};

//////////////////////////////////////////////////////////////////////
//UNITS//
//////////////////////////////////////////////////////////////////////

class Unit {
protected:
	int unit_position,Max_HP, hp, dodge, prot, speed, accMod, baseCrit, minDmg, maxDmg, stunResist, speed_turn;
	std::string name, class_n;
	bool stunned, is_hero;
	Unit():name(""),class_n(""),stunned(false),unit_position(0),Max_HP(0),hp(0),dodge(0),prot(0),speed(0),accMod(0),baseCrit(0),minDmg(0),maxDmg(0),stunResist(0),is_hero(false),speed_turn(0)
	{}
public:
	std::string get_name() {
		return name;
	}
	std::string get_class() {
		return class_n;
	}
	int get_hp() {
		return hp;
	}
	int get_pos() {
		return unit_position;
	}
	void set_pos() {
		unit_position -= 1;
		if (unit_position == 0)
			unit_position = 4;
	}

	bool is_Hero() {
		return is_hero;
	}
	bool is_Alive() {
		if (hp > 0) {
			return true;
		}
		else {
			return false;
		}
	}
	void check_hp() {
		if (hp > 0) {
			std::cout << name << " is at " << hp << " Health!" << std::endl;
		}
		else {
			std::cout << name << " is dead" << std::endl;
		}
	}
	bool is_Stunned() {
		if (stunned == true)
			return true;
		else
			return false;
	}
	
	void calculate_StunChance(int stunBase, Unit* targetUnit, bool is_crit) {
		int stunChance = stunBase - targetUnit->stunResist;
		if (targetUnit->is_Stunned()== true){
			std::cout << targetUnit->name << " is Stunned!!" << std::endl;
			targetUnit->stunned = true;
		}
		else {
			if (is_crit == true)
				stunChance = 20 + stunBase - targetUnit->stunResist;

			if (stunChance >= rand() % 101) {
				std::cout << targetUnit->name << " is Stunned!!" << std::endl;
				targetUnit->stunned = true;
			}
			else
				std::cout << "Stun Resisted!!" << std::endl;
		}
	}

	bool calculate_HitChance(int baseAcc,Unit* targetUnit) {
		int hit_chance = baseAcc + accMod - targetUnit->dodge;

		if (hit_chance >= rand()%101 ) {
			return true;

		}
		else {
			return false;
		}
	}
	bool calculate_CritChance(int critMod) {
		int crit_Chance = baseCrit + critMod;
		if (crit_Chance >= rand() % 101)
			return true;
		else
			return false;

	}

	int calculate_Dmg(int dmgMod, Unit *targetUnit,bool is_crit) {
		int dmg = rand() % (maxDmg - minDmg + 1) + minDmg;
		double rawDmg = dmg * (100 + dmgMod) / 100;
		int actualDmg = rawDmg - rawDmg * (targetUnit->prot / 100);
		if (is_crit == true) {
			std::cout << "Critical!" << std::endl;
			return (actualDmg * 1.5);
		}
		else
			return actualDmg;
	}

	void get_Dmged(int actualDmg) {
		
		if (actualDmg >= hp)
			hp = 0;
		else
			hp = hp - actualDmg;
		std::cout << "HIT!!! dmg: " << actualDmg << std::endl;
		
	}

	void get_Healed(int heal_rate) {
		hp += heal_rate;
		std::cout << "HEALED! : " << heal_rate << std::endl;
		if (hp > Max_HP)
			hp = Max_HP;
	}
	

	void set_speed_turn(int i) {
		speed_turn = i;
	}

	int get_speed(){
		return speed;
	}

	int get_speed_turn() {
		return speed_turn;
	}

	virtual void divine_Comfort(std::vector<Unit*>& heroes){}

	virtual void attack(Unit *targetUnit) {}
	
};

///////////////////////////////////////////////////////

class Hero : public Unit {
protected:
	int deathBlowResist;
public:
	bool are_allDead(std::vector<Hero*>& heroes) {
		if (heroes.at(0)->hp == 0 && heroes.at(1)->hp == 0 && heroes.at(2)->hp == 0 && heroes.at(3)->hp == 0) {
			return true;
		}
		else
			return false;
	}
	void lance(std::vector<Hero*>& heroes) {
		for (int i = 0; i < 4; i++) {
			heroes.at(i)->set_pos();
		}
	}
	
};

class Crusader : public Hero, public Smite, public Stunning_Blow, public Holy_Lance, public Bulwark_of_Faith {
public:
	Crusader(std::string unit_name, int pos){
		name = unit_name;
		unit_position = pos;
		hp = 33;
		Max_HP = 33;
		dodge = 5;
		prot = 0;
		speed = 1;
		speed_turn = 0;
		accMod = 0;
		baseCrit = 3;
		minDmg = 6;
		maxDmg = 12;
		deathBlowResist = 67;
		stunResist = 40;
		stunned = false;
		is_hero = true;
		class_n = "crusader";
		
	}

	int round_count = 0;
	void attack(Unit *targetUnit) {
		if (this->is_Alive() == true && this->is_Stunned() == false && targetUnit->is_Alive() == true) {
			if (unit_position <= 2 && targetUnit->get_pos()<=2) {
				unsigned int attack_selector =rand() % 3;
				switch (attack_selector) {
				case 0:
					if (this->calculate_HitChance(Smite::baseAcc,targetUnit) == true) {
						std::cout << this->name << " used Smite on " << targetUnit->get_name() << std::endl;
						targetUnit->get_Dmged(this->calculate_Dmg(Smite::dmgMod,targetUnit,this->calculate_CritChance(Smite::critMod)));
						if (targetUnit->get_hp() == 0)
							targetUnit->check_hp();
					}
					else
					{	
						std::cout << this->name << " used Smite on " << targetUnit->get_name() << std::endl;
						std::cout << "MISSED!!!" << std::endl;
					}
					break;
				case 1:
					if (this->calculate_HitChance(Stunning_Blow::baseAcc,targetUnit) == true) {
						std::cout << this->name << " used Stunning Blow on " << targetUnit->get_name() << std::endl;
						targetUnit->get_Dmged(this->calculate_Dmg(Stunning_Blow::dmgMod, targetUnit, this->calculate_CritChance(Stunning_Blow::critMod)));
						this->calculate_StunChance(Stunning_Blow::stunBase, targetUnit, this->calculate_CritChance(Stunning_Blow::critMod));
						if (targetUnit->get_hp() == 0)
							targetUnit->check_hp();

					}
					else
					{	
						std::cout << this->name << " used Stunning Blow on " << targetUnit->get_name() << std::endl;
						std::cout << "MISSED!!!" << std::endl;
					}
					break;
				case 2:
					this->Bulwark(this->prot);
					round_count = 0;
					std::cout << name << " used Bulwark of Faith" << std::endl;
					break;
				}
			}
			else {
				if (this->calculate_HitChance(Holy_Lance::baseAcc,targetUnit) == true) {
					std::cout << this->name << " used Holy Lance on " << targetUnit->get_name() << std::endl;
					targetUnit->get_Dmged(this->calculate_Dmg(Holy_Lance::dmgMod, targetUnit, this->calculate_CritChance(Holy_Lance::critMod)));
					if (targetUnit->get_hp() == 0)
						targetUnit->check_hp();

				}
				else
				{	
					std::cout << this->name << " used Holy Lance on " << targetUnit->get_name() << std::endl;
					std::cout << "MISSED!!!" << std::endl;
				}
			}
		}
		else {
			if(this->is_Stunned()==true)
				std::cout << this->name << " is Stunned!!!" << std::endl;
			stunned = false;
		}
		if (round_count == 3) {
			prot = 0;
			round_count = 0;
		}
		round_count++;
	}
};

class Vestal : public Hero, public Mace_Bash, public Dazzling_Light, public Divine_Comfort, public Divine_Grace {
public:
	Vestal(std::string unit_name,int pos) {
		unit_position = pos;
		name = unit_name;
		hp = 24;
		Max_HP = 24;
		dodge = 0;
		prot = 0;
		speed = 4;
		speed_turn = 0;
		accMod = 0;
		baseCrit = 1;
		minDmg = 4;
		maxDmg = 8;
		deathBlowResist = 77;
		stunResist = 30;
		stunned = false;
		is_hero = true;
		class_n = "vestal";
	}


	void attack(Unit* targetUnit) {
		if (this->is_Alive() == true && this->is_Stunned() == false && targetUnit->is_Alive() == true) {
			if (unit_position == 1 && targetUnit->is_Hero() == false) {
				if (this->calculate_HitChance(Mace_Bash::baseAcc,targetUnit) == true) {
					std::cout << this->name << " used Mace Bash on " << targetUnit->get_name() << std::endl;
					targetUnit->get_Dmged(this->calculate_Dmg(Mace_Bash::dmgMod, targetUnit,this->calculate_CritChance(Mace_Bash::critMod)));
					if (targetUnit->get_hp() == 0)
						targetUnit->check_hp();
				}
				else
				{	
					std::cout << this->name << " used Mace Bash on " << targetUnit->get_name() << std::endl;
					std::cout << "MISSED!!!" << std::endl;
				}
			}
			else if (unit_position == 2) {
				if (targetUnit->is_Hero() == false) {
					int attack_selector = rand() % 3;
					switch (attack_selector) {
					case 0:
						if (this->calculate_HitChance(Mace_Bash::baseAcc, targetUnit) == true) {
							std::cout << this->name << " used Mace Bash on " << targetUnit->get_name() << std::endl;
							targetUnit->get_Dmged(this->calculate_Dmg(Mace_Bash::dmgMod, targetUnit, this->calculate_CritChance(Mace_Bash::critMod)));
							if (targetUnit->get_hp() == 0)
								targetUnit->check_hp();
						}
						else
						{
							std::cout << this->name << " used Mace Bash on " << targetUnit->get_name() << std::endl;
							std::cout << "MISSED!!!" << std::endl;
						}
						break;
					case 1:
						if (this->calculate_HitChance(Dazzling_Light::baseAcc, targetUnit) == true) {
							std::cout << this->name << " used Dazzling Light on " << targetUnit->get_name() << std::endl;
							targetUnit->get_Dmged(this->calculate_Dmg(Dazzling_Light::dmgMod, targetUnit, this->calculate_CritChance(Dazzling_Light::critMod)));
							this->calculate_StunChance(Dazzling_Light::stunBase, targetUnit, this->calculate_CritChance(Dazzling_Light::critMod));
							if (targetUnit->get_hp() == 0)
								targetUnit->check_hp();

						}
						else
						{
							std::cout << this->name << " used Dazzling Light on " << targetUnit->get_name() << std::endl;
							std::cout << "MISSED!!!" << std::endl;
						}
						break;
					}
				}
				else{
					std::cout << this->name << " used Divine Grace on " << targetUnit->get_name() << std::endl;
					targetUnit->get_Healed(this->graced());
					}
			}
			else {
				if (targetUnit->is_Hero()==false) {
					if (this->calculate_HitChance(Dazzling_Light::baseAcc, targetUnit) == true) {
						std::cout << this->name << " used Dazzling Light on " << targetUnit->get_name() << std::endl;
						targetUnit->get_Dmged(this->calculate_Dmg(Dazzling_Light::dmgMod, targetUnit, this->calculate_CritChance(Dazzling_Light::critMod)));
						this->calculate_StunChance(Dazzling_Light::stunBase, targetUnit, this->calculate_CritChance(Dazzling_Light::critMod));
						if (targetUnit->get_hp() == 0)
							targetUnit->check_hp();
					}
					else
					{
						std::cout << this->name << " used Dazzling Light on " << targetUnit->get_name() << std::endl;
						std::cout << "MISSED!!!" << std::endl;
					}
				}
				else {	
					std::cout << this->name << " used Divine Grace on " << targetUnit->get_name() << std::endl;
					targetUnit->get_Healed(this->graced());	
				}
			}
		}
		else {
			if (this->is_Stunned() == true)
				std::cout << this->name << " is Stunned!!!" << std::endl;
			stunned = false;
		}
	}
	void divine_Comfort(std::vector<Unit*>& units) {
		std::cout << this->name << " Used Divine Comfort" << std::endl;
		int random = rand() % 3 + 1;
		for (int i = 0; i < 8; i++) {
			if (units.at(i)->is_Hero() == true) {
				std::cout << units.at(i)->get_name() << " ";
				units.at(i)->get_Healed(random);
			}
		}
	}
};

///////////////////////////////////////////////////////

class Monster : public Unit {
public:
	bool are_allDead(std::vector<Monster*>& monsters) {
		if (monsters.at(0)->hp == 0 && monsters.at(1)->hp == 0 && monsters.at(2)->hp == 0 && monsters.at(3)->hp == 0) {
			return true;
		}
		else
			return false;

	}
	void stumble(std::vector<Monster*>& monsters) {
		for (int i = 0; i < 4; i++) {
			monsters.at(i)->set_pos();
		}
	}
};

class Bone_Soldier : public Monster, public Graveyard_Slash, public Graveyard_Stumble {
public:
	Bone_Soldier(std::string unit_name,int pos) {
		name = unit_name;
		unit_position = pos;
		hp = 35;
		Max_HP = 35;
		dodge = 10;
		prot = 15;
		speed = 2;
		speed_turn = 0;
		accMod = 0;
		baseCrit = 0;
		minDmg = 3;
		maxDmg = 8;
		stunResist = 25;
		stunned = false;
		is_hero = false;
		class_n = "soldier";
	}

	void attack(Unit* targetUnit) {
		if (this->is_Alive() == true) {
			if (unit_position <= 3 &&(targetUnit->get_pos() == 1 || targetUnit->get_pos() == 2 || targetUnit->get_pos() == 3)) {


				if (this->calculate_HitChance(Graveyard_Slash::baseAcc,targetUnit) == true) {
					std::cout << this->name << " used Graveyard Slash on " << targetUnit->get_name() << std::endl;
					targetUnit->get_Dmged(this->calculate_Dmg(Graveyard_Slash::dmgMod, targetUnit, this->calculate_CritChance(Graveyard_Slash::critMod)));
					if (targetUnit->get_hp() == 0)
						targetUnit->check_hp();
				}
				else
				{	
					std::cout << this->name << " used Graveyard Slash on " << targetUnit->get_name() << std::endl;
					std::cout << "MISSED!!!" << std::endl;
				}

			}

			else if(unit_position == 4 && (targetUnit->get_pos() == 1 || targetUnit->get_pos() == 2)) {
				if (this->calculate_HitChance(Graveyard_Stumble::baseAcc,targetUnit) == true) {
					std::cout << this->name << " used Graveyard Stumble on " << targetUnit->get_name() << std::endl;
					targetUnit->get_Dmged(this->calculate_Dmg(Graveyard_Stumble::dmgMod, targetUnit, this->calculate_CritChance(Graveyard_Stumble::critMod)));
					if (targetUnit->get_hp() == 0)
						targetUnit->check_hp();

				}
				else
				{	
					std::cout << this->name << " used Graveyard Stumble on " << targetUnit->get_name() << std::endl;
					std::cout << "MISSED!!!" << std::endl;
				}
			}
		}
		else {
			if (this->is_Stunned() == true)
				std::cout << this->name << " is Stunned!!!" << std::endl;
			stunned = false;
		}
	}
};

class Bone_Defender : public Monster,public Axeblade, public Dead_Weight,public Knitting_Bones {
public:
	Bone_Defender(std::string unit_name ,int pos) {
		name = unit_name;
		unit_position = pos;
		hp = 22;
		Max_HP = 22;
		dodge = 8;
		prot = 45;
		speed = 1;
		speed_turn = 0;
		accMod = 0;
		baseCrit = 0;
		minDmg = 2;
		maxDmg = 4;
		stunResist = 45;
		stunned = false;
		is_hero = false;
		class_n = "defender";
	}
	void attack(Unit* targetUnit) {
		if (this->is_Alive() == true&& this->is_Stunned() == false) {
			if (unit_position < 3 && targetUnit->get_pos()==1 || targetUnit->get_pos() == 2 && targetUnit->is_Hero() == true) {
				int attack_selector = rand() % 3;
				switch (attack_selector) {
				case 0:
					if (this->calculate_HitChance(Axeblade::baseAcc, targetUnit) == true) {
						std::cout << this->name << " used Axeblade on " << targetUnit->get_name() << std::endl;
						targetUnit->get_Dmged(this->calculate_Dmg(Axeblade::dmgMod, targetUnit, this->calculate_CritChance(Axeblade::critMod)));
						if (targetUnit->get_hp() == 0)
							targetUnit->check_hp();
					}
					else
					{
						std::cout << this->name << " used Axeblade on " << targetUnit->get_name() << std::endl;
						std::cout << "MISSED!!!" << std::endl;
					}
					break;
				case 1:
					if (this->calculate_HitChance(Dead_Weight::baseAcc, targetUnit) == true) {
						std::cout << this->name << " used Dead Weight on " << targetUnit->get_name() << std::endl;
						targetUnit->get_Dmged(this->calculate_Dmg(Dead_Weight::dmgMod, targetUnit, this->calculate_CritChance(Dead_Weight::critMod)));
						this->calculate_StunChance(Dead_Weight::stunBase, targetUnit, this->calculate_CritChance(Dead_Weight::critMod));
						if (targetUnit->get_hp() == 0)
							targetUnit->check_hp();

					}
					else
					{
						std::cout << this->name << " used Dead Weight on " << targetUnit->get_name() << std::endl;
						std::cout << "MISSED!!!" << std::endl;
					}
					break;
				}
			}
			else if (unit_position == 3 && targetUnit->get_pos()==1||2 && targetUnit->is_Hero() == true) {
				if (this->calculate_HitChance(Dead_Weight::baseAcc,targetUnit) == true) {
					std::cout << this->name << " used Dead Weight on " << targetUnit->get_name() << std::endl;
					targetUnit->get_Dmged(this->calculate_Dmg(Dead_Weight::dmgMod, targetUnit, this->calculate_CritChance(Dead_Weight::critMod)));
					this->calculate_StunChance(Dead_Weight::stunBase, targetUnit, this->calculate_CritChance(Dead_Weight::critMod));
					if (targetUnit->get_hp() == 0)
						targetUnit->check_hp();

				}
				else
				{	
					std::cout << this->name << " used Dead Weight on " << targetUnit->get_name() << std::endl;
					std::cout << "MISSED!!!" << std::endl;
				}
			}
			else if (unit_position >= 3 && targetUnit->is_Hero() == false) {
				std::cout << this->name << " Used Knitting Bones on " << targetUnit->get_name() << std::endl;
				targetUnit->get_Healed(this->knitting());
			}
		}
		else {
			if (this->is_Stunned() == true)
				std::cout << this->name << " is Stunned!!!" << std::endl;
			stunned = false;
		}
	}
};

