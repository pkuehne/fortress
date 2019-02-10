target_include_directories(fortresslib PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_sources (fortresslib
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/algorithm.cpp
    ${CMAKE_CURRENT_LIST_DIR}/fov_algorithm.cpp
    ${CMAKE_CURRENT_LIST_DIR}/los_algorithm.cpp
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/algorithm.h
    ${CMAKE_CURRENT_LIST_DIR}/fov_algorithm.h
    ${CMAKE_CURRENT_LIST_DIR}/los_algorithm.h
    )