#include "file_saver.h"
#include "game_engine.h"
#include <typeinfo>
#include "collider_component.h"
#include "consumable_component.h"
#include "description_component.h"
#include "droppable_component.h"
#include "equipment_component.h"
#include "health_component.h"
#include "npc_component.h"
#include "player_component.h"
#include "sprite_component.h"
#include "stair_component.h"
#include "wearable_component.h"
#include "wieldable_component.h"
#include <glog/logging.h>

void FileSaver::saveState ()
{
    m_file.open ("World1.sav");
    LOG(INFO) << "Saving state" << std::endl;

    //Start with the header
    m_file << "[MAP_WIDTH:" << m_engine->getMap()->getMapWidth() << "]" << std::endl;
    m_file << "[MAP_HEIGHT:" << m_engine->getMap()->getMapHeight() << "]" << std::endl;
    m_file << "[MAP_DEPTH:" << m_engine->getMap()->getMapDepth() << "]" << std::endl;
    m_file << "[TURN:" << m_engine->getTurn() << "]" << std::endl;

    for (unsigned int zz = 0; zz < m_engine->getMap()->getMapDepth(); zz++) {
        for (unsigned int yy = 0; yy < m_engine->getMap()->getMapHeight(); yy++) {
            for (unsigned int xx = 0; xx < m_engine->getMap()->getMapWidth(); xx++) {
                m_file << "[TILE_VISITED:" << m_engine->getMap()->getTile(xx, yy, zz).lastVisited << "]" << std::endl;
            }
        }
    }

    // Save entities
    EntityHolder& entities = m_engine->getEntities()->get();
    for (EntityId entity : entities) {
        m_file << "[ENTITY:" << entity << "]" << std::endl;
        Location location = m_engine->getEntities()->getLocation (entity);
        m_file << "[LOCATION_X:" << location.x << "]" << std::endl;
        m_file << "[LOCATION_Y:" << location.y << "]" << std::endl;
        m_file << "[LOCATION_Z:" << location.z << "]" << std::endl;
        m_file << "[AREA:" << location.area << "]" << std::endl;
        
        ComponentHolder& components = m_engine->getComponents()->getAll(entity);
        for (ComponentBase* component : components) {
            saveComponent (component);
        }
    }

    m_file.close();
    LOG(INFO) << "Save complete" << std::endl;
}

void FileSaver::saveComponent (ComponentBase* component)
{
    ColliderComponent* l_coll = dynamic_cast<ColliderComponent*> (component);
    if (l_coll) {
        m_file << "[COMPONENT:COLLIDER]" << std::endl;
        return;
    }
    ConsumableComponent* l_cons = dynamic_cast<ConsumableComponent*> (component);
    if (l_cons) {
        m_file << "[COMPONENT:CONSUMABLE]" << std::endl;
        m_file << "[QUENCHES:"          << l_cons->quenches << "]" << std::endl;
        m_file << "[QUENCH_STRENGTH:"   << l_cons->quenchStrength << "]" << std::endl;
        m_file << "[EFFECT:"            << l_cons->effect << "]" << std::endl;
        m_file << "[EFFECT_STRENGTH:"   << l_cons->effectStrength << "]" << std::endl;
        return;
    }
    DescriptionComponent* l_desc = dynamic_cast<DescriptionComponent*> (component);
    if (l_desc) {
        m_file << "[COMPONENT:DESCRIPTION]" << std::endl;
        m_file << "[TITLE:" << l_desc->title << "]" << std::endl;
        m_file << "[TEXT:" << l_desc->text << "]" << std::endl;
        return;
    }
    DroppableComponent* l_drop = dynamic_cast<DroppableComponent*> (component);
    if (l_drop) {
        m_file << "[COMPONENT:DROPPABLE]" << std::endl;
        return;
    }
    EquipmentComponent* l_equip = dynamic_cast<EquipmentComponent*> (component);
    if (l_equip) {
        m_file << "[COMPONENT:EQUIPMENT]" << std::endl;
        m_file << "[HEAD_WEARABLE:" << l_equip->headWearable << "]" << std::endl;
        m_file << "[FACE_WEARABLE:" << l_equip->faceWearable << "]" << std::endl;
        m_file << "[CHEST_WEARABLE:" << l_equip->chestWearable << "]" << std::endl;
        m_file << "[ARMS_WEARABLE:" << l_equip->armsWearable << "]" << std::endl;
        m_file << "[HANDS_WEARABLE:" << l_equip->handsWearable << "]" << std::endl;
        m_file << "[LEGS_WEARABLE:" << l_equip->legsWearable << "]" << std::endl;
        m_file << "[FEET_WEARABLE:" << l_equip->feetWearable << "]" << std::endl;
        m_file << "[RIGHT_HAND_WIELDABLE:" << l_equip->rightHandWieldable << "]" << std::endl;
        m_file << "[LEFT_HAND_WIELDABLE:" << l_equip->leftHandWieldable << "]" << std::endl;
        for (EntityId entity : l_equip->carriedEquipment) {
            m_file << "[CARRIED:" << entity << "]" << std::endl;
        }
        m_file << "[MAX_CARRY_WEIGHT:" << l_equip->maxCarryWeight << "]" << std::endl;
        m_file << "[MAX_CARRY_VOLUME:" << l_equip->maxCarryVolume << "]" << std::endl;
        return;
    }
    HealthComponent* l_health = dynamic_cast<HealthComponent*> (component);
    if (l_health) {
        m_file << "[COMPONENT:HEALTH]" << std::endl;
        m_file << "[HEALTH:" << l_health->health << "]" << std::endl;
        m_file << "[HUNGER:" << l_health->hunger << "]" << std::endl;
        m_file << "[THIRST:" << l_health->thirst << "]" << std::endl;
        return;
    }
    NpcComponent* l_npc = dynamic_cast<NpcComponent*>(component);
    if (l_npc) {
        m_file << "[COMPONENT:NPC]" << std::endl;
        return;
    }
    PlayerComponent* l_player = dynamic_cast<PlayerComponent*>(component);
    if (l_player) {
        m_file << "[COMPONENT:PLAYER]" << std::endl;
        return;
    }
    SpriteComponent* l_sprite = dynamic_cast<SpriteComponent*>(component);
    if (l_sprite) {
        m_file << "[COMPONENT:SPRITE]" << std::endl;
        m_file << "[SPRITE:" << (int) l_sprite->sprite << "]" << std::endl;
        m_file << "[FG_RED:" << l_sprite->fgColor.Red() << "]" << std::endl;
        m_file << "[FG_GREEN:" << l_sprite->fgColor.Green() << "]" << std::endl;
        m_file << "[FG_BLUE:" << l_sprite->fgColor.Blue() << "]" << std::endl;
        m_file << "[BG_RED:" << l_sprite->bgColor.Red() << "]" << std::endl;
        m_file << "[BG_GREEN:" << l_sprite->bgColor.Green() << "]" << std::endl;
        m_file << "[BG_BLUE:" << l_sprite->bgColor.Blue() << "]" << std::endl;
        return;
    }
    StairComponent* l_stair = dynamic_cast<StairComponent*>(component);
    if (l_stair) {
        m_file << "[COMPONENT:STAIR]" << std::endl;
        m_file << "[DIRECTION:" << l_stair->direction << "]" << std::endl;
        return;
    }
    WearableComponent* l_wear = dynamic_cast<WearableComponent*>(component);
    if (l_wear) {
        m_file << "[COMPONENT:WEARABLE]" << std::endl;
        m_file << "[BASE_DAMAGE:" << l_wear->baseDamageAbsorb << "]" << std::endl;
        m_file << "[POSITION:" << l_wear->position << "]" << std::endl;
        m_file << "[WARMTH:" << l_wear->warmth << "]" << std::endl;
        return;

    }
    WieldableComponent* l_wield = dynamic_cast<WieldableComponent*>(component);
    if (l_wield) {
        m_file << "[COMPONENT:WIELDABLE]" << std::endl;
        m_file << "[BASE_DAMAGE:" << l_wield->baseDamage << "]" << std::endl;
        m_file << "[WBASE_DEFENCE:" << l_wield->baseDefence << "]" << std::endl;
        m_file << "[POSITION:" << l_wield->position << "]" << std::endl;
        return;
    }
    LOG(ERROR) << "Could not save a component: " << typeid (component).name() << std::endl;
}
