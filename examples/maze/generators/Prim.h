#ifndef PRIM_H
#define PRIM_H

#include "../MazeGeneratorBase.h"
#include "Point2D.h"
#include <map>
#include <vector>
#include "../Node.h"

enum NODE_STATUS
{
	N, S, E, W,
	IN,
	FRONTIER,
};

class Prim : public MazeGeneratorBase
{
public:
	Prim() = default;
	std::string GetName() override { return "Prim"; };
	bool Step(World* world) override;
	void Clear(World* world) override;

	void mark(Point2D point, World* world);
	void add(Point2D point, World* world);
	std::vector<Point2D> getNeighbors(Point2D point, World* world);
	NODE_STATUS getDirection(Point2D node, Point2D neighbor);
	NODE_STATUS getOppositeDirection(NODE_STATUS direction);
	Node buildNode(Point2D point);

private:
	// Marks points as being "in" the maze
	std::map<int, std::map<int, NODE_STATUS>> grid;
	// Points that are being expanded from to create the maze (no weight?)
	std::map<int, int> frontier;

	bool init = false;
};

#endif