#include <string.h>
#include <time.h>
#include <vector>
#include <algorithm>
#include <set>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
using namespace std;

class InsultGenerator {//Class in charge of the whole process
public:
	InsultGenerator();
	void initialize();//Creates list of insults read from SourceFile
	string talkToMe();//Generates a sentence from said list
	vector<string> generate(const int n);//generates list of n lines of insults in alphabetical order
	vector<string> generateAndSave(const string s, const int n);// saves genrated list and writes into a new file

private:
	vector<string> col1, col2, col3, contents;
	set<string> insultSet;
};
class NumInsultsOutOfBounds {// Bounds Class checks in list to be genrated is within alloted bounds 0 - 10000
public:
	NumInsultsOutOfBounds(const string&);
	string what() const;
private:
	string message;
};
class FileException {//Checks if file is valid returns error if not
public:
	FileException(const string&);
	string what() const;
private:
	string message;
};

