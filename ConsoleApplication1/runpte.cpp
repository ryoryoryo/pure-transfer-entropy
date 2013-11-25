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
	// file open
	ofstream result_file;
	result_file.open("B:\\workspace-c\\data\\pte\\length9pattern2\\result.txt");

	// time
	clock_t start, end;
	start = clock();

	int datanum = 9;
	int patternnum = 2;
	int countor = 0;

	list<string> data = makedata(datanum, patternnum);

	list<string>::iterator x = data.begin();
	while (x != data.end())
	{
		list<string>::iterator y = data.begin();
		while (y != data.end())
		{
			result_file << *x << "\t" << *y << "\t" << pteXtoY(*x, *y, patternnum) << endl;
			++y;
			countor++;
			cout << countor << "/" << data.size() * data.size() << endl;
		}
		++x;
	}

	end = clock();
	// time file open
	ofstream time_file;
	time_file.open("B:\\workspace-c\\data\\pte\\length9pattern2\\time.txt");
	time_file << (double)(end - start) / CLOCKS_PER_SEC << "sec";
	time_file.close();
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
