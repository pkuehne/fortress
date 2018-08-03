#pragma once

#include <set>

typedef unsigned long EntityId;

typedef std::set<EntityId> EntityHolder;
typedef EntityHolder::iterator EntityIter;
typedef EntityHolder::const_iterator EntityConstIter;
