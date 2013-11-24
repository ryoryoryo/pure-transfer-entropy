#include "stdafx.h"
#include "changetype.h"


string toNDigit(int n, int value, int number);

//datanum: number of data

list<string> makedata(int datanum, int patternnum)
{
	using namespace std;
	int datasize = 1;

	for (int i = 0; i < datanum; i++) {
		datasize = datasize * patternnum;
	}

	list<string> data;
	for (int i = 0; i < datasize; i++) {
		data.push_back(toNDigit(patternnum, i, datanum));
	}

	return data;
}


// n:n-digit value:value number:length of bit
string toNDigit(int n, int value, int number)
{
	using namespace std;
	string tmpresult("");
	int tmpvalue = value;
	while (tmpvalue >= n) {
		string tmps = intToString(tmpvalue % n);
		tmpresult = tmps + tmpresult;
		tmpvalue = tmpvalue / n;
	}
	string tmps = intToString(tmpvalue % n);
	tmpresult = tmps + tmpresult;

	int slen = tmpresult.size();
	//cout << slen;

	int rlen = number - slen;
	if (rlen > 0) {
		for (int i = 0; i < rlen; i++) {
			tmpresult = "0" + tmpresult;
		}
	}

	return tmpresult;
}