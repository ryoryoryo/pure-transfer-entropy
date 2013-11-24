/*
 * pure transfer entropy
 *
 */

#include "stdafx.h"

double pte(string x, string y, int ndigit)
{
	int lenx = x.size();
	int leny = y.size();

	if (lenx == leny) {
		int lenxy = lenx;
		cout << "test:";
		//initial
		int n3 = ndigit * ndigit * ndigit;
		int n2 = ndigit * ndigit;
		int n1 = ndigit;

		int *mp3x = new int[n3];
		for (int i = 0; i < n3; i++) {
			mp3x[i] = 0;
		}
		int *mp3y = new int[n3];
		for (int i = 0; i < n3; i++) {
			mp3y[i] = 0;
		}
		int *mpxy = new int[n2];
		for (int i = 0; i < n2; i++) {
			mpxy[i] = 0;
		}
		int *mpyx = new int[n2];
		for (int i = 0; i < n2; i++) {
			mpyx[i] = 0;
		}
		int *mpx = new int[n2];
		for (int i = 0; i < n2; i++) {
			mpx[i] = 0;
		}
		int *mpy = new int[n2];
		for (int i = 0; i < n2; i++) {
			mpy[i] = 0;
		}
		int *px = new int[n1];
		for (int i = 0; i < n1; i++) {
			px[i] = 0;
		}
		int *py = new int[n1];
		for (int i = 0; i < n1; i++) {
			py[i] = 0;
		}


		// count number
		for (int i = 0; i < lenxy; i++) {
			mp3x[n2 * x[i + 1] + n1 * x[i] + y[i]] += 1;
			mp3y[n2 * y[i + 1] + n1 * y[i] + x[i]] += 1;
			mpx[n1 * x[i + 1] + x[i]] += 1;
			mpy[n1 * y[i + 1] + y[i]] += 1;
			mpxy[n1 * x[i] + y[i]] += 1;
			mpyx[n1 * y[i] + x[i]] += 1;
			px[x[i]] += 1;
			py[y[i]] += 1;
		}
		mpxy[n1 * x[lenxy - 1] + y[lenxy - 1]] += 1;
		mpyx[n1 * y[lenxy - 1] + x[lenxy - 1]] += 1;
		px[x[lenxy - 1]] += 1;
		py[y[lenxy - 1]] += 1;


		//calcurate x->y


		double result = 0.0;

		return result;
	}
}