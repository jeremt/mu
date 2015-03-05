cmake_minimum_required(VERSION 2.8.4)
project(mu)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")
set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Web;Android;IOS" CACHE STRING "" FORCE)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

if(CMAKE_BUILD_TYPE MATCHES "Debug" OR CMAKE_BUILD_TYPE MATCHES "Release")
    find_package(SDL2 REQUIRED)
    find_package(OpenGL REQUIRED)
endif()

include("${CMAKE_SOURCE_DIR}/cmake/config.cmake")
include("${CMAKE_SOURCE_DIR}/cmake/platform/ios.cmake")

include_directories(${MU_INCLUDE_DIR})
if (CMAKE_BUILD_TYPE MATCHES "Web")
    set(CMAKE_CXX_COMPILER ${CMAKE_SOURCE_DIR}/../Dude/emsdk_portable/emscripten/incoming/em++)
    add_executable(${PROJECT_NAME}
        ${MU_SOURCE_FILES} ${MU_INCLUDE_FILES}
        ${MU_GAME_FILES}
        ${CMAKE_SOURCE_DIR}/platform/web/main.cpp
    )
    set_target_properties(${PROJECT_NAME} PROPERTIES
        COMPILE_FLAGS "${COMPILE_FLAGS} -Wno-warn-absolute-paths -s USE_SDL=2 -s ASM_JS=1"
        LINK_FLAGS "${LINK_FLAGS} --bind -s USE_SDL=2 -s FULL_ES2=1"
        RUNTIME_OUTPUT_DIRECTORY ${MU_OUTPUT_DIRECTORY}
        SUFFIX ".js"
    )
elseif(CMAKE_BUILD_TYPE MATCHES "Debug" OR CMAKE_BUILD_TYPE MATCHES "Release")
    add_executable(${PROJECT_NAME}
        ${MU_SOURCE_FILES} ${MU_INCLUDE_FILES}
        ${MU_GAME_FILES}
        ${CMAKE_SOURCE_DIR}/platform/desktop/main.cpp
    )
    target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARY} ${SDL2_LIBRARY})
elseif(CMAKE_BUILD_TYPE MATCHES "IOS")
    set(SOURCE_FILES ${MU_SOURCE_FILES} ${MU_GAME_FILES})
    add_framework(${PROJECT_NAME}
        ${CMAKE_SOURCE_DIR}/platform/ios/Template/Template/Frameworks
        "${MU_INCLUDE_FILES}" "${SOURCE_FILES}"
    )
endif()
