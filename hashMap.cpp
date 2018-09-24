/*
* markov-tweets
* Theodore Fleck
* CPEG 476
*/

#include "hashMap.hpp"
#include "hashNode.hpp"
#include <cstdlib> 
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

hashMap::hashMap()
{
	map = new hashNode *[100]();
	for (int i = 0; i<100; i++) {
		map[i] = new hashNode();
	}
	numKeys = 0;
	mapSize = 100;
}//hashMap()

void hashMap::addKeyValue(string k, string v)
{
	int index = findKey(k);
	if(index == -1)
	{
		int i = getIndex(k);
		map[i] = new hashNode(k,v);
		numKeys++;
	}
	else
	{
		map[index]->addValue(v);
	}
	if (numKeys >= mapSize*0.7)
	{
		reHash();
	}
}//addKeyValue(string k, string v)

int hashMap::getIndex(string k)
{
	if(numKeys >= mapSize*0.7)
	{
		reHash();
	}
	return dblHash(calcHash(k),1,k);
}//getIndex(string k)

int hashMap::calcHash(string k)
{
	int hash = 0;
	for (int i=0; i<k.length(); i++) {
		char c = k[i];
		hash = (37 * hash + c) % mapSize;
	}
	if(hash < 0)
	{
		hash = hash * -1;
	}
	return hash;
}//calcHash(string s)

void hashMap::getClosestPrime()
{
	bool found = false;
	int nextPrime = mapSize * 2;
	while(!found)
	{
		if(nextPrime <= 3)
		{
			break;
		}
		for(int i=2; true; i++)
		{
			int num = nextPrime / i;
			if(num < i)
			{
				found = true;
				break;
			}
			if(nextPrime % i == 0)
			{
				nextPrime++;
				break;
			}
		}
	}
	mapSize = nextPrime;
}//getClosestPrime()

void hashMap::reHash()
{
	int oldSize = mapSize;
	getClosestPrime();
	hashNode** map2 = new hashNode *[mapSize]();
	for (int i = 0; i<mapSize; i++) {
		map2[i] = new hashNode();
	}
	for (int i = 0; i < oldSize; i++) {
		if(map[i]->valuesSize != 0)
		{
			int index = calcHash(map[i]->keyword);
			for (int j= 1; map2[index]->valuesSize != 0; j++)
			{
				index = (index + int(pow(j, 2))) % mapSize;
			}
			map2[index] = map[i];
		}
	}
	delete[] map;
	map = map2;
}//reHash()

int hashMap::dblHash(int h, int i, string k)
{
	if(map[h]->valuesSize == 0)
	{
		return h;
	}
	int index = (h + int(pow(i, 2))) % mapSize;
	return dblHash(index, i + 1, k);
}//dblHash(int h, int i, string s)

int hashMap::findKey(string k)
{
	if(numKeys == 0)
	{
		return -1;
	}
	int index = calcHash(k);
	for(int i=0; map[index]->keyword.compare(k); i++)
	{
		if (map[index]->valuesSize == 0)
		{
			return -1;
		}
		index = (index + int(pow(i, 2))) % mapSize;
	}
	return index;
}//findKey(string k)

void hashMap::printMap()
{
	string newfile = "map.txt";
	ofstream outfile(newfile.c_str(), ios::out);
	for (int i = 0; i<mapSize; i++) {
		string vals = "";
		string weights = "";
		for(int j=0; j<map[i]->currSize; j++)
		{
			vals += map[i]->values[j] + ",";
			char c = map[i]->weights[j]+'0';
			//int num = map[i]->weights[j];
			//sprintf(str, "%d", num);
			weights.append(1,c);
			weights += ",";
			//cout << weights << endl;
		}
		if(vals.length() > 4){
			outfile << map[i]->keyword << " : " << vals << "\n";
			outfile << map[i]->keyword << " : " << weights << "\n";
		}
		//cout << map[i]->keyword << " : " << map[i]->currSize << endl;
	}
	outfile.close();
}//printMap()