target_include_directories(fortresslib PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_sources (fortresslib
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/collider_component.h
    ${CMAKE_CURRENT_LIST_DIR}/component_base.h
    ${CMAKE_CURRENT_LIST_DIR}/connector_component.h
    ${CMAKE_CURRENT_LIST_DIR}/consumable_component.h
    ${CMAKE_CURRENT_LIST_DIR}/description_component.h
    ${CMAKE_CURRENT_LIST_DIR}/dialog_component.h
    ${CMAKE_CURRENT_LIST_DIR}/droppable_component.h
    ${CMAKE_CURRENT_LIST_DIR}/equipment_component.h
    ${CMAKE_CURRENT_LIST_DIR}/experience_component.h
    ${CMAKE_CURRENT_LIST_DIR}/combat_component.h
    ${CMAKE_CURRENT_LIST_DIR}/graphics_effect_component.h
    ${CMAKE_CURRENT_LIST_DIR}/grouping_component.h
    ${CMAKE_CURRENT_LIST_DIR}/health_component.h
    ${CMAKE_CURRENT_LIST_DIR}/key_component.h
    ${CMAKE_CURRENT_LIST_DIR}/logmessage_component.h
    ${CMAKE_CURRENT_LIST_DIR}/npc_component.h
    ${CMAKE_CURRENT_LIST_DIR}/openable_component.h
    ${CMAKE_CURRENT_LIST_DIR}/player_component.h
    ${CMAKE_CURRENT_LIST_DIR}/sprite_component.h
    ${CMAKE_CURRENT_LIST_DIR}/wearable_component.h
    ${CMAKE_CURRENT_LIST_DIR}/wieldable_component.h
    )