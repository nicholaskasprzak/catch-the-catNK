#ifndef PRIMNEW_H
#define PRIMNEW_H

#include "../MazeGeneratorBase.h"
#include "Point2D.h"
#include <map>
#include <vector>
#include "../Node.h"

class PrimNew : public MazeGeneratorBase
{
public:
	PrimNew() = default;
	std::string GetName() override { return "Prim New"; };
	bool Step(World* world) override;
	void Clear(World* world) override;

	void markAsVisited(Point2D point);
	void markAsIn(Point2D point);
	std::vector<Point2D> getNeighbors(Point2D point, World* world);
	std::vector<Point2D> getInNeighbors(Point2D point, World* world);
	void buildPath(Point2D currentPoint, Point2D inPoint, World* world);
	void initMaze(World* world);

private:
	// Keeps track of points in the maze and if
	// they've been visited (put in frontier)
	std::map<std::pair<int, int>, bool> visited;

	// Keeps track of points in the maze and if
	// they've been added to the path
	std::map<std::pair<int, int>, bool> inMaze;

	// Keeps track of points in the frontier
	std::vector<std::pair<int, int>> frontier;

	bool hasBeenInit = false;
};

#endif