#pragma once

template <typename T>
void calculateAverage(T * signal, T * output, short const & winLen, int const & size)
{
	T sum = 0.0;

	for (int i = 0; i != winLen; ++i)
	{
		sum += signal[i];
		output[i] = sum / i;
	}


	for (int i = winLen; i != size; ++i)
	{
		sum -= signal[i - winLen];
		sum += signal[i];

		output[i] = sum / winLen;
	}
}