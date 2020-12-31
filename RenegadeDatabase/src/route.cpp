#include "./route.hpp"
/* Default Constructor
 * Returns nothing
 * Has no parameters
 * Constructs a pokemon
 */
Route::Route(){}
ostream& operator<<(ostream& outStream, const Route& route){
    unordered_multimap<string, commonTrainerStruct>::const_iterator trainerMapIt;
    unordered_multimap<string, int>::const_iterator trainerTeamIt;
    map<string, int>::const_iterator encounterMapIt;
    vector<itemStruct>::const_iterator itemIt;
    vector<bossTrainer>::const_iterator bossIt;
    vector<bossPokemon>::const_iterator teamIt;
    bool mornDayNightEquiv = false;
    bool mornDayEquiv = false;
    bool goodOldEquiv = false;
    int padding;
    string output = "";
    padding = 28 - (route.getFullName().size() / 2);
    outStream << "========================================================" << endl;
    for(int i = 0; i < padding; i++) outStream << ' ';
    outStream << route.getFullName() << endl;
    outStream << "========================================================" << endl;
    if(route.trainerMap.size() != 0){
        outStream << "  ----------------------Trainers----------------------" << endl;
        for(trainerMapIt = route.trainerMap.cbegin(); trainerMapIt != route.trainerMap.cend(); trainerMapIt++){
            outStream << "  " << trainerMapIt->first << endl;
            outStream << "    ";
            for(trainerTeamIt = trainerMapIt->second.firstTeam.cbegin(); trainerTeamIt != trainerMapIt->second.firstTeam.cend(); trainerTeamIt++){
                output += trainerTeamIt->first + " Lv. " + to_string(trainerTeamIt->second) + ", ";
            }
            output.pop_back();
            output.pop_back();
            outStream << output << endl;
            output = "";
            if(trainerMapIt->second.secondTeam.size() != 0){
                outStream << "    ";
                for(trainerTeamIt = trainerMapIt->second.secondTeam.cbegin(); trainerTeamIt != trainerMapIt->second.secondTeam.cend(); trainerTeamIt++){
                    output += trainerTeamIt->first + " Lv. " + to_string(trainerTeamIt->second) + ", ";
                }
                output.pop_back();
                output.pop_back();
                output += " (3)";
                outStream << output << endl;
                output = "";
            }
            if(trainerMapIt->second.thirdTeam.size() != 0){
                outStream << "    ";
                for(trainerTeamIt = trainerMapIt->second.thirdTeam.cbegin(); trainerTeamIt != trainerMapIt->second.thirdTeam.cend(); trainerTeamIt++){
                    output += trainerTeamIt->first + " Lv. " + to_string(trainerTeamIt->second) + ", ";
                }
                output.pop_back();
                output.pop_back();
                output += " (5)";
                outStream << output << endl;
                output = "";
            }
            if(trainerMapIt->second.fourthTeam.size() != 0){
                outStream << "    ";
                for(trainerTeamIt = trainerMapIt->second.fourthTeam.cbegin(); trainerTeamIt != trainerMapIt->second.fourthTeam.cend(); trainerTeamIt++){
                    output += trainerTeamIt->first + " Lv. " + to_string(trainerTeamIt->second) + ", ";
                }
                output.pop_back();
                output.pop_back();
                output += " (8)";
                outStream << output << endl;
                output = "";
            }
            if(trainerMapIt->second.fifthTeam.size() != 0){
                outStream << "    ";
                for(trainerTeamIt = trainerMapIt->second.fifthTeam.cbegin(); trainerTeamIt != trainerMapIt->second.fifthTeam.cend(); trainerTeamIt++){
                    output += trainerTeamIt->first + " Lv. " + to_string(trainerTeamIt->second) + ", ";
                }
                output.pop_back();
                output.pop_back();
                output += " (C)";
                outStream << output << endl;
                output = "";
            }
            if(trainerMapIt->second.sixthTeam.size() != 0){
                outStream << "    ";
                for(trainerTeamIt = trainerMapIt->second.sixthTeam.cbegin(); trainerTeamIt != trainerMapIt->second.sixthTeam.cend(); trainerTeamIt++){
                    output += trainerTeamIt->first + " Lv. " + to_string(trainerTeamIt->second) + ", ";
                }
                output.pop_back();
                output.pop_back();
                output += " (S)";
                outStream << output << endl;
                output = "";
            }
        }
        outStream << "  ----------------------------------------------------" << endl;
    }

    if(route.bossTrainers.size() != 0){
        outStream << "  ------------------------Bosses----------------------" << endl;
        for(bossIt = route.bossTrainers.cbegin(); bossIt != route.bossTrainers.cend(); bossIt++){
            outStream << "  " << bossIt->name << endl;
            for(teamIt = bossIt->team.cbegin(); teamIt != bossIt->team.cend(); teamIt++){
                printf("    %-10s (Lv. %d) @ %-12s", teamIt->name.c_str(), teamIt->level, teamIt->item.c_str());
                if(teamIt->nature != "?"){
                    printf(" / %-7s", teamIt->nature.c_str());
                }
                printf(" / %-12s / %s,%s,%s,%s\n", teamIt->ability.c_str(), teamIt->moves[0].c_str(), teamIt->moves[1].c_str(), teamIt->moves[2].c_str(), teamIt->moves[3].c_str());
            }
        }
        outStream << "  ----------------------------------------------------" << endl;
    }
    //onto the wild pokemon section
    if(route.morningMap.size() != 0 || route.surfMap.size() != 0 || route.honeyTreeMap.size() != 0){
        outStream << "  ---------------------Wild Pokemon-------------------" << endl;
        if(route.morningMap == route.dayMap && route.dayMap == route.nightMap && route.morningMap.size() != 0){
            mornDayNightEquiv = true;
            outStream << "  Morning, Day, and Night Encounters - Levels: " << route.walkingLevelLow << " - " << route.walkingLevelHigh << endl;
            outStream << "    ";
            for(encounterMapIt = route.morningMap.cbegin(); encounterMapIt != route.morningMap.cend(); encounterMapIt++){
                output += encounterMapIt->first + " (" + to_string(encounterMapIt->second) + "%), ";
            }
            //this erases the ", " from the very last pokemon
            output.pop_back();
            output.pop_back();
            outStream << output << endl;
            output = "";
        }
        else if(route.morningMap == route.dayMap && route.dayMap != route.nightMap && route.morningMap.size() != 0){
            mornDayEquiv = true;
            outStream << "  Morning and Day Encounters - Levels: " << route.walkingLevelLow << " - " << route.walkingLevelHigh << endl;
            outStream << "    ";
            for(encounterMapIt = route.morningMap.cbegin(); encounterMapIt != route.morningMap.cend(); encounterMapIt++){
                output += encounterMapIt->first + " (" + to_string(encounterMapIt->second) + "%), ";
            }
            //this erases the ", " from the very last pokemon
            output.pop_back();
            output.pop_back();
            outStream << output << endl;
            output = "";
        }
        if(route.morningMap.size() != 0 && !mornDayNightEquiv && !mornDayEquiv){
            outStream << "  Morning Encounters - Levels: " << route.walkingLevelLow << " - " << route.walkingLevelHigh << endl;
            outStream << "    ";
            for(encounterMapIt = route.morningMap.cbegin(); encounterMapIt != route.morningMap.cend(); encounterMapIt++){
                output += encounterMapIt->first + " (" + to_string(encounterMapIt->second) + "%), ";
            }
            //this erases the ", " from the very last pokemon
            output.pop_back();
            output.pop_back();
            outStream << output << endl;
            output = "";
        }
        if(route.dayMap.size() != 0 && !mornDayNightEquiv && !mornDayEquiv){
            outStream << "  Day Encounters - Levels: " << route.walkingLevelLow << " - " << route.walkingLevelHigh << endl;
            outStream << "    ";
            for(encounterMapIt = route.dayMap.cbegin(); encounterMapIt!= route.dayMap.cend(); encounterMapIt++){
                output += encounterMapIt->first + " (" + to_string(encounterMapIt->second) + "%), ";
            }
            //this erases the ", " from the very last pokemon
            output.pop_back();
            output.pop_back();
            outStream << output << endl;
            output = "";
        }
        if(route.nightMap.size() != 0 && !mornDayNightEquiv){
            outStream << "  Night Encounters - Levels: " << route.walkingLevelLow << " - " << route.walkingLevelHigh << endl;
            outStream << "    ";
            for(encounterMapIt = route.nightMap.cbegin(); encounterMapIt!= route.nightMap.cend(); encounterMapIt++){
                output += encounterMapIt->first + " (" + to_string(encounterMapIt->second) + "%), ";
            }
            //this erases the ", " from the very last pokemon
            output.pop_back();
            output.pop_back();
            outStream << output << endl;
            output = "";
        }
        if(route.surfMap.size() != 0){
            outStream << "  Surf Encounters - Levels: " << route.surfingLevelLow << " - " << route.surfingLevelHigh << endl;
            outStream << "    ";
            for(encounterMapIt = route.surfMap.cbegin(); encounterMapIt != route.surfMap.cend(); encounterMapIt++){
                output += encounterMapIt->first + " (" + to_string(encounterMapIt->second) + "%), ";
            }
            //this erases the ", " from the very last pokemon
            output.pop_back();
            output.pop_back();
            outStream << output << endl;
            output = "";
        }
        if(route.oldRodMap == route.goodRodMap && route.oldRodMap.size() != 0){
            goodOldEquiv = true;
            outStream << "  Old Rod and Good Rod Encounters - Level: 10 and Level: 25" << endl;
            outStream << "    ";
            for(encounterMapIt = route.oldRodMap.cbegin(); encounterMapIt != route.oldRodMap.cend(); encounterMapIt++){
                output += encounterMapIt->first + " (" + to_string(encounterMapIt->second) + "%), ";
            }
            //this erases the ", " from the very last pokemon
            output.pop_back();
            output.pop_back();
            outStream << output << endl;
            output = "";
        }
        if(route.oldRodMap.size() != 0 && !goodOldEquiv){
            outStream << "  Old Rod Encounters - Level: 10" << endl;
            outStream << "    ";
            for(encounterMapIt = route.oldRodMap.cbegin(); encounterMapIt != route.oldRodMap.cend(); encounterMapIt++){
                output += encounterMapIt->first + " (" + to_string(encounterMapIt->second) + "%), ";
            }
            //this erases the ", " from the very last pokemon
            output.pop_back();
            output.pop_back();
            outStream << output << endl;
            output = "";
        }
        if(route.goodRodMap.size() != 0 && !goodOldEquiv){
            outStream << "  Good Rod Encounters - Level: 25" << endl;
            outStream << "    ";
            for(encounterMapIt = route.goodRodMap.cbegin(); encounterMapIt != route.goodRodMap.cend(); encounterMapIt++){
                output += encounterMapIt->first + " (" + to_string(encounterMapIt->second) + "%), ";
            }
            //this erases the ", " from the very last pokemon
            output.pop_back();
            output.pop_back();
            outStream << output << endl;
            output = "";
        }
        if(route.superRodMap.size() != 0){
            outStream << "  Super Rod Encounters - Level: 50" << endl;
            outStream << "    ";
            for(encounterMapIt = route.superRodMap.cbegin(); encounterMapIt != route.superRodMap.cend(); encounterMapIt++){
                output += encounterMapIt->first + " (" + to_string(encounterMapIt->second) + "%), ";
            }
            //this erases the ", " from the very last pokemon
            output.pop_back();
            output.pop_back();
            outStream << output << endl;
            output = "";
        }
        if(route.pokeRadarMap.size() != 0){
            outStream << "  Poke Radar Encounters - Levels: " << route.walkingLevelLow << " - " << route.walkingLevelHigh << endl;
            outStream << "    ";
            for(encounterMapIt = route.pokeRadarMap.cbegin(); encounterMapIt != route.pokeRadarMap.cend(); encounterMapIt++){
                output += encounterMapIt->first + " (" + to_string(encounterMapIt->second) + "%), ";
            }
            //this erases the ", " from the very last pokemon
            output.pop_back();
            output.pop_back();
            outStream << output << endl;
            output = "";
        }
        if(route.honeyTreeMap.size() != 0){
            outStream << "  Honey Tree Encounters - Level: " << route.honeyLevel << endl;
            outStream << "    ";
            for(encounterMapIt = route.honeyTreeMap.cbegin(); encounterMapIt!= route.honeyTreeMap.cend(); encounterMapIt++){
                output += encounterMapIt->first + " (" + to_string(encounterMapIt->second) + "%), ";
            }
            //this erases the ", " from the very last pokemon
            output.pop_back();
            output.pop_back();
            outStream << output << endl;
            output = "";
        }
        outStream << "  ----------------------------------------------------" << endl;
    }
    if(route.itemVec.size() != 0){
        outStream << "  ------------------------Items-----------------------" << endl;
        for(itemIt = route.itemVec.cbegin(); itemIt != route.itemVec.cend(); itemIt++){
            // outStream << "name is: " << itemIt->name << endl;
            // outStream << "method is: " << itemIt->method << endl;
            printf("    %-23s - %-22s", itemIt->name.c_str(), itemIt->method.c_str());
            outStream << endl;
        }
        outStream << "  ----------------------------------------------------" << endl;
    } 
    return(outStream);
}

void Route::clearRoute(){
    morningMap.clear();
    dayMap.clear();
    nightMap.clear();
    surfMap.clear();
    oldRodMap.clear();
    goodRodMap.clear();
    superRodMap.clear();
    pokeRadarMap.clear();
    honeyTreeMap.clear();
    trainerMap.clear();
}
unordered_multimap<string, int> insertTrainerTeam(string input){
    string pokemonName;
    int pokemonLevel;
    unordered_multimap<string, int> returnTeam;
    while(input.find("Lv.") != string::npos){
        pokemonName = input.substr(0, input.find("Lv.")-1); //get the name
        // cout << pokemonName << endl;

        input.erase(0, input.find("Lv.")+4); //erases "Psyduck Lv. "10
        pokemonLevel = stoi(input.substr(0, 2)); //get the level

        returnTeam.insert(make_pair(pokemonName, pokemonLevel));

        input.erase(0, 4); //erases "10, "Sunskern, aka prepares data for next loop
    }
    return(returnTeam);
}
map<string, Route*> readRoute(string fileName){
    map<string, Route*> routeMap;
	multimap<int, Pokemon>::iterator pokemonMapIt;
	/*for(pokemonMapIt = pokemonMap.begin(); pokemonMapIt != pokemonMap.end(); pokemonMapIt++){
		cout << pokemonMapIt->second << endl;
	}*/
	ifstream wildPokemon; //whole file ifstream
	Pokemon pokemon;
    Route *route;
    
    string routeString, singleLine, routeName, routeLevels, equalsbars, pokemonName, encounterCondition = "";
    int walkingLevelLow, walkingLevelHigh, surfingLevelLow, surfingLevelHigh, honeyLevel;
    wildPokemon.open(fileName);
    if(wildPokemon.fail()){ //does the file exist?
        cout << fileName << " does not exist." << endl;
		exit(1);
    }
    if(wildPokemon.peek()==EOF){ //is the file empty?
        cout << fileName << " is empty." << endl;
        exit(1);
    }

    while(!wildPokemon.eof()){
        route = new Route();
        getline(wildPokemon, routeName);
        getline(wildPokemon, routeLevels);
        getline(wildPokemon, equalsbars);
        singleLine = "";
        routeString = "";
        pokemon.clearPokemon();
		while(singleLine != " "){
            getline(wildPokemon, singleLine);
            //cout << "single line is:" << singleLine << endl;
			routeString += (singleLine + "\n");
		}
        route->setFullName(routeName); //Mt. Coronet ~ B1F
        if(routeName.find("~") != string::npos){
            route->setSectionName(routeName.substr(routeName.find("~") + 2, routeName.length() - (routeName.find("~") + 2))); // B1F
            // routeName.erase(routeName.find("~")-1, routeName.length() - routeName.find("~")-1); //erase the extra data
            routeName.erase(routeName.find("~")-1, 15); //erase the extra data
            route->setMainName(routeName); //Mt. Coronet
            route->setHasSubsections(true);
            // cout << "full name is ~" << route->fullName << "~" << endl;
            // cout << "mainName is: ~" << route->mainName << "~" << endl;
            // cout << "section name is: ~" << route->sectionName << "~" << endl;
        }
        else{
            route->setHasSubsections(false);
        }

        routeLevels.erase(0, 8); //erase "Levels: "
        //erase the information from the previous route.
        
        // walkingLevelLow = 0;
        // walkingLevelHigh = 0;
        // surfingLevelLow = 0;
        // surfingLevelHigh = 0;
        // honeyLevel = 0;
        // allRods = false;

        do{ //this loop is used to determine the levels in that route
            if(routeLevels.find("(Walking)") != string::npos){
                walkingLevelLow = stoi(routeLevels.substr(0, routeLevels.find("-") - 1));
                walkingLevelHigh = stoi(routeLevels.substr((routeLevels.find("-") + 2), (routeLevels.find("(") - 1) - (routeLevels.find("-") + 2)));
                routeLevels.erase(0, routeLevels.find(")") + 3);
                route->setWalkingLevelHigh(walkingLevelHigh);
                route->setWalkingLevelLow(walkingLevelLow);
            }
            else if(routeLevels.find("(Surfing)") != string::npos){
                surfingLevelLow = stoi(routeLevels.substr(0, routeLevels.find("-") - 1));
                surfingLevelHigh = stoi(routeLevels.substr((routeLevels.find("-") + 2), (routeLevels.find("(") - 1) - (routeLevels.find("-") + 2)));
                routeLevels.erase(0, routeLevels.find(")") + 3);
                route->setSurfingLevelHigh(surfingLevelHigh);
                route->setSurfingLevelLow(surfingLevelLow);
            }
            else if(routeLevels.find("(Honey Tree)") != string::npos){
                honeyLevel = stoi(routeLevels.substr(0, routeLevels.find("(") - 1));
                routeLevels.erase(0, routeLevels.find(")") + 3);
                route->setHoneyLevel(honeyLevel);
            }
            else if(routeLevels.find("(All Rods)")){
                // allRods = true;
                routeLevels.erase(0, routeLevels.find(")") + 3);
            }
        }while(routeLevels.find(")") != string::npos);

        // cout << route->fullName << endl;
        while(routeString.find("Morning") != string::npos ||
              routeString.find("Day") != string::npos ||
              routeString.find("Night") != string::npos ||
              routeString.find("Surf") != string::npos ||
              routeString.find("Poke Radar") != string::npos ||
              routeString.find("Old Rod") != string::npos ||
              routeString.find("Good Rod") != string::npos ||
              routeString.find("Super Rod") != string::npos || 
              routeString.find("Honey Tree") != string::npos)
        {
            if(routeString.find("Morning") != string::npos){
                encounterCondition = routeString.substr(12, routeString.find("\n") - 12); //12 erases the section name
                // cout << "  Morning - Levels: " << walkingLevelLow << " - " << walkingLevelHigh << endl << "    ";
                // cout << route->fullName << endl;
                // cout << "  morning map size is " << route->morningMap.size() << endl;
                route->setMorningMap(insertWild(encounterCondition)); //insert all these pokemon in the morning map
                routeString.erase(0, routeString.find("\n") +1); //erase data for loop
                // cout << "    morning map size is now: " << route->morningMap.size();
                // cout << endl;
            }
            else if(routeString.find("Day") != string::npos){
                encounterCondition = routeString.substr(12, routeString.find("\n") - 12); //12 erases the section name
                // cout << endl << "  Day - Levels: " << walkingLevelLow << " - " << walkingLevelHigh << endl << "    ";
                route->setDayMap(insertWild(encounterCondition)); //insert all these pokemon in the morning map
                routeString.erase(0, routeString.find("\n") +1);
            }
            else if(routeString.find("Night") != string::npos){
                encounterCondition = routeString.substr(12, routeString.find("\n") - 12); //12 erases the section name
                // cout << endl << "  Night - Levels: " << walkingLevelLow << " - " << walkingLevelHigh << endl << "    ";
                route->setNightMap(insertWild(encounterCondition)); //insert all these pokemon in the morning map
                routeString.erase(0, routeString.find("\n") +1);
            }
            else if(routeString.find("Poke Radar") != string::npos){
                encounterCondition = routeString.substr(12, routeString.find("\n") - 12); //12 erases the section name
                // cout << endl << "  Poke Radar - Levels: " << walkingLevelLow << " - " << walkingLevelHigh << endl << "    ";
                route->setPokeRadarMap(insertWild(encounterCondition)); //insert all these pokemon in the morning map
                routeString.erase(0, routeString.find("\n") +1);
            }
            else if(routeString.find("Surf") != string::npos){
                encounterCondition = routeString.substr(12, routeString.find("\n") - 12); //12 erases the section name
                // cout << endl << "  Surfing - Levels: " << surfingLevelLow << " - " << surfingLevelHigh << endl << "    ";
                route->setSurfMap(insertWild(encounterCondition)); //insert all these pokemon in the morning map
                routeString.erase(0, routeString.find("\n") +1);
            }
            else if(routeString.find("Old Rod") != string::npos){
                encounterCondition = routeString.substr(12, routeString.find("\n") - 12); //12 erases the section name
                // if(allRods == true){//just if the route is the resort
                //     // cout << endl << "  Old Rod - Levels: 1-100" << endl << "    ";
                // }
                // else{
                //     // cout << endl << "  Old Rod - Level: 10" << endl << "    ";
                // }
                route->setOldRodMap(insertWild(encounterCondition)); //insert all these pokemon in the morning map
                routeString.erase(0, routeString.find("\n") +1);
            }
            else if(routeString.find("Good Rod") != string::npos){
                encounterCondition = routeString.substr(12, routeString.find("\n") - 12); //12 erases the section name
                // if(allRods == true){//just if the route is the resort
                //     // cout << endl << "  Good Rod - Levels: 1-100" << endl << "    ";
                // }
                // else{
                //     // cout << endl << "  Good Rod - Level: 25" << endl << "    ";
                // }
                route->setGoodRodMap(insertWild(encounterCondition)); //insert all these pokemon in the morning map
                routeString.erase(0, routeString.find("\n") +1);
            }
            else if(routeString.find("Super Rod") != string::npos){
                encounterCondition = routeString.substr(12, routeString.find("\n") - 12); //12 erases the section name
                // if(allRods == true){//just if the route is the resort
                //     // cout << endl << "  Super Rod - Levels: 1-100" << endl << "    ";
                // }
                // else{
                //     // cout << endl << "  Super Rod - Level: 50" << endl << "    ";
                // }
                route->setSuperRodMap(insertWild(encounterCondition)); //insert all these pokemon in the morning map
                routeString.erase(0, routeString.find("\n") +1);
            }
            else if(routeString.find("Honey Tree") != string::npos){
                encounterCondition = routeString.substr(12, routeString.find("\n") - 12); //12 erases the section name
                // cout << endl << "  Honey Tree - Level: " << honeyLevel << endl << "    ";
                route->setHoneyTreeMap(insertWild(encounterCondition)); //insert all these pokemon in the morning map
                routeString.erase(0, routeString.find("\n") +1);
            }
        }
        routeMap.insert(make_pair(route->getFullName(), route));
    }
    return(routeMap);
}
map<string, Route*> readTrainers(string fileName, map<string, Route*> &routeMap){
    ifstream trainerPokemon; //whole file ifstream
    string routeName, equalsbars, singleLine, routeData, trainerName, pokemonName;
    Route *route;
    Pokemon pokemon;
    commonTrainerStruct trainer;
    multimap<int, Pokemon>::iterator pokemonMapIt;
    map<string, Route*>::iterator routeMapIt;
    unordered_multimap<string, commonTrainerStruct>::iterator trainerMapIt;

    trainerPokemon.open(fileName);
        if(trainerPokemon.fail()){ //does the file exist?
        cout << fileName << " does not exist." << endl;
		exit(1);
    }
    if(trainerPokemon.peek()==EOF){ //is the file empty?
        cout << fileName << " is empty." << endl;
        exit(1);
    }
    while(!trainerPokemon.eof()){
        getline(trainerPokemon, routeName);
        getline(trainerPokemon, equalsbars);
        singleLine = "";
        routeData = "";
        pokemonName = "";
        while(singleLine != "==========="){
            getline(trainerPokemon, singleLine);
            routeData += singleLine + '\n';
        }

        if(routeMap.count(routeName) > 0){
            routeMapIt = routeMap.find(routeName);
            route = routeMapIt->second;
            // cout << routeName << " has a match." << endl;
        }
        else{
            // cout << routeName << " does not have a match." << endl;
            route = new Route();
            // route->clearRoute();
            // route->trainerMap.clear();
            route->setFullName(routeName);
            routeMap.insert(make_pair(route->getFullName(), route));
            //add a search for the ~ to find subsection and main name
            //set main name
            //set sub section
        }
        // route->getTrainerMap().clear();
        //now within just the trainers section of a route
        while(singleLine != " " && singleLine != ""){ //single line will equal just one line of trainers and their pokemon
            singleLine = routeData.substr(0, routeData.find("\n"));
            if(singleLine != "==========="){
                trainerName = singleLine.substr(0, singleLine.find("  "));
            }
            else{
                break;
            }
            trainer.name = trainerName;
            //cout << "beginning of loop" << endl;
            //cout << "trainer name is" << trainer.name << endl;
            singleLine.erase(0, 28);
            //ok now single line contains just the team of that trainer
            trainer.firstTeam = insertTrainerTeam(singleLine);
            route->getTrainerMap().insert(make_pair(trainer.name, trainer));
            routeData.erase(0, routeData.find("\n")+1);
            singleLine = routeData.substr(0, routeData.find("\n"));
            //cout << "singleline is: " << singleLine << endl;
        }
        if(routeData.find("Rematches") != string::npos){
            routeData.erase(0, routeData.find("Rematches") + 10); //+10 erases rematches and the newline after
            singleLine = routeData.substr(0, routeData.find("\n")); //reset single line here since it was last equal to "" or " "
            while(singleLine != " " && singleLine != "" && singleLine != "==========="){ //while there are still trainers
                singleLine = routeData.substr(0, routeData.find("\n")); //now that we're in the loop, single line needs to be data

                trainerName = singleLine.substr(0, singleLine.find("(") - 1);
                trainerMapIt = route->getTrainerMap().find(trainerName);
                // trainer = trainerMapIt->second;

                if(singleLine.find("(3)") != string::npos){
                    singleLine.erase(0, 28);
                    //ok now single line contains just the team of that trainer
                    //cout << "single line 3 is " << singleLine << endl;
                    trainerMapIt->second.secondTeam = insertTrainerTeam(singleLine);
                }
                else if(singleLine.find("(5)") != string::npos){
                    singleLine.erase(0, 28);
                    //cout << "singleline is" << singleLine << endl;
                    //ok now single line contains just the team of that trainer
                    trainerMapIt->second.thirdTeam = insertTrainerTeam(singleLine);
                }
                else if(singleLine.find("(8)") != string::npos){
                    singleLine.erase(0, 28);
                    //ok now single line contains just the team of that trainer
                    trainerMapIt->second.fourthTeam = insertTrainerTeam(singleLine);
                }
                else if(singleLine.find("(C)") != string::npos){
                    singleLine.erase(0, 28);
                    //ok now single line contains just the team of that trainer
                    trainerMapIt->second.fifthTeam = insertTrainerTeam(singleLine);
                }
                else if(singleLine.find("(S)") != string::npos){
                    singleLine.erase(0, 28);
                    //ok now single line contains just the team of that trainer
                    trainerMapIt->second.sixthTeam = insertTrainerTeam(singleLine);
                }
                routeData.erase(0, routeData.find('\n') + 1); //erase this trainer
                singleLine = routeData.substr(0, routeData.find("\n")); //reset single line to the next trainer
            }
        }
    }
    return(routeMap);
}
map<string, int> insertWild(string input){
    map<string, int> returnMap; //this map is meant to be a map of wild pokemon
    multimap<int, Pokemon>::iterator pokemonMapIt;
    string pokemonName;
    int encounterRate;
    while(input.find(")") != string::npos){
        pokemonName = input.substr(0, input.find("(") - 1);
        encounterRate = stoi(input.substr((input.find("(")+1), (input.find(")")-2) - input.find("(")));

        returnMap.insert(make_pair(pokemonName, encounterRate));
        input.erase(0, input.find(")")+3); //erase this pokemon so we can go to next
    }
    return(returnMap);
}
map<string, Route*> insertItems(string itemFileName, map<string, Route*> &routeMap){
	ifstream itemInput;
    ifstream TMInput;
    string TMFileName = "./input/TMLocations.csv";
    string singleLine, itemName, itemMethod, location;
    set<itemStruct> items;
    itemStruct item;
    int numlocations;
    bool newLocation;
    map<string, Route*>::iterator routeMapIt;

    Route* HearthomeCity;
    HearthomeCity = new Route();
    HearthomeCity->setFullName("Hearthome City");
    routeMap.insert(make_pair(HearthomeCity->getFullName(), HearthomeCity));
    
    Route* SolaceonTown;
    SolaceonTown = new Route();
    SolaceonTown->setFullName("Solaceon Town");
    routeMap.insert(make_pair(SolaceonTown->getFullName(), SolaceonTown));

    Route* FullmoonIsland;
    FullmoonIsland = new Route();
    FullmoonIsland->setFullName("Fullmoon Island");
    routeMap.insert(make_pair(FullmoonIsland->getFullName(), FullmoonIsland));

    Route* SurvivalArea;
    SurvivalArea = new Route();
    SurvivalArea->setFullName("Survival Area");
    routeMap.insert(make_pair(SurvivalArea->getFullName(), SurvivalArea));

    Route* SandgemTown;
    SandgemTown = new Route();
    SandgemTown->setFullName("Sandgem Town");
    routeMap.insert(make_pair(SandgemTown->getFullName(), SandgemTown));

	itemInput.open(itemFileName);

    if(itemInput.fail()){ //does the file exist?
        cout << itemFileName << " does not exist." << endl;
        exit(1);
    }
    if(itemInput.peek()==EOF){ //is the file empty?
        cout << itemFileName << " is empty." << endl;
        exit(1);
    }
    // int c = 1;
	while(getline(itemInput, singleLine)){
        itemName = getUntilComma(&singleLine);
        numlocations = stoi(getUntilComma(&singleLine));
        for(int i = 0; i < numlocations; i++){
            item = *new itemStruct;
            location = getUntilComma(&singleLine);
            itemMethod = getUntilComma(&singleLine);
            routeMapIt = routeMap.find(location);

            item.name = itemName;
            item.method = itemMethod;
            item.newLocation = false;
            routeMapIt->second->insertItems(item);
        }
    }

    TMInput.open(TMFileName);
    if(TMInput.fail()){ //does the file exist?
        cout << TMFileName << " does not exist." << endl;
        exit(1);
    }
    if(TMInput.peek()==EOF){ //is the file empty?
        cout << TMFileName << " is empty." << endl;
        exit(1);
    }
    while(getline(TMInput, singleLine)){
        //read in the variables
        itemName = getUntilComma(&singleLine);
        location = getUntilComma(&singleLine);
        itemMethod = getUntilComma(&singleLine);
        if(getUntilComma(&singleLine) == "1"){
            newLocation = true;
        }
        else{
            newLocation = false;
        }
        //set the variables into a new item
        item = *new itemStruct;
        item.name = itemName;
        item.method = itemMethod;
        item.newLocation = newLocation;

        //find the route & insert the item
        routeMapIt = routeMap.find(location);
        routeMapIt->second->insertItems(item);
    }
    return(routeMap);
}
map<string, Route*> insertBossBattles(string bossFileName, map<string, Route*> &routeMap){
    ifstream bossBattleInput; //whole file ifstream
    string routeName, equalsbars, singleLine, routeData, trainerName, pokemonLine;
    multimap<int, Pokemon>::iterator pokemonMapIt;
    map<string, Route*>::iterator routeMapIt;
    unordered_multimap<string, commonTrainerStruct>::iterator trainerMapIt;
    vector<bossTrainer> bosses;
    bossTrainer* boss;
    bossPokemon* bosspokemon;
    set<int> testing;
    bossBattleInput.open(bossFileName);
    if(bossBattleInput.fail()){ //does the file exist?
        cout << bossFileName << " does not exist." << endl;
		exit(1);
    }
    if(bossBattleInput.peek()==EOF){ //is the file empty?
        cout << bossFileName << " is empty." << endl;
        exit(1);
    }

    Route* DistortionWorld;
    DistortionWorld = new Route();
    DistortionWorld->setFullName("Distortion World");
    routeMap.insert(make_pair(DistortionWorld->getFullName(), DistortionWorld));

    while(!bossBattleInput.eof()){
        getline(bossBattleInput, routeName);
        getline(bossBattleInput, equalsbars);
        singleLine = "";
        routeData = "";
        pokemonLine = "";
        while(singleLine != "==========="){
            getline(bossBattleInput, singleLine);
            routeData += singleLine + '\n';
        }
        routeMapIt = routeMap.find(routeName);
        singleLine = "";
        
        while(singleLine != "==========="){
            if(singleLine == " "){
                routeData.erase(0, 2); //erase the " \n" because we're on a route with more than one boss
            }
            trainerName = routeData.substr(0, routeData.find('\n'));
            routeData.erase(0, routeData.find('\n')+1);
            boss = new bossTrainer;
            boss->name = trainerName;
            // routeData.erase(0, routeData.find('\n')+1);
            pokemonLine = routeData.substr(0, routeData.find('\n'));
            while(pokemonLine != " " && pokemonLine != "==========="){

                bosspokemon = new bossPokemon;
                bosspokemon->name = pokemonLine.substr(0, pokemonLine.find('(')-1);
                pokemonLine.erase(0, pokemonLine.find("Lv. ")+4);
                bosspokemon->level = stoi(pokemonLine.substr(0, 2));
                pokemonLine.erase(0, pokemonLine.find('@')+2);
                bosspokemon->item = pokemonLine.substr(0, pokemonLine.find("  "));
                pokemonLine.erase(0, pokemonLine.find('/')+4);
                bosspokemon->nature = pokemonLine.substr(0, pokemonLine.find("  "));
                pokemonLine.erase(0, pokemonLine.find('/')+4);
                bosspokemon->ability = pokemonLine.substr(0, pokemonLine.find("  "));
                pokemonLine.erase(0, pokemonLine.find('/')+4);
                bosspokemon->moves[0] = getUntilComma(&pokemonLine);
                bosspokemon->moves[1] = getUntilComma(&pokemonLine);
                bosspokemon->moves[2] = getUntilComma(&pokemonLine);
                bosspokemon->moves[3] = getUntilComma(&pokemonLine);
                boss->team.push_back(*bosspokemon);

                routeData.erase(0, routeData.find('\n')+1);
                pokemonLine = routeData.substr(0, routeData.find('\n'));
            }
            routeMapIt->second->insertBoss(*boss);
            singleLine = routeData.substr(0, routeData.find('\n'));
        }

    }
    return(routeMap);
}