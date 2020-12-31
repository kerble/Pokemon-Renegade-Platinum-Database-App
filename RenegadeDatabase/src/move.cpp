#include "./move.hpp"
using namespace std;

/* Default Constructor
 * Returns nothing
 * Has no parameters
 * Constructs a move
 */
Move::Move(){}

/* 7-arg Constructor
 * Returns nothing
 * Takes all the crap to make a move
 * Constructs a move
 */
Move::Move(string n, int p, string t, string c, int a, int pnt, string d){
	setName(n);
	setPower(p);
	setType(t);
	setCategory(c);
	setAccuracy(a);
	setPP(pnt);
	setDescription(d);
}

bool Move::operator<(const Move& m)const{
	return(this->name < m.name);
}
bool Move::operator==(const Move& m)const{
	return(this->name == m.name);
}
bool Move::operator>(const Move& m)const{
	return(this->name > m.name);
}
ostream& operator<<(ostream& outStream, const Move& MV){
	// cout << MV.getName() << ", " << MV.getType() << ", " << MV.getCategory() << ", "
	// << MV.getPP() << ", ";
	printf("%-15s %-8s %-8s %2d ", MV.getName().c_str(), MV.getType().c_str(), MV.getCategory().c_str(), MV.getPP());
	if(MV.getPower() == 251){ //status moves that have no power
		cout << "--- ";
	}
	else{
		// cout << MV.getPower() << ", ";
		printf("%3d ", MV.getPower());
	}
	if(MV.getAccuracy() == 404 || MV.getAccuracy() == 251){ //moves whose accuracy bypass
		cout << "--- ";			//accuracy checks or status moves like swords dance
	}
	else{
		// cout << MV.getAccuracy();
		printf("%3d", MV.getAccuracy());
	}

	return(outStream);
}
string getUntilComma(string* input){
	int commalocation;
	string retval;
	commalocation = input->find(",");
	retval = input->substr(0, commalocation);
	input->erase(0, commalocation+1);
	return(retval);
}
unordered_map<string, Move> readMoves(string movestxt){
	ifstream moveinput;
	string movelinestring;
	Move move;
	unordered_map<string, Move> moveMap;

    moveinput.open(movestxt);
    if(moveinput.fail()){ //does the file exist?
        cout << movestxt << " does not exist." << endl;
        exit(1);
    }
    if(moveinput.peek()==EOF){ //is the file empty?
        cout << movestxt << " is empty." << endl;
        exit(1);
    }
	while(!moveinput.eof()){
		getline(moveinput, movelinestring);

		move.setName(getUntilComma(&movelinestring));
		move.setType(getUntilComma(&movelinestring));
		move.setCategory(getUntilComma(&movelinestring));
		move.setPP(stoi(getUntilComma(&movelinestring)));
		move.setPower(stoi(getUntilComma(&movelinestring)));
		move.setAccuracy(stoi(getUntilComma(&movelinestring)));

		moveMap.insert(make_pair(move.getName(), move));
	}
	return(moveMap);
}