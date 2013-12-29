#include "stdafx.h"
#include "multidata.h"
#include "pte.h"
#include "tte.h"
#include "changetype.h"

#define DATA_NUM 17
#define PATTERN_NUM 5

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
// input
string x = "112233441122334";
string y = "000000000444444";

// output
cout << x + "\t" + y + "\t" + doubleToString(pteXtoY(x, y, PATTERN_NUM)) + "\n" << endl;

return 0;
}

/*test
int _tmain(int argc, _TCHAR* argv[])
{
	string result("");

	string data[10] = {
		"112233441122334",
		"011223322112233",
		"011222244112222",
		"000022224444222",
		"011113344114433",
		"000000000444444",
		"000022222222222",
		"000000000000000",
		"000022222222222",
		"000000000444444",
	};

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			result.append(intToString(i) + "\t" + intToString(j) + "\t" + doubleToString(tteXtoY(data[i], data[j], PATTERN_NUM, 4)) + "\n");
		}
	}
	// file open
	ofstream result_file;
	result_file.open("B:/transfer-entropy/artificial_experiment/ver1.0/TE_ver1_exp_ver11/result_TTE_4.txt", ios::out);
	result_file << result;
	result_file.close();

	return 0;
	}*/