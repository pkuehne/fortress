target_include_directories(fortresslib PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_sources (fortresslib
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/dungeon_generator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/room.cpp
    ${CMAKE_CURRENT_LIST_DIR}/rural_generator.cpp
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/generator_interface.h
    ${CMAKE_CURRENT_LIST_DIR}/dungeon_generator.h
    ${CMAKE_CURRENT_LIST_DIR}/room.h
    ${CMAKE_CURRENT_LIST_DIR}/rural_generator.h
    )