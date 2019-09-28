emcc -std=c++11 \
"src/Utilities.cpp" \
"src/API.cpp" \
"src/Components/FilterLP.cpp" \
"src/Components/MasterMixer.cpp" \
"src/Components/Oscillator.cpp" \
"src/Components/Component.cpp" \
"src/Audio/SDL2Audio.cpp" \
-s USE_SDL=2 -s \
EXPORTED_FUNCTIONS='["_InitAudio", 
"_MasterComp", 
"_MasterGetAmp", 
"_MasterSetAmp", 
"_CompAddOsc", 
"_CompAddLP", 
"_CompDelete", 
"_CompSetOut", 
"_CompGetOut", 
"_OscSetFreq", 
"_OscGetFreq", 
"_OscSetAmp", 
"_OscGetAmp", 
"_OscSetPhase", 
"_OscGetPhase", 
"_OscSetWave", 
"_OscGetWave", 
"_LPGetCutoff", 
"_LPSetCutoff"]' \
-s EXTRA_EXPORTED_RUNTIME_METHODS='["cwrap"]' \
-s WASM=1 \
-o "../react-audio/public/audio.js" \
-s ENVIRONMENT=web \
-Oz \
-s ASSERTIONS=1