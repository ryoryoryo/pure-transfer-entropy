
#include "stdafx.h"
#include "multidata.h"
#include "pte.h"
#include "tte.h"
#include "changetype.h"
#include "runnoise.h"
#include "Dir.h"

#define DATA_NUM 10
#define PATTERN_NUM 10

using namespace std;

//string inputDir("B:\\transfer-entropy\\artificial_experiment\\ver1.0\\TE_ver1_exp_ver15\\");
char inputDir[] = "B:\\transfer-entropy\\artificial_experiment\\ver1.0\\TE_ver1_exp_ver15\\*";
//LPCTSTR inputDir = _T("B:/transfer-entropy/artificial_experiment/ver1.0/TE_ver1_exp_ver15/*");


int _tmain(int argc, _TCHAR* argv[])
{
	vector<string*> tteresult;

	Dir dir;
	vector<string> fileList = dir.readAllFiles(inputDir, "csv");
	cout << endl << endl << "start:" << fileList.size() << endl;
	for (int fileindex = 0; fileindex < fileList.size(); fileindex++) {
		string result("");

		// path
		string dirpath1, dirpath2, dirpath3, noisenum, testnum;
		string inputFilePath = fileList[fileindex];
		int path_i_1 = inputFilePath.find_last_of("\\");

		if (path_i_1 != string::npos){
			dirpath1 = inputFilePath.substr(0, path_i_1);
			int path_i_2 = dirpath1.find_last_of("\\");
			dirpath2 = inputFilePath.substr(0, path_i_2);
			int path_i_3 = dirpath2.find_last_of("\\");
			dirpath3 = inputFilePath.substr(0, path_i_3);

			testnum = Replace(dirpath1, dirpath2 + "\\", "");
			noisenum = Replace(dirpath2, dirpath3 + "\\", "");

			cout << fileindex << "\t" << testnum << endl;
			cout << fileindex << "\t" << noisenum << endl;
		}
		string *data = readCsv(fileList[fileindex], DATA_NUM);
		tteresult.push_back(data);

		for (int i = 0; i < DATA_NUM; i++) {
			for (int j = 0; j < 10; j++) {
				if (i == 0 && j == 4) {
					cout << endl;
					cout << "stop" << endl;
				}
				result.append(intToString(i) + "\t" + intToString(j) + "\t" + doubleToString(tteXtoY(data[i], data[j], PATTERN_NUM, 4)) + "\n");
			}
		}
		// file open
		ofstream result_file;
		result_file.open("B:/transfer-entropy/artificial_experiment/ver1.0/TE_ver1_exp_ver15/" + noisenum + "/" + testnum + "/exp_ver15" + Replace(noisenum, "0", "") + testnum + "_result_TTE_4.txt", ios::out);
		cout << result;
		result_file << result;
		result_file.close();
	}

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

int readFiles(LPCTSTR path)
{
	HANDLE hFind;
	WIN32_FIND_DATA fd;
	FILETIME ft;
	SYSTEMTIME st;

	/* 最初のファイル検索 */
	hFind = FindFirstFile(path, &fd);

	/* 検索失敗? */
	if (hFind == INVALID_HANDLE_VALUE) {
		printf("検索失敗\n");
		return 1; /******** エラー終了 ********/
	}

	do {
		// 現在のディレクトリ（フォルダ）と親ディレクトリは排除 
		/*if (strcmp(fd.cFileName, "..") == 0
		|| strcmp(fd.cFileName, ".") == 0)
		{
		continue;
		}*/

		/* 結果の表示 */
		//printf("ファイル名: %2s%100s", path, fd.cFileName);
		cout << path << fd.cFileName << endl;

		if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			printf("(ディレクトリ)\n");
		}
		else {
			printf("\n");
		}

	} while (FindNextFile(hFind, &fd));

	/* 検索終了 */
	FindClose(hFind);
}

string Replace(std::string String1, std::string String2, std::string String3)
{
	std::string::size_type  Pos(String1.find(String2));

	while (Pos != std::string::npos)
	{
		String1.replace(Pos, String2.length(), String3);
		Pos = String1.find(String2, Pos + String3.length());
	}

	return String1;
}