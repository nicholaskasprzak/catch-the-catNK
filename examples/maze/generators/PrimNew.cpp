#include "PrimNew.h"
#include "../World.h"
#include "Random.h"
#include <climits>
#include <algorithm>

bool PrimNew::Step(World* world)
{
	if (!hasBeenInit)
	{
		initMaze(world);
		hasBeenInit = true;
	}

	if (!frontier.empty())
	{
		// Get random point from the frontier
		int randomFrontierIndex = Random::Range(0, frontier.size() - 1);
		Point2D currentPoint = Point2D(frontier[randomFrontierIndex].first, frontier[randomFrontierIndex].second);
		markAsIn(currentPoint);

		// Build a path to this point from an in neighbor
		// and mark the current node as in
		std::vector<Point2D> inNeighbors = getInNeighbors(currentPoint, world);

		// Check to make sure that a path isn't constructed
		// when it doesn't need to be
		if (inNeighbors.size() != 0)
		{
			// Choose a random neighbor to build from
			int randomIndex = Random::Range(0, inNeighbors.size() - 1);
			Point2D randomInNeighbor = inNeighbors[randomIndex];

			// Build a path between the two nodes
			buildPath(currentPoint, randomInNeighbor, world);
		}

		// Get the out neighbors of current point
		std::vector<Point2D> neighbors = getNeighbors(currentPoint, world);

		// Add each neighbor to the frontier
		// and mark them as visited
		// Update their node color to red to mark
		// their status in the frontier
		for (int i = 0; i < neighbors.size(); i++)
		{
			frontier.push_back(std::make_pair(neighbors[i].x, neighbors[i].y));
			markAsVisited(neighbors[i]);

			world->SetNodeColor(neighbors[i], Color::Red);
		}

		// Remove the current node from the frontier
		frontier.erase(frontier.begin() + randomFrontierIndex);

		return true;
	}

	return false;
}

void PrimNew::Clear(World* world)
{
	visited.clear();
	inMaze.clear();
	frontier.clear();

	hasBeenInit = false;
}

void PrimNew::markAsVisited(Point2D point)
{
	visited[std::make_pair(point.x, point.y)] = true;
	return;
}

void PrimNew::markAsIn(Point2D point)
{
	inMaze[std::make_pair(point.x, point.y)] = true;
	return;
}

std::vector<Point2D> PrimNew::getNeighbors(Point2D point, World* world)
{
	std::vector<Point2D> neighbors;
	int sideOver = world->GetSize() / 2;

	int x = point.x;
	int y = point.y;

	// Check if each potential neighbor is within the
	// grid and has not already been visited.
	if ((abs(x) <= sideOver && abs(y - 1) <= sideOver) &&
		visited[std::make_pair(x, y - 1)] == false &&
		world->GetNorth({ x, y - 1 }))
	{
		neighbors.emplace_back(x, y - 1);
	}

	if ((abs(x) <= sideOver && abs(y + 1) <= sideOver) &&
		visited[std::make_pair(x, y + 1)] == false &&
		world->GetNorth({ x, y + 1 }))
	{
		neighbors.emplace_back(x, y + 1);
	}

	if ((abs(x - 1) <= sideOver && abs(y) <= sideOver) &&
		visited[std::make_pair(x - 1, y)] == false &&
		world->GetNorth({ x - 1, y }))
	{
		neighbors.emplace_back(x - 1, y);
	}

	if ((abs(x + 1) <= sideOver && abs(y) <= sideOver) &&
		visited[std::make_pair(x + 1, y)] == false &&
		world->GetNorth({ x + 1, y }))
	{
		neighbors.emplace_back(x + 1, y);
	}

	return neighbors;
}

std::vector<Point2D> PrimNew::getInNeighbors(Point2D point, World* world)
{
	std::vector<Point2D> neighbors;
	int sideOver = world->GetSize() / 2;
	int x = point.x;
	int y = point.y;

	// Check if each potential neighbor is within the
	// grid and has been marked as in
	if ((abs(x) <= sideOver && abs(y - 1) <= sideOver) &&
		inMaze[std::make_pair(x, y - 1)] == true)
	{
		neighbors.emplace_back(x, y - 1);
	}

	if ((abs(x) <= sideOver && abs(y + 1) <= sideOver) &&
		inMaze[std::make_pair(x, y + 1)] == true)
	{
		neighbors.emplace_back(x, y + 1);
	}

	if ((abs(x - 1) <= sideOver && abs(y) <= sideOver) &&
		inMaze[std::make_pair(x - 1, y)] == true)
	{
		neighbors.emplace_back(x - 1, y);
	}

	if ((abs(x + 1) <= sideOver && abs(y) <= sideOver) &&
		inMaze[std::make_pair(x + 1, y)] == true)
	{
		neighbors.emplace_back(x + 1, y);
	}

	return neighbors;
}

void PrimNew::buildPath(Point2D currentPoint, Point2D inPoint, World* world)
{
	// Get the direction

	// East
	if (currentPoint.x < inPoint.x)
	{
		Node currentNode = Node(true, false, true, true);
		Node inNode = world->GetNode(inPoint);
		inNode.SetWest(false);

		world->SetNode(currentPoint, currentNode);
		world->SetNodeColor(currentPoint, Color::Black);

		world->SetNode(inPoint, inNode);
		world->SetNodeColor(inPoint, Color::Black);

		return;
	}

	// West
	else if (currentPoint.x > inPoint.x)
	{
		Node currentNode = Node(true, true, true, false);
		Node inNode = world->GetNode(inPoint);
		inNode.SetEast(false);

		world->SetNode(currentPoint, currentNode);
		world->SetNodeColor(currentPoint, Color::Black);

		world->SetNode(inPoint, inNode);
		world->SetNodeColor(inPoint, Color::Black);

		return;
	}

	// South
	else if (currentPoint.y < inPoint.y)
	{
		Node currentNode = Node(true, true, false, true);
		Node inNode = world->GetNode(inPoint);
		inNode.SetNorth(false);

		world->SetNode(currentPoint, currentNode);
		world->SetNodeColor(currentPoint, Color::Black);

		world->SetNode(inPoint, inNode);
		world->SetNodeColor(inPoint, Color::Black);

		return;
	}

	// North
	else if (currentPoint.y > inPoint.y)
	{
		Node currentNode = Node(false, true, true, true);
		Node inNode = world->GetNode(inPoint);
		inNode.SetSouth(false);

		world->SetNode(currentPoint, currentNode);
		world->SetNodeColor(currentPoint, Color::Black);

		world->SetNode(inPoint, inNode);
		world->SetNodeColor(inPoint, Color::Black);

		return;
	}
}

void PrimNew::initMaze(World* world)
{
	int worldSize = world->GetSize()/2;
	// Select a random starting point
	int randX = Random::Range(-worldSize, worldSize);
	int randY = Random::Range(-worldSize, worldSize);
	std::pair<int, int> point = std::make_pair(randX, randY);

	Node startNode = Node(true, true, true, true);

	frontier.push_back(point);
	visited.emplace(point, true);
	inMaze.emplace(point, true);

	world->SetNode(Point2D(randX, randY), startNode);
	world->SetNodeColor(Point2D(randX, randY), Color::Black);
	return;
}