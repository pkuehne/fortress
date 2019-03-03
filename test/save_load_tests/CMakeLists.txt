add_executable(save_load_test "")
target_link_libraries(save_load_test fortresslib)

target_include_directories(save_load_test PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_sources (save_load_test 
    PRIVATE
    component_tests.cpp
    )

target_link_libraries(save_load_test soil)
target_link_libraries(save_load_test glog::glog)
target_link_libraries(save_load_test yaml-cpp)
target_link_libraries(save_load_test glfw)
target_link_libraries(save_load_test gtest_main gmock)

# target_link_libraries(save_load_test gmock gtest)
target_link_libraries(save_load_test -llua5.3 -lm -ldl)
target_link_libraries(save_load_test stdc++fs)
target_link_libraries(save_load_test GL)
target_link_libraries(save_load_test c)
target_link_libraries(save_load_test m)
target_link_libraries(save_load_test pthread)
    
add_test(fortress_save_load_test save_load_test)