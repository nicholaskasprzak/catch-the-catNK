#include "Agent.h"
#include "World.h"

void Agent::GetNeighbors(std::priority_queue<queueEntry>& priorityQueue, std::map<int, std::map<int, std::pair<int, int>>>& cameFromMap, World* world, queueEntry current)
{
	// Load neighbors vector with neighboring Point2Ds
	std::vector<Point2D> neighbors;
	neighbors.push_back(world->E(current.position));
	neighbors.push_back(world->NE(current.position));
	neighbors.push_back(world->NW(current.position));
	neighbors.push_back(world->SE(current.position));
	neighbors.push_back(world->SW(current.position));
	neighbors.push_back(world->W(current.position));

	// Iterate through each neighbor and check if they meet the criteria to be added to the priority queue
	for (int i = 0; i < neighbors.size(); i++)
	{
		// Check if the position is a valid space in the grid
		// If the space is invalid, continue
		bool isValid = world->isValidPosition(neighbors[i]);

		if (!isValid)
		{
			return;
		}
		
		// Checks if the neighbor has already been visited
		// by seeing it has been added to cameFrom.
		// If the neighbor has been visited, continue
		if (cameFromMap[neighbors[i].x].find(neighbors[i].y) != cameFromMap[neighbors[i].x].end())
		{
			continue;
		}

		// Check if the space is blocked using getContent
		bool isOccupied = world->getContent(neighbors[i]);

		// If the space is occupied, continue
		if (isOccupied)
		{
			continue;
		}

		// Otherwise, mark it as visited now and continue
		// This should also account for preventing the same
		// location from being added to the queue twice at
		// the same time.
		cameFromMap[neighbors[i].x][neighbors[i].y] = std::pair<int, int>(current.position.x, current.position.y);

		// Otherwise, it passes all the checks and has a
		// queueEntry created for it.

		queueEntry newEntry;
		newEntry.position = neighbors[i];
		newEntry.cameFrom = current.position;
		newEntry.weight = current.weight + 1;
		newEntry.visited = true;
		newEntry.blocked = false;

		// This new entry is then added to the priorityQueue
		// by reference.
		priorityQueue.push(newEntry);
	}
}

void Agent::Search(std::priority_queue<queueEntry>& frontier, std::map<int, std::map<int, std::pair<int, int>>>& cameFromMap, Point2D& goalPos, World* world)
{
	// While all elements haven't been visited, visit them
	// Breadth first search to get full path
	while (!frontier.empty())
	{
		// Get first element from queue
		queueEntry current = frontier.top();

		// Check if the current position is the goal
		// If it is, cache it to goal and break early
		bool isGoal = CheckIfGoal(world, current.position);

		if (isGoal)
		{
			goalPos = current.position;
			break;
		}

		// Mark the head as visited
		current.visited = true;

		// Pass all neighbors into the priorityQueue and cameFrom
		GetNeighbors(frontier, cameFromMap, world, current);

		// Pop the front of the priorityQueue
		frontier.pop();
	}
}

bool Agent::CheckIfGoal(World* world, Point2D position)
{
	int worldSize = world->getWorldSideSize();

	if (position.x == -worldSize/2 ||
		position.x == worldSize/2 ||
		position.y == -worldSize/2 ||
		position.y == worldSize/2)
	{
		return true;
	}

	return false;
}