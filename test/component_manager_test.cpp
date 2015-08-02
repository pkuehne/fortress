#include <component_manager.h>
#include <gtest/gtest.h>

TEST (ComponentManager, testAddGetRemove)
{
    ComponentManager<int>   manager;
    Entity                  entity;
    int                     val = 5;
    entity.setId (900000);

    EXPECT_EQ (0, manager.get (entity.getId()));

    manager.add (entity.getId(), val);
    EXPECT_EQ (val, *(manager.get (entity.getId())));

    manager.remove (entity.getId());
    EXPECT_EQ (static_cast<int*>(0), manager.get (entity.getId()));
}

TEST (ComponentManager, getAll)
{
    ComponentManager<int>   manager;
    Entity                  firstEntity;
    int                     firstVal        = 5;
    Entity                  secondEntity;
    int                     secondVal       = 10;
    firstEntity.setId (900000);
    secondEntity.setId (1000000);

    EXPECT_EQ (0, manager.getAll().size());

    manager.add (firstEntity.getId(), firstVal);
    manager.add (secondEntity.getId(), secondVal);

    EXPECT_EQ (2, manager.getAll().size());

}
