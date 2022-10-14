#include "Cat.h"
#include "World.h"
#include <stdexcept>
#include <vector>
#include <algorithm>

// Goal of the cat is to find the shortest path to the edge of the screen
Point2D Cat::Move(World* world)
{
	// Gets current cat position
	Point2D catPos = world->getCat();

	// Goal assigned to out of bounds as a way of saying it hasn't been found
	Point2D goalPos = Point2D(world->getWorldSideSize() + 1, world->getWorldSideSize() + 1);

	// Keeps track of spaces that need to be visited
	std::priority_queue<queueEntry> frontier;

	// Keeps track of what points came from where.
	// Should also keep track of what has been visited.
	std::map<int, std::map<int, std::pair<int, int>>> cameFrom;

	// Bootstrap first element
	queueEntry cat;
	cat.position = catPos;
	cat.cameFrom = catPos;
	cat.weight = 1;
	cat.visited = true;
	cat.blocked = true;

	frontier.push(cat);
	cameFrom[cat.position.x][cat.position.y] = std::pair<int, int>(cat.cameFrom.x, cat.cameFrom.y);

	// Start search
	Search(frontier, cameFrom, goalPos, world);

	// Check if a goal was found. If not, it will
	// still be the default value of out of bounds.
	// Since the cat will not have a goal to move to
	// it will instead choose to move to a random
	// nearby position.

	// Or should it move to the furthest open position?
	if (goalPos == Point2D(world->getWorldSideSize() + 1, world->getWorldSideSize() + 1))
	{
		std::vector<Point2D> neighbors;
		neighbors.push_back(world->E(catPos));
		neighbors.push_back(world->NE(catPos));
		neighbors.push_back(world->NW(catPos));
		neighbors.push_back(world->SE(catPos));
		neighbors.push_back(world->SW(catPos));
		neighbors.push_back(world->W(catPos));

		std::vector<Point2D> availableNeighbors;
		for (int i = 0; i < neighbors.size(); i++)
		{
			if (!world->getContent(neighbors[i]))
			{
				availableNeighbors.push_back(neighbors[i]);
			}
		}

		if (availableNeighbors.size() != 0)
		{
			int random = rand() % availableNeighbors.size();

			return availableNeighbors[random];
		}

		std::cout << "Cat Caught" << std::endl;
		return catPos;
	}

	if (catPos == goalPos)
	{
		std::cout << "Cat Escaped" << std::endl;
		return catPos;
	}

	// If cameFrom is empty, then nothing was searched
	// and the cat is completely surrounded
	if (cameFrom.size() == 1)
	{
		std::cout << "Cat Caught" << std::endl;
		return catPos;
	}

	// Then create a lowest weight path to the exit from what was visited
	// Work back from the end towards the cat and save the next space the
	// cat should move to.
	Point2D moveTo = Point2D(0, 0);

	Point2D currentSpace = goalPos;
	bool catFound = false;

	while (!catFound)
	{
		std::pair<int, int> nextSpacePair = cameFrom[currentSpace.x][currentSpace.y];
		Point2D nextSpace = Point2D(nextSpacePair.first, nextSpacePair.second);

		if (nextSpace == catPos)
		{
			catFound = true;
			break;
		}

		currentSpace = nextSpace;
	}

	moveTo = currentSpace;
	return moveTo;
}
