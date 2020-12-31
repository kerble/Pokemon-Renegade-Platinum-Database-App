#include "./pokemon.hpp"
#include <set>
struct commonTrainerStruct{ //declaration for map of trainers below
	string name;
	unordered_multimap<string, int> firstTeam; //very small map of pokemon, no more than 10
	unordered_multimap<string, int> secondTeam;
	unordered_multimap<string, int> thirdTeam;
	unordered_multimap<string, int> fourthTeam;
	unordered_multimap<string, int> fifthTeam;
	unordered_multimap<string, int> sixthTeam; //no trainer has 6 rematches, but each team is used to discern when the rematch is available
};
struct itemStruct{ 
	string name;
	string method;
	bool newLocation;
};
struct bossPokemon{
	string name;
	string item;
	string nature;
	string ability;
	string moves[4];
	int level;
};
struct bossTrainer{
	string name;
	vector<bossPokemon> team;
};
class Route{
private: //private data has to be first because trainerstruct is declared here
	string fullName, mainName, sectionName; //name of route
	bool hasSubsections = false;
	int walkingLevelHigh;
	int walkingLevelLow;
	int surfingLevelHigh;
	int surfingLevelLow;
	int honeyLevel;
    map<string, int> morningMap;
    map<string, int> dayMap;
    map<string, int> nightMap;
    map<string, int> surfMap;
    map<string, int> oldRodMap;
    map<string, int> goodRodMap;
    map<string, int> superRodMap;
    map<string, int> pokeRadarMap;
    map<string, int> honeyTreeMap;

	vector<itemStruct> itemVec;
	unordered_multimap<string, commonTrainerStruct> trainerMap;
	vector<bossTrainer> bossTrainers;
public:
	/*Default constructor
	 * Returns nothing
	 * Parameters: None
	 * Constructs a route
	 */
	Route();
	/* 4-arg Constructor
	* Returns nothing
	* Takes stuff and constructs a route
	* Constructs a route
	*/
	Route(string, multimap<int, Pokemon>, unordered_map<string, itemStruct>, unordered_map<string, commonTrainerStruct>);
	// /* Copy Constructor
	// * Returns nothing
	// * Parameters: A constant route by reference
	// * Copies the route
	// */
	// Route(const Route&); 
	/*Destructor
	  * Destroys a route
	  */
	virtual ~Route(){};

	//getters
	string getFullName()const{return(fullName);}
	string getMainName()const{return(mainName);}
	string getSectionName()const{return(sectionName);}
	map<string, int>& getMorningMap(){return(morningMap);}
	map<string, int>& getDayMap(){return(dayMap);}
	map<string, int>& getNightMap(){return(nightMap);}
	map<string, int>& getSurfMap(){return(surfMap);}
	map<string, int>& getOldRodMap(){return(oldRodMap);}
	map<string, int>& getGoodRodMap(){return(goodRodMap);}
	map<string, int>& getSuperRodMap(){return(superRodMap);}
	map<string, int>& getPokeRadarMap(){return(pokeRadarMap);}
	map<string, int>& getHoneyTreeMap(){return(honeyTreeMap);}
	unordered_multimap<string, commonTrainerStruct>& getTrainerMap(){return(trainerMap);}
	vector<itemStruct>& getItems(){return itemVec;}
	vector<bossTrainer>& getBosses(){return bossTrainers;}
	//setters
	void setFullName(string fn){
		fullName = fn;
	}
	void setMainName(string mn){
		mainName = mn;
	}
	void setSectionName(string sn){
		sectionName = sn;
	}
	void setMorningMap(map<string, int> mm){
		morningMap = mm;
	}
	void setDayMap(map<string, int> dm){
		dayMap = dm;
	}
	void setNightMap(map<string, int> nm){
		nightMap = nm;
	}
	void setSurfMap(map<string, int> sm){
		surfMap = sm;
	}
	void setOldRodMap(map<string, int> orm){
		oldRodMap = orm;
	}
	void setGoodRodMap(map<string, int> grm){
		goodRodMap = grm;
	}
	void setSuperRodMap(map<string, int> srm){
		superRodMap = srm;
	}
	void setPokeRadarMap(map<string, int> prm){
		pokeRadarMap = prm;
	}
	void setHoneyTreeMap(map<string, int> htm){
		honeyTreeMap = htm;
	}
	void setTrainerMap(unordered_multimap<string, commonTrainerStruct> tm){
		trainerMap = tm;
	}
	void setHasSubsections(bool hss){
		hasSubsections = hss;
	}
	void setWalkingLevelLow(int wll){
		walkingLevelLow = wll;
	}
	void setWalkingLevelHigh(int wlh){
		walkingLevelHigh = wlh;
	}
	void setSurfingLevelLow(int sll){
		surfingLevelLow = sll;
	}
	void setSurfingLevelHigh(int slh){
		surfingLevelHigh = slh;
	}
	void setHoneyLevel(int hl){
		honeyLevel = hl;
	}
	void insertItems(itemStruct item){
		itemVec.push_back(item);
	}
	void insertBoss(bossTrainer boss){
		bossTrainers.push_back(boss);
	}
	friend ostream& operator<<(ostream&, const Route&);
	void clearRoute();
};
map<string, int> insertWild(string);
unordered_multimap<string, int> insertTrainerTeam(string);
map<string, Route*> readRoute(string);
map<string, Route*> readTrainers(string, map<string, Route*>&);
map<string, Route*> insertItems(string, map<string, Route*> &);
map<string, Route*> insertBossBattles(string, map<string, Route*> &);