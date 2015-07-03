#include <gtest/gtest.h>
#include <entity.h>

TEST (Entity, GetSetId)
{
    Entity entity;
    entity.setId (900000000);
    EXPECT_EQ (900000000, entity.getId());
}

TEST (Entity, GetSetName)
{
    Entity entity;
    entity.setName ("TEST NAME");
    EXPECT_EQ ("TEST NAME", entity.getName());
}

TEST (Entity, Tags)
{
    Entity entity;

    EXPECT_EQ (0, entity.getTags().size());

    entity.addTag (MONSTER);
    EXPECT_EQ (1, entity.getTags().size());
    EXPECT_EQ (MONSTER, *(entity.getTags().begin()));
}

TEST (Entity, IdComparator)
{
    Entity a;
    a.setId (900000000);

    Entity b;
    b.setId (900000001);

    EXPECT_TRUE (a < b);
}
