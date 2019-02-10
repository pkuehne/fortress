target_include_directories(fortresslib PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_sources (fortresslib
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/camera.cpp
    ${CMAKE_CURRENT_LIST_DIR}/frame.cpp
    ${CMAKE_CURRENT_LIST_DIR}/icon.cpp
    ${CMAKE_CURRENT_LIST_DIR}/label.cpp
    ${CMAKE_CURRENT_LIST_DIR}/listbox.cpp
    ${CMAKE_CURRENT_LIST_DIR}/numeric_entry.cpp
    ${CMAKE_CURRENT_LIST_DIR}/progress_bar.cpp
    ${CMAKE_CURRENT_LIST_DIR}/tab.cpp
    ${CMAKE_CURRENT_LIST_DIR}/text_block.cpp
    ${CMAKE_CURRENT_LIST_DIR}/text_entry.cpp
    ${CMAKE_CURRENT_LIST_DIR}/widget.cpp
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/camera.h
    ${CMAKE_CURRENT_LIST_DIR}/frame.h
    ${CMAKE_CURRENT_LIST_DIR}/icon.h
    ${CMAKE_CURRENT_LIST_DIR}/label.h
    ${CMAKE_CURRENT_LIST_DIR}/listbox.h
    ${CMAKE_CURRENT_LIST_DIR}/numeric_entry.h
    ${CMAKE_CURRENT_LIST_DIR}/progress_bar.h
    ${CMAKE_CURRENT_LIST_DIR}/tab.h
    ${CMAKE_CURRENT_LIST_DIR}/text_block.h
    ${CMAKE_CURRENT_LIST_DIR}/text_entry.h
    ${CMAKE_CURRENT_LIST_DIR}/widget.h
    )