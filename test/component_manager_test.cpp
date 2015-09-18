#include <component_manager.h>
#include <gtest/gtest.h>

TEST (ComponentManager, testAddGetRemove)
{
    ComponentManager<int>   manager;
    EntityId                entity = 900000;
    int                     val = 5;

    EXPECT_EQ (0, manager.get (entity));

    manager.add (entity, val);
    EXPECT_EQ (val, *(manager.get (entity)));

    manager.remove (entity);
    EXPECT_EQ (static_cast<int*>(0), manager.get (entity));
}

TEST (ComponentManager, getAll)
{
    ComponentManager<int>   manager;
    EntityId                firstEntity = 900000;
    int                     firstVal        = 5;
    EntityId                secondEntity = 1000000;
    int                     secondVal       = 10;

    EXPECT_EQ (0, manager.getAll().size());

    manager.add (firstEntity, firstVal);
    manager.add (secondEntity, secondVal);

    EXPECT_EQ (2, manager.getAll().size());

}
