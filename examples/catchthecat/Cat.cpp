#include "Cat.h"
#include "World.h"
#include <stdexcept>
#include <vector>
#include <algorithm>

// Goal of the cat is to find the shortest path to the edge of the screen
Point2D Cat::Move(World* world) {
  Point2D catPos = world->getCat();

  // Bootstrap first element
  
  // While all elements haven't been visited, visit them

	// Get first element from queue

	// Mark the head as visited
	
	// For each neighbor:
	// - Check if it hasnt been visited
	// - Check if it is not in the queue
	// - Check if it can be visited
	// - Add to the queue adding 1 to the weight
	// - Mark the neighbor as it came from the current head as popped
}
