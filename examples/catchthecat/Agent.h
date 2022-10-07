#ifndef AGENT_H
#define AGENT_H
#include "Point2D.h"
#include <map>

struct queueEntry
{
	queueEntry() = default;
	/*
	queueEntry(Point2D cameFrom, int weight, bool visited)
	{
		this->cameFrom = cameFrom; // no default constructor?
		this->weight = weight;
		this->visited = visited;
	}
	*/

	Point2D position;
	Point2D cameFrom;
	int weight; // accumulated
	bool visited;
	bool blocked;
	// in queue?

	bool operator< (queueEntry& rhs)
	{
		return weight < rhs.weight;
	}

};

class World;

class Agent {
public:
  explicit Agent()= default;;
  virtual Point2D Move(World*)=0;

  //std::map<int, std::map<int, bool>> getVisited() { return visited; }

private:
  // This needs to be built to represent all available spaces.
  //std::map<int, std::map<int, queueEntry>> visited;
};

#endif  // AGENT_H
