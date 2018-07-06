#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "../core/location.h"
#include "../core/utility.h"
#include <map>
#include <vector>

class Node {
public:
    Location location;
    unsigned int distance = 0;
    unsigned int priority = 0;
    Location origin;

    Node() {}

    Node(const Location& l, unsigned int d, unsigned int p, const Location& o)
        : location(l), distance(d), priority(p), origin(o) {}
};

typedef std::map<Location, Node> NodeMap;
typedef std::map<Location, Node>::iterator NodeMapIter;
typedef std::vector<Location> PathVector;

typedef int (*costFunc)(const Location& location, void* customData);
typedef unsigned int (*neighbourFunc)(const Location& location,
                                      Location* neighbours, void* customData);
typedef unsigned int (*distanceFunc)(const Location& start, const Location& end,
                                     void* customData);

class Algorithm {
public:
    Algorithm();
    void findPath(const Location& start, const Location& end,
                  PathVector& output);

    void setCostFunction(costFunc a_func) { m_costFunction = a_func; }
    void setNeighbourFunction(neighbourFunc a_func) {
        m_neighbourFunction = a_func;
    }
    void setNumNeighbours(unsigned int numNeighbours) {
        m_numNeighbours = numNeighbours;
    }
    void setDistanceFunction(distanceFunc a_func) {
        m_distanceFunction = a_func;
    }
    void setCustomData(void* data) { m_customData = data; }

private:
    costFunc m_costFunction;
    neighbourFunc m_neighbourFunction;
    distanceFunc m_distanceFunction;
    void* m_customData = 0;
    unsigned int m_numNeighbours = 0;
};

#endif
