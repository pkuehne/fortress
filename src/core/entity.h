#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <set>

typedef unsigned long EntityId;

typedef std::set<EntityId> EntityHolder;
typedef EntityHolder::iterator EntityIter;
typedef EntityHolder::const_iterator EntityConstIter;

#endif
