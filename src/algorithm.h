#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>
#include <map>

class Node
{
public:
    unsigned int index;
    unsigned int distance;
    unsigned int priority;
    unsigned int origin;

    Node ()
    {
        index       = 0;
        distance    = 0;
        priority    = 0;
        origin      = 0;
    }

    Node (unsigned int i, unsigned int d, unsigned int p, unsigned int o)
    {
        index       = i;
        distance    = d;
        priority    = p;
        origin      = o;
    }
};

typedef std::map<int, Node>             NodeMap;
typedef std::map<int, Node>::iterator   NodeMapIter;
typedef std::vector<unsigned int>       PathVector;

typedef unsigned int (* costFunc ) (const unsigned char input, void* customData);
typedef unsigned int (* neighbourFunc) (unsigned int index, unsigned int* neighbours, void* customData);
typedef unsigned int (* distanceFunc) (unsigned int start, unsigned int end, void* customData);

class Algorithm {
public:
    Algorithm();
    void findPath (unsigned int start, unsigned int end, PathVector& output);

    void setCostFunction (costFunc a_func) { m_costFunction = a_func; }
    void setNeighbourFunction (neighbourFunc a_func) { m_neighbourFunction = a_func; }
    void setNumNeighbours (unsigned int numNeighbours) { m_numNeighbours = numNeighbours; }
    void setDistanceFunction (distanceFunc a_func) { m_distanceFunction = a_func; }
    void setCustomData (void* data) { m_customData = data; }
private:
    costFunc        m_costFunction;
    neighbourFunc   m_neighbourFunction;
    distanceFunc    m_distanceFunction;
    void*           m_customData;
    unsigned int    m_numNeighbours;

};

#endif
