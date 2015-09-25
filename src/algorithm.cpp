#include "algorithm.h"
#include "game_engine.h"
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <ctime>
#include <unistd.h>
#include <iostream>


bool operator< (const Node& lhs, const Node& rhs)
{
    return lhs.priority > rhs.priority;
}

unsigned int defaultCostFunction (unsigned int point, void* customData)
{
    std::cout << "WARN: Using defaultCostFunction!" << std::endl;
    return 1;
}

unsigned int defaultNeighbourFunction (unsigned int index, unsigned int* neighbours, void* customData)
{
    std::cout << "WARN: Using defaultNeighbourFunction!" << std::endl;
    return 0;
}

unsigned int defaultDistanceFunction (unsigned int start, unsigned int end, void* customData)
{
    std::cout << "WARN: Using defaultDistanceFunction!" << std::endl;
    return 0;
}

Algorithm::Algorithm()
: m_costFunction (defaultCostFunction)
, m_neighbourFunction (defaultNeighbourFunction)
, m_distanceFunction (defaultDistanceFunction)
, m_numNeighbours (0) // To be safe
{

}

void Algorithm::findPath (unsigned int start, unsigned int end, PathVector& output)
{
    NodeMap l_open;
    NodeMap l_closed;
    std::priority_queue<Node> l_priority;

    // Create Start Node
    Node startNode (start, 0, 0, 0);

    // Add start to priority queue and open set
    l_priority.push (startNode);
    l_open[start] = startNode;

    while (!l_priority.empty()) {
        Node l_current = l_priority.top();
        l_priority.pop();

        l_open.erase (l_current.index);
        l_closed[l_current.index] = l_current;

        // Check whether this is the target node
        if (l_current.index == end) {
            unsigned int index = l_current.index;
            while (index != start) {
                //output.push_back (index);
                output.insert (output.begin(), index);
                NodeMapIter open_iter = l_closed.find (index);
                index = open_iter->second.origin;
                if (index == 0) break;
            }
            return;
        }

        // Process neighbours
        unsigned int neighbours[m_numNeighbours] = {0};
        unsigned int validNeighbours = m_neighbourFunction (l_current.index, neighbours, m_customData);
        for (size_t ii = 0; ii < validNeighbours; ii++) {
            if (neighbours[ii] < 0) continue; // Not a valid neighbour
            unsigned int cost = m_costFunction (neighbours[ii], m_customData);
            // If cost is -ve, we will close the node

            unsigned int path = l_current.distance + cost;
            unsigned int priority = path + m_distanceFunction (neighbours[ii], end, m_customData) + 1;
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
                l_open.erase(open_iter);
            } else if (cost >= 0) {
                // Neighbour not in open
                l_open[neighbours[ii]] = neighbour;
                l_priority.push (neighbour);
            }
        }
    }
}
