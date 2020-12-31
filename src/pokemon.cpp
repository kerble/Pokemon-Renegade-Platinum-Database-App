#include <iostream>
#include "./pokemon.hpp"

using namespace std;

/* Default Constructor
 * Returns nothing
 * Has no parameters
 * Constructs a pokemon
 */
Pokemon::Pokemon(){}

/* 14-arg Constructor
 * Returns nothing
 * Takes an hour, minute, second, millisecond
 * Constructs a pokemon
 */
Pokemon::Pokemon(int dno, string pname, string ot1, string ot2, string nt1, string nt2, bool tc, string oab1,
				string oab2, string nab1, string nab2, bool abc, int ohp, int oatk, int odfns, int ospatk, int ospdef, int ospd, int obst,
				int nhp, int natk, int ndfns, int nspatk, int nspdef, int nspd, int nbst, bool sc, string expr, string evo){
	setDexno(dno);
	setName(pname);
	
	setOldType1(ot1);
	setOldType2(ot2);
	setNewType1(nt1);
	setNewType2(nt2);
	setTypeChanged(tc);
	
	setOldAbility1(oab1);
	setOldAbility2(oab2);
	setNewAbility1(nab1);
	setNewAbility2(nab2);
	setAbilityChanged(abc);
	
	setOldHP(ohp);
	setOldAttack(oatk);
	setOldDefense(odfns);
	setOldSpAttack(ospatk);
	setOldSpDefense(ospdef);
	setOldSpeed(ospd);
	setOldBST(obst);
	
	setNewHP(nhp);
	setNewAttack(natk);
	setNewDefense(ndfns);
	setNewSpAttack(nspatk);
	setNewSpDefense(nspdef);
	setNewSpeed(nspd);
	setNewBST(nbst);
	
	setStatChanged(sc);
	
	setExperience(expr);

	setEvolution(evo);
}

bool Pokemon::operator<(const Pokemon& p)const{
	return(this->dexno < p.dexno);
}
bool Pokemon::operator==(const Pokemon& p)const{
	return(this->dexno == p.dexno);
}
bool Pokemon::operator>(const Pokemon& p)const{
	return(this->dexno > p.dexno);
}
ostream& operator<<(ostream& outStream, const Pokemon& PK){
	//name and dexno
	
	printf("%03d - %s\n", PK.dexno, PK.name.c_str());
	// outStream << PK.dexno << " - " << PK.name << endl;

	//typing
	if(PK.typeChanged == true){
		outStream << "  Old Type: " << PK.oldType1;
		if(PK.oldType2 != ""){
			outStream << " / " << PK.oldType2;
		}
		outStream << endl << "  New Type: " << PK.newType1;
		if(PK.newType2 != "None"){
			outStream << " / " << PK.newType2;
		}
	}
	else{ //statchanged == false
		outStream << "  Type: " << PK.oldType1;
		if(PK.oldType2 != "None"){
			outStream << " / " << PK.oldType2;
		}
	}

	//ability
	if(PK.abilityChanged == true){
		outStream << endl << "  Old Ability: " << PK.getOldAbility1();
		if(PK.oldAbility2 != "None"){
			outStream << " / " << PK.getOldAbility2();
		}
		outStream << endl << "  New Ability: " << PK.getNewAbility1();
		if(PK.newAbility2 != "None"){
			outStream << " / " << PK.getNewAbility2();
		}
	}
	else{
		outStream << endl << "  Ability: " << PK.getOldAbility1();
		if(PK.oldAbility2 != "None"){
			outStream << " / " << PK.getOldAbility2();
		}
	}
	//stats
	if(PK.statChanged == true){
		outStream << endl << "  Old Base Stats: "
		<< PK.getOldHP() << " HP / " << PK.getOldAttack() << " Atk / " << PK.getOldDefense() << " Def / " << PK.getOldSpAttack()
		<< " SpAtk / " << PK.getOldSpDefense() << " SpDef / " << PK.getOldSpeed() << " Spd / " << PK.getOldBST() << " BST" << endl;
		outStream << "  New Base Stats: "
		<< PK.getNewHP() << " HP / " << PK.getNewAttack() << " Atk / " << PK.getNewDefense() << " Def / " << PK.getNewSpAttack()
		<< " SpAtk / " << PK.getNewSpDefense() << " SpDef / " << PK.getNewSpeed() << " Spd / " << PK.getNewBST() << " BST" << endl;
	}
	else{ //stats haven't been changed
		outStream << endl << "  Base Stats: "
		<< PK.getOldHP() << " HP / " << PK.getOldAttack() << " Atk / " << PK.getOldDefense() << " Def / " << PK.getOldSpAttack()
		<< " SpAtk / " << PK.getOldSpDefense() << " SpDef / " << PK.getOldSpeed() << " Spd / " << PK.getOldBST() << " BST " << endl;
	}
	//exp group
	outStream << "  Experience Leveling Group: " << PK.getExperience() << endl;
	//evolution
	if(PK.evolution != "no changes"){
		outStream << "  Evolution notes: " << PK.getEvolution() << endl;
	}
	//level up learnset
	outStream << "  Level up Learnset:" << endl;
	outStream << "      Lvl - Name            Type     Category PP Pwr Acc" << endl << endl;
	for(int i = 0; i < 29; i++){
		if(PK.allLevelMoves[i].learn == true){
			if(PK.allLevelMoves[i].newM == true)
					outStream << "     !";
			else{ //not stab
					outStream << "      ";
			}
			if(PK.allLevelMoves[i].stab == true){
				outStream << "*";
			}
			else{
				outStream << " ";
			}
			printf("%2d - ", PK.allLevelMoves[i].level);
			outStream << PK.allLevelMoves[i].move << endl;
		}
	}
	//tm learnset
	outStream << "  TM Learnset:" << endl;
	outStream << "     TM## - Name            Type     Category PP Pwr Acc" << endl << endl;
	for(int i = 0; i < 100; i++){
		if(PK.allTmMoves[i].canLearn == true){
			if(PK.allTmMoves[i].newM == true)
				outStream << "   !";
			else{ //not stab
				outStream << "    ";
			}
			if(PK.allTmMoves[i].stab == true){
				outStream << "*";
			}
			else{
				outStream << " ";
			}
			outStream << PK.allTmMoves[i].tmNo << " - " << PK.allTmMoves[i].move << endl;
		}
	}
	return(outStream);
}
/* clear pokemon
 * resets all data types to zero or none
 * returns void
 */
void Pokemon::clearPokemon(){
	setDexno(0);
	setName("None");
	setOldType1("None");
	setOldType2("None");
	setNewType1("None");
	setNewType2("None");
	setTypeChanged(false);
	setOldAbility1("None");
	setOldAbility2("None");
	setNewAbility1("None");
	setNewAbility2("None");
	setAbilityChanged(false);
	setOldHP(0);
	setOldAttack(0);
	setOldDefense(0);
	setOldSpDefense(0);
	setOldSpeed(0);
	setOldBST(0);
	setNewHP(0);
	setNewAttack(0);
	setNewDefense(0);
	setNewSpAttack(0);
	setNewSpDefense(0);
	setNewSpeed(0);
	setNewBST(0);
	setStatChanged(false);
	setEvolution("");
	setExperience("Error");
}
/* read and insert tm moves
 * reads tmlearnset.csv and inserts the tm moves from the moveMap to each pokemon
 * then returns the map of pokemon thus updating it.
 */ 
multimap<int, Pokemon> readInsertTMMoves(multimap<int, Pokemon> &pokemonMap, unordered_map<string, Move> &moveMap){
	ifstream tmMoveInput;
	tmMoveInput.open("./input/TMLearnSets.csv");
	string movelinestring, substring;
	int pokemonDexno = 1; //dexno iterates the dexnumber of the pokemon based on the line of the inputfile
	unordered_map<string, Move>::iterator moveMapIt;
	multimap<int, Pokemon>::iterator pokemonMapIt;
	Pokemon pokemon;
	Move singleMove;
	const string allTmNames[100] = {"Focus Punch","Dragon Claw","Water Pulse","Calm Mind","Roar","Toxic","Hail","Bulk Up",
	"Bullet Seed","Hidden Power","Sunny Day","Taunt","Ice Beam","Blizzard","Hyper Beam","Light Screen","Protect",
	"Rain Dance","Giga Drain","Safeguard","Frustration","Solar Beam","Iron Tail","Thunderbolt","Thunder","Earthquake",
	"Return","Dig","Psychic","Shadow Ball","Brick Break","Double Team","Reflect","Shock Wave","Flamethrower",
	"Sludge Bomb","Sandstorm","Fire Blast","Rock Tomb","Aerial Ace","Torment","Facade","Secret Power","Rest","Attract",
	"Thief","Steel Wing","Skill Swap","Snatch","Overheat","Roost","Focus Blast","Energy Ball","False Swipe","Scald",
	"Fling","Wild Charge","Endure","Dragon Pulse","Drain Punch","Will-O-Wisp","Bug Buzz","Embargo","Explosion",
	"Shadow Claw","Payback","Recycle","Giga Impact","Rock Polish","Flash","Stone Edge","Avalanche","Thunder Wave",
	"Gyro Ball","Swords Dance","Stealth Rock","Psych Up","Captivate","Dark Pulse","Rock Slide","X-Scissor","Sleep Talk",
	"Hyper Voice","Poison Jab","Dazzling Gleam","Grass Knot","Swagger","Hurricane","U-turn","Substitute","Flash Cannon",
	"Trick Room","Cut","Fly","Surf","Strength","Defog","Rock Smash","Waterfall","Rock Climb"};
	while(getline(tmMoveInput, movelinestring)){
		pokemonMapIt = pokemonMap.find(pokemonDexno);
		//cout << pokemonMapIt->first << " - " << pokemonMapIt->second.getName() << endl;
		//cout << "Can learn: " << endl;
		for(int i=0; i <= 99; i++){
			substring = movelinestring.substr(0, movelinestring.find(","));	
			if(substring == "TRUE"){
				//find the move in the map to extract power type accuracy etc data
				substring = allTmNames[i];
				moveMapIt = moveMap.find(substring);
				singleMove = moveMapIt->second;
				if(i < 9){
					pokemonMapIt->second.getTmMoves(i).tmNo = "TM0" + to_string(i+1);
				}
				else if(i < 92 && i >= 9){
					pokemonMapIt->second.getTmMoves(i).tmNo = "TM" + to_string(i+1);
				}
				else{ //i is greater than 91, aka we're in the HM sections
					pokemonMapIt->second.getTmMoves(i).tmNo = "HM0" + to_string(i-91);
				}
				pokemonMapIt->second.getTmMoves(i).move = singleMove;
				pokemonMapIt->second.getTmMoves(i).canLearn = true;
				pokemonMapIt->second.getTmMoves(i).newM = false;

				//cout << "    " << pokemonMapIt->second.allTmMoves[i].tmNo << " - ";
				//cout << pokemonMapIt->second.allTmMoves[i].move << endl;
			}
			movelinestring.erase(0, movelinestring.find(",") + 1);
		}
		pokemonDexno++; //every time we get line we go to a new pokemon
	}
	return(pokemonMap);
}
/* Read Pokemon From Gamefreak
 * Reads in a pokemon from a single getline from gmf.csv.
 * Input is formatted as such: 1,Bulbasaur,"['Overgrow', 'Chlorophyll']",45,49,49,65,65,45,318,1059860,grass,poison
 * Takes a string with the data above and a pokemon to edit and return.
 * might change later to remove pokemon in the input and just return one because that makes more sense.
 */
multimap<int, Pokemon> readPokemonGmf(string pokemontxt, unordered_map<string, Move> &moveMap){
	string pokemonlinestring, movelinestring, evolution;
	ifstream pokemoninput;
	multimap<int, Pokemon> pokemonMap;
	unordered_map<string, Move>::iterator moveMapIt;
    pokemoninput.open(pokemontxt);
	Pokemon pokemon;
    if(pokemoninput.fail()){ //does the file exist?
        cout << pokemontxt << " does not exist." << endl;
        exit(1);
    }
    if(pokemoninput.peek()==EOF){ //is the file empty?
        cout << pokemontxt << " is empty." << endl;
		exit(1);
    }
	while(!pokemoninput.eof()){
		pokemon = *new Pokemon;
		getline(pokemoninput, pokemonlinestring); //getting one line at a time
		
		pokemon.setDexno(stoi(getUntilComma(&pokemonlinestring)));
		pokemon.setName(getUntilComma(&pokemonlinestring));
		pokemon.setOldAbility1(getUntilComma(&pokemonlinestring));
		pokemon.setOldAbility2(getUntilComma(&pokemonlinestring));
		pokemon.setOldHP(stoi(getUntilComma(&pokemonlinestring)));
		pokemon.setOldAttack(stoi(getUntilComma(&pokemonlinestring)));
		pokemon.setOldDefense(stoi(getUntilComma(&pokemonlinestring)));
		pokemon.setOldSpAttack(stoi(getUntilComma(&pokemonlinestring)));
		pokemon.setOldSpDefense(stoi(getUntilComma(&pokemonlinestring)));
		pokemon.setOldSpeed(stoi(getUntilComma(&pokemonlinestring)));
		pokemon.setOldBST(stoi(getUntilComma(&pokemonlinestring)));
		pokemon.setOldType1(getUntilComma(&pokemonlinestring));
		pokemon.setOldType2(getUntilComma(&pokemonlinestring));
		pokemon.setUncommonHeldItem(getUntilComma(&pokemonlinestring));
		pokemon.setRareHeldItem(getUntilComma(&pokemonlinestring));


		if(pokemon.getUncommonHeldItem() == pokemon.getRareHeldItem()){
			pokemon.setAlwaysHeldItem(pokemon.getRareHeldItem());
			pokemon.setUncommonHeldItem("None");
			pokemon.setRareHeldItem("None");
		}
		pokemon.setExperience(getUntilComma(&pokemonlinestring));

		// evolution = getUntilComma(&pokemonlinestring);
		evolution = getUntilComma(&pokemonlinestring);
		while(evolution.find("$") != string::npos){
			evolution.replace(evolution.find("$"), 1, "\n");
		}
		pokemon.setEvolution(evolution);

		pokemonMap.insert(make_pair(pokemon.getDexno(), pokemon));
	}
	//tm moves
	pokemonMap = readInsertTMMoves(pokemonMap, moveMap);
	return(pokemonMap);
}


/* Read Pokemon from Drayano
 * Reads in a pokemon from Drayano's pokemon change list
 * Does not take a single line, takes data from the equals bars above the name to the end of that pokemon
 * takes a string with all the data, returns a pokemon with filled in data.
 * Calls readpokemongmf to enter in any data that is not included in drayano's list.
 * Returns a completed pokemon
 */
multimap<int, Pokemon> readPokemonDry(string pokemonchangestxt, multimap<int, Pokemon> &pokemonMap, unordered_map<string, Move> &moveMap){
	/*
	 * Following code is for reading in data from Drayano's Pokemon Changelist
	 * found here: https://pastebin.com/uw0pkBWN
	 * data is copied starting from line 54.
	 */

	multimap<int, Pokemon>::iterator pokemonMapIt;

	unordered_map<string, Move>::iterator moveMapIt;
	ifstream pokemonchanges; //whole file ifstream
	Pokemon pokemon;
	Move move;
	string equalsbars;
	string pokemondata;
    pokemonchanges.open(pokemonchangestxt);
    if(pokemonchanges.fail()){ //does the file exist?
        cout << pokemonchangestxt << " does not exist." << endl;
		exit(1);
    }
    if(pokemonchanges.peek()==EOF){ //is the file empty?
        cout << pokemonchangestxt << " is empty." << endl;
        exit(1);
    }

	while(!pokemonchanges.eof()){
		//code below is for a single pokemon
		pokemon.clearPokemon();
		string pokemonnamestring, pokemondatastring, combineddata, singleline, substring = ""; //reset each variable so that we dont continually append

		getline(pokemonchanges, pokemonnamestring);		//001 - Bulbasaur
		getline(pokemonchanges, equalsbars);			//===================
		while(singleline!="==================="){		//read the rest of the data (everything but the name) until next pokemon
			getline(pokemonchanges, singleline);		//Ability:
			pokemondatastring += (singleline + "\n");	//now lets add this line to entire data-string
		}
		pokemondata = (pokemonnamestring + "\n\n") + pokemondatastring; //add newline to the end of the name, then add the data. looks nice and formatted.
									//just to further clarify, pokemondatastring is all pokemondata EXCEPT the name and dexno. pokemondata includes that too

		string categorystring, idstr;
		categorystring = pokemondata.substr(0, pokemondata.find("\n")); //001 - Bulbasaur
		idstr = categorystring.substr(0, categorystring.find("-")-1); //001
		pokemonMapIt = pokemonMap.find(stoi(idstr)); //search map based on dexno

		pokemon = pokemonMapIt->second; //pokemon is a pointer so when we edit pokemon we edit the actual item in the map
		pokemondata.erase(0, pokemondata.find("\n") +1); //erase the first line
		
		//this section deals with form pokemon who have multiple entries. up until now we have treated them as seperate pokemon
		//but here we fix their dexnos so that they are accurate.

		//deoxys
		if(pokemon.getDexno() == 494 || pokemon.getDexno() == 495 || pokemon.getDexno() == 496){
			pokemon.setDexno(386);
		}
		//wormadam
		else if(pokemon.getDexno() == 497 || pokemon.getDexno() == 498){
			pokemon.setDexno(413);
		}
		//giratina
		else if(pokemon.getDexno() == 499){
			pokemon.setDexno(487);
		}
		//shaymin
		else if(pokemon.getDexno() == 500){
			pokemon.setDexno(492);
		}
		//rotom
		else if(pokemon.getDexno() > 500){
			pokemon.setDexno(479);
		}

		while(pokemondata.find("Ability (Complete):") != string::npos || //this while loop is so ugly. would it be better to set a bool variable for each condition
		pokemondata.find("Base Stats (Complete):") != string::npos || //and then turn them off/on in the if statements down below?
		pokemondata.find("Type (Complete):") != string::npos ||
		pokemondata.find("Moves:\n") != string::npos ||
		pokemondata.find("Evolution:") != string::npos ||
		pokemondata.find("Held Item:") != string::npos ||
		pokemondata.find("Base Happiness:") != string::npos){
			if(pokemondata.find("Ability (Complete):") != string::npos){ //if the ability has been changed
					categorystring = pokemondata.substr(pokemondata.find("Ability (Complete):"), pokemondata.find("\n\n") - pokemondata.find("Ability (Complete):")); //categorystring of ability data
					
					//erase "Ability (Complete): \n Old     "
					categorystring.erase(0, 28); //now categorystring is just //Old     Overgrow / None \n New     Chlorophyll / Overgrow
					//old ability 1 parsing and setting
					substring = categorystring.substr(0, categorystring.find("/") - 1); //just Overgrow, minus one because it gets rid of the space
					pokemon.setOldAbility1(substring);
					categorystring.erase(0, categorystring.find("/") + 2); //erase "Overgrow /" the +2 is to erase the / and the space after
					//old ability 2 parsing and setting
					substring = categorystring.substr(0, categorystring.find("\n")); //substring should just be "None"
					pokemon.setOldAbility2(substring);
					categorystring.erase(0, categorystring.find("\n") + 9); //+9 because 1 for newline and 8 for "New     "
					//new ability 1 parsing and setting
					substring = categorystring.substr(0, categorystring.find("/") - 1); //just minus 1 because it gets rid of the space
					pokemon.setNewAbility1(substring);
					categorystring.erase(0, categorystring.find("/") + 2); //same thing as earlier
					//new ability 2 parsing and setting
					pokemon.setNewAbility2(categorystring); //dont have to do any substringing left here cause the only data left in categorystring is the new ability2
					//erase pokemondata from the beginning to the end of the ability category. tbh we could do this at any point in this if statement.

					pokemon.setAbilityChanged(true);

					pokemondata.erase(pokemondata.find("Ability (Complete):"), (pokemondata.find("\n\n") - pokemondata.find("Ability (Complete):"))+2);
				}
			else if(pokemondata.find("Base Stats (Complete):") != string::npos){
					categorystring = pokemondata.substr(pokemondata.find("Base Stats (Complete):"), pokemondata.find("\n\n") - pokemondata.find("Base Stats (Complete):")); //categorystring of base stat data
					categorystring.erase(0, 31); //erase base stats complete new
					//old hp
					substring = categorystring.substr(0, categorystring.find("HP") - 1);
					pokemon.setOldHP(stoi(substring));
					categorystring.erase(0, categorystring.find("HP") + 5); //+5 to get rid of //80 "HP / "
					//old attack
					substring = categorystring.substr(0, categorystring.find("Atk") - 1);
					pokemon.setOldAttack(stoi(substring));
					categorystring.erase(0, categorystring.find("Atk") + 6); //+6 because "Atk / " is 6 characters
					//old defense
					substring = categorystring.substr(0, categorystring.find("Def") - 1);
					pokemon.setOldDefense(stoi(substring));
					categorystring.erase(0, categorystring.find("Def") + 6); //+6 because "Def / " is 6 characters
					//old special attack
					substring = categorystring.substr(0, categorystring.find("SAtk") - 1);
					pokemon.setOldSpAttack(stoi(substring));
					categorystring.erase(0, categorystring.find("SAtk") + 7);//+7 because "SAtk / " is 6 characters
					//old special defense
					substring = categorystring.substr(0, categorystring.find("SDef") - 1);
					pokemon.setOldSpDefense(stoi(substring));
					categorystring.erase(0, categorystring.find("SDef") + 7);//+7 because "SDef / " is 6 characters
					//old speed
					substring = categorystring.substr(0, categorystring.find("Spd") - 1);
					pokemon.setOldSpeed(stoi(substring));
					categorystring.erase(0, categorystring.find("Spd") + 6);//+6 because "Spd / " is 6 characters
					//old bst
					substring = categorystring.substr(0, categorystring.find("BST") - 1);
					pokemon.setOldBST(stoi(substring));
					categorystring.erase(0, categorystring.find("BST") + 12);//+4 because "BST\nNew" is 4 characters


					//new hp
					substring = categorystring.substr(0, categorystring.find("HP") - 1);
					pokemon.setNewHP(stoi(substring));
					categorystring.erase(0, categorystring.find("HP") + 5); //+5 to get rid of //80 "HP / "
					//new attack
					substring = categorystring.substr(0, categorystring.find("Atk") - 1);
					pokemon.setNewAttack(stoi(substring));
					categorystring.erase(0, categorystring.find("Atk") + 6); //+6 because "Atk / " is 6 characters
					//new defense
					substring = categorystring.substr(0, categorystring.find("Def") - 1);
					pokemon.setNewDefense(stoi(substring));
					categorystring.erase(0, categorystring.find("Def") + 6); //+6 because "Def / " is 6 characters
					//new special attack
					substring = categorystring.substr(0, categorystring.find("SAtk") - 1);
					pokemon.setNewSpAttack(stoi(substring));
					categorystring.erase(0, categorystring.find("SAtk") + 7);//+7 because "SAtk / " is 6 characters
					//new special defense
					substring = categorystring.substr(0, categorystring.find("SDef") - 1);
					pokemon.setNewSpDefense(stoi(substring));
					categorystring.erase(0, categorystring.find("SDef") + 7);//+7 because "SDef / " is 6 characters
					//new speed
					substring = categorystring.substr(0, categorystring.find("Spd") - 1);
					pokemon.setNewSpeed(stoi(substring));
					categorystring.erase(0, categorystring.find("Spd") + 6);//+6 because "Spd / " is 6 characters
					//new bst
					substring = categorystring.substr(0, categorystring.find("BST") - 1);
					pokemon.setNewBST(stoi(substring));
					categorystring.erase(0, categorystring.find("BST") + 4);//+4 because "BST\n" is 4 characters
					
					pokemon.setStatChanged(true);

					pokemondata.erase(pokemondata.find("Base Stats (Complete):"), (pokemondata.find("\n\n") - pokemondata.find("Base Stats (Complete):"))+2);
				}
			else if(pokemondata.find("Evolution:") != string::npos){
				categorystring = pokemondata.substr(pokemondata.find("Evolution:"), pokemondata.find("\n\n") - pokemondata.find("Evolution:")); //categorystring of evolution data
				categorystring.erase(0, 11); //11 because that's the length of "Evolution:\n"
				substring = categorystring.substr(0, categorystring.find("\n\n"));
				substring = pokemon.getEvolution() + substring;
				pokemon.setEvolution(substring);
				pokemondata.erase(pokemondata.find("Evolution:"), (pokemondata.find("\n\n") - pokemondata.find("Evolution:"))+2);
			}
			else if(pokemondata.find("Moves:\n") != string::npos){
				categorystring = pokemondata.substr(pokemondata.find("Moves:"), pokemondata.find("\n\n") - pokemondata.find("Moves:")+2); //categorystring of moves data
				string tmMoveLine, tmMoveNo;
				int tmindex;
				substring = categorystring.substr(7, categorystring.length() - 7); //delete moves:
				while (substring != "\n"){
					substring.erase(0, 20); //deleting "Now Compatible with "
					tmMoveNo = substring.substr(0, 4); //TM01
					tmindex = stoi(tmMoveNo.substr(2, 2));
					tmindex--;
					if(tmMoveNo.substr(0, 2) == "HM"){ //the move is a tm
						tmindex += 92; //90 because hms are 92 to 100 in the array but numbered 01 to 09
					}
					substring.erase(0, 6); //should just be the move and a period and maybe a !! now
					tmMoveLine = substring.substr(0, substring.find(".")); //setting tmMoveLine equal to just the name of the move
					moveMapIt = moveMap.find(tmMoveLine); //finding that move in the move map
					pokemon.getTmMoves(tmindex).move = moveMapIt->second; //setting the pokemon's move's data equal to the data from the map
					pokemon.getTmMoves(tmindex).canLearn = true; //now this pokemon can learn the move
					pokemon.getTmMoves(tmindex).tmNo = tmMoveNo;
					//cout << "substring is:" << substring << "~~" << endl;
					if(substring.find("(!!)") < substring.find("\n")){ //if it is a new move
						pokemon.getTmMoves(tmindex).newM = true;
					}
					else{ //if it isnt a new move
						pokemon.getTmMoves(tmindex).newM = false;
					}
					//cout << endl;
					substring.erase(0, substring.find("\n")+1); //erased the whole line
				}
				pokemondata.erase(pokemondata.find("Moves:"), (pokemondata.find("\n\n") - pokemondata.find("Moves:")) + 2);
			}
			else if(pokemondata.find("Type (Complete):") != string::npos){
				categorystring = pokemondata.substr(pokemondata.find("Type (Complete):"), pokemondata.find("\n\n") - pokemondata.find("Type (Complete):")); //categorystring of type data
				categorystring.erase(0, 17); //17 bc length of Type (Complete):\n
				categorystring.erase(0, categorystring.find("\n")+9); //erase old type line cause we dont really care about it, i mean, do we? also +9 because we get rid of "New     "
				//new type 1
				substring = categorystring.substr(0, categorystring.find("/") - 1); //-1 bc we want to get rid of the space before the /
				pokemon.setNewType1(substring);
				categorystring.erase(0, categorystring.find("/") + 2); //+2 bc we want to get rid of / and space after
				//new type 2
				substring = categorystring.substr(0, categorystring.find("\n"));
				pokemon.setNewType2(substring);
				pokemondata.erase(pokemondata.find("Type (Complete):"), (pokemondata.find("\n\n") - pokemondata.find("Type (Complete):"))+2);

				pokemon.setTypeChanged(true);

			}
			else if(pokemondata.find("Held Item:") != string::npos){
				categorystring = pokemondata.substr(pokemondata.find("Held Item:"), pokemondata.find("\n\n") - pokemondata.find("Held Item:")); //categorystring of held item data
				//do stuff to categorystring
				pokemondata.erase(pokemondata.find("Held Item:"), (pokemondata.find("\n\n") - pokemondata.find("Held Item:"))+2);
			}
			else if(pokemondata.find("Base Happiness:") != string::npos){
				string tmp;
				categorystring = pokemondata.substr(pokemondata.find("Base Happiness:"), pokemondata.find("\n\n") - pokemondata.find("Base Happiness:")); //categorystring of base happiness
				categorystring.erase(0, 17); //erase "Base Happiness:" \n
				//we use evolution bc base happiness is only changed to make evolution easier
				tmp = pokemon.getEvolution();
				tmp += "\n  This Pokemon also has a higher base happiness so it will evolve faster.";
				pokemon.setEvolution(tmp); 
				pokemondata.erase(pokemondata.find("Base Happiness:"), (pokemondata.find("\n\n") - pokemondata.find("Base Happiness:"))+2);
			}
			//no need for another else statement because it will never be met. the condition for this while loop is that one of the if statements works.

		}
		//Level Up:
		pokemondata.erase(0, pokemondata.find("\n")+1); //erase whole line
		pokemondata.erase(0, pokemondata.find("\n")+1); //erase whole line
		moveStruct learnedMove;
		categorystring = pokemondata.substr(0, pokemondata.find("==================="));
		//cout << pokemon.getDexno() << " - " << pokemon.getName() << endl << "Level up Learnset:" << endl;
		int levelindex = 0; //index of array of moves learned by level. NOT the integer to store the level the pokemon learns the move
		for(int i = 0; i<29; i++){ //reset all the moves .learn to false. literally have no idea why i have to do this.
			pokemon.getLevelMoves(i).learn = false; //i shouldnt have to do this but it fixes it
			pokemon.getLevelMoves(i).newM = false;
		}
		while(categorystring != "\n"){
			substring = categorystring.substr(0, categorystring.find("\n"));
			learnedMove.level = stoi( substring.substr(0, substring.find(" ")));
			substring.erase(0, substring.find("-") + 2); //+2 because we want to get rid of " - "
			if(substring.find("(!!)") != string::npos){
				substring = substring.substr(0, substring.find("(!!)") - 1);
				learnedMove.newM = true;
			}
			else{
				learnedMove.newM = false;
			}
			moveMapIt = moveMap.find(substring);
			learnedMove.move = moveMapIt->second;
			//stab checker
			if(pokemon.getTypeChanged()){
				if((learnedMove.move.getType() == pokemon.getNewType1() || learnedMove.move.getType() == pokemon.getNewType2())
				&& learnedMove.move.getCategory() != "Status"){
					learnedMove.stab = true;
				}
				else{
					learnedMove.stab = false;
				}
			}
			else{ //pokemon's type hasn't been changed
				if((learnedMove.move.getType() == pokemon.getOldType1() || learnedMove.move.getType() == pokemon.getOldType2())
				&& learnedMove.move.getCategory() != "Status"){
					learnedMove.stab = true;
				}
				else{
					learnedMove.stab = false;
				}
			}
			learnedMove.learn = true;

			pokemon.getLevelMoves(levelindex).learn = learnedMove.learn;
			pokemon.getLevelMoves(levelindex).level = learnedMove.level;
			pokemon.getLevelMoves(levelindex).move = learnedMove.move;
			pokemon.getLevelMoves(levelindex).newM = learnedMove.newM;
			pokemon.getLevelMoves(levelindex).stab = learnedMove.stab;

			levelindex++;
			categorystring.erase(0, categorystring.find("\n") + 1); //+1 to erase the newline character as well
		}

		//iterating through all TM moves to check if they're stab
		for(int i = 0; i <= 99; i++){
			if(pokemon.getTypeChanged()){
				if((pokemon.getTmMoves(i).move.getType() == pokemon.getNewType1() || pokemon.getTmMoves(i).move.getType() == pokemon.getNewType2())
				&& pokemon.getTmMoves(i).move.getCategory() != "Status"){
					pokemon.getTmMoves(i).stab = true;
				}
				else{
					pokemon.getTmMoves(i).stab = false;
				}
			}
			else{ //pokemon's type hasn't been changed
				if((pokemon.getTmMoves(i).move.getType() == pokemon.getOldType1() || pokemon.getTmMoves(i).move.getType() == pokemon.getOldType2())
				&& pokemon.getTmMoves(i).move.getCategory() != "Status"){
					pokemon.getTmMoves(i).stab = true;
				}
				else{
					pokemon.getTmMoves(i).stab = false;
				}
			}
		}
		//pokemonMap[pokemonMapIt->first] = pokemon;
		pokemonMapIt->second = pokemon;
		//cout << pokemonMapIt->second << endl;
	}
	return(pokemonMap);
}