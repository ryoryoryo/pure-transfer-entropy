// ConsoleApplication1.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "multidata.h"
#include "pte.h"

using namespace std;

void printdata(int datanum, int ndigit);

int _tmain(int argc, _TCHAR* argv[])
{
	pte("000", "000", 2);

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
