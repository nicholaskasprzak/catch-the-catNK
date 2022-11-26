#ifndef BIOMEGENERATOR_H
#define BIOMEGENERATOR_H

#include "../GeneratorBase.h"

class BiomeGenerator : public ScenarioGeneratorBase {
public:
	std::vector<Color32> Generate(int sideSize, float displacement = 0) override;
	std::string GetName() override;

	std::vector<std::vector<float>> noiseGeneratorTest(int sideSize);

private:
	float amplitudes[6] = { 0.2, 0.5, 1.0, 0.7, 0.5, 0.4 };
	int frequencies[6] = { 1, 2, 4, 8, 16, 32 };
};

#endif  // BIOMEGENERATOR_H