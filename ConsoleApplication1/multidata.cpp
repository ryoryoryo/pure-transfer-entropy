#include "stdafx.h"

//datanum: number of data
std::list<int> makedata(int datanum, int patternnum)
{
	int datasize = 1;
	for(int i = 0; i < datanum; i++) {
		datasize = datasize * patternnum;
	}

	std::list<int> data;
	for(int i = 0; i < datanum; i++) {
		data.push_back(toNDigit(patternnum, i));
	}

	return data;
}

int toNDigit(int n, int value)
{
	
}