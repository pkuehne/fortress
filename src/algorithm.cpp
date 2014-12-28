#include "algorithm.h"
#include "map.h"
#include "tile.h"
#include "gameengine.h"
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <ctime>
#include <unistd.h>
#include <vector>
#include <map>
#include <iostream>

bool operator< (const Node& lhs, const Node& rhs)
{
    return lhs.priority > rhs.priority;
}

int getUnitPathCost (const Tile& tile, void* unit)
{ Unit* l_unit = static_cast<Unit*> (unit); 
    if (tile.getConstruction() != CON_EMPTY) return -1;    
    if (tile.getBackground() == TILE_PLAIN) return 1;
    if (tile.getBackground() == TILE_WATER && l_unit->canSwim()) return 3;

    return -1;
}

void Algorithm::findUnitPath (  int startIndex, 
                                int endIndex, 
                                Unit& unit, 
                                std::vector<int>& path)
{
    findPath (startIndex, endIndex, getUnitPathCost, &unit, path);
}

void Algorithm::findPath (  int startIndex, 
                            int endIndex, 
                            costFunc costFunction,
                            void* costInput,
                            std::vector<int>& retPath)
{
    NodeMap l_open;
    NodeMap l_closed;
    const Map& l_map = GameEngine::getEngine()->getMap();

    std::priority_queue<Node> l_priority;
    Node startNode (startIndex, 0, 0, 0);
   
    if (startIndex < 0 || startIndex > l_map.getMapSize()) return;
    if (endIndex < 0 || endIndex > l_map.getMapSize()) return;

    int endx = l_map.getTile (endIndex).getX();
    int endy = l_map.getTile (endIndex).getY();

    // Add start to priority queue and open set
    l_priority.push (startNode);
    l_open[startIndex] = startNode;

    while (!l_priority.empty()) {
        Node l_current = l_priority.top();
        l_priority.pop();

        l_open.erase (l_current.index);
        l_closed[l_current.index] = l_current;
        
        // Check whether target node
        if (l_current.index == endIndex) {
            int index = l_current.index;
            std::vector<int> l_reverse;
            while (index != startIndex) {
                retPath.push_back (index);
                NodeMapIter open_iter = l_closed.find (index);
                index = open_iter->second.origin;
                if (index == 0) break;
            }

            return;
        }
       
        // Process neighbours
        int neighbours[Map::dir];
        l_map.getNeighbours (l_current.index, neighbours); 

        for (int ii = 0; ii< Map::dir; ii++) {
            if (neighbours[ii] < 0) continue; // Not a valid neighbour
            int cost = costFunction (l_map.getTile(neighbours[ii]), costInput);
            // If cost is -ve, we will close the node

            int path = l_current.distance + cost;
            int priority = path 
                         + (abs(endx - l_map.getTile(neighbours[ii]).getX()) 
                         +  abs(endy - l_map.getTile(neighbours[ii]).getY())) 
                         * 1 ;
            Node neighbour (neighbours[ii], path, priority, l_current.index);

            // Is it closed?
            NodeMapIter closed_iter = l_closed.find (neighbours[ii]);
            if (closed_iter != l_closed.end()) {
                // But dow we now have a better path?
                if (cost > 0 && path < closed_iter->second.distance) {
                    l_closed.erase (closed_iter);
                } else {
                    continue; // It's closed and there's no better path
                }
            }

            NodeMapIter open_iter = l_open.find (neighbours[ii]);
            if (open_iter != l_open.end()) {
                // Remove it from open if there's a better path now
                //l_open.erase(open_iter);
            } else if (cost > 0) {
                // Neighbour not in open   
                l_open[neighbours[ii]] = neighbour;
                l_priority.push (neighbour);
            }
        }
    }
    return;
}
