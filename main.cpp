/*
* markov-tweets
* Theodore Fleck
* CPEG 476
*/

#include "makeTweet.hpp"
#include <cstdlib> 
#include <time.h>

int main()
{
	srand(time(NULL));
	makeTweet *m = new makeTweet("dprk.txt", "newDprk.txt");
    return 0;
}

