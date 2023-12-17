#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

double* Convolution_1D(double* data, int data_size, double* kernel, int kernel_size) {
	double* res = new double[data_size + kernel_size - 1];
	for (int num = 0; num < data_size + kernel_size - 1; num++) {
		double sum = 0;
		for (int m = 0; m < data_size; m++) {
			if (num - m >= 0 && num - m < kernel_size) sum = sum + data[m] * kernel[num - m];
		}
		res[num] = sum;
	}
	return res;
}


int main() {
	double a[4] = { 2, 1, 3, -1 };
	int kernel_size;
	cout << "Enter kernel size: \n";
	cin >> kernel_size;
	double* kernel = new double[kernel_size];
	cout << "Now enter the kernel\n";
	for (int i = 0; i < kernel_size; i++) {
		cin >> kernel[i];
	}
	cout << endl;
	
	double* convolution;
	convolution = Convolution_1D(a, 4, kernel, kernel_size);
	for (int i = 0; i < 6; i++) {
		cout << convolution[i] << endl;
	}

	delete[] kernel;
	delete[] convolution;
	return 0;
}
