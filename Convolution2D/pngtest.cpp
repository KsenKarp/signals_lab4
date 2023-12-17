#include "PngProc.h"
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <fstream>

using namespace std;

void Convolution_2D(unsigned char* pOut
			 , unsigned char* pIn
			 , size_t nWidth
			 , size_t nHeight, const int* pKernel, int iKernelSize);


int main(int argc, char* argv[])
{
	class CBitsPtrGuard
	{
	public:
		CBitsPtrGuard(unsigned char** pB) : m_ppBits(pB) { }
		~CBitsPtrGuard() { if (*m_ppBits) delete *m_ppBits, *m_ppBits = 0; }
	protected:
		unsigned char** m_ppBits;
	};

	// parse input parameters
	char	szInputFileName[256];
	char    szOutputFileName[256];
	if (argc < 2)
		printf("\nformat: pngtest <input_file> [<output_file>]");
	else 
	{
		strcpy(szInputFileName, argv[1]);
		if (argc > 2)
			strcpy(szOutputFileName, argv[2]);
		else
		{
			strcpy(szOutputFileName, szInputFileName);
			strcat(szOutputFileName, "_out.png");
		}
	}


	size_t nReqSize = NPngProc::readPngFile(szInputFileName, 0, 0, 0, 0);
	if (nReqSize == NPngProc::PNG_ERROR)
	{
		printf("\nError ocured while pngfile was read");
		return -1;
	}
	

	unsigned char* pInputBits = new unsigned char[nReqSize];
	if (!pInputBits)
	{
		printf("\nCan't allocate memory for image, required size is %u", nReqSize);
		return -1;
	}
	CBitsPtrGuard InputBitsPtrGuard(&pInputBits);


	unsigned char* pOutputBits = new unsigned char[nReqSize];
	if (!pOutputBits)
	{
		printf("\nCan't allocate memory for image, required size is %u", nReqSize);
		return -1;
	}


	CBitsPtrGuard OutputBitsPtrGuard(&pOutputBits);

	size_t nWidth, nHeight;
	unsigned int nBPP;

	size_t nRetSize = NPngProc::readPngFileGray(szInputFileName, pInputBits, &nWidth, &nHeight/*, &nBPP*/);
	nBPP = 8;



	int iKernelSize;
	cout << "Enter the kernel to \'kernel.txt\' and then enter the size of a kernel:\n";
	cin >> iKernelSize;

	int* pKernel = new int[iKernelSize * iKernelSize];
	ifstream f;
	f.open("kernel.txt");
	int k = 0;
	for (int i = 0; i < iKernelSize; ++i) {
		for (int j = 0; j < iKernelSize; ++j) {
			f >> pKernel[k]; 
			++k;
		}
	}

	// ASSERT(nRetSize == nReqSize);

	// TODO: image processing 
	Convolution_2D(pOutputBits, pInputBits, nWidth, nHeight, pKernel, iKernelSize);

	if (NPngProc::writePngFile(szOutputFileName, pOutputBits, nWidth, nHeight, nBPP) == NPngProc::PNG_ERROR)
	{
		printf("\nError ocuured during png file was written");
		return -1;
	}

	f.close();

	return 0;
}

void Convolution_2D(unsigned char* pRes
			 , unsigned char* pSrc
			 , size_t iWidth
			 , size_t iHeight, const int* pKernel, int iKernelSize) {

		int iHalf = iKernelSize / 2;
		memcpy(pRes, pSrc, sizeof(*pRes) * iWidth * iHeight);
		// копирование изображения (для полос по краям изображения)
		for (int y = iHalf; y < iHeight - iHalf; ++y) { // свертка
			for (int x = iHalf; x < iWidth - iHalf; ++x) {
				const int* pk = pKernel;
				const unsigned char* ps = &pSrc[(y - iHalf) * iWidth + x - iHalf];
				int iSum = 0;
				for (int v = 0; v < iKernelSize; ++v) {
					for (int u = 0; u < iKernelSize; ++u)
						iSum += ps[u] * pk[u];

					pk += iKernelSize;  // Переход к следующей строкам
					ps += iWidth;
				}
				if (iSum > 255) iSum = 255; // Контроль выхода из диапазона 8 bpp
				else
					if (iSum < 0) iSum = 0;
				pRes[y * iWidth + x] = (unsigned char)iSum;
			}
		}

}
