#include <iostream>
#include "MovingAverage.h"

int main(int argc, char * argv[])
{
	constexpr short wins[6] = { 4,8,16,32,64,128 };

	int N = 0;
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
	if (N < wins[0])
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
		double edge = 100.0;

		for (int i = 0; i != N; ++i)
		{
			int t = rand();

			dsignal[i] = edge * t / RAND_MAX;
			fsignal[i] = dsignal[i];
		}
	}

	delete[] dsignal;
	delete[] fsignal;

	return 0;
}


