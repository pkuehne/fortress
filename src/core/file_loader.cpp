#include "file_loader.h"
#include "tag.h"
#include <fstream>
#include <iostream>
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

void FileLoader::loadState ()
{
    /*
    LOG(INFO) << "Loading save" << std::endl;
    std::ifstream l_file ("World1.sav");
    if (!l_file.is_open()) {
        LOG(ERROR) << "Could not open save file!" << std::endl;
        return;
    }

    while (!l_file.eof()) {
        std::string l_line;
        std::getline (l_file, l_line);
        m_tags.push_back (Tag (l_line));
    }
    LOG(INFO) << "Completed reading file. Parsing..." << std::endl;

    int line = 0;

    // Current Turn
    m_engine->setTurn (m_tags[line++].getNum());

    unsigned int currArea = m_tags[line++].getNum();
    unsigned int areas = m_tags[line++].getNum();
	EntityId id = 0;

	unsigned int area = 0;
	for (unsigned int ii = line; ii < m_tags.size(); ii++) {
		if (m_tags[ii].getName() == "AREA") {
			loadMap (ii);
			ii--;
			//areas--;
			continue;
		}
		if (m_tags[ii].getName() == "ENTITY") {
			// Set up the entity
			id = m_tags[ii].getNum();
			ii++;
			Location location = loadLocation (ii);
			if (location.area != area) {
				area = location.area;
				areas--;
			}
			m_engine->state()->entityManager()->addEntity (id, location);
			ii--;
			continue;
		}
		if (m_tags[ii].getName() == "COMPONENT") {
			ComponentBase* component = loadComponent (ii, m_tags[ii].getStr());
			if (component) {
				m_engine->state()->components()->add (id, component);
			}
			ii--;
			continue;
		}
	}
	m_engine->state()->map()->setArea (currArea);

    LOG(INFO) << "Completed loading save game" << std::endl;
    */
}


Location FileLoader::loadLocation (unsigned int& pos)
{
    Location location;
    for (unsigned int ii = 0; ii < 4; ii++) {
        if (m_tags[pos].getName() == "LOCATION_X") location.x = m_tags[pos].getNum();
        if (m_tags[pos].getName() == "LOCATION_Y") location.y = m_tags[pos].getNum();
        if (m_tags[pos].getName() == "LOCATION_Z") location.z = m_tags[pos].getNum();
        if (m_tags[pos].getName() == "LOCATION_A") location.area = m_tags[pos].getNum();

        pos++;
    }
    return location;
}

void FileLoader::loadMap (unsigned int& pos) {
	unsigned int area = m_tags[pos++].getNum();
	unsigned int width = m_tags[pos++].getNum();
	unsigned int height = m_tags[pos++].getNum();
	unsigned int depth = m_tags[pos++].getNum();
    m_engine->state()->map()->resetMap (area, width, height, depth);

	for (unsigned int zz = 0; zz < m_engine->state()->map()->getMapDepth(); zz++) {
		for (unsigned int yy = 0; yy < m_engine->state()->map()->getMapHeight(); yy++) {
			for (unsigned int xx = 0; xx < m_engine->state()->map()->getMapWidth(); xx++) {
				m_engine->state()->map()->getTile(Location(xx, yy, zz)).lastVisited = m_tags[pos++].getNum();
			}
		}
	}
}

ComponentBase* FileLoader::loadComponent (unsigned int& pos, const std::string& component)
{
    pos++;
    if (component == "COLLIDER") {
        ColliderComponent* retval = new ColliderComponent();
        return retval;
    }
    if (component == "CONSUMABLE") {
        ConsumableComponent* retval = new ConsumableComponent();
        retval->quenches        = static_cast<HUNGER_THIRST>(m_tags[pos++].getNum());
        retval->quenchStrength  = m_tags[pos++].getNum();
        retval->effect          = static_cast<EFFECT>(m_tags[pos++].getNum());
        retval->effectStrength  = m_tags[pos++].getNum();
        return retval;
    }
    if (component == "DESCRIPTION") {
        DescriptionComponent* retval = new DescriptionComponent();
        retval->title   = m_tags[pos++].getStr();
        retval->text    = m_tags[pos++].getStr();
        return retval;
    }
    if (component == "DROPPABLE") {
        DroppableComponent* retval = new DroppableComponent();
        return retval;
    }
    if (component == "EQUIPMENT") {
        EquipmentComponent* retval = new EquipmentComponent();
        retval->headWearable    = m_tags[pos++].getNum();
        retval->faceWearable    = m_tags[pos++].getNum();
        retval->chestWearable   = m_tags[pos++].getNum();
        retval->armsWearable    = m_tags[pos++].getNum();
        retval->handsWearable   = m_tags[pos++].getNum();
        retval->legsWearable    = m_tags[pos++].getNum();
        retval->feetWearable    = m_tags[pos++].getNum();

        retval->rightHandWieldable  = m_tags[pos++].getNum();
        retval->leftHandWieldable   = m_tags[pos++].getNum();

        while (m_tags[pos].getName() == "CARRIED") {
            retval->carriedEquipment.push_back (m_tags[pos++].getNum());
        }
        retval->maxCarryWeight  = m_tags[pos++].getNum();
        retval->maxCarryVolume  = m_tags[pos++].getNum();

        return retval;
    }
    if (component == "HEALTH") {
        HealthComponent* retval = new HealthComponent();
        retval->health = m_tags[pos++].getNum();
        retval->hunger = m_tags[pos++].getNum();
        retval->thirst = m_tags[pos++].getNum();
        return retval;
    }
    if (component == "NPC") {
        NpcComponent* retval = new NpcComponent();
        return retval;
    }
    if (component == "PLAYER") {
        PlayerComponent* retval = new PlayerComponent();
        return retval;
    }
    if (component == "SPRITE") {
        SpriteComponent* retval = new SpriteComponent();
        retval->sprite          = m_tags[pos++].getNum();
        retval->fgColor.Red()   = m_tags[pos++].getDec();
        retval->fgColor.Green() = m_tags[pos++].getDec();
        retval->fgColor.Blue()  = m_tags[pos++].getDec();
        retval->bgColor.Red()   = m_tags[pos++].getDec();
        retval->bgColor.Green() = m_tags[pos++].getDec();
        retval->bgColor.Blue()  = m_tags[pos++].getDec();
        retval->renderLayer		= m_tags[pos++].getDec();
        return retval;
    }
    if (component == "STAIR") {
        StairComponent* retval = new StairComponent();
        retval->direction = static_cast<STAIR>(m_tags[pos++].getNum());
        retval->target = m_tags[pos++].getNum();
        return retval;
    }
    if (component == "WEARABLE") {
        WearableComponent* retval = new WearableComponent();
        retval->baseDamageAbsorb    = m_tags[pos++].getNum();
        retval->position            = static_cast<WearablePosition>(m_tags[pos++].getNum());
        retval->warmth              = m_tags[pos++].getNum();

        return retval;
    }
    if (component == "WIELDABLE") {
        WieldableComponent* retval = new WieldableComponent();
        retval->baseDamage  = m_tags[pos++].getNum();
        retval->baseDefence = m_tags[pos++].getNum();
        retval->position    = static_cast<WieldablePosition>(m_tags[pos++].getNum());
        return retval;
    }

    std::cout << "Could not load a component: " << component << std::endl;
    return nullptr;
}
