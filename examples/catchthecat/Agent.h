#ifndef AGENT_H
#define AGENT_H
#include "Point2D.h"
//#include "World.h"
#include <map>
#include <queue>

struct queueEntry
{
	queueEntry() = default;

	Point2D position = Point2D(0, 0);
	Point2D cameFrom = Point2D(0, 0); // How would I make this null? Negatives?
	// Having a queueEntry pointer would probably work better if it werent for deallocation being troublesome.
	//queueEntry* cameFrom;
	int weight; // accumulated

	// The existance of both of these seems to imply the possibility
	// of creating an enriched map using queueEntries.
	// Can't do that though. cameFrom wouldn't work in that context.
	// What purpose do these serve then?
	bool visited;
	bool blocked;

	bool operator< (const queueEntry& rhs) const { return weight > rhs.weight; }

	bool operator== (Point2D& rhs) const { return (position.x == rhs.x && position.y == rhs.y); }
};

class World;

class Agent {
public:
  explicit Agent()= default;;
  virtual Point2D Move(World*)=0;

  void Search(std::priority_queue<queueEntry>& frontier, std::map<int, std::map<int, std::pair<int, int>>>& cameFromMap, Point2D& goalPos, World* world);
  void GetNeighbors(std::priority_queue<queueEntry>& priorityQueue, std::map<int, std::map<int, std::pair<int, int>>>& cameFromMap, World* world, queueEntry current);
  bool CheckIfGoal(World* world, Point2D position);

private:
};

#endif  // AGENT_H
