/*
	Date Created: November 18th 2020
	Thierry Jones 17tfj2
*/
#include<iostream>
#include<exception>
#include<string>
#include<stdlib.h>
using namespace std;
typedef char* charArrayPtr;

class JumblePuzzle {
public:
	JumblePuzzle(const string& toHide, const string& diff); //Constructor that takes a word and a difficulty, Takes 2 strings: Word to be hidden and Difficulty
	~JumblePuzzle(); //Destructor, gets rid of the matrix object on the heap when the player has guessed the word or terminated the program
	JumblePuzzle(const JumblePuzzle& right); //Copy Constructor
	
	JumblePuzzle& operator=(const JumblePuzzle& right); //Assignment operator overloading
	charArrayPtr* getJumble() const; //Getter for the matrix

	//Getters for matrix variables
	int getSize() const; 
	int getRowPos() const; 
	int getColPos() const; 
	char getDirection() const; 
private:
	int row;
	int col;
	int length;
	char direction;
	charArrayPtr* matrix;
};

class BadJumbleException {
public:
	BadJumbleException(const string&); //Gives a customized message for Jumble Exceptions such as difficulty invalid, the word is too big or too small
	string& what();
private:
	string message;
};