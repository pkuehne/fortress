cmake_minimum_required (VERSION 3.13)
project (Fortress)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(fortress src/main.cpp)
add_library(fortresslib "")
target_link_libraries(fortress fortresslib)

# Add external dependenies from FetchContent
include(FetchContent)
message(STATUS "Downloading dependencies")

FetchContent_Declare(flecs
    GIT_REPOSITORY https://github.com/SanderMertens/flecs
    GIT_TAG master
)
FetchContent_Declare(spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog/
    GIT_TAG v1.x
)
FetchContent_Declare(yaml-cpp
    GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
    GIT_TAG yaml-cpp-0.7.0
)
FetchContent_Declare(lua
    GIT_REPOSITORY https://github.com/walterschell/Lua.git
    GIT_TAG v5.4.5
)
FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        main
)

message(STATUS "Configuring dependencies")
set(YAML_CPP_BUILD_TESTS OFF CACHE BOOL "Enable testing" FORCE)
set(YAML_CPP_BUILD_TOOLS OFF CACHE BOOL "Enable parse tools" FORCE)
set(YAML_CPP_BUILD_CONTRIB OFF CACHE BOOL "Enable contrib stuff in library" FORCE)
set(YAML_CPP_INSTALL OFF CACHE BOOL "Enable generation of install target" FORCE)

FetchContent_MakeAvailable(flecs spdlog yaml-cpp lua googletest)

# Add SDL2 depndencies
INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

# Add include paths
include_directories(fortresslib ${SDL2_INCLUDE_DIRS})
include_directories(fortresslib ${SDL2IMAGE_INCLUDE_DIRS})

# Ensure they are added to compiler and linker paths
target_link_libraries(fortresslib flecs::flecs_static)
target_link_libraries(fortresslib lua_static)
target_link_libraries(fortresslib spdlog::spdlog)
target_link_libraries(fortresslib yaml-cpp::yaml-cpp)
target_link_libraries(fortresslib ${SDL2_LIBRARIES})
target_link_libraries(fortresslib ${SDL2IMAGE_LIBRARIES})

# Add Compiler definitions
add_compile_definitions(FORTRESS_VERSION_MAJOR=0)
add_compile_definitions(FORTRESS_VERSION_MINOR=5)
add_compile_definitions(FORTRESS_VERSION_PATCH=0)
add_compile_definitions(FORTRESS_VERSION_BUILD="dev-build")

# Include source files
add_subdirectory(src/core)
add_subdirectory(src/algos)
add_subdirectory(src/components)
add_subdirectory(src/generators)
add_subdirectory(src/windows)
add_subdirectory(src/widgets)
add_subdirectory(src/systems)
add_subdirectory(src/world)

# Compiler options
target_compile_options(fortress PRIVATE -Wall -Wpedantic -Werror)

# Additional libraries
target_link_libraries(fortress dl)
target_link_libraries(fortress stdc++fs)
target_link_libraries(fortress c)
target_link_libraries(fortress m)
target_link_libraries(fortress pthread)

# Add Testing target
enable_testing()
add_subdirectory(test/unit_tests)

# Add 'run' command
add_custom_target(run
    COMMAND ./fortress
    DEPENDS fortress
)

# add_custom_target(lint ALL
#     COMMAND cpplint --recursive ../src
# )

# add_custom_target(check ALL
#     COMMAND cppcheck ../src/ --enable=information,warning --error-exitcode=1 -DMAJOR=1 --inline-suppr
# )
