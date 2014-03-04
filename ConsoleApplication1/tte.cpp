/*
* pure transfer entropy
*
*/

#include "stdafx.h"
#include "changetype.h"
#include "Compare.h"
#include "Split.h"

double tte(string x, string y, int ndigit, int type)
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
		for (int i = 0; i < n1; i++) { //y1
			for (int j = 0; j < n1; j++) { //y
				for (int k = 0; k < n1; k++) { //x
					if (k == type && i == type && j != type) {
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
		}


		//calcurate y->x
		double xte = 0.0;
		for (int i = 0; i < n1; i++) { //x1
			for (int j = 0; j < n1; j++) { //x
				for (int k = 0; k < n1; k++) { //y
					if (k == type && i == type && j != type) {
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


		//cout << "y->x:" << xte;
		//cout << "x->y:" << yte;

		return xte;
	}
}


double tteXtoY(string x, string y, int ndigit, int type)
{
	vector<string> xTopics = splitVector(x, " ");
	vector<string> yTopics = splitVector(y, " ");
	int lenx = xTopics.size();
	int leny = yTopics.size();
	int lenxy = getMin(lenx, leny);
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
		int xi1 = (int)(stringToInt(xTopics[i + 1]));
		int yi1 = (int)(stringToInt(yTopics[i + 1]));
		int xi = (int)(stringToInt(xTopics[i]));
		int yi = (int)(stringToInt(yTopics[i]));

		mp3x[n2 * xi1 + n1 * xi + yi] = mp3x[n2 * xi1 + n1 * xi + yi] + 1;
		mp3y[n2 * yi1 + n1 * yi + xi] = mp3y[n2 * yi1 + n1 * yi + xi] + 1;
		mpx[n1 * xi1 + xi] = mpx[n1 * xi1 + xi] + 1;
		mpy[n1 * yi1 + yi] = mpy[n1 * yi1 + yi] + 1;
		mpxy[n1 * xi + yi] = mpxy[n1 * xi + yi] + 1;
		mpyx[n1 * yi + xi] = mpyx[n1 * yi + xi] + 1;
		px[xi] = px[xi] + 1;
		py[yi] = py[yi] + 1;
	}
	int xn = (int)(stringToInt(xTopics[lenxy - 1]));
	int yn = (int)(stringToInt(yTopics[lenxy - 1]));
	mpxy[n1 * xn + yn] = mpxy[n1 * xn + yn] + 1;
	mpyx[n1 * yn + xn] = mpyx[n1 * yn + xn] + 1;
	px[xn] = px[xn] + 1;
	py[yn] = py[yn] + 1;


	//check
	/*
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
	for (int i = 0; i < n1; i++) { //y1
		for (int j = 0; j < n1; j++) { //y
			for (int k = 0; k < n1; k++) { //x
				if (k == type && i == type && j != type) {
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
							//cout << "index:" << index3 << endl;
							//cout << "numerator:" << numerator << " = " << "mp3x:" << index3 << " " << mp3y[index3] << " * py:" << index_y << " " << py[index_y] << endl;
							//cout << "index_yx:" << index_yx << endl;
							//cout << "denominator:" << denominator << " = " << "mpyx:" << index_yx << " " << mpyx[index_yx] << " * mpy:" << index_yy << " " << mpy[index_yy] << endl;
							//cout << "len:" << lenxy - 1 << endl;
							//cout << "ans:" << ((double)mp3y[index3] / (lenxy - 1)) * log10(nd) << endl;
							yte = yte + ((double)mp3y[index3] / (lenxy - 1)) * log10(nd);
						}
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


double tteXYZ(vector<string> contents, int ndigit, int type)
{
	//initial
	int n3 = ndigit * ndigit * ndigit;
	int n2 = ndigit * ndigit;
	int n1 = ndigit;

	int *mp3x = new int[n3];
	for (int i = 0; i < n3; i++) {
		mp3x[i] = 0;
	}
	int *mpxy = new int[n2];
	for (int i = 0; i < n2; i++) {
		mpxy[i] = 0;
	}
	int *mpx = new int[n2];
	for (int i = 0; i < n2; i++) {
		mpx[i] = 0;
	}
	int *px = new int[n1];
	for (int i = 0; i < n1; i++) {
		px[i] = 0;
	}


	// count number
	int tmp = 0;
	for (int i = 0; i < contents.size(); i++) {
		// define 
		string line = contents[i];
		int xi = 0;
		int yi = 0;
		int zi = 0;
		int p;
		int count = 0;

		// init xi,yi,zi
		while ((p = line.find("\t")) != line.npos){
			if (count == 0){
				xi = stringToInt(line.substr(0, p));
			}
			else if (count == 1) {
				yi = stringToInt(line.substr(0, p));
				zi = stringToInt(line.substr(p + 1));
				break;
			}
			else {
				break;
			}
			line = line.substr(p + 1);
			count = count + 1;
		}
		if (i == contents.size() - 1) {
			mpxy[n1 * tmp + yi] = mpxy[n1 * tmp + yi] + 1;
		}
		else
		{
			mp3x[n2 * zi + n1 * xi + yi] = mp3x[n2 * zi + n1 * xi + yi] + 1;
			mpx[n1 * zi + xi] = mpx[n1 * zi + xi] + 1;
			mpxy[n1 * xi + yi] = mpxy[n1 * xi + yi] + 1;
			px[xi] = px[xi] + 1;
			if (i == contents.size() - 2) {
				px[zi] = px[zi] + 1;
				tmp = zi;
			}
		}
	}

	/*//check
	for (int i = 0; i < n3; i++) {
	cout << "mp3x" << i << ":";
	cout << mp3x[i] << endl;
	}
	for (int i = 0; i < n2; i++) {
	cout << "mpxy" << i << ":";
	cout << mpxy[i] << endl;
	}
	for (int i = 0; i < n2; i++) {
	cout << "mpx" << i << ":";
	cout << mpx[i] << endl;
	}
	for (int i = 0; i < n1; i++) {
	cout << "px" << i << ":";
	cout << px[i] << endl;
	}*/


	//calcurate y->x
	double xte = 0.0;
	for (int i = 0; i < n1; i++) {
		for (int j = 0; j < n1; j++) {
			for (int k = 0; k < n1; k++) {
				if (k == type && i == type) {// && j != type
					int index3 = n2 * i + n1 * j + k;
					int index_xx = n1 * i + j;
					int index_xy = n1 * j + k;
					int index_x = j;

					if (mp3x[index3] != 0 && px[index_x] != 0 && mpxy[index_xy] != 0 && mpx[index_xx] != 0)
					{
						double numerator = (double)mp3x[index3] * (double)px[index_x];
						double denominator = (double)mpxy[index_xy] * (double)mpx[index_xx];
						double nd = numerator / denominator;
						if (nd != 0) {
							xte = xte + ((double)mp3x[index3] / (contents.size() - 1)) * log10(nd);
						}
					}
				}
			}
		}
	}

	// free
	delete[] mp3x;
	delete[] mpxy;
	delete[] mpx;
	delete[] px;

	return xte;
}

double tteMultiXYZ(vector<string> contents, int type)
{
	//initial
	int ndigit = 2;
	int n3 = ndigit * ndigit * ndigit;
	int n2 = ndigit * ndigit;
	int n1 = ndigit;

	int *mp3x = new int[n3];
	for (int i = 0; i < n3; i++) {
		mp3x[i] = 0;
	}
	int *mpxy = new int[n2];
	for (int i = 0; i < n2; i++) {
		mpxy[i] = 0;
	}
	int *mpx = new int[n2];
	for (int i = 0; i < n2; i++) {
		mpx[i] = 0;
	}
	int *px = new int[n1];
	for (int i = 0; i < n1; i++) {
		px[i] = 0;
	}


	// count number
	int tmp = 0;
	for (int i = 0; i < contents.size(); i++) {
		// define 
		string line = contents[i];
		int xi = 0;
		int yi = 0;
		int zi = 0;
		int p;
		int count = 0;

		// init xi,yi,zi
		while ((p = line.find("\t")) != line.npos){
			if (count == 0){
				int px;
				string valueX = line.substr(0, p);
				int flagX = 1;
				while ((px = valueX.find(",")) != valueX.npos){
					if (valueX.substr(0, px).substr(0, px) == intToString(type)) {
						xi = 1;
						flagX = 0;
						break;
					}
					valueX = valueX.substr(px + 1);
				}
				if (valueX == intToString(type)) {
					xi = 1;
					flagX = 0;
				}
				if (flagX == 1) {
					xi = 0;
				}
			}
			else if (count == 1) {
				// y
				int py;
				string valueY = line.substr(0, p);
				int flagY = 1;
				while ((py = valueY.find(",")) != valueY.npos){
					if (valueY.substr(0, py) == intToString(type)) {
						yi = 1;
						flagY = 0;
						break;
					}
					valueY = valueY.substr(py + 1);
				}
				if (valueY == intToString(type)) {
					yi = 1;
					flagY = 0;
				}
				if (flagY == 1) {
					yi = 0;
				}

				// z
				int pz;
				string valueZ = line.substr(p + 1);
				int flagZ = 1;
				while ((pz = valueZ.find(",")) != valueZ.npos){
					if (valueZ.substr(0, pz) == intToString(type)) {
						zi = 1;
						flagZ = 0;
						break;
					}
					valueZ = valueZ.substr(pz + 1);
				}
				if (valueZ == intToString(type)) {
					zi = 1;
					flagZ = 0;
				}
				if (flagZ == 1) {
					zi = 0;
				}

				break;
			}
			else {
				break;
			}
			line = line.substr(p + 1);
			count = count + 1;
		}
		if (i == contents.size() - 1) {
			mpxy[n1 * tmp + yi] = mpxy[n1 * tmp + yi] + 1;
		}
		else
		{
			mp3x[n2 * zi + n1 * xi + yi] = mp3x[n2 * zi + n1 * xi + yi] + 1;
			mpx[n1 * zi + xi] = mpx[n1 * zi + xi] + 1;
			mpxy[n1 * xi + yi] = mpxy[n1 * xi + yi] + 1;
			px[xi] = px[xi] + 1;
			if (i == contents.size() - 2) {
				px[zi] = px[zi] + 1;
				tmp = zi;
			}
		}
		//cout << line << endl;
	}

	/*//check
	for (int i = 0; i < n3; i++) {
		cout << "mp3x" << i << ":";
		cout << mp3x[i] << endl;
	}
	for (int i = 0; i < n2; i++) {
		cout << "mpxy" << i << ":";
		cout << mpxy[i] << endl;
	}
	for (int i = 0; i < n2; i++) {
		cout << "mpx" << i << ":";
		cout << mpx[i] << endl;
	}
	for (int i = 0; i < n1; i++) {
		cout << "px" << i << ":";
		cout << px[i] << endl;
	}*/


	//calcurate y->x 101, 111
	double xte = 0.0;
	//for (int i = 0; i < n1; i++) {
	int i = 1;
	int k = 1;
	for (int j = 0; j < n1; j++) {
		//for (int k = 0; k < n1; k++) {
		int index3 = n2 * i + n1 * j + k;
		int index_xx = n1 * i + j;
		int index_xy = n1 * j + k;
		int index_x = j;

		if (mp3x[index3] != 0 && px[index_x] != 0 && mpxy[index_xy] != 0 && mpx[index_xx] != 0)
		{
			double numerator = (double)mp3x[index3] * (double)px[index_x];
			double denominator = (double)mpxy[index_xy] * (double)mpx[index_xx];
			double nd = numerator / denominator;
			if (nd != 0) {
				xte = xte + ((double)mp3x[index3] / (contents.size() - 1)) * log10(nd);
			}
		}
		//}
	}
	//}

	// free
	delete[] mp3x;
	delete[] mpxy;
	delete[] mpx;
	delete[] px;

	return xte;
}