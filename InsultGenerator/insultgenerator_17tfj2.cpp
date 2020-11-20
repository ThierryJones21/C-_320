#include "insultgenerator_17tfj2.h"

using namespace std;


FileException::FileException(const string& m) : message(m) {}
string FileException::what() const {
	return message;
}

NumInsultsOutOfBounds::NumInsultsOutOfBounds(const string& m) : message(m) {}
string NumInsultsOutOfBounds::what() const {
	return message;
}

InsultGenerator::InsultGenerator() {}

void InsultGenerator::initialize() {//Reads in a the insult file write it into a vector and said vector writes into columns of vectors
	ifstream fileIn("InsultsSource.txt");
	vector<string> contents;
	string line;
	if (fileIn.fail()) {
		throw FileException("File can't be read.");
	}
	stringstream SS;
	while (getline(fileIn, line)) {
		SS.clear();
		SS.str(" ");
		SS << line;
		while (SS >> line) {
			contents.push_back(line);
		}
	}
	for (int i = 0; i < contents.size(); i += 3) {
		col1.push_back(contents[i]);
		col2.push_back(contents[i + 1]);
		col3.push_back(contents[i + 2]);
	}  
	fileIn.close();
} 

string InsultGenerator::talkToMe() {//generates 3 random numbers and uses them to generate sentences
	int number1, number2, number3;
	int randNumber1, randNumber2, randNumber3;
	randNumber1 = rand() % 49;
	randNumber2 = rand() % 49;
	randNumber3 = rand() % 49;
	number1 = randNumber1;
	number2 = randNumber2;
	number3 = randNumber3;
	string insultLine;
	insultLine = "Thou " + col1[number1] + " " + col2[number2] + " " + col3[number3] + "!";
	return insultLine;
}

vector<string> InsultGenerator::generate(int y) {//create a list of y elemnts and uses the talkToMe() func to genrate random sentences line by line 
	if (y > 10000 || y < 1) { 
		throw NumInsultsOutOfBounds("\nNumber of insults not in bounds(generate)\n");
		return vector<string>();
	}
	set<string> insultsSet; 
	while (y > insultsSet.size()) {
		string temp(talkToMe());
		insultsSet.insert(temp);
	}
	vector<string> returnedInsults(insultsSet.begin(), insultsSet.end()); 
	return returnedInsults;
} 

vector<string> InsultGenerator::generateAndSave(string file, int x) {//  same as generate but writes out to a new file specified in main func
	ofstream outputFile(file);
	set<string> insultsSet;
	if (x < 1 || x > 10000) {
		throw NumInsultsOutOfBounds("\nNumber of Insults not in bounds(generateAndSave)\n");
		return vector<string>();
	}
	else {
		while (x > insultsSet.size()) {
			string insult = talkToMe();
			insultsSet.insert(insult);
			outputFile << insult << "\n";
		} 
	}
	vector<string> returnedInsults(insultsSet.begin(), insultsSet.end());
	return returnedInsults;
}
