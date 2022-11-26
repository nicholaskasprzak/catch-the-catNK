#include "BiomeGenerator.h"
#include <random>

std::vector<std::vector<float>> BiomeGenerator::noiseGeneratorTest(int sideSize)
{
	std::vector<std::vector<float>> noiseVector;

	// Generate a height map of numbers between 0 and 1
	for (int i = 0; i < sideSize; i++)
	{
		noiseVector.emplace_back(std::vector<float>(0));
		for (int j = 0; j < sideSize; j++)
		{
			// Generate white noise for each element in the array
			noiseVector[i].emplace_back(((double)rand() / (RAND_MAX)));
		}
	}

	// Modify the white noise to make it red noise
	for (int i = 0; i < sideSize; i++)
	{
		for (int j = 0; j < sideSize; j++)
		{
			// Cache the current white noise value
			float currentVal = noiseVector[i][j];
			// Used to get average of neighboring values
			int neighbors = 0;

			// Get sum of all neighboring values
			if (i - 1 > 0)
			{
				//currentVal += noiseVector[i - 1][j];
				//neighbors++;
			}

			if (i + 1 < sideSize)
			{
				currentVal += noiseVector[i + 1][j];
				neighbors++;
			}

			if (j - 1 > 0)
			{
				//currentVal += noiseVector[i][j - 1];
				//neighbors++;
			}

			if (j + 1 < sideSize)
			{
				//currentVal += noiseVector[i][j + 1];
				//neighbors++;
			}

			// Get average of neighboring values
			currentVal /= neighbors;
		}
	}

	return noiseVector;
}

std::vector<Color32> BiomeGenerator::Generate(int sideSize, float displacement)
{
	std::vector<Color32> colors;

	//std::vector<float> amplitudesVec = [amplitudes, amplitudes + sizeof(amplitudes) / sizeof(float)];
	//std::vector<int> frequenciesVec = [frequencies, frequencies + sizeof(frequencies) / sizeof(int)];

	// Noise generator
	std::vector<std::vector<float>> noise = noiseGeneratorTest(sideSize);

	for (int i = 0; i < sideSize; i++)
	{
		for (int j = 0; j < sideSize; j++)
		{
			float color = (((noise[i][j] + 1) / 2) * 255);
			colors.emplace_back(color, color, color);
		}
	}

	return colors;
}
std::string BiomeGenerator::GetName() { return "BIOME"; }