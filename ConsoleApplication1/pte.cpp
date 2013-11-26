/*
 * pure transfer entropy
 *
 */

#include "stdafx.h"
#include "changetype.h"

double pte(string x, string y, int ndigit)
{
	int lenx = x.size();
	int leny = y.size();

	if (lenx == leny) {
		int lenxy = lenx;
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
		for (int i = 0; i < lenxy - 1; i++) {
			int xi1 = (int)(x[i + 1] - '0');
			int yi1 = (int)(y[i + 1] - '0');
			int xi = (int)(x[i] - '0');
			int yi = (int)(y[i] - '0');

			mp3x[n2 * xi1 + n1 * xi + yi] = mp3x[n2 * xi1 + n1 * xi + yi] + 1;
			mp3y[n2 * yi1 + n1 * yi + xi] = mp3y[n2 * yi1 + n1 * yi + xi] + 1;
			mpx[n1 * xi1 + xi] = mpx[n1 * xi1 + xi] + 1;
			mpy[n1 * yi1 + yi] = mpy[n1 * yi1 + yi] + 1;
			mpxy[n1 * xi + yi] = mpxy[n1 * xi + yi] + 1;
			mpyx[n1 * yi + xi] = mpyx[n1 * yi + xi] + 1;
			px[xi] = px[xi] + 1;
			py[yi] = py[yi] + 1;
		}
		int xn = (int)(x[lenxy - 1] - '0');
		int yn = (int)(y[lenxy - 1] - '0');
		mpxy[n1 * xn + yn] = mpxy[n1 * xn + yn] + 1;
		mpyx[n1 * yn + xn] = mpyx[n1 * yn + xn]  + 1;
		px[xn] = px[xn] + 1;
		py[yn] = py[yn] + 1;

		/*
		//check
		for (int i = 0; i < n3; i++) {
			cout << "mp3x" << i << ":";
			cout << mp3x[i] << endl;
		}
		for (int i = 0; i < n3; i++) {
			cout << "mp3y" << i << ":";
			cout << mp3y[i] << endl;
		}
		for (int i = 0; i < n2; i++) {
			cout << "mpxy" << i << ":";
			cout << mpxy[i] << endl;
		}
		for (int i = 0; i < n2; i++) {
			cout << "mpyx" << i << ":";
			cout << mpyx[i] << endl;
		}
		for (int i = 0; i < n2; i++) {
			cout << "mpx" << i << ":";
			cout << mpx[i] << endl;
		}
		for (int i = 0; i < n2; i++) {
			cout << "mpy" << i << ":";
			cout << mpy[i] << endl;
		}
		for (int i = 0; i < n1; i++) {
			cout << "px" << i << ":";
			cout << px[i] << endl;
		}
		for (int i = 0; i < n1; i++) {
			cout << "py" << i << ":";
			cout << py[i] << endl;
		}*/


		//calcurate x->y
		double yte = 0.0;
		for (int i = 0; i < n1; i++) {
			for (int j = 0; j < n1; j++) {
				for (int k = 0; k < n1; k++) {
					int index3 = n2 * i + n1 * j + k;
					int index_yy = n1 * i + j;
					int index_yx = n1 * j + k;
					int index_y = j;

					if (mp3y[index3] != 0 && py[index_y] != 0 && mpyx[index_yx] != 0 && mpy[index_yy] != 0) //  mpyx[index3] != 0 && mpy[index2] != 0  ??
					{
						double numerator = (double)mp3y[index3] * (double)py[index_y];
						double denominator = (double)mpyx[index_yx] * (double)mpy[index_yy];
						double nd = numerator / denominator;
						if (nd != 0) {
							yte = yte + ((double)mp3y[index3] / (lenxy - 1)) * log10(nd);
						}
					}
				}
			}
		}


		//calcurate y->x
		double xte = 0.0;
		for (int i = 0; i < n1; i++) {
			for (int j = 0; j < n1; j++) {
				for (int k = 0; k < n1; k++) {
					int index3 = n2 * i + n1 * j + k;
					int index_xx = n1 * i + j;
					int index_xy = n1 * j + k;
					int index_x = j;

					if (mp3x[index3] != 0 && px[index_x] != 0 && mpxy[index_xy] != 0 && mpx[index_xx] != 0)//  mpxy[index3] != 0 && mpx[index2] != 0  ??
					{
						double numerator = (double)mp3x[index3] * (double)px[index_x];
						double denominator = (double)mpxy[index_xy] * (double)mpx[index_xx];
						double nd = numerator / denominator;
						if (nd != 0) {
							xte = xte + ((double)mp3x[index3] / (lenxy - 1)) * log10(nd);
						}
					}
				}
			}
		}

		// free
		delete[] mp3x;
		delete[] mp3y;
		delete[] mpxy;
		delete[] mpyx;
		delete[] mpx;
		delete[] mpy;
		delete[] px;
		delete[] py;


		cout << "y->x:" << xte;
		cout << "x->y:" << yte;

		return xte;
	}
}


double pteXtoY(string x, string y, int ndigit)
{
	int lenx = x.size();
	int leny = y.size();

	if (lenx == leny) {
		int lenxy = lenx;
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
		for (int i = 0; i < lenxy - 1; i++) {
			int xi1 = (int)(x[i + 1] - '0');
			int yi1 = (int)(y[i + 1] - '0');
			int xi = (int)(x[i] - '0');
			int yi = (int)(y[i] - '0');

			mp3x[n2 * xi1 + n1 * xi + yi] = mp3x[n2 * xi1 + n1 * xi + yi] + 1;
			mp3y[n2 * yi1 + n1 * yi + xi] = mp3y[n2 * yi1 + n1 * yi + xi] + 1;
			mpx[n1 * xi1 + xi] = mpx[n1 * xi1 + xi] + 1;
			mpy[n1 * yi1 + yi] = mpy[n1 * yi1 + yi] + 1;
			mpxy[n1 * xi + yi] = mpxy[n1 * xi + yi] + 1;
			mpyx[n1 * yi + xi] = mpyx[n1 * yi + xi] + 1;
			px[xi] = px[xi] + 1;
			py[yi] = py[yi] + 1;
		}
		int xn = (int)(x[lenxy - 1] - '0');
		int yn = (int)(y[lenxy - 1] - '0');
		mpxy[n1 * xn + yn] = mpxy[n1 * xn + yn] + 1;
		mpyx[n1 * yn + xn] = mpyx[n1 * yn + xn] + 1;
		px[xn] = px[xn] + 1;
		py[yn] = py[yn] + 1;


		//calcurate x->y
		double yte = 0.0;
		for (int i = 0; i < n1; i++) {
			for (int j = 0; j < n1; j++) {
				for (int k = 0; k < n1; k++) {
					int index3 = n2 * i + n1 * j + k;
					int index_yy = n1 * i + j;
					int index_yx = n1 * j + k;
					int index_y = j;

					if (mp3y[index3] != 0 && py[index_y] != 0 && mpyx[index_yx] != 0 && mpy[index_yy] != 0) //  mpyx[index3] != 0 && mpy[index2] != 0  ??
					{
						double numerator = (double)mp3y[index3] * (double)py[index_y];
						double denominator = (double)mpyx[index_yx] * (double)mpy[index_yy];
						double nd = numerator / denominator;
						if (nd != 0) {
							yte = yte + ((double)mp3y[index3] / (lenxy - 1)) * log10(nd);
						}
					}
				}
			}
		}

		// free
		delete[] mp3x;
		delete[] mp3y;
		delete[] mpxy;
		delete[] mpyx;
		delete[] mpx;
		delete[] mpy;
		delete[] px;
		delete[] py;


		//cout << "x->y:" << yte;

		return yte;
	}
}