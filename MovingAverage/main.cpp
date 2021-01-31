#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <string>
#include "MovingAverage.h"


int main(int argc, char * argv[])
{
	constexpr short winsEdges[2] = { 4,128 };

	int N = 1000000;
	int randomSeed = 0;

	double * dsignal = nullptr;
	float * fsignal = nullptr;

	
	//cmd args
	if (argc > 2)
	{
		for (int i = 1; i != argc - 1; ++i)
		{
			if (argv[i][1] == 'N')
				N = atoi(argv[i + 1]);

			if (argv[i][1] == 'R')
				randomSeed = atoi(argv[i + 1]);
		}
	}

	//input check
	if (N < winsEdges[0])
	{
		std::cout << "Wrong input!\n";
		return 0;
	}

	srand(randomSeed);

	//memory 
	//use 2N size. 0..N - input, N..2N - output
	dsignal = new double[2 * N];
	fsignal = new float[2 * N];

	//generator
	{
		double edge = 1000.0;

		std::ofstream BaseSignal("SourceSignal.txt");

		for (int i = 0; i != N; ++i)
		{
			dsignal[i] = edge * rand() / (double)RAND_MAX;
			fsignal[i] = (float) dsignal[i];

			BaseSignal << dsignal[i] <<"\n";
		}
	}

	//main part
	{
		short c = winsEdges[0];

		std::ofstream outPerformance("PerformanceOutput.txt");

		unsigned F = CLOCKS_PER_SEC * N;

		while (c != winsEdges[1] * 2)
		{
			if (c > N) break;

			//for testing
			std::ofstream outSignal(std::string("FSignal") + std::to_string(c) + std::string(".txt"));
			outSignal << "WinLength fPerfomance dPerfomance";

			unsigned startClock = clock();

			calculateAverage<float>(fsignal, fsignal + N, c, N);

			unsigned midClock = clock();

			calculateAverage<double>(dsignal, dsignal + N, c, N);

			unsigned endClock = clock();

			if (midClock - startClock > 0 && endClock - midClock > 0)
				outPerformance << c << " " << F / (float)(midClock - startClock) << " " << F /(float) (endClock - midClock) << "\n";

			for (int i = 0; i != N; ++i) outSignal << fsignal[i + N] << "\n";

			c *= 2;
		}
	}

	delete[] dsignal;
	delete[] fsignal;

	return 0;
}


