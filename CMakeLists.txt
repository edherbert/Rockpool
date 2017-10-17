cmake_minimum_required(VERSION 2.8.9)
project (rockpool)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -D_FILE_OFFSET_BITS=64 -D__WXGTK__ -pthread")

set(OGRE_MAIN_LIB "OgreMain" CACHE FILEPATH "")
set(OGRE_TERRAIN_LIB "OgreTerrain" CACHE FILEPATH "")
set(OGRE_MAIN_INCLUDE "/usr/local/include/OGRE" CACHE FILEPATH "")
set(OGRE_TERRAIN_INCLUDE "/usr/local/include/OGRE/Terrain" CACHE FILEPATH "")

option(TERRAIN_ENABLED "" ON)

if(${TERRAIN_ENABLED})
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DTERRAIN_ENABLED=true")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DTERRAIN_ENABLED=false")
endif()

include_directories(${OGRE_MAIN_INCLUDE})
include_directories(${OGRE_TERRAIN_INCLUDE})

find_package(wxWidgets COMPONENTS core base gl aui)
find_package(Boost COMPONENTS system thread)

file(GLOB_RECURSE INCLUDE_FILES src/*.h)
file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(rockpool ${SRC_FILES} ${INCLUDE_FILES})

include_directories(${wxWidgets_INCLUDE_DIRS})

target_link_libraries(rockpool ${wxWidgets_LIBRARIES} ${OGRE_MAIN_LIB} ${OGRE_TERRAIN_LIB} boost_system boost_thread )
