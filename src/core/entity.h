#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <unordered_set>

typedef unsigned long EntityId;

typedef std::unordered_set<EntityId> EntityHolder;
typedef EntityHolder::iterator EntityIter;
typedef EntityHolder::const_iterator EntityConstIter;


#endif
