#include "./route.hpp"
#include <ctype.h>
#include <set>
#include <iostream>
//utility functions

bool is_number(const string&);
bool contains(string, string);
string makeLowerCase(string);

//menu functions
void printMenu(map<string, Route*>&, multimap<int, Pokemon>&);
void searchPokemon(map<string, Route*>&, multimap<int, Pokemon>&);
void showChanges(multimap<int, Pokemon> &);
void printPokemon(char*, Pokemon);

int main(){
	unordered_map<string, Move> moveMap;
	multimap<int, Pokemon> pokemonMap;
	map<string, Route*> routeMap;
    map<string, Route*>::iterator routeMapIt;
    multimap<int, Pokemon>::iterator pokemonMapIt;
    vector<bossTrainer>::iterator bossTrainersIt;
    vector<bossPokemon>::iterator teamIt;

    cout << "Creating database of moves. . . ";
	moveMap = readMoves("./input/CompleteMovesList.csv"); //create a map of all moves to search from later
	cout << "Done" << endl;
    
    cout << "Creating database of Pokemon. . . ";
	pokemonMap = readPokemonGmf("./input/personalData.csv", moveMap); //input original data, including tm learnsets, not including level up learnsets
	cout << "Done" << endl;

    cout << "Updating Pokemon Database with Renegade Platinum Changes. . . ";
	pokemonMap = readPokemonDry("./input/pokemonchanges.txt", pokemonMap, moveMap); //update the map to renegade platinum's changes
	cout << "Done" << endl;
	// for(pokemonMapIt = pokemonMap.begin(); pokemonMapIt != pokemonMap.end(); pokemonMapIt++){
	// 	cout << pokemonMapIt->second << endl;
	// }
    cout << "Creating routes and adding wild Pokemon to them. . . ";
	routeMap = readRoute("./input/wildpokemon.txt");
	cout << "Done" << endl;

	cout << "Adding trainers and their teams to the routes. . . ";
	routeMap = readTrainers("./input/trainerPokemon.txt", routeMap);
    cout << "Done" << endl;

    cout << "Inserting powerful trainers to the maps. . .";
    routeMap = insertBossBattles("./input/BossBattles.txt", routeMap);
    cout << "Done" << endl;

    cout << "Adding items to the routes. . .";
    routeMap = insertItems("./input/Items.csv", routeMap);
    cout << "Done" << endl;

    printMenu(routeMap, pokemonMap);

    for(routeMapIt = routeMap.begin(); routeMapIt != routeMap.end(); routeMapIt++){
        for(bossTrainersIt = routeMapIt->second->getBosses().begin(); bossTrainersIt != routeMapIt->second->getBosses().end(); bossTrainersIt++){
            vector<bossPokemon>().swap(bossTrainersIt->team); //funky way of calling delete
        }
        vector<bossTrainer>().swap(routeMapIt->second->getBosses());
        vector<itemStruct>().swap(routeMapIt->second->getItems());
        delete routeMapIt->second;
    }
    for(pokemonMapIt = pokemonMap.begin(); pokemonMapIt != pokemonMap.end(); pokemonMapIt++){
        delete &pokemonMapIt->second;
    }
    return(0);
}
//utility functions
string makeLowerCase(string toConvert){
    locale loc;
    for(size_t i = 0; i < toConvert.size(); i++){
        toConvert.at(i) = tolower(toConvert.at(i), loc);
    }
    return(toConvert);
}
bool contains(string main_str, string find_str){
    if(main_str.find(find_str) != string::npos){
        return(true);
    }
    else{
        return(false);
    }
}
bool is_number(const std::string& s){
    string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

//menu functions
void printMenu(map<string, Route*> &routeMap, multimap<int, Pokemon> &pokemonMap){
    string choiceInput = "0";
    int choice = 0;
    char choiceCharArray[8];
    multimap<int, Pokemon> resultMap;
	multimap<int, Pokemon>::iterator pokemonMapIt;
    map<string, Route*> resultRouteMap;
    map<string, Route*>::iterator routeMapIt;
    map<string, int>::iterator encounterMapIt;

    string inputString;
    string printChoice;
    string useless;
    while(choice != 7){
        cout << "================Main Menu================" << endl;
        cout << " 1 - Search Pokemon by name" << endl;
        cout << " 2 - Search Pokemon by traits" << endl;
        cout << " 3 - Show changes only" << endl;
        cout << " 4 - Search wild locations of a Pokemon" << endl;
        cout << " 5 - Search Routes by name" << endl;
        cout << " 6 - Search items" << endl;
        cout << " 7 - Close Program" << endl;
        cout << "=========================================" << endl;
        cin >> choiceInput;
        if(!is_number(choiceInput) || stoi(choiceInput) < 1 || stoi(choiceInput) > 7){
            cout << "Please enter a number between 1 and 7." << endl;
            system("pause");
            continue;
        }
        choice = stoi(choiceInput);
        resultRouteMap.clear();
        resultMap.clear();
        if(choice == 1){
            cout << "Enter the name of the Pokemon you want to find." << endl;
            cin.ignore();
            getline(cin, inputString);
            
            // pokemonMapIt = pokemonMap.find(inputString);
            for(pokemonMapIt = pokemonMap.begin(); pokemonMapIt != pokemonMap.end(); pokemonMapIt++){
                // if(pokemonMapIt->second.getName() == inputString){
                    // break; //now that the pokemon is found exit the loop so the iterator stays on the pokemon
                // }
                if(contains(makeLowerCase(pokemonMapIt->second.getName()), makeLowerCase(inputString))){
                    resultMap.insert(make_pair(pokemonMapIt->second.getDexno(), pokemonMapIt->second));
                } 
            }
            if(resultMap.size() == 0){
                cout << inputString << " was not found." << endl;
                system("pause");
            }
            else if(resultMap.size() == 1){ //1 match
                pokemonMapIt = resultMap.begin();
                cout << pokemonMapIt->second.getName() << " was found." << endl;
                cout << "What to print?" << endl;
                cout << "'r' for recommended data" << endl;
                cout << "'a' for all data" << endl;

                cin >> choiceCharArray[0];
                if(choiceCharArray[0] != 'r' && choiceCharArray[0] != 'a'){
                    cout << "Please enter 'r' or 'a'" << endl;
                    system("pause");
                    continue;
                }
                printPokemon(choiceCharArray, pokemonMapIt->second);
                system("pause");
            }
            else{ //multiple matches
                cout << inputString << " has multiple matches." << endl;
                cout << "What to print?" << endl;
                cout << "'r' for recommended data" << endl;
                cout << "'a' for all data" << endl;

                cin >> choiceCharArray[0];
                if(choiceCharArray[0] != 'r' && choiceCharArray[0] != 'a'){
                    cout << "Please enter 'r' or 'a'" << endl;
                    system("pause");
                    continue;
                }
                for(pokemonMapIt = resultMap.begin(); pokemonMapIt != resultMap.end(); pokemonMapIt++){
                    printPokemon(choiceCharArray, pokemonMapIt->second);
                }
                system("pause");
            }
        }
        else if(choice == 2){
            searchPokemon(routeMap, pokemonMap);
        }
        else if(choice == 3){
            showChanges(pokemonMap);
        }
        else if(choice == 4){
            string outputStr = "";
            set<string> matches;
            cout << "Enter the name of the Pokemon you want to find." << endl;
            cin.ignore();
            getline(cin, inputString);
            for(routeMapIt = routeMap.begin(); routeMapIt != routeMap.end(); routeMapIt++){
                if(routeMapIt->second->getMorningMap().size() != 0){
                    for(encounterMapIt = routeMapIt->second->getMorningMap().begin(); encounterMapIt != routeMapIt->second->getMorningMap().end(); encounterMapIt++){
                        if(contains(makeLowerCase(encounterMapIt->first), makeLowerCase(inputString))){
                            resultRouteMap.insert(make_pair(routeMapIt->first, routeMapIt->second));
                        }
                    }
                }
                if(routeMapIt->second->getDayMap().size() != 0){
                    for(encounterMapIt = routeMapIt->second->getDayMap().begin(); encounterMapIt!= routeMapIt->second->getDayMap().end(); encounterMapIt++){
                        if(contains(makeLowerCase(encounterMapIt->first), makeLowerCase(inputString))){
                            resultRouteMap.insert(make_pair(routeMapIt->first, routeMapIt->second));
                        }
                    }
                }
                if(routeMapIt->second->getNightMap().size() != 0){
                    for(encounterMapIt = routeMapIt->second->getNightMap().begin(); encounterMapIt!= routeMapIt->second->getNightMap().end(); encounterMapIt++){
                        if(contains(makeLowerCase(encounterMapIt->first), makeLowerCase(inputString))){
                            resultRouteMap.insert(make_pair(routeMapIt->first, routeMapIt->second));
                        }
                    }
                }
                if(routeMapIt->second->getSurfMap().size() != 0){
                    for(encounterMapIt = routeMapIt->second->getSurfMap().begin(); encounterMapIt != routeMapIt->second->getSurfMap().end(); encounterMapIt++){
                        if(contains(makeLowerCase(encounterMapIt->first), makeLowerCase(inputString))){
                            resultRouteMap.insert(make_pair(routeMapIt->first, routeMapIt->second));
                        }
                    }
                }
                if(routeMapIt->second->getOldRodMap().size() != 0){
                    for(encounterMapIt = routeMapIt->second->getOldRodMap().begin(); encounterMapIt != routeMapIt->second->getOldRodMap().end(); encounterMapIt++){
                        if(contains(makeLowerCase(encounterMapIt->first), makeLowerCase(inputString))){
                            resultRouteMap.insert(make_pair(routeMapIt->first, routeMapIt->second));
                        }
                    }
                }
                if(routeMapIt->second->getGoodRodMap().size() != 0){
                    for(encounterMapIt = routeMapIt->second->getGoodRodMap().begin(); encounterMapIt != routeMapIt->second->getGoodRodMap().end(); encounterMapIt++){
                        if(contains(makeLowerCase(encounterMapIt->first), makeLowerCase(inputString))){
                            resultRouteMap.insert(make_pair(routeMapIt->first, routeMapIt->second));
                        }
                    }
                }
                if(routeMapIt->second->getSuperRodMap().size() != 0){
                    for(encounterMapIt = routeMapIt->second->getSuperRodMap().begin(); encounterMapIt != routeMapIt->second->getSuperRodMap().end(); encounterMapIt++){
                        if(contains(makeLowerCase(encounterMapIt->first), makeLowerCase(inputString))){
                            resultRouteMap.insert(make_pair(routeMapIt->first, routeMapIt->second));
                        }
                    }
                }
                if(routeMapIt->second->getPokeRadarMap().size() != 0){
                    for(encounterMapIt = routeMapIt->second->getPokeRadarMap().begin(); encounterMapIt != routeMapIt->second->getPokeRadarMap().end(); encounterMapIt++){
                        if(contains(makeLowerCase(encounterMapIt->first), makeLowerCase(inputString))){
                            resultRouteMap.insert(make_pair(routeMapIt->first, routeMapIt->second));
                        }
                    }
                }
                if(routeMapIt->second->getHoneyTreeMap().size() != 0){
                    for(encounterMapIt = routeMapIt->second->getHoneyTreeMap().begin(); encounterMapIt!= routeMapIt->second->getHoneyTreeMap().end(); encounterMapIt++){
                        if(contains(makeLowerCase(encounterMapIt->first), makeLowerCase(inputString))){
                            resultRouteMap.insert(make_pair(routeMapIt->first, routeMapIt->second));
                        }
                    }
                }
            }
            if(resultRouteMap.size() == 0){
                cout << "Either " << inputString << " isn't a part of a Pokemon's name or you can't catch a wild one." << endl;
            }
            else{
                for(routeMapIt = resultRouteMap.begin(); routeMapIt != resultRouteMap.end(); routeMapIt++){
                    outputStr += routeMapIt->first + '\n';
                    if(routeMapIt->second->getMorningMap().size() != 0){
                        for(encounterMapIt = routeMapIt->second->getMorningMap().begin(); encounterMapIt != routeMapIt->second->getMorningMap().end(); encounterMapIt++){
                            if(contains(makeLowerCase(encounterMapIt->first), makeLowerCase(inputString))){
                                outputStr += "  " + to_string(encounterMapIt->second) + "% - Morning (Walking)\n";
                                matches.insert(encounterMapIt->first);
                            }
                        }
                    }
                    if(routeMapIt->second->getDayMap().size() != 0){
                        for(encounterMapIt = routeMapIt->second->getDayMap().begin(); encounterMapIt!= routeMapIt->second->getDayMap().end(); encounterMapIt++){
                            if(contains(makeLowerCase(encounterMapIt->first), makeLowerCase(inputString))){
                                outputStr += "  " + to_string(encounterMapIt->second) + "% - Day (Walking)\n";
                                matches.insert(encounterMapIt->first);
                            }
                        }
                    }
                    if(routeMapIt->second->getNightMap().size() != 0){
                        for(encounterMapIt = routeMapIt->second->getNightMap().begin(); encounterMapIt!= routeMapIt->second->getNightMap().end(); encounterMapIt++){
                            if(contains(makeLowerCase(encounterMapIt->first), makeLowerCase(inputString))){
                                outputStr += "  " + to_string(encounterMapIt->second) + "% - Night (Walking)\n";
                                matches.insert(encounterMapIt->first);
                            }
                        }
                    }
                    if(routeMapIt->second->getSurfMap().size() != 0){
                        for(encounterMapIt = routeMapIt->second->getSurfMap().begin(); encounterMapIt != routeMapIt->second->getSurfMap().end(); encounterMapIt++){
                            if(contains(makeLowerCase(encounterMapIt->first), makeLowerCase(inputString))){
                                outputStr += "  " + to_string(encounterMapIt->second) + "% - Surfing\n";
                                matches.insert(encounterMapIt->first);
                            }
                        }
                    }
                    if(routeMapIt->second->getOldRodMap().size() != 0){
                        for(encounterMapIt = routeMapIt->second->getOldRodMap().begin(); encounterMapIt != routeMapIt->second->getOldRodMap().end(); encounterMapIt++){
                            if(contains(makeLowerCase(encounterMapIt->first), makeLowerCase(inputString))){
                                outputStr += "  " + to_string(encounterMapIt->second) + "% - Old Rod\n";
                                matches.insert(encounterMapIt->first);
                            }
                        }
                    }
                    if(routeMapIt->second->getGoodRodMap().size() != 0){
                        for(encounterMapIt = routeMapIt->second->getGoodRodMap().begin(); encounterMapIt != routeMapIt->second->getGoodRodMap().end(); encounterMapIt++){
                            if(contains(makeLowerCase(encounterMapIt->first), makeLowerCase(inputString))){
                                outputStr += "  " + to_string(encounterMapIt->second) + "% - Good Rod\n";
                                matches.insert(encounterMapIt->first);
                            }
                        }
                    }
                    if(routeMapIt->second->getSuperRodMap().size() != 0){
                        for(encounterMapIt = routeMapIt->second->getSuperRodMap().begin(); encounterMapIt != routeMapIt->second->getSuperRodMap().end(); encounterMapIt++){
                            if(contains(makeLowerCase(encounterMapIt->first), makeLowerCase(inputString))){
                                outputStr += "  " + to_string(encounterMapIt->second) + "% - Super Rod\n";
                                matches.insert(encounterMapIt->first);
                            }
                        }
                    }
                    if(routeMapIt->second->getPokeRadarMap().size() != 0){
                        for(encounterMapIt = routeMapIt->second->getPokeRadarMap().begin(); encounterMapIt != routeMapIt->second->getPokeRadarMap().end(); encounterMapIt++){
                            if(contains(makeLowerCase(encounterMapIt->first), makeLowerCase(inputString))){
                                outputStr += "  " + to_string(encounterMapIt->second) + "% - Poke Radar\n";
                                matches.insert(encounterMapIt->first);
                            }
                        }
                    }
                    if(routeMapIt->second->getHoneyTreeMap().size() != 0){
                        for(encounterMapIt = routeMapIt->second->getHoneyTreeMap().begin(); encounterMapIt!= routeMapIt->second->getHoneyTreeMap().end(); encounterMapIt++){
                            if(contains(makeLowerCase(encounterMapIt->first), makeLowerCase(inputString))){
                                outputStr += "  " + to_string(encounterMapIt->second) + "% - Honey Tree\n";
                                matches.insert(encounterMapIt->first);
                            }
                        }
                    }
                }
                if(matches.size() > 1){
                    cout << "Please refine your search. \"" << inputString << "\" was able to find multiple Pokemon." << endl;
                    system("pause");
                    continue;
                }
                else{ //matches size is 1. It can't be zero or we would have gotten an error earlier.
                    cout << "Found: " << *matches.begin() << endl;
                    cout << outputStr;
                    system("pause");
                }
            }
        }
        else if(choice == 5){
            cout << "Enter the name of the route that you want to search for." << endl;
            cin.ignore();
            getline(cin, inputString);
            // routeMapIt = routeMap.find(inputString);
            for(routeMapIt = routeMap.begin(); routeMapIt != routeMap.end(); routeMapIt++){
                if(contains(makeLowerCase(routeMapIt->second->getFullName()), makeLowerCase(inputString)) ||
                contains(makeLowerCase(routeMapIt->second->getMainName()), makeLowerCase(inputString))){
                    resultRouteMap.insert(make_pair(routeMapIt->first, routeMapIt->second));
                }
            }
            if(resultRouteMap.size() == 0){
                cout << inputString << " was not found." << endl;
            }
            else{
                for(routeMapIt = resultRouteMap.begin(); routeMapIt != resultRouteMap.end(); routeMapIt++){
                    cout << *routeMapIt->second;
                }
            }
            system("pause");
        }
        else if(choice == 6){
            vector<itemStruct>::iterator vecIt;
            set<string> itemSet;
            set<string>::iterator itemit;
            string output = "";
            int padding;
            cin.ignore();
            cout << "Enter the name of the item you want to search for." << endl;
            getline(cin, inputString);
            for(routeMapIt = routeMap.begin(); routeMapIt != routeMap.end(); routeMapIt++){
                for(vecIt = routeMapIt->second->getItems().begin(); vecIt != routeMapIt->second->getItems().end(); vecIt++){
                    if(contains(makeLowerCase(vecIt->name), makeLowerCase(inputString))){
                        itemSet.insert(vecIt->name);
                        padding = 14 - routeMapIt->second->getFullName().size();
                        output += "  " + routeMapIt->second->getFullName();
                        for(int i = 0; i < padding; i++){
                            output.push_back(' ');
                        }
                        output += " - " + vecIt->method + '\n';
                    }
                }
            }
            for(pokemonMapIt = pokemonMap.begin(); pokemonMapIt != pokemonMap.end(); pokemonMapIt++){
                if(contains(makeLowerCase(pokemonMapIt->second.getUncommonHeldItem()), makeLowerCase(inputString))){
                    itemSet.insert(pokemonMapIt->second.getUncommonHeldItem());
                    output += "  " + pokemonMapIt->second.getName();
                    padding = 14 - pokemonMapIt->second.getName().size();
                    for(int i = 0; i < padding; i++){
                        output.push_back(' ');
                    }
                    output += " - 5%\n";
                }
                if(contains(makeLowerCase(pokemonMapIt->second.getRareHeldItem()), makeLowerCase(inputString))){
                    itemSet.insert(pokemonMapIt->second.getRareHeldItem());
                    output += "  " + pokemonMapIt->second.getName();
                    padding = 14 - pokemonMapIt->second.getName().size();
                    for(int i = 0; i < padding; i++){
                        output.push_back(' ');
                    }
                    output += " - 50%\n";
                }
                if(contains(makeLowerCase(pokemonMapIt->second.getAlwaysHeldItem()), makeLowerCase(inputString))){
                    itemSet.insert(pokemonMapIt->second.getAlwaysHeldItem());
                    output += "  " + pokemonMapIt->second.getName();
                    padding = 14 - pokemonMapIt->second.getName().size();
                    for(int i = 0; i < padding; i++){
                        output.push_back(' ');
                    }
                    output += " - 100%\n";
                }
            }
            if(itemSet.size() == 0){
                cout << inputString << " was not found." << endl;
                system("pause");
                continue;
            }
            if(itemSet.size() > 1){
                cout << inputString << " found more than one item. Please be more specific in your search." << endl;
                system("pause");
                continue;
            }
            else{
                cout << "Found: " << *itemSet.begin() << endl;
                cout << output;
                system("pause");
            }
        }
    }
}
void searchPokemon(map<string, Route*> &routeMap, multimap<int, Pokemon> &pokemonMap){
    static int choice = 0;
    string choiceString;
    choice = 0;
    string inputLow;
    string inputHigh;
    int low;
    int high;
    string type1;
    string type2 = "";
    string inputString, useless;
	multimap<int, Pokemon> resultMap;
	multimap<int, Pokemon>::iterator pokemonMapIt;
    map<string, Route*> resultRouteMap;
    map<string, Route*>::iterator routeMapIt;
    map<string, int>::iterator encounterMapIt;
    while(choice != 6){
        cout << "========Search Pokemon by traits=========" << endl;
        cout << "  1 - Search Pokemon by ability" << endl;
        cout << "  2 - Search Pokemon by base stats" << endl;
        cout << "  3 - Search Pokemon by type" << endl;
        cout << "  4 - Search Pokemon by moves learned" << endl;
        cout << "  5 - Add search parameter" << endl;
        cout << "  6 - Return to main menu" << endl;
        cout << "=========================================" << endl;
        cin >> choiceString;
        if(!is_number(choiceString) || stoi(choiceString) < 1 || stoi(choiceString) > 6){
            cout << "Please enter a number between 1 and 6." << endl;
            system("pause");
            continue;
        }
        choice = stoi(choiceString);
        if(choice != 5){
            resultMap.clear();
            resultRouteMap.clear();
        }
        if(choice == 1){
            bool firstAbility = false;
            cout << "Enter the name of the ability you want to find." << endl;
            cin.ignore();
            getline(cin, inputString);
            for(pokemonMapIt = pokemonMap.begin(); pokemonMapIt != pokemonMap.end(); pokemonMapIt++){
                if(pokemonMapIt->second.getAbilityChanged()){ //if their ability has been changed we care about new ability 1 and 2
                    if(contains(makeLowerCase(pokemonMapIt->second.getNewAbility1()), makeLowerCase(inputString))
                    || contains(makeLowerCase(pokemonMapIt->second.getNewAbility2()), makeLowerCase(inputString))){
                        resultMap.insert(make_pair(pokemonMapIt->second.getDexno(), pokemonMapIt->second));
                    }
                }
                else{ //else their ability has not been changed so we dont care about it
                    if(contains(makeLowerCase(pokemonMapIt->second.getOldAbility1()), makeLowerCase(inputString))
                    || contains(makeLowerCase(pokemonMapIt->second.getOldAbility2()), makeLowerCase(inputString))){
                        resultMap.insert(make_pair(pokemonMapIt->second.getDexno(), pokemonMapIt->second));
                    }
                }
            }
            if(resultMap.size() == 0){
                cout << "Could not find " << inputString << '.' << endl;
            }
            for(pokemonMapIt = resultMap.begin(); pokemonMapIt != resultMap.end(); pokemonMapIt++){
                if(pokemonMapIt->second.getAbilityChanged()){
                    firstAbility = (contains(makeLowerCase(pokemonMapIt->second.getNewAbility1()), makeLowerCase(inputString))? true : false );
                }
                if(pokemonMapIt->second.getAbilityChanged() &&
                   firstAbility && 
                   pokemonMapIt->second.getNewAbility1() != pokemonMapIt->second.getOldAbility1() && 
                   pokemonMapIt->second.getNewAbility1() != pokemonMapIt->second.getOldAbility2()){
                    cout << '!';
                }
                else if(pokemonMapIt->second.getAbilityChanged() &&
                   !firstAbility && 
                   pokemonMapIt->second.getNewAbility2() != pokemonMapIt->second.getOldAbility1() && 
                   pokemonMapIt->second.getNewAbility2() != pokemonMapIt->second.getOldAbility2()){
                       cout << '!';
                   }
                else{
                    cout << ' ';
                }
                cout << pokemonMapIt->second.getDexno() << " - " << pokemonMapIt->second.getName() << endl;
            }
            system("pause");
        }
        else if(choice == 2){
            char changed = ' ';
            cout << "This program prints every pokemon between two base stat totals." << endl;
            cout << "Note: The highest BST is 720 and the lowest is 180." << endl;
            cout << "Enter the low end base stat total now." << endl;
            cin.ignore();
            getline(cin, inputLow);
            cout << "Enter the high end base stat total now." << endl;
            getline(cin, inputHigh);
            if(!is_number(inputLow) || !is_number(inputHigh)){
                cout << "Please enter numbers for the high and low." << endl;
                system("pause");
                continue;
            }
            low = stoi(inputLow);
            high = stoi(inputHigh);
            if((high - low) < 0){
                cout << "Please make sure that the low value is lower than the high value." << endl;
                system("pause");
                continue;
            }
            for(pokemonMapIt = pokemonMap.begin(); pokemonMapIt != pokemonMap.end(); pokemonMapIt++){
                if(pokemonMapIt->second.getStatChanged() == true){
                    if(pokemonMapIt->second.getNewBST() >= low && pokemonMapIt->second.getNewBST() <= high){
                        resultMap.insert(make_pair(pokemonMapIt->second.getDexno(), pokemonMapIt->second));
                    }
                }
                else{ //their base stats haven't been changed
                    if(pokemonMapIt->second.getOldBST() >= low && pokemonMapIt->second.getOldBST() <= high){
                        resultMap.insert(make_pair(pokemonMapIt->second.getDexno(), pokemonMapIt->second));
                    }
                }
            }
            if(resultMap.size() == 0){
                cout << "No results" << endl;
            }
            for(pokemonMapIt = resultMap.begin(); pokemonMapIt != resultMap.end(); pokemonMapIt++){
                if(pokemonMapIt->second.getStatChanged()){
                    changed = '!';
                }
                cout << changed;
                printf("%03d - %-10s \n", pokemonMapIt->first, pokemonMapIt->second.getName().c_str());
                if(pokemonMapIt->second.getStatChanged()){
                    printf("   Old: %d HP / %d Atk / %d Def / %d SpAtk / %d SpDef / %d Spd / %d BST\n",
                    pokemonMapIt->second.getOldHP(), pokemonMapIt->second.getOldAttack(),
                    pokemonMapIt->second.getOldDefense(), pokemonMapIt->second.getOldSpAttack(),
                    pokemonMapIt->second.getOldSpDefense(), pokemonMapIt->second.getOldSpeed(),
                    pokemonMapIt->second.getOldBST());
                    printf("   New: %d HP / %d Atk / %d Def / %d SpAtk / %d SpDef / %d Spd / %d BST\n",
                    pokemonMapIt->second.getNewHP(), pokemonMapIt->second.getNewAttack(),
                    pokemonMapIt->second.getNewDefense(), pokemonMapIt->second.getNewSpAttack(),
                    pokemonMapIt->second.getNewSpDefense(), pokemonMapIt->second.getNewSpeed(),
                    pokemonMapIt->second.getNewBST());
                }
                else{
                    printf("   %d HP / %d Atk / %d Def / %d SpAtk / %d SpDef / %d Spd / %d BST\n",
                    pokemonMapIt->second.getOldHP(), pokemonMapIt->second.getOldAttack(),
                    pokemonMapIt->second.getOldDefense(), pokemonMapIt->second.getOldSpAttack(),
                    pokemonMapIt->second.getOldSpDefense(), pokemonMapIt->second.getOldSpeed(),
                    pokemonMapIt->second.getOldBST());
                }
                changed = ' ';
            }
            system("pause");
        }
        else if(choice == 3){
            bool firstType = false;
            cout << "Enter the type(s) you want to search for. If you want to input multiple types separate them by a space." << endl;
            cin.ignore();
            getline(cin, inputString);
            if(inputString.find(' ') != string::npos){ //if the user input two types
                type1 = inputString.substr(0, inputString.find(' '));
                type2 = inputString.substr(inputString.find(' ') + 1, inputString.size() - inputString.find(' ') + 1);
                for(pokemonMapIt = pokemonMap.begin(); pokemonMapIt != pokemonMap.end(); pokemonMapIt++){
                    if(pokemonMapIt->second.getTypeChanged() == true){ //if the pokemon's type has been changed
                        if((makeLowerCase(pokemonMapIt->second.getNewType1()) == makeLowerCase(type1) && makeLowerCase(pokemonMapIt->second.getNewType2()) == makeLowerCase(type2)) ||
                           (makeLowerCase(pokemonMapIt->second.getNewType1()) == makeLowerCase(type2) && makeLowerCase(pokemonMapIt->second.getNewType2()) == makeLowerCase(type1)))
                        { //if both the new types equal both the user input types
                            resultMap.insert(make_pair(pokemonMapIt->second.getDexno(), pokemonMapIt->second));
                        }
                    }
                    else{ //type changed is false
                        if((makeLowerCase(pokemonMapIt->second.getOldType1()) == makeLowerCase(type1) && makeLowerCase(pokemonMapIt->second.getOldType2()) == makeLowerCase(type2)) ||
                           (makeLowerCase(pokemonMapIt->second.getOldType1()) == makeLowerCase(type2) && makeLowerCase(pokemonMapIt->second.getOldType2()) == makeLowerCase(type1)))
                        { //if both the old types equal the user input types
                            resultMap.insert(make_pair(pokemonMapIt->second.getDexno(), pokemonMapIt->second));
                        }
                    }
                }
            }
            else{ //there is no space, thus it is only one type
                type1 = inputString;
                for(pokemonMapIt = pokemonMap.begin(); pokemonMapIt != pokemonMap.end(); pokemonMapIt++){
                    if(pokemonMapIt->second.getTypeChanged() == true){
                        if(makeLowerCase(pokemonMapIt->second.getNewType1()) == makeLowerCase(type1) || makeLowerCase(pokemonMapIt->second.getNewType2()) == makeLowerCase(type1)){
                            resultMap.insert(make_pair(pokemonMapIt->second.getDexno(), pokemonMapIt->second));
                        }
                    }
                    else{ //type changed is false
                        if(makeLowerCase(pokemonMapIt->second.getOldType1()) == makeLowerCase(type1) || makeLowerCase(pokemonMapIt->second.getOldType2()) == makeLowerCase(type1)){
                            resultMap.insert(make_pair(pokemonMapIt->second.getDexno(), pokemonMapIt->second));
                        }
                    }
                }
            }
            if(resultMap.size() == 0){
                cout << "Either " << inputString << " isn't a type or there are no Pokemon with that combination." << endl;
                system("pause");
                continue;
            }
            for(pokemonMapIt = resultMap.begin(); pokemonMapIt != resultMap.end(); pokemonMapIt++){
                if(pokemonMapIt->second.getTypeChanged()){
                    firstType = (makeLowerCase(pokemonMapIt->second.getNewType1()) == makeLowerCase(inputString)? true : false);
                }
                if(pokemonMapIt->second.getTypeChanged() &&
                   firstType &&
                   pokemonMapIt->second.getNewType1() != pokemonMapIt->second.getOldType1() &&
                   pokemonMapIt->second.getNewType1() != pokemonMapIt->second.getOldType2()){
                    cout << '!';
                   }
                else if(pokemonMapIt->second.getTypeChanged() &&
                   !firstType &&
                   pokemonMapIt->second.getNewType2() != pokemonMapIt->second.getOldType1() &&
                   pokemonMapIt->second.getNewType2() != pokemonMapIt->second.getOldType2()){
                    cout << '!';
                   }
                else{
                    cout << ' ';
                }
                // cout << pokemonMapIt->first << " - " << pokemonMapIt->second.getName() << endl;
                printf("%03d - %-10s \n", pokemonMapIt->second.getDexno(), pokemonMapIt->second.getName().c_str());
            }
            system("pause");
        }
        else if(choice == 4){
            string output;
            string tmp;
            set<string> acquisition;
            set<string> pokeNames;
            set<string>::iterator setIt;
            bool found = false;
            cout << "Enter the full name of the move." << endl;
            cin.ignore();
            getline(cin, inputString);
            for(pokemonMapIt = pokemonMap.begin(); pokemonMapIt != pokemonMap.end(); pokemonMapIt++){
                pokeNames.clear();
                acquisition.clear();
                output = "";
                for(int i = 0; i < 30; i++){
                    if(makeLowerCase(pokemonMapIt->second.getLevelMoves(i).move.getName()) == makeLowerCase(inputString)){
                        pokeNames.insert(pokemonMapIt->second.getName());
                        acquisition.insert("lv. " + to_string(pokemonMapIt->second.getLevelMoves(i).level));
                        found = true;
                    }
                }
                for(int i = 0; i < 100; i++){
                    //if this pokemon is a match and isn't already in the map then insert
                    if((makeLowerCase(pokemonMapIt->second.getTmMoves(i).move.getName()) == makeLowerCase(inputString)) && (resultMap.count(pokemonMapIt->second.getDexno()) == 0)){ 
                        pokeNames.insert(pokemonMapIt->second.getName());
                        acquisition.insert(pokemonMapIt->second.getTmMoves(i).tmNo);
                        found = true;
                    }
                }
                if(pokeNames.size() != 0){
                    tmp = *pokeNames.begin();
                    printf("  %-10s - ", tmp.c_str());
                }
                if(acquisition.size() != 0){
                    for(setIt = acquisition.begin(); setIt != acquisition.end(); setIt++){
                        output += *setIt + ", ";
                    }
                    output.pop_back();
                    output.pop_back();
                    cout << output << endl;
                }
            }
            if(!found){
                cout << inputString << " was not found." << endl;
                system("pause");
                continue;
            }
            system("pause");
        }
        else if(choice == 5){
            searchPokemon(routeMap, resultMap);
        }
    }
}
void printPokemon(char choiceA[8], Pokemon pokemon){
    bool showType, showAbility, showStats, showExp, showTM, showLevel;
    showType = (choiceA[2] == 'y'? true : false);
    showAbility = (choiceA[3] == 'y'? true : false);
    showStats = (choiceA[4] == 'y'? true : false);
    showExp = (choiceA[5] == 'y'? true : false);
    showLevel = (choiceA[6] == 'y'? true : false);
    showTM = (choiceA[7] == 'y'? true : false);


    if(choiceA[0] == 'a'){
        cout << pokemon;
        return;
    }
    else if(choiceA[0] == 'r'){
        //name and dexno
        // cout << pokemon.getDexno() << " - " << pokemon.getName() << endl;
        printf("%03d - %s\n", pokemon.getDexno(), pokemon.getName().c_str());

        //typing
        if(pokemon.getTypeChanged() == true){
            cout << "  Old Type: " << pokemon.getOldType1();
            if(pokemon.getOldType2() != "None"){
                cout << " / " << pokemon.getOldType2();
            }
            cout << endl << "  New Type: " << pokemon.getNewType1();
            if(pokemon.getNewType2() != ""){
                cout << " / " << pokemon.getNewType2();
            }
        }
        else{ //statchanged == false
            cout << "  Type: " << pokemon.getOldType1();
            if(pokemon.getOldType2() != "None"){
                cout << " / " << pokemon.getOldType2();
            }
        }

        //ability
        if(pokemon.getAbilityChanged() == true){
            cout << endl << "  Old Ability: " << pokemon.getOldAbility1();
            if(pokemon.getOldAbility2() != "None"){
                cout << " / " << pokemon.getOldAbility2();
            }
            cout << endl << "  New Ability: " << pokemon.getNewAbility1();
            if(pokemon.getNewAbility2() != "None"){
                cout << " / " << pokemon.getNewAbility2();
            }
        }
        else{
            cout << endl << "  Ability: " << pokemon.getOldAbility1();
            if(pokemon.getOldAbility2() !="None"){
                cout << " / " << pokemon.getOldAbility2();
            }
        }
        //stats
        if(pokemon.getStatChanged() == true){
            cout << endl << "  Old Base Stats: "
            << pokemon.getOldHP() << " HP / " << pokemon.getOldAttack() << " Atk / " << pokemon.getOldDefense() << " Def / " << pokemon.getOldSpAttack()
            << " SpAtk / " << pokemon.getOldSpDefense() << " SpDef / " << pokemon.getOldSpeed() << " Spd / " << pokemon.getOldBST() << " BST" << endl;
            cout << "  New Base Stats: "
            << pokemon.getNewHP() << " HP / " << pokemon.getNewAttack() << " Atk / " << pokemon.getNewDefense() << " Def / " << pokemon.getNewSpAttack()
            << " SpAtk / " << pokemon.getNewSpDefense() << " SpDef / " << pokemon.getNewSpeed() << " Spd / " << pokemon.getNewBST() << " BST" << endl;
        }
        else{ //stats haven't been changed
            cout << endl << "  Base Stats: "
            << pokemon.getOldHP() << " HP / " << pokemon.getOldAttack() << " Atk / " << pokemon.getOldDefense() << " Def / " << pokemon.getOldSpAttack()
            << " SpAtk / " << pokemon.getOldSpDefense() << " SpDef / " << pokemon.getOldSpeed() << " Spd / " << pokemon.getOldBST() << " BST " << endl;
        }
        if(pokemon.getEvolution() != ""){
            cout << "  " << pokemon.getEvolution() << endl;
        }
        cout << "  Experience Group: " << pokemon.getExperience() << endl;
    }
    else{ //custom input
        printf("%03d - %s\n", pokemon.getDexno(), pokemon.getName().c_str());
        if(showType){
            if(pokemon.getTypeChanged() == true){
                cout << "  Old Type: " << pokemon.getOldType1();
                if(pokemon.getOldType2() != "None"){
                    cout << " / " << pokemon.getOldType2();
                }
                cout << endl << "  New Type: " << pokemon.getNewType1();
                if(pokemon.getNewType2() != "None"){
                    cout << " / " << pokemon.getNewType2();
                }
            }
            else{ //statchanged == false
                cout << "  Type: " << pokemon.getOldType1();
                if(pokemon.getOldType2() != "None"){
                    cout << " / " << pokemon.getOldType2();
                }
            }
            cout << endl;
        }
        if(showAbility){
            if(pokemon.getAbilityChanged() == true){
                cout << "  Old Ability: " << pokemon.getOldAbility1();
                if(pokemon.getOldAbility2() != "None"){
                    cout << " / " << pokemon.getOldAbility2();
                }
                cout << endl << "  New Ability: " << pokemon.getNewAbility1();
                if(pokemon.getNewAbility2() != "None"){
                    cout << " / " << pokemon.getNewAbility2();
                }
            }
            else{
                cout << endl << "  Ability: " << pokemon.getOldAbility1();
                if(pokemon.getOldAbility2() != "None"){
                    cout << " / " << pokemon.getOldAbility2();
                }
            }
            cout << endl;
        }
        if(showStats){
            if(pokemon.getStatChanged() == true){
                cout << "  Old Base Stats: "
                << pokemon.getOldHP() << " HP / " << pokemon.getOldAttack() << " Atk / " << pokemon.getOldDefense() << " Def / " << pokemon.getOldSpAttack()
                << " SpAtk / " << pokemon.getOldSpDefense() << " SpDef / " << pokemon.getOldSpeed() << " Spd / " << pokemon.getOldBST() << " BST" << endl;
                cout << "  New Base Stats: "
                << pokemon.getNewHP() << " HP / " << pokemon.getNewAttack() << " Atk / " << pokemon.getNewDefense() << " Def / " << pokemon.getNewSpAttack()
                << " SpAtk / " << pokemon.getNewSpDefense() << " SpDef / " << pokemon.getNewSpeed() << " Spd / " << pokemon.getNewBST() << " BST" << endl;
            }
            else{ //stats haven't been changed
                cout << endl << "  Base Stats: "
                << pokemon.getOldHP() << " HP / " << pokemon.getOldAttack() << " Atk / " << pokemon.getOldDefense() << " Def / " << pokemon.getOldSpAttack()
                << " SpAtk / " << pokemon.getOldSpDefense() << " SpDef / " << pokemon.getOldSpeed() << " Spd / " << pokemon.getOldBST() << " BST " << endl;
            }
        }
        if(showExp){
            cout << "  Experience Leveling Group: " << pokemon.getExperience() << endl;
        }
        if(showLevel){
            cout << "  Level up Learnset:" << endl;
            cout << "      Lvl - Name            Type     Category PP Pwr Acc" << endl << endl;
            for(int i = 0; i < 29; i++){
                if(pokemon.getLevelMoves(i).learn == true){
                    if(pokemon.getLevelMoves(i).newM == true)
                            cout << "     !";
                    else{ //not stab
                            cout << "      ";
                    }
                    if(pokemon.getLevelMoves(i).stab == true){
                        cout << "*";
                    }
                    else{
                        cout << " ";
                    }
                    printf("%2d - ", pokemon.getLevelMoves(i).level);
                    cout << pokemon.getLevelMoves(i).move << endl;
                }
            }
        }
        if(showTM){
            cout << "  TM Learnset:" << endl;
            cout << "     TM## - Name            Type     Category PP Pwr Acc" << endl << endl;
            for(int i = 0; i <= 99; i++){
                if(pokemon.getTmMoves(i).canLearn == true){
                    if(pokemon.getTmMoves(i).newM == true)
                        cout << "   !";
                    else{ //not stab
                        cout << "    ";
                    }
                    if(pokemon.getTmMoves(i).stab == true){
                        cout << "*";
                    }
                    else{
                        cout << " ";
                    }
                    cout << pokemon.getTmMoves(i).tmNo << " - " << pokemon.getTmMoves(i).move << endl;
                }
            }
        }
    }
}
void showChanges(multimap<int, Pokemon> &pokemonMap){
    int SCchoice = 0;
    string inputString;
    char choiceA[8] = {'y', 'y', 'n', 'n', 'n', 'n', 'n', 'n'};
    multimap<int, Pokemon> resultMap;
    multimap<int, Pokemon>::iterator pokemonMapIt;
    string useless;
    while(SCchoice != 5){
        cout << "=============Pokemon Changes=============" << endl;
        cout << "  1 - Show all changes" << endl;
        cout << "  2 - Show type changes" << endl;
        cout << "  3 - Show ability changes" << endl;
        cout << "  4 - Show stat changes" << endl;
        cout << "  5 - Return to main menu" << endl;
        cout << "=========================================" << endl;
        cin >> inputString;
        if(!is_number(inputString) || stoi(inputString) < 1 || stoi(inputString) > 5){
            cout << "Please enter a number between 1 and 5." << endl;
            system("pause");
            continue;
        }
        SCchoice = stoi(inputString);
        resultMap.clear();
        if(SCchoice == 1){
            for(pokemonMapIt = pokemonMap.begin(); pokemonMapIt != pokemonMap.end(); pokemonMapIt++){
                if(pokemonMapIt->second.getTypeChanged() || pokemonMapIt->second.getAbilityChanged() || pokemonMapIt->second.getStatChanged()){
                    resultMap.insert(make_pair(pokemonMapIt->second.getDexno(), pokemonMapIt->second));
                }
            }
            cout << "result map size is: " << resultMap.size() << endl;
            for(pokemonMapIt = resultMap.begin(); pokemonMapIt != resultMap.end(); pokemonMapIt++){
                if(pokemonMapIt->second.getTypeChanged() && pokemonMapIt->second.getAbilityChanged() && pokemonMapIt->second.getStatChanged()){
                    choiceA[2] = 'y';
                    choiceA[3] = 'y';
                    choiceA[4] = 'y';
                    printPokemon(choiceA, pokemonMapIt->second);
                }
                else if(pokemonMapIt->second.getTypeChanged() && pokemonMapIt->second.getAbilityChanged() && !pokemonMapIt->second.getStatChanged()){
                    choiceA[2] = 'y';
                    choiceA[3] = 'y';
                    choiceA[4] = 'n';
                    printPokemon(choiceA, pokemonMapIt->second);
                }
                else if(pokemonMapIt->second.getTypeChanged() && !pokemonMapIt->second.getAbilityChanged() && !pokemonMapIt->second.getStatChanged()){
                    choiceA[2] = 'y';
                    choiceA[3] = 'n';
                    choiceA[4] = 'n';
                    printPokemon(choiceA, pokemonMapIt->second);
                }
                else if(pokemonMapIt->second.getTypeChanged() && !pokemonMapIt->second.getAbilityChanged() && pokemonMapIt->second.getStatChanged()){
                    choiceA[2] = 'y';
                    choiceA[3] = 'n';
                    choiceA[4] = 'y';
                    printPokemon(choiceA, pokemonMapIt->second);
                }
                else if(!pokemonMapIt->second.getTypeChanged() && pokemonMapIt->second.getAbilityChanged() && pokemonMapIt->second.getStatChanged()){
                    choiceA[2] = 'n';
                    choiceA[3] = 'y';
                    choiceA[4] = 'y';
                    printPokemon(choiceA, pokemonMapIt->second);
                }
                else if(!pokemonMapIt->second.getTypeChanged() && pokemonMapIt->second.getAbilityChanged() && !pokemonMapIt->second.getStatChanged()){
                    choiceA[2] = 'n';
                    choiceA[3] = 'y';
                    choiceA[4] = 'n';
                    printPokemon(choiceA, pokemonMapIt->second);
                }
                else if(!pokemonMapIt->second.getTypeChanged() && !pokemonMapIt->second.getAbilityChanged() && pokemonMapIt->second.getStatChanged()){
                    choiceA[2] = 'n';
                    choiceA[3] = 'n';
                    choiceA[4] = 'y';
                    printPokemon(choiceA, pokemonMapIt->second);
                }
            }
        }
        else if(SCchoice == 2){
            choiceA[2] = 'y';
            choiceA[3] = 'n';
            choiceA[4] = 'n';
            for(pokemonMapIt = pokemonMap.begin(); pokemonMapIt != pokemonMap.end(); pokemonMapIt++){
                if(pokemonMapIt->second.getTypeChanged()){
                    resultMap.insert(make_pair(pokemonMapIt->second.getDexno(), pokemonMapIt->second));
                }
            }
            for(pokemonMapIt = resultMap.begin(); pokemonMapIt != resultMap.end(); pokemonMapIt++){
                printPokemon(choiceA, pokemonMapIt->second);
            }
        }
        else if(SCchoice == 3){
            choiceA[2] = 'n';
            choiceA[3] = 'y';
            choiceA[4] = 'n';
            for(pokemonMapIt = pokemonMap.begin(); pokemonMapIt != pokemonMap.end(); pokemonMapIt++){
                if(pokemonMapIt->second.getAbilityChanged()){
                    resultMap.insert(make_pair(pokemonMapIt->second.getDexno(), pokemonMapIt->second));
                }
            }
            for(pokemonMapIt = resultMap.begin(); pokemonMapIt != resultMap.end(); pokemonMapIt++){
                printPokemon(choiceA, pokemonMapIt->second);
            }
        }
        else if(SCchoice == 4){
            choiceA[2] = 'n';
            choiceA[3] = 'n';
            choiceA[4] = 'y';
            for(pokemonMapIt = pokemonMap.begin(); pokemonMapIt != pokemonMap.end(); pokemonMapIt++){
                if(pokemonMapIt->second.getStatChanged()){
                    resultMap.insert(make_pair(pokemonMapIt->second.getDexno(), pokemonMapIt->second));
                }
            }
            for(pokemonMapIt = resultMap.begin(); pokemonMapIt != resultMap.end(); pokemonMapIt++){
                printPokemon(choiceA, pokemonMapIt->second);
            }
        }
        if(SCchoice != 5){
            system("pause");
        }
    }
}