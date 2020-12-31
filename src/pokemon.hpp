#include <fstream>
#include <vector>
#include <iostream>
#include "./move.hpp"
using namespace std;

struct moveStruct {
	Move move;
	int level; //level at which the pokemon learns the move
	bool stab; //if this pokemon gets STAB using this move (same type attack bonus)
	bool newM = false; //true if the move has been added to drayano's rom hack
	bool learn = false; //the need for this variable is a bit weird. some pokemon learn more moves than others. the array is set to 30 moves.
				//but not all pokemon learn 30 moves. most learn way less. so i set learn to true if alllevelmoves[i].movesstruct.learn
				//is true and otherwise its not even a real move so who cares
};
struct tmMoveStruct {
	string tmNo;
	Move move;
	bool canLearn = false;
	bool stab = false;
	bool newM = false;
};

class Pokemon{

private:
	int dexno;
	string name;
	
	string oldType1;
	string oldType2;
	string newType1;
	string newType2;
	bool typeChanged = false; //has the type been altered?
	
	string oldAbility1;
	string oldAbility2;
	string newAbility1;
	string newAbility2;
	bool abilityChanged = false; //has the ability been altered?
	
	int oldHp;
	int oldAttack;
	int oldDefense;
	int oldSpAttack;
	int oldSpDefense;
	int oldSpeed;
	int oldBst;
	int newHp;
	int newAttack;
	int newDefense;
	int newSpAttack;
	int newSpDefense;
	int newSpeed;
	int newBst;
	bool statChanged = false; //have any of the stats been changed?clTabCtrl
	
	string evolution = "no changes"; //since evolution data is only in the updated file, if it has any data it has been changed.
	
	string experience;

	string uncommonHeldItem;
	string rareHeldItem;
	string alwaysHeldItem;
	tmMoveStruct allTmMoves[100];
	moveStruct allLevelMoves[30];

	string item; //only used for boss trainers
	string ability; //only used for boss trainers
	string nature; //only used for boss trainers
	Move bossTrainerMoves[4]; //only used for boss trainers

public:
	/*Default constructor
	 * Returns nothing
	 * Parameters: None
	 * Constructs a pokemon
	 */
	Pokemon();
	/* 8-arg Constructor
	* Returns nothing
	* Takes a dexno, name, hp, attack, defense, spattack, spdefense, speed, bst, experience, abilities, type1, type2, changed (if the pokemon has been changed or not)
	* Constructs a pokemon
	*/
	Pokemon(int, string, string, string, string, string, bool, string, string, string, string, bool, int, int, int, int, int, int, int,
			int, int, int, int, int, int, int, bool, string, string);
	/*Destructor
	 * Destroys a pokemon
	 */
	virtual ~Pokemon(){};
	//Pokemon& operator=(const Pokemon&);
	bool operator<(const Pokemon&)const;
	bool operator==(const Pokemon&)const;
	bool operator>(const Pokemon&)const;
	friend ostream& operator<<(ostream&, const Pokemon&);

	//getters
	int getDexno()const{return dexno;};
	string getName()const{return name;};
	
	string getOldType1()const{return oldType1;};
	string getOldType2()const{return oldType2;};
	
	string getNewType1()const{return newType1;};
	string getNewType2()const{return newType2;};
	
	string getOldAbility1()const{return oldAbility1;};
	string getOldAbility2()const{return oldAbility2;};
	
	string getNewAbility1()const{return newAbility1;};
	string getNewAbility2()const{return newAbility2;};

	int getOldHP()const{return oldHp;};
	int getOldAttack()const{return oldAttack;};
	int getOldDefense()const{return oldDefense;};
	int getOldSpAttack()const{return oldSpAttack;};
	int getOldSpDefense()const{return oldSpDefense;};
	int getOldSpeed()const{return oldSpeed;};
	int getOldBST()const{return oldBst;};
	
	int getNewHP()const{return newHp;};
	int getNewAttack()const{return newAttack;};
	int getNewDefense()const{return newDefense;};
	int getNewSpAttack()const{return newSpAttack;};
	int getNewSpDefense()const{return newSpDefense;};
	int getNewSpeed()const{return newSpeed;};
	int getNewBST()const{return newBst;};
	
	string getExperience()const{return experience;};
	string getEvolution()const{return evolution;};
	
	string getUncommonHeldItem()const{return uncommonHeldItem;};
	string getRareHeldItem()const{return rareHeldItem;};
	string getAlwaysHeldItem()const{return alwaysHeldItem;};

	bool getStatChanged()const{return statChanged;};
	bool getTypeChanged()const{return typeChanged;};
	bool getAbilityChanged()const{return abilityChanged;};
	moveStruct& getLevelMoves(int i){return allLevelMoves[i];};
	tmMoveStruct& getTmMoves(int i){return allTmMoves[i];};
	//setter declarations
	void setDexno(int d){
		dexno = d;
	}
	void setName(string n){
		name = n;
	}
	
	void setOldType1(string t1){
		oldType1 = t1;
	}
	void setOldType2(string t2){
		oldType2 = t2;
	}
	
	void setNewType1(string t1){
		newType1 = t1;
		typeChanged = true;
	}
	void setNewType2(string t2){
		newType2 = t2;
		typeChanged = true;
	}
	void setTypeChanged(bool tc){
		typeChanged = tc;
	}
	
	void setOldAbility1(string ab1){
		oldAbility1 = ab1;
	}
	void setOldAbility2(string ab2){
		oldAbility2 = ab2;
	}

	void setNewAbility1(string ab1){
		newAbility1 = ab1;
	}
	void setNewAbility2(string ab2){
		newAbility2 = ab2;
	}
	void setAbilityChanged(bool abc){
		abilityChanged = abc;
	}
	
	void setOldHP(int h){
		oldHp = h;
	}
	void setOldAttack(int a){
		oldAttack = a;
	}
	void setOldDefense(int d){
		oldDefense = d;
	}
	void setOldSpAttack(int spa){
		oldSpAttack = spa;
	}
	void setOldSpDefense(int spd){
		oldSpDefense = spd;
	}
	void setOldSpeed(int s){
		oldSpeed = s;
	}
	void setOldBST(int b){
		oldBst = b;
	}

	void setNewHP(int h){
		newHp = h;
	}
	void setNewAttack(int a){
		newAttack = a;
	}
	void setNewDefense(int d){
		newDefense = d;
	}
	void setNewSpAttack(int spa){
		newSpAttack = spa;
	}
	void setNewSpDefense(int spd){
		newSpDefense = spd;
	}
	void setNewSpeed(int s){
		newSpeed = s;
	}
	void setNewBST(int b){
		newBst = b;
	}
	void setStatChanged(bool sc){
		statChanged = sc;
	}
	
	void setEvolution(string e){
		evolution = e;
	}
	
	void setExperience(string e){
		if(e == "Slow" || e == "Medium Slow" || e == "Medium Fast" || e == "Fast" || e == "Fluctuating" || e == "Erratic"){
			experience = e;
		}
		else{
			experience = "Error";
		}
	}
	void setUncommonHeldItem(string i){
		uncommonHeldItem = i;
	}
	void setRareHeldItem(string i){
		rareHeldItem = i;
	}
	void setAlwaysHeldItem(string i){
		alwaysHeldItem = i;
	}
	void clearPokemon();
};
multimap<int, Pokemon> readInsertTMMoves(multimap<int, Pokemon>&, unordered_map<string, Move>&);
multimap<int, Pokemon> readPokemonGmf(string, unordered_map<string, Move>&);
multimap<int, Pokemon> readPokemonDry(string, multimap<int, Pokemon>&, unordered_map<string, Move>&);