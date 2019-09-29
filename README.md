This is a CPP component based audio library designed to be reusable and have minimal dependencies.

A project using this library can be found at: http://audio.arturjaakman.com
and its GUI github repo: https://github.com/ajaakman/react-audio-app

UML class diagram can be found in 'other' folder.
compile.sh file provides the emscripten compile command to compile the library to WebAssembly.

vs2019 folder contains a Visual Studio 2019 solution. AudioLib.vcxproj is the static audio library. Example.vsxproj is an example project showing how to use the audio library.

src/API.cpp file contains implementation for the libraries public API functions.

main.cpp file in the src/example folder contains an example demo.

The project uses the SDL2 audio library for writing to the audio buffer. The implementation can be found in the SDL2Audio Class. Any other audio API or Library, such as PortAudio, can be used for this task. The implementation needs to inherit from the IAudio interface.

The Component Abstract Base Class provides an interface for all audio components.
Currently implemented Audio Components:

1. MasterMixer (Only one instance of this class must exist and is managed by the class that inherits from the IAudio interface)
2. Oscillator
3. LPFilter

The scripts folder contains a 'generate_component.py' Python script to generate some boilerplate code for making a new audio component class.
