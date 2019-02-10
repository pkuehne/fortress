target_include_directories(fortresslib PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_sources (fortresslib
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/grouping_manager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/grouping.cpp
    ${CMAKE_CURRENT_LIST_DIR}/world_info.cpp
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/grouping_manager.h
    ${CMAKE_CURRENT_LIST_DIR}/grouping.h
    ${CMAKE_CURRENT_LIST_DIR}/world_info.h
    )