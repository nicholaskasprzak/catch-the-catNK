#include "Cat.h"
#include "World.h"
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <queue>

// Goal of the cat is to find the shortest path to the edge of the screen
Point2D Cat::Move(World* world) {
  Point2D catPos = world->getCat();
  std::priority_queue<Point2D> frontier; // sort by closest to goal?

  // Bootstrap first element
  frontier.push(catPos);

  // While all elements haven't been visited, visit them
  while (!frontier.empty())
  {
	  // Get first element from queue
	  Point2D current = frontier.top();
	  //frontier.pop(); // Should this be removed?

	  // Mark the head as visited
	  

	  // For each neighbor:
	  // - Check if it hasnt been visited
	  // - Check if it is not in the queue
	  // - Check if it can be visited
	  // - Add to the queue adding 1 to the weight
	  // - Mark the neighbor as it came from the current head as popped
  }

  // Then create a lowest weight path to the exit from what was visited

  // First element is the cat and the last element is the catcher

  // Would an optimization be to only reconstrust the path if it gets blocked?
}
