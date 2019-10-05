cmake_minimum_required(VERSION 3.15.3)

project("AudioProj")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_library(AudioLib STATIC
src/API.h
src/API.cpp
src/Globals.h
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

if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
    target_link_libraries( AudioLib ${CMAKE_CURRENT_LIST_DIR}/deps/SDL2-2.0.10/lib/x64/SDL2.lib)
    target_link_libraries( AudioLib ${CMAKE_CURRENT_LIST_DIR}/deps/SDL2-2.0.10/lib/x64/SDL2main.lib)
else ()
    target_link_libraries( AudioLib ${CMAKE_CURRENT_LIST_DIR}/deps/SDL2-2.0.10/lib/x86/SDL2.lib)
    target_link_libraries( AudioLib ${CMAKE_CURRENT_LIST_DIR}/deps/SDL2-2.0.10/lib/x86/SDL2main.lib)
endif ()
target_compile_features(AudioLib PRIVATE cxx_std_17)
target_compile_features(Example PRIVATE cxx_std_17)

include_directories(deps/SDL2-2.0.10/include)

target_link_libraries( ${AudioApp} AudioLib )