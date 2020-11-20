/*
	Date Created: November 18th 2020
	Thierry Jones 17tfj2
*/
#include "jumble.h"
#include<iostream>
#include<stdlib.h>
#include<sstream>
#include<time.h>
#include<stdio.h>

using namespace std;

BadJumbleException::BadJumbleException(const string& e) : message(e) { }
string& BadJumbleException::what() { return message; }

JumblePuzzle::JumblePuzzle(const string& toHide, const string& diff) {
	length = toHide.length();
	if (length < 3) {//Checks to see that the word is not too short or too long
		throw BadJumbleException("ERROR: Word length cannot be less than 3");
	}
	if (length > 10) {
		throw BadJumbleException("ERROR: Word length cannot be more than 10");
	}
	if (diff == "easy") { 
		length *= 2; 
	}
	else if (diff == "medium") { 
		length *= 3; 
	}
	else if (diff == "hard") { 
		length *= 4; 
	}
	else {
		throw BadJumbleException("ERROR: Difficulty must be easy, medium, or hard");
	}
	matrix = new char* [length]; //Matrix of new length based on difficulty

	for (int i = 0; i < length; i++) {
		matrix[i] = new char[length]; //Making the Matrix 2D, Adding columns
	}

	const char* letters = "abcdefghijklmnopqrstuvwxyz"; //all letters in the alphabet

	srand(time(NULL));// start time 

	for (int i = 0; i < length; i++)
		for (int j = 0; j < length; j++)
			matrix[i][j] = (char)letters[rand() % 25]; //randomize letters in the matrix

	row = rand() % length;
	col = rand() % length;

	matrix[row][col] = toHide.at(0);
	const char* dir = "nesw"; // create a string with all directions
	bool hidden = false;

	while (!hidden) {
		// Pick a random direction
		direction = dir[rand() % 4];
		//North
		if (direction == 'n') { 
			for (int i = 1; i < toHide.length(); i++)
			{
				// Out of bounds
				if ((row - i) < 0){
					break;
				}
				else if (i == (toHide.length() - 1)) { // last letter
					matrix[row - i][col] = toHide.at(i);
					hidden = true;
				}
				else {
					matrix[row - i][col] = toHide.at(i);
				}
			}
		}//East
		else if (direction == 'e') { 
			for (int i = 1; i < toHide.length(); i++) {
				if ((col + toHide.length()) > (this->getSize() - 1)){
					break;
				}
				else if (i == (toHide.length() - 1)) {
					matrix[row][col + i] = toHide.at(i);
					hidden = true;
				}
				else{
					matrix[row][col + i] = toHide.at(i);
				}
			}
		}
		else if (direction == 's') {
			// South
			for (int i = 1; i < toHide.length(); i++) {
				if ((row + toHide.length()) > (this->getSize() - 1)) {
					break;
				}
				else if (i == (toHide.length() - 1)) {
					matrix[row + i][col] = toHide.at(i);
					hidden = true;
				}
				else {
					matrix[row + i][col] = toHide.at(i);
				}
			}
		}
		else { //West
			for (int i = 1; i < toHide.length(); i++) {
				if ((col - i) < 0) {
					break;
				}
				else if (i == (toHide.length() - 1)) {
					matrix[row][col - i] = toHide.at(i);
					hidden = true;
				}
				else {
					matrix[row][col - i] = toHide.at(i);
				}
			}
		}
	}
}

JumblePuzzle::JumblePuzzle(const JumblePuzzle& right) { // copy constructor 
	length = right.getSize();
	row = right.getRowPos();
	col = right.getColPos();
	direction = right.getDirection();
	matrix = new char* [length];

	for (int i = 0; i < length; i++)
		matrix[i] = new char[length];

	charArrayPtr* rightMatrix = right.getJumble();

	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++)
			matrix[i][j] = rightMatrix[i][j];
	}
}
//Getters for copy constructor
int JumblePuzzle::getSize() const { 
	return length; 
}
int JumblePuzzle::getRowPos() const { 
	return row; 
}
int JumblePuzzle::getColPos() const { 
	return col; 
}
char JumblePuzzle::getDirection() const { 
	return direction; 
}

charArrayPtr* JumblePuzzle::getJumble() const {
	charArrayPtr* newMatrix = new char* [length];

	for (int i = 0; i < length; i++) {
		newMatrix[i] = new char[length];
	}
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++)
			newMatrix[i][j] = matrix[i][j];
	}
	return newMatrix;
}

JumblePuzzle::~JumblePuzzle() {
	for (int i = 0; i < length; i++)
		delete matrix[i];
	delete[] matrix;
}

JumblePuzzle& JumblePuzzle::operator=(const JumblePuzzle& right) {
	if (this != &right)//checks if not equal to previous jumble
	{
		row = right.getRowPos();
		col = right.getColPos();
		direction = right.getDirection();
		length = right.getSize();

		for (int i = 0; i < length; i++) {
			delete[] matrix[i];//Dynamic array deletion
		}
		delete[] matrix;
		matrix = new char* [length];
		
		for (int i = 0; i < length; i++) {
			matrix[i] = new char[length];
		}

		charArrayPtr* rightJumble = right.getJumble();

		for (int i = 0; i < length; i++) {
			for (int j = 0; j < length; j++)
				matrix[i][j] = rightJumble[i][j];
		}
	}
	return *this;
}

