// ConsoleApplication1.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "multidata.h"
#include "pte.h"
#include "changetype.h"

using namespace std;

void printdata(int datanum, int ndigit);

int _tmain(int argc, _TCHAR* argv[])
{
	// time
	clock_t start, end;
	start = clock();

	int datanum = 7;
	int patternnum = 3;
	int countor = 0;
	int tmpcountor = 0;
	int filecountor = 0;

	string result("");
	/*
	list<string> data = makedata(datanum, patternnum);
	
	list<string>::iterator x = data.begin();
	while (x != data.end())
	{
		list<string>::iterator y = data.begin();
		while (y != data.end())
		{
			countor++;
			//cout << countor << ": " << *x << " " << *y << endl;
			result.append(*x + "\t" + *y + "\t" + doubleToString(pteXtoY(*x, *y, patternnum)) + "\n");
			
			//countor++;
			tmpcountor++;
			if (tmpcountor > 1000000) {
				ofstream result_file;
				result_file.open("B:\\workspace-c\\data\\pte\\length7pattern3\\result" + intToString(filecountor) + ".txt", ios::out);
				result_file << result;
				result_file.close();
				filecountor++;
				result = "";
				tmpcountor = 0;
			}
			++y;
			//cout << countor << "/" << data.size() * data.size() << endl;
		}
		++x;
	}*/

	int datasize = 1;

	for (int i = 0; i < datanum; i++) {
		datasize = datasize * patternnum;
	}

	string *x = makedata2(datanum, patternnum);
	string *y = makedata2(datanum, patternnum);

	for (int i = 0; i < datasize; i++) {
		for (int j = 0; j < datasize; j++) {
			countor++;
			result.append(x[i] + "\t" + y[j] + "\t" + doubleToString(pteXtoY(x[i], y[j], patternnum)) + "\n");

			cout << filecountor << ":" << i * datasize + j << "/" << datasize * datasize << endl;
			tmpcountor++;
			if (tmpcountor > 1000000) {
				ofstream result_file;
				result_file.open("B:\\workspace-c\\data\\pte\\length7pattern3\\result" + intToString(filecountor) + ".txt", ios::out);
				result_file << result;
				result_file.close();
				filecountor++;
				result = "";
				tmpcountor = 0;
			}
		}
	}

	//free
	delete[] x;
	delete[] y;


	end = clock();
	// time file open
	ofstream time_file;
	time_file.open("B:\\workspace-c\\data\\pte\\length7pattern3\\time.txt", ios::out);
	time_file << (double)(end - start) / CLOCKS_PER_SEC << "sec";
	time_file.close();


	// file open
	ofstream result_file;
	result_file.open("B:\\workspace-c\\data\\pte\\length7pattern3\\result" + intToString(filecountor) + ".txt", ios::out);
	result_file << result;
	result_file.close();

	return 0;
}

void printdata(int datanum, int ndigit)
{
	list<string> testlist = makedata(datanum, ndigit);

	cout << "test" << endl;

	list<string>::iterator it = testlist.begin();
	while (it != testlist.end())
	{
		cout << *it << endl;
		++it;
	}
}
