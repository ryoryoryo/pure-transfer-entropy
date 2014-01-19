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


int _tmain(int argc, _TCHAR* argv[])
{
	string Dir("B:/transfer-entropy/artificial_experiment/ver1.0/TE_ver1_exp_ver16/0/");

	string resultTE("");
	string resultTTE1("");
	string resultTTE2("");
	string resultTTE3("");
	string resultTTE4("");

	string *data = readCsv(Dir + "exp_ver160_network-time-series.csv", DATA_NUM);

	for (int i = 0; i < DATA_NUM; i++) {
		for (int j = 0; j < 10; j++) {
			if (i == 0 && j == 4) {
				cout << endl;
				cout << "stop" << endl;
			}
			resultTE.append(intToString(i) + "\t" + intToString(j) + "\t" + doubleToString(pteXtoY(data[i], data[j], PATTERN_NUM)) + "\n");
			resultTTE1.append(intToString(i) + "\t" + intToString(j) + "\t" + doubleToString(tteXtoY(data[i], data[j], PATTERN_NUM, 1)) + "\n");
			resultTTE2.append(intToString(i) + "\t" + intToString(j) + "\t" + doubleToString(tteXtoY(data[i], data[j], PATTERN_NUM, 2)) + "\n");
			resultTTE3.append(intToString(i) + "\t" + intToString(j) + "\t" + doubleToString(tteXtoY(data[i], data[j], PATTERN_NUM, 3)) + "\n");
			resultTTE4.append(intToString(i) + "\t" + intToString(j) + "\t" + doubleToString(tteXtoY(data[i], data[j], PATTERN_NUM, 4)) + "\n");
		}
	}
	// file open
	// te
	ofstream resultTE_file;
	resultTE_file.open(Dir + "exp_ver160_result_TE.txt", ios::out);
	cout << resultTE;
	resultTE_file << resultTE;
	resultTE_file.close();
	// tte 1
	ofstream resultTTE1_file;
	resultTTE1_file.open(Dir + "exp_ver160_result_TTE_1.txt", ios::out);
	cout << resultTTE1;
	resultTTE1_file << resultTTE1;
	resultTTE1_file.close();
	// tte 2
	ofstream resultTTE2_file;
	resultTTE2_file.open(Dir + "exp_ver160_result_TTE_2.txt", ios::out);
	cout << resultTTE2;
	resultTTE2_file << resultTTE2;
	resultTTE2_file.close();
	// tte 3
	ofstream resultTTE3_file;
	resultTTE3_file.open(Dir + "exp_ver160_result_TTE_3.txt", ios::out);
	cout << resultTTE3;
	resultTTE3_file << resultTTE3;
	resultTTE3_file.close();
	// tte 4
	ofstream resultTTE4_file;
	resultTTE4_file.open(Dir + "exp_ver160_result_TTE_4.txt", ios::out);
	cout << resultTTE4;
	resultTTE4_file << resultTTE4;
	resultTTE4_file.close();

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
}