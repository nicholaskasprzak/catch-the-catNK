#ifndef AGENT_H
#define AGENT_H
#include "Point2D.h"
#include <map>

class World;

class Agent {
public:
  explicit Agent()= default;;
  virtual Point2D Move(World*)=0;

  std::map<int, std::map<int, bool>> getVisited() { return visited; }

private:
  std::map<int, std::map<int, bool>> visited;
};

#endif  // AGENT_H
