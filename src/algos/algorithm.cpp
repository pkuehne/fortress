#include "algorithm.h"
#include "../core/game_engine.h"
#include "../core/location.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <queue>
#include <unistd.h>

bool operator<(const Node& lhs, const Node& rhs) {
    return lhs.priority > rhs.priority;
}

int defaultCostFunction(const Location& location, void* customData) {
    std::cout << "WARN: Using defaultCostFunction!" << std::endl;
    return 1;
}

unsigned int defaultNeighbourFunction(const Location& location,
                                      Location* neighbours, void* customData) {
    std::cout << "WARN: Using defaultNeighbourFunction!" << std::endl;
    return 0;
}

unsigned int defaultDistanceFunction(const Location& start, const Location& end,
                                     void* customData) {
    std::cout << "WARN: Using defaultDistanceFunction!" << std::endl;
    return 0;
}

Algorithm::Algorithm()
    : m_costFunction(defaultCostFunction),
      m_neighbourFunction(defaultNeighbourFunction),
      m_distanceFunction(defaultDistanceFunction) {}

void Algorithm::findPath(const Location& start, const Location& end,
                         PathVector& output) {
    NodeMap l_open;
    NodeMap l_closed;
    std::priority_queue<Node> l_priority;

    // Create Start Node
    Location origin;
    Node startNode(start, 0, 0, origin);

    // Add start to priority queue and open set
    l_priority.push(startNode);
    l_open[start] = startNode;

    while (!l_priority.empty()) {
        Node l_current = l_priority.top();
        l_priority.pop();

        l_open.erase(l_current.location);
        l_closed[l_current.location] = l_current;

        // Check whether this is the target node
        if (l_current.location == end) {
            Location current = l_current.location;
            while (current != start) {
                // output.push_back (index);
                output.insert(output.begin(), current);
                NodeMapIter open_iter = l_closed.find(current);
                current = open_iter->second.origin;
                if (current.x == UINT_MAX)
                    break;
            }
            return;
        }

        // Process neighbours
        Location* neighbours = new Location[m_numNeighbours];
        unsigned int validNeighbours =
            m_neighbourFunction(l_current.location, neighbours, m_customData);
        for (size_t ii = 0; ii < validNeighbours; ii++) {
            // TODO: not needed? if (neighbours[ii] < 0) continue; // Not a
            // valid neighbour
            int cost = m_costFunction(neighbours[ii], m_customData);
            // If cost is -ve, we will close the node

            unsigned int path = l_current.distance + cost;
            unsigned int priority =
                path + m_distanceFunction(neighbours[ii], end, m_customData) +
                1;
            Node neighbour(neighbours[ii], path, priority, l_current.location);

            // Is it closed?
            NodeMapIter closed_iter = l_closed.find(neighbours[ii]);
            if (closed_iter != l_closed.end()) {
                // But dow we now have a better path?
                if (cost > 0 && path < closed_iter->second.distance) {
                    l_closed.erase(closed_iter);
                } else {
                    continue; // It's closed and there's no better path
                }
            }

            NodeMapIter open_iter = l_open.find(neighbours[ii]);
            if (open_iter != l_open.end()) {
                // Remove it from open if there's a better path now
                l_open.erase(open_iter);
            } else if (cost >= 0) {
                // Neighbour not in open
                l_open[neighbours[ii]] = neighbour;
                l_priority.push(neighbour);
            }
        }
        delete[] neighbours;
    }
}
