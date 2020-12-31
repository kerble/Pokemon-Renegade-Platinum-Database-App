#include <string>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <unordered_map>
#include <map>
using namespace std;

class Move{
public:
	/*Default constructor
	 * Returns nothing
	 * Parameters: None
	 * Constructs a move
	 */
	Move();
	/* 8-arg Constructor
	* Returns nothing
	* Takes a Name, Type, Power, Accuracy, PP, Description
	* Constructs a move
	*/
	Move(string, int, string, string, int, int, string);
	/* Copy Constructor
	* Returns nothing
	* Parameters: A constant move by reference
	* Copies the move
	*/
	//Move(const Move&); 
	/*Destructor
	 * Destroys a move
	 */
	virtual ~Move(){};
	//getters
	string getName()const{return(name); }
	int getPower()const{return(power); }
	string getType()const{return(type); }
	string getCategory()const{return(category); }
	int getAccuracy()const{return(accuracy); }
	int getPP()const{return(pp); }
	string getDescription()const{return(description); }
	//setters
	void setName(string n){
		name = n;
	}
	void setPower(int p){
		power = p;
	}
	void setType(string t){
		if( t == "Fire" || "Water" || "Grass" || "Electric"||
		"Rock" || "Ground" || "Fighting" || "Steel" || "Ice" ||
		"Dark" || "Fairy" || "Dragon" || "Psychic" || "Bug" ||
		"Flying" || "Poison" || "Normal" || "Ghost" || "???" )
			type = t;
		else
			type = "unknown";
	}
	void setCategory(string c){
		if(c == "Physical" || "Special" || "Status" ){
			category = c;
		}
		else{
			category = "Unknown";
		}
	}
	void setAccuracy(int a){
		if(a > 0 && a <= 100)
			accuracy = a;
		else
			accuracy = 404;
	}
	void setPP(int pnt){
		if(pnt <= 40)
			pp = pnt;
		else
			pp = 404;
	}
	void setDescription(string d){
		description = d;
	}
	//Move& operator=(const Move&);
	bool operator<(const Move&)const;
	bool operator==(const Move&)const;
	bool operator>(const Move&)const;
	friend ostream& operator<<(ostream&, const Move&);
private:
	string name;
	int power;
	string type;
	string category;
	int accuracy;
	int pp;
	string description;
};
string getUntilComma(string*);
unordered_map<string, Move> readMoves(string);