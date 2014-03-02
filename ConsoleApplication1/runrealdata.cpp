#include "stdafx.h"
#include "pte.h"
#include "tte.h"
#include "changetype.h"
#include "runrealdata.h"
#include "Dir.h"


#define PATTERN_NUM 75

using namespace std;

char inputDir[] = "B:\\transfer-entropy\\te\\real_experiment\\ver2.0\\ver2.0.3\\ver2.0.3.3.2\\time-series\\between-user-tweet-topics\\*";

string outputDir = "B:/transfer-entropy/te/real_experiment/ver2.0/ver2.0.3/ver2.0.3.3.2/te-result/result/";


int _tmain(int argc, _TCHAR* argv[])
{
	Dir dir;

	// read file
	vector<string> fileList = dir.readAllFiles(inputDir, "txt");
	cout << endl << endl << "start:" << fileList.size() << endl;

	// init
	string resultTE("");
	string *resultTTE = new string[PATTERN_NUM];
	for (int i = 0; i < PATTERN_NUM; i++) {
		resultTTE[i] = "";
	}


	for (int fileindex = 0; fileindex < fileList.size(); fileindex++) {
		cout << fileindex + 1 << " / " << fileList.size() << endl;

		// file pass
		string inputFilePath = fileList[fileindex];

		// file names
		string influencer = "";
		string receiver = "";
		int last_index = inputFilePath.find_last_of("\\") + 1;
		if (last_index != string::npos){
			string fileName = inputFilePath.substr(last_index, inputFilePath.length());
			int before_name_index = fileName.find("_to_");
			influencer = fileName.substr(0, before_name_index);
			int after_name_length = fileName.find(".txt") - fileName.rfind("_to_") - 4;
			receiver = fileName.substr(before_name_index + 4, after_name_length);
		}

		// calcurate
		if (influencer == "aipocom") {
			// file contents
			vector<string> contents = readContentsXYZ(inputFilePath);

			if (contents.size() > 0) {
				for (int i = 0; i < PATTERN_NUM; i++) {
					resultTTE[i].append(influencer + "\t" + receiver + "\t" + doubleToString(tteMultiXYZ(contents, i)) + "\n");
				}
			}
			else {
				resultTE.append(influencer + "\t" + receiver + "\tNULL\n");
				for (int i = 0; i < PATTERN_NUM; i++) {
					resultTTE[i].append(influencer + "\t" + receiver + "\tNULL\n");
				}
			}
		}
	}


	// te
	ofstream resultTE_file;
	resultTE_file.open(outputDir + "result_aipocom_TE.txt", ios::out);
	resultTE_file << resultTE;
	resultTE_file.close();

	// tte
	for (int i = 0; i < PATTERN_NUM; i++) {
		ofstream resultTTE_file;
		resultTTE_file.open(outputDir + "result_aipocom_TTE_" + intToString(i) + ".txt", ios::out);
		resultTTE_file << resultTTE[i];
		resultTTE_file.close();
	}

	// free
	delete[] resultTTE;

	return 0;
}

string* readContents(string path)
{
	ifstream ifs(path);
	string *data = new string[2];

	if (ifs.fail()){
		// error
		cerr << "failed." << endl;
		exit(0);
	}

	string line;
	int p;
	int index = 0;
	while (getline(ifs, line)){
		data[index] = line;
		index = index + 1;
	}

	return data;
}

vector<string> readContentsXYZ(string path)
{
	ifstream ifs(path);
	vector<string> data;

	if (ifs.fail()){
		// error
		cerr << "failed." << endl;
		exit(0);
	}

	// need to change
	string line;
	int p;
	int index = 0;
	while (getline(ifs, line)){
		data.push_back(line);
	}

	return data;
}