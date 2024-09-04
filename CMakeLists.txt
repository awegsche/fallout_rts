# CMakeList.txt : CMake project for omcmeas, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)


project("fallout_rts" VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
find_package(Threads REQUIRED)
find_package(ZLIB REQUIRED)

include(FetchContent)

find_package(raylib QUIET)
if (NOT raylib_FOUND)
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.0
        )
    FetchContent_MakeAvailable(raylib)
endif()

find_package(raygui QUIET)
if (NOT raygui_FOUND)
    message("---- RAYGUI ------------------")
    FetchContent_Declare(
        raygui
        GIT_REPOSITORY https://github.com/raysan5/raygui.git
        GIT_TAG 4.0
        )
    FetchContent_MakeAvailable(raygui)
endif()

add_executable(fallout_rts
    "src/rlights.cpp"
    "src/game.cpp"
    "src/main.cpp"

    #ui
    "src/ui/ui.cpp"

    #world
    "src/world/terrain.cpp"
    "src/world/chunk.cpp"
    "src/world/world.cpp"

    # buildings
    #"src/world/buildings/building_manager.cpp"
    "src/world/buildings/gatherer.cpp"
    )

target_include_directories(fallout_rts PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${raygui_INCLUDE_DIR}
    ${FETCHCONTENT_BASE_DIR}/raygui-src/src
    )

target_link_libraries(fallout_rts
    raylib
    )

add_custom_command(TARGET fallout_rts POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/assets/"
        "$<TARGET_FILE_DIR:fallout_rts>/assets")

add_custom_command(TARGET fallout_rts POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/shaders/"
        "$<TARGET_FILE_DIR:fallout_rts>/shaders")
