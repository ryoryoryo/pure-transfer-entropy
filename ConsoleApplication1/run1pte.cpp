#include "stdafx.h"
#include "multidata.h"
#include "pte.h"
#include "tte.h"
#include "changetype.h"

#define DATA_NUM 10
#define PATTERN_NUM 10

using namespace std;

/*
int _tmain(int argc, _TCHAR* argv[])
{
// input
string x = "22447824837714412718927686210540";
string y = "08721272904023010010400042023258";

// output
cout << endl;
cout << x + "\t" + y + "\t" + doubleToString(pte(x, y, PATTERN_NUM)) + "\n" << endl;

return 0;
}
*/

/*
int _tmain(int argc, _TCHAR* argv[])
{
	string result("");

	string *data = readCsv("B:/transfer-entropy/artificial_experiment/ver1.0/TE_ver1_exp_ver14/90/5/exp_ver1495_network-time-series.csv", DATA_NUM);

	//comment
	string data[10] = {
		"12344321123",
		"01233332112",
		"00000000000",
		"00234432222",
		"01134434111",
		"01114444111",
		"00111444411",
		"00000000000",
		"00023333222",
		"00000044444",
	};


	for (int i = 0; i < DATA_NUM; i++) {
		for (int j = 0; j < 10; j++) {
			if (i == 0 && j == 4) {
				cout << endl;
				cout << "stop" << endl;
			}
			result.append(intToString(i) + "\t" + intToString(j) + "\t" + doubleToString(pteXtoY(data[i], data[j], PATTERN_NUM)) + "\n");
		}
	}
	// file open
	ofstream result_file;
	result_file.open("B:/transfer-entropy/artificial_experiment/ver1.0/TE_ver1_exp_ver14/90/5/exp_ver1495_result_TE.txt", ios::out);
	cout << result;
	result_file << result;
	result_file.close();

	return 0;
}

string* readCsv(string path, int datasize)
{
	ifstream ifs(path);
	string *data = new string[datasize];

	if (ifs.fail()){
		// error
		cerr << "failed." << endl;
		exit(0);
	}

	string line;
	string lineSum;
	int p;
	int index = 0;
	while (getline(ifs, line)){
		lineSum = "";
		while ((p = line.find(",")) != line.npos){
			lineSum = lineSum + line.substr(0, p);
			line = line.substr(p + 1);
		}
		lineSum = lineSum + line.substr(0, p);
		data[index] = lineSum;
		index = index + 1;
	}

	return data;
	}*/