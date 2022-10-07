#include "Cat.h"
#include "World.h"
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <queue>

// Goal of the cat is to find the shortest path to the edge of the screen
Point2D Cat::Move(World* world) {
  Point2D catPos = world->getCat();
  std::priority_queue<queueEntry> frontier; // Holds the path?

  // enrich map in map of a map of a node.
  // not most effective method.
  // Does it build up a large vector of queueEntries to represent each node in the map?
  // What would be more effective?

  // Bootstrap first element
  //frontier.push(queueEntry());

  // While all elements haven't been visited, visit them
  // Breadth first search to get full path
  while (!frontier.empty())
  {
	  // Get first element from queue
	  queueEntry current = frontier.top();
	  //frontier.pop(); // Should this be removed?

	  // Mark the head as visited
	  current.visited = true;

	  // Get neighbors of current
	  // Construct this from queueEntries instead of Point2Ds
	  std::vector<Point2D> neighbors;

	  neighbors.push_back(world->E(current.position));
	  neighbors.push_back(world->NE(current.position));
	  neighbors.push_back(world->NW(current.position));
	  neighbors.push_back(world->SE(current.position));
	  neighbors.push_back(world->SW(current.position));
	  neighbors.push_back(world->W(current.position));

	  // For each neighbor:
	  // - Check if it hasnt been visited
	  // - Check if it is not in the queue
	  // - Check if it can be visited
	  // - If any are false, continue?
	  // - Add to the queue adding 1 to the weight (Breadth first doesnt require it)
	  // - Mark the neighbor as it came from the current head as popped
	  // - If it is the exit, break

	  for (int i = 0; i < neighbors.size(); i++)
	  {
		  if (true)
		  {

		  }
	  }
  }

  // Then create a lowest weight path to the exit from what was visited
  // Work back from the end towards the cat.

  // First element is the cat and the last element is the catcher

  // Would an optimization be to only reconstrust the path if it gets blocked?
}
