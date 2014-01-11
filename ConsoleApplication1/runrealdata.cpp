#include "stdafx.h"
#include "pte.h"
#include "tte.h"
#include "changetype.h"
#include "runrealdata.h"

#define DATA_NUM 17
#define PATTERN_NUM 5

using namespace std;

/*
int _tmain(int argc, _TCHAR* argv[]) {
	QDir q_dir("C:/MinGW");

	if (q_dir.exists())
		QStringList filelist = q_dir.entryList();

}

map<string, string> readCsv(string path)
{
	ifstream ifs(path);
	map<string, string> result;

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
		int elementNum = 0;
		string topic = "";
		string time = "";
		while ((p = line.find("\t")) != line.npos){
			if (elementNum == 1) {
				time = line.substr(p + 1);
			}
			else if (elementNum == 2) {
				topic = line.substr(p + 1);
			}
		}
		result.insert(map<string, string>::value_type(time, topic));
		index = index + 1;
	}

	return result;
	}*/