#include "Catcher.h"
#include "World.h"

// Goal is to block the cat's path and encapsulate it.
// Check all possible paths the cat can take and place
// a block in a position closest to another block on
// said path? Would this slowly block off the cat's 
// path over time? Or would it just be better to place
// a block on the cat's path closest to the cat?
// How should this account for movement?

Point2D Catcher::Move(World* world) 
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

	// Place a block where the cat is
	// trying to move to.
	Point2D moveTo = goalPos;

	// If a goal wasn't found, try to
	// surround the cat completely
	if (goalPos == Point2D(world->getWorldSideSize() + 1, world->getWorldSideSize() + 1))
	{
		// Load neighbors vector with neighboring Point2Ds
		std::vector<Point2D> neighbors;
		neighbors.push_back(world->E(catPos));
		neighbors.push_back(world->NE(catPos));
		neighbors.push_back(world->NW(catPos));
		neighbors.push_back(world->SE(catPos));
		neighbors.push_back(world->SW(catPos));
		neighbors.push_back(world->W(catPos));

		// Block the first neighbor found that isn't occupied
		for (int i = 0; i < neighbors.size(); i++)
		{
			if (!world->getContent(neighbors[i]))
			{
				return neighbors[i];
			}
		}
	}

	return moveTo;
}
