#include "Catcher.h"
#include "World.h"

// Goal is to block the cat's path and encapsulate it.
// Check all possible paths the cat can take and place
// a block in a position closest to another block on
// said path? Would this slowly block off the cat's 
// path over time? Or would it just be better to place
// a block on the cat's path closest to the cat?
// How should this account for movement?

Point2D Catcher::Move(World* world) {
  auto side = world->getWorldSideSize()/2;
  for(;;) {
    Point2D p = {Random::Range(-side, side), Random::Range(-side, side)};
    auto cat = world->getCat();
    if(cat.x!=p.x && cat.y!=p.y && !world->getContent(p))
      return p;
  }
}
