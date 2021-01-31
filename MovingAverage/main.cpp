#include <iostream>
#include "MovingAverage.h"

int main(int argc, char * argv[])
{
	constexpr short wins[6] = { 4,8,16,32,64,128 };

	int N = 0;
	int randomSeed = 0;

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

	std::cout << N << "\n" << randomSeed;

	return 0;
}


