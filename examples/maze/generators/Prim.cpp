#include "Prim.h"
#include "../World.h"
#include "Random.h"
#include <climits>
#include <algorithm>

bool Prim::Step(World* world)
{
	// Choose a random grid space if the
	// maze hasn't been initalized yet
	if (!init)
	{
		int worldSize = world->GetSize();
		int randX = Random::Range(-worldSize / 2, worldSize / 2);
		int randY = Random::Range(-worldSize / 2, worldSize / 2);

		mark(Point2D(randX, randY), world);

		init = true;
	}

	// While the frontier isn't empty,
	// build the maze based on what is
	// in the frontier
	if (frontier.size() != 0)
	{
		// Choose a random element from the frontier
		auto iterator = frontier.begin();
		int random = rand() % frontier.size();
		std::advance(iterator, random);

		std::pair<int, int> pair = (*iterator);
		Point2D node = Point2D(pair.first, pair.second);
		frontier.erase(iterator);

		// Choose randomly from one of it's "in" neighbors
		std::vector<Point2D> neighbors = getNeighbors(node, world);
		Point2D randomNeighbor = neighbors[Random::Range(0, neighbors.size())];

		// This is then recorded as a passage from that
		// in node to the current node
		NODE_STATUS direction = getDirection(node, randomNeighbor);
		grid[node.x].insert(std::make_pair(node.y, direction));
		grid[randomNeighbor.x].insert(std::make_pair(randomNeighbor.y, getOppositeDirection(direction)));

		// Display the new changes
		Node nodeObj = buildNode(node);
		world->SetNode(node, nodeObj);
		world->SetNodeColor(node, Color::Black);

		// Lastly, mark the current node as "in" and
		// pass its neighbors into the frontier
		mark(node, world);
	}

	return true;
}

void Prim::Clear(World* world)
{
	return;
}

void Prim::mark(Point2D point, World* world)
{
	// Marks the given point as in the maze
	grid[point.x].insert(std::make_pair(point.y, IN));

	// Cache coordinates as seperate values
	int x = point.x;
	int y = point.y;

	// Adds all "out" neighbors to the frontier
	add(Point2D(x - 1, y), world);
	add(Point2D(x + 1, y), world);
	add(Point2D(x, y - 1), world);
	add(Point2D(x, y + 1), world);

	std::cout << frontier.size() << std::endl;
}

// Utility function that handles logic behind adding
// a given point to the frontier.
void Prim::add(Point2D point, World* world)
{
	int worldSize = world->GetSize();

	// Checks if the given point is within the bounds of the world
	// and returns if it outside the bounds in any fashion.
	if (point.x < -worldSize / 2 ||
		point.x > worldSize / 2 ||
		point.y < -worldSize / 2 ||
		point.y > worldSize / 2)
	{
		return;
	}

	// Otherwise, the neighbor is valid so it
	// gets added to the frontier and has it's
	// status updated to FRONTIER
	frontier.insert(std::make_pair(point.x, point.y));
	grid[point.x].insert(std::make_pair(point.y, FRONTIER));
}

// Returns a vector of "in" neighbors
std::vector<Point2D> Prim::getNeighbors(Point2D point, World* world)
{
	int worldSize = world->GetSize();

	std::vector<Point2D> neighbors;
	int x = point.x;
	int y = point.y;

	// Load all possible neighbors into the vector
	neighbors.push_back(Point2D(x + 1, y));
	neighbors.push_back(Point2D(x - 1, y));
	neighbors.push_back(Point2D(x, y + 1));
	neighbors.push_back(Point2D(x, y - 1));

	// Check if each neighbor in the vector is
	// in the bounds of the world
	for (int i = 0; i < neighbors.size(); i++)
	{
		// If a neighbor isn't, remove it
		// from the return vector
		if (neighbors[i].x < -worldSize / 2 &&
			neighbors[i].x > worldSize / 2 &&
			neighbors[i].y < -worldSize / 2 &&
			neighbors[i].y > worldSize / 2)
		{
			neighbors.erase(neighbors.begin() + i);
		}

		// If a neighbor isn't in, remove it
		// from the return vector
		if (grid[neighbors[i].x].find(neighbors[i].y) != grid[neighbors[i].x].end())//[neighbors[i].x][neighbors[i].y] != grid.end())
		{
			neighbors.erase(neighbors.begin() + i);
		}
	}

	return neighbors;
}

NODE_STATUS Prim::getDirection(Point2D node, Point2D neighbor)
{
	if (node.x < neighbor.x)
	{
		return E;
	}

	else if (node.x > neighbor.x)
	{
		return W;
	}

	else if (node.y < neighbor.y)
	{
		return S;
	}

	else if (node.y > neighbor.y)
	{
		return N;
	}
}

NODE_STATUS Prim::getOppositeDirection(NODE_STATUS direction)
{
	if (direction == N)
	{
		return S;
	}

	else if (direction == S)
	{
		return N;
	}

	else if (direction == E)
	{
		return W;
	}

	else if (direction == W)
	{
		return E;
	}
}

Node Prim::buildNode(Point2D point)
{
	NODE_STATUS direction = grid[point.x][point.y];

	Node returnNode = Node(true, true, true, true);

	if (direction == N)
	{
		returnNode.SetNorth(false);
	}

	else if (direction == S)
	{
		returnNode.SetSouth(false);
	}

	else if (direction == E)
	{
		returnNode.SetEast(false);
	}

	else if (direction == W)
	{
		returnNode.SetWest(false);
	}

	return returnNode;
}