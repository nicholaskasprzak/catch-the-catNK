#ifndef ELLER_H
#define ELLER_H

#include "../MazeGeneratorBase.h"
#include "Point2D.h"
#include <map>
#include <vector>

class Eller : public MazeGeneratorBase
{
public:
	Eller() = default;
	std::string GetName() override { return "Eller"; };
	bool Step(World* world) override;
	void Clear(World* world) override;

	void merge(Point2D mergingNode, Point2D targetNode);
	void add(Point2D node, int set);
	bool sameSet(Point2D node1, Point2D node2);
	void populate(World* world);

private:
	// Keeps track of what nodes belong to what set
	std::map<int, std::vector<std::pair<int, int>>> sets;

	// Keeps track of what set each node is in
	std::map<int, std::map<int, int>> nodes;

	int currentStep;
	int currentRow;
	bool finished = false;
	std::vector<std::pair<int, int>> previousVerticals;
};

#endif