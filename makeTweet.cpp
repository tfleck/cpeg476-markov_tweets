/*
* markov-tweets
* Theodore Fleck
* CPEG 476
*/

#include "makeTweet.hpp"
#include "hashMap.hpp"
#include <cstdlib> 
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>

using namespace std;

int maxLength = 280;

makeTweet::makeTweet(string f1, string f2) {
	ht = new hashMap();
	newfile = f2;
	fn = f1;
	readFile();
	writeFile();
}
void makeTweet::readFile() {
	cout << "readng" << endl;
	ifstream infile(fn.c_str(), ios::in); // open file
	string key = "";
	string value = "";
	infile >> key;
	ht->first = key;
	while (infile >> value) { // loop getting single characters
		//cout << key << ": " << value << endl;
		ht->addKeyValue(key, value);
		key = value;
		value = "";
	}
	ht->addKeyValue(key, value);
	cout << endl;
	infile.close();
}
void makeTweet::writeFile() {
	cout << "writing" << endl;
	ht->printMap();
	cout << "map printed" <<endl;
	ofstream outfile(newfile.c_str(), ios::out);
	//outfile << ht->first << " ";
	string key = "";
	//int ind = ht->findKey(ht->first);
	//string value = ht->map[ind]->getRandValue();
	int chars = 0;
	while (chars < maxLength) {
		int ind = ht->findKey(key);
		string value = ht->map[ind]->getRandValue();
		while(value.compare("") == 0){
			ind = rand() % ht->numKeys;
			value = ht->map[ind]->getRandValue();	
		}
		chars += value.length()+1;
		if(chars <= 280){
			outfile << value << " ";
		}
		//cout << "Num: " << ct << endl;
		key = value;
	}
	outfile.close();
}
