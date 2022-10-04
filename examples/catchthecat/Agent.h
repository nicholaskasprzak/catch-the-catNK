#ifndef AGENT_H
#define AGENT_H
#include "Point2D.h"
#include <map>

struct queueEntry
{
	queueEntry() = default;
	//queueEntry(Point2D pos, int weight) { this->pos = pos; this->weight = weight; }
	
	Point2D pos;
	int weight; // accumulated
	// bool visited?

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
  std::map<int, std::map<int, queueEntry>> visited;
};

#endif  // AGENT_H
