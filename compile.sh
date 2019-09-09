emcc -std=c++11 \
"cpp-audio/API.cpp" \
"cpp-audio/Oscillator.cpp" \
"cpp-audio/FilterLP.cpp" \
"cpp-audio/MasterMixer.cpp" \
"cpp-audio/SDL2Audio.cpp" \
"cpp-audio/Component.cpp" \
"cpp-audio/Utilities.cpp" \
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