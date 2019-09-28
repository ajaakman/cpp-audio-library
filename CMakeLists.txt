cmake_minimum_required(VERSION 3.15.3)

project("AudioProj")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_library(AudioLib STATIC
src/API.h
src/API.cpp
src/Utilities.h
src/Utilities.cpp
src/Audio/IAudio.h
src/Audio/SDL2Audio.h
src/Audio/SDL2Audio.cpp
src/Components/Component.h
src/Components/Component.cpp
src/Components/FilterLP.h
src/Components/FilterLP.cpp
src/Components/MasterMixer.h
src/Components/MasterMixer.cpp
src/Components/Oscillator.h
src/Components/Oscillator.cpp
)

set(AudioApp Example)

add_executable(${AudioApp} 
src/Example/Main.cpp 
src/Example/TestLoop.h
src/Example/TestLoopMacros.h
)

target_link_libraries( ${AudioApp} AudioLib )
target_link_libraries( AudioLib ${SDL2_LIBRARIES})