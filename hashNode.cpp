/*
* markov-tweets
* Theodore Fleck
* CPEG 476
*/

#include "hashNode.hpp"
#include <cstdlib> 
#include <time.h> 
#include <string.h>
#include <iostream>

using namespace std;

hashNode::hashNode()
{
	keyword = "";
	values = new string[100];
	weights = new int[100];
	valuesSize = 0;
	currSize = 0;
}//hashNode()

hashNode::hashNode(string s)
{
	keyword = s;
	values = new string[100];
	weights = new int[100];
	valuesSize = 100;
	currSize = 0;
}//hashNode(string s)

hashNode::hashNode(string s, string v)
{
	keyword = s;
	values = new string[100];
	values[0] = v;
	weights = new int[100];
	weights[0] = 1;
	valuesSize = 100;
	currSize = 1;
}//hashNode(string s, string v)

void hashNode::addValue(string v)
{
	int ind = getValIndex(v);
	if(ind >= 0)
	{
		weights[ind] += 1;
	}
	else
	{
		if(currSize >= valuesSize)
		{
			dblArray();
		}
		values[currSize] = v;
		weights[currSize] = 1;
		currSize++;
	}
}//addValue(string v)

void hashNode::dblArray()
{
	string *strTemp = new string[valuesSize*2];
	int *intTemp = new int[valuesSize*2];
	for (int i = 0; i<valuesSize; i++)
	{
		strTemp[i] = values[i];
		intTemp[i] = weights[i];
	}
	delete[] values;
	delete[] weights;
	values = strTemp;
	weights = intTemp;
	valuesSize = valuesSize*2;
}//dblArray()

string hashNode::getRandValue()
{
	if(currSize < 1)
	{
		return "";
	}
	int totalWeights = 0;
	for(int i = 0; i<valuesSize; i++)
	{
		totalWeights += weights[i];
	}
	int num = rand() % totalWeights;
	int pos = 0;
	for(int i = 0; i<valuesSize; i++)
	{
		pos += weights[i];
		if(num < pos)
		{
			return values[i];
		}
	}
	return "";
}//getRandValue()

int hashNode::getValIndex(string v)
{
	for(int i = 0; i<valuesSize; i++)
	{
		if(v.compare(values[i]) == 0)
		{
			return i;
		}
	}
	return -1;
}




