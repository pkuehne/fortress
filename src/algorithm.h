#ifndef __ALGORITHM_H__
#define __ALGORITHM_H__

#include <map>
#include <vector>

class Node
{
public:
    int index;
    int distance;
    int priority;
    int origin;

    Node ()
    {
        index       = 0;
        distance    = 0;
        priority    = 0;
        origin      = 0;
    }

    Node (int i, int d, int p, int o)
    {
        index       = i;
        distance    = d;
        priority    = p;
        origin      = o;
    }
};

typedef std::map<int, Node>             NodeMap;
typedef std::map<int, Node>::iterator   NodeMapIter;

class Algorithm {
public:
    static void findPath (  int startIndex, 
                            int endIndex, 
                            std::vector<int>& retPath);

};

#endif
