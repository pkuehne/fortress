#include "entity_manager.h"
#include "gameengine.h"
#include <cJSON/cJSON.h>
#include <fstream>
#include <iostream>

void EntityManager::initialise()
{
    maxId = 0;
}

void EntityManager::destroy ()
{

}

void EntityManager::createWallEntity (unsigned int x, unsigned int y)
{
    Entity l_entity = createEntity();

    //Sprite Component
    SpriteComponent l_sprite;
    l_sprite.fgColor    = Color (WHITE);
    l_sprite.bgColor    = Color (BLACK);
    l_sprite.sprite     = 247;
    l_sprite.xPos       = x;
    l_sprite.yPos       = y;
    getSprites().add (l_entity, l_sprite);

    //Collider Component
    ColliderComponent l_collider;
    getColliders().add (l_entity, l_collider);
}

void EntityManager::createPlayerEntity (unsigned int x, unsigned int y)
{
    Entity l_entity = createEntity();

    //Sprite Component
    SpriteComponent l_sprite;
    l_sprite.fgColor    = Color (RED);
    l_sprite.bgColor    = Color (BLACK);
    l_sprite.sprite     = '@';
    l_sprite.xPos       = x;
    l_sprite.yPos       = y;
    getSprites().add (l_entity, l_sprite);


    //Collider Component
    ColliderComponent l_collider;
    getColliders().add (l_entity, l_collider);
}

void EntityManager::createEnemyEntity (unsigned int x, unsigned int y)
{
    Entity l_entity = createEntity();

    //Sprite Component
    SpriteComponent l_sprite;
    l_sprite.fgColor    = Color (RED);
    l_sprite.bgColor    = Color (BLACK);
    l_sprite.sprite     = 321;
    l_sprite.xPos       = x;
    l_sprite.yPos       = y;
    getSprites().add (l_entity, l_sprite);

}

void EntityManager::createRoom (unsigned int xStart, unsigned int yStart, unsigned int xEnd, unsigned int yEnd)
{
    for (unsigned int xx = xStart; xx <= xEnd; xx++) {
        createWallEntity (xx, yStart);
        createWallEntity (xx, yEnd);
    }

    for (unsigned int yy = yStart+1; yy < yEnd; yy++) {
        createWallEntity (xStart, yy);
        createWallEntity (xEnd, yy);
    }
}
